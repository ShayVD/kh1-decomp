#ifndef PLATFORM_PALCACHE_H
#define PLATFORM_PALCACHE_H

/* A port's palette cache (docs/renderer-spec.md 4.13 "Session 115" and "Session 116", vita-port-plan
 * 5.1bd): port code, not game code.  Every textured sprite loads its CLUT in its own picture (4.9), and
 * the same block holds many palettes in one frame (0x3700 per model record, 0x3A00 per HUD part), so a
 * decoded palette is keyed by the entries the CLD load read, never by (CBP, CSA): at each load the
 * renderer passes the 16 or 256 RGBA8 entries (on the host: kh1_gsmem_clut) and gets a slot whose GPU
 * palette holds them.  A hit costs a hash of the entries and one compare; a miss fills the least
 * recently used slot that no draw of this frame uses (a GPU still reading it), and says so, so the
 * renderer uploads that slot.  Nothing has to be dropped on a room or effect load: changed bytes are a
 * new key, and the room's cross-fade (the one palette that changes between frames without a load) is
 * a miss the frame it changes.  Not part of the PS2 build. */
#ifndef KH1_PS2
#define KH1_PALCACHE_SLOTS 64

typedef struct {
    u32 hash;     /* FNV-1a of the n entries; 0 with n 0: empty */
    u32 n;        /* 16 or 256 */
    u32 frame;    /* the frame that last used it */
    u32 use;      /* the use count when last used: least recent first */
    u32 col[256]; /* RGBA8, R in bits 0-7 */
} KH1PalSlot;

typedef struct {
    KH1PalSlot slot[KH1_PALCACHE_SLOTS];
    u32 frame, use;
    u32 hits, misses, full; /* full: a load with every slot used this frame (returned -1) */
} KH1PalCache;

void kh1_palcache_init(KH1PalCache *c);
/* a new frame: slots used before it may be refilled */
void kh1_palcache_frame(KH1PalCache *c);
/* the slot holding these n (16 or 256) entries; *fill is 1 when the slot was filled now (upload it).
 * -1 when n is neither, or every slot is in use this frame (draw uncached) */
int kh1_palcache_get(KH1PalCache *c, const u32 *col, u32 n, int *fill);
#endif

#endif
