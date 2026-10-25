#ifndef PLATFORM_HUDANCHOR_H
#define PLATFORM_HUDANCHOR_H

/* The HUD's anchor table (docs/renderer-spec.md 5.3 step 2, 5.3.1): port data, not game code.
 * Each gameplay HUD part sends its drawing environment and then its sprites from the shared
 * staging buffer D_00351E10 (src/hud, gspkt.nostrict_nofill.c func_00237018), so a send is
 * keyed by the environment sent before it (tools/host/gsstate.py --extents keys it the same way).
 * Under a wide view a part keeps its side of the screen: a left one moves by the view's left
 * margin (-82.8 canvas pixels at 960 x 544), a right one by the right margin, a centred one
 * stays.  Markers over 3D (lock-on, damage numbers, labels, actor marks) send through their own
 * environments, which are not in the table: they come out of the wide projection already in
 * place and must not move.  Not part of the PS2 build. */
#ifndef KH1_PS2
typedef struct {
    const void *env; /* the part's drawing environment (the send's start) */
    s32 side;        /* -1 left, 0 centre (stays), 1 right */
    const char *name;
} KH1HudAnchor;

extern const KH1HudAnchor kh1_hud_anchors[];
extern const s32 kh1_hud_nanchors;
/* session 93: the markers' environments (not moved; tools/host/hudcheck.py checks that every
 * environment src/hud sends is an anchor or a marker) */
typedef struct {
    const void *env;
    const char *name;
} KH1HudMarker;
extern const KH1HudMarker kh1_hud_markers[];
extern const s32 kh1_hud_nmarkers;
/* the staging buffer the parts' sprites are sent from, and its size in bytes */
extern const void *const kh1_hud_staging;
extern const u32 kh1_hud_staging_size;
#endif

#endif
