#ifndef PLATFORM_TEXCACHE_H
#define PLATFORM_TEXCACHE_H

/* A port's decoded-texture cache (docs/renderer-spec.md 4.13 "Session 117" and "Session 118",
 * vita-port-plan 5.1bf): port code, not game code.  A texture is keyed by its layout (TEX0's TBP0, TBW,
 * PSM, TW, TH) and the platform's page stamp (on the host kh1_gsmem_tex_stamp: the newest write to any
 * page the texels lie in).  A stamp hit reads no texel.  On a stamp miss the texels are read and
 * hashed, and an entry of the same layout holding the same bytes is a hit (a re-upload of the same
 * picture: the slot 0x3600, texanim's scroll cycle); only new bytes are kept as a new entry (a
 * "decode": one GPU texture upload).  The entries hold the stored texels, row by row: the index for
 * PSMT4 / PSMT8 / T8H / T4HL / T4HH (the palette is the palette cache's, include/platform/palcache.h,
 * so the CLUT is not in the key) and the stored value otherwise (CT24 / CT16's alpha comes from TEXA
 * when sampled, so TEXA is not in the key either).
 *
 * Session 118 (4.13 "Session 118"): a texture in a render target's pages (on the host
 * kh1_gsmem_tex_target: a draw wrote the bits it reads and no upload has since) is the GPU target's
 * own and is never kept: its stamp does not move with each draw (the model marks a target's pages
 * again only after an upload, a copy or a pixel write), so an entry would go stale.  The caller passes
 * the target and gets 0 back (counted in targets).  Not part of the PS2 build. */
#ifndef KH1_PS2
#define KH1_TEXCACHE_SLOTS  128
#define KH1_TEXCACHE_TEXELS (4u << 20) /* texels kept at most (16 MB); a 1024 x 1024 texture is 1M */

typedef struct {
    u32 lo, hi;  /* the key: TEX0 with TBP0, TBW, PSM, TW (lo) and TH (lo bits 30-31, hi bits 0-1) only */
    u32 stamp;   /* the page stamp the bytes were last seen at */
    u32 hash;    /* FNV-1a of the n texels */
    u32 n;       /* w x h; 0: empty */
    u32 frame;   /* the frame that last drew it */
    u32 use;     /* the use count when last drawn: least recent first */
    u32 *tex;    /* n stored texels, row by row */
    u32 *raw;    /* session 142: the raw words of the pages the texels lie in, when last seen (KH1TexRaw) */
    u32 nraw;
} KH1TexSlot;

/* session 142: the raw words of every page TEX0 (lo, hi)'s texels lie in, at most max, into out: their
 * count, 0 when not known.  The same words give the same texels, so on a stamp miss an entry of the same
 * layout whose pages hold the same words is a hit without reading the texels (Dive to the Heart streams a
 * few textures through one slot every frame, each a stamp miss) */
typedef u32 (*KH1TexRaw)(u32 tex0_lo, u32 tex0_hi, u32 *out, u32 max);
#define KH1_TEXCACHE_RAW (64u * 2048) /* words: 64 pages */

typedef struct {
    KH1TexSlot slot[KH1_TEXCACHE_SLOTS];
    u32 *scratch; /* a stamp miss's texels (1M) */
    u32 frame, use, texels;
    u32 draws;      /* lookups */
    u32 stamp_hits; /* no texel read */
    u32 hash_hits;  /* read and hashed, the bytes held: no decode */
    u32 decodes;    /* new bytes kept (a GPU upload) */
    u32 targets;    /* a render target's texture: the GPU's own, not kept */
    u32 full;       /* not kept: too big, or every slot / the budget in use this frame */
    u32 hashed;     /* texels read to hash */
    u32 decoded;    /* texels kept */
    KH1TexRaw raw;  /* session 142: set by the caller after kh1_texcache_init, or 0 */
    u32 *rawbuf;    /* KH1_TEXCACHE_RAW words */
    u32 raw_hits;   /* of hash_hits: the pages' words held, no texel read */
} KH1TexCache;

/* reads the texture TEX0 (lo, hi) names: its 1 << TW by 1 << TH stored texels, row by row, into out */
typedef void (*KH1TexRead)(u32 tex0_lo, u32 tex0_hi, u32 *out, void *ctx);

/* 0, or -1 when the scratch buffer cannot be had */
int kh1_texcache_init(KH1TexCache *c);
void kh1_texcache_free(KH1TexCache *c);
/* a new frame: entries drawn before it may be dropped */
void kh1_texcache_frame(KH1TexCache *c);
/* the stored texels for a draw of TEX0 (lo, hi) at page stamp `stamp`; `target` nonzero (a render
 * target's texture) returns 0 without reading.  *decoded is 1 when the texels were kept now (upload
 * them).  0 also when the texture is not kept (full): the caller reads the texels itself */
const u32 *kh1_texcache_get(KH1TexCache *c, u32 tex0_lo, u32 tex0_hi, u32 stamp, u32 target, KH1TexRead read,
                            void *ctx, int *decoded);
#endif

#endif
