/* The HUD's anchor table (include/platform/hudanchor.h, docs/renderer-spec.md 5.3.1): each gameplay
 * HUD part's drawing environment and the side of the screen it keeps under a wide view.  Port data
 * for every platform; the host's null GIF path applies it under KH1_HOST_WIDE (host/null/dmawalk.c,
 * kh1_dma_hud_anchors).  The sides follow 5.3's rule (x0 >= 341 right, x1 <= 171 left, else
 * centre) on 5.3.1's rectangles, read from the ELF's sprite files; the real-disc run's
 * `gsstate.py --extents` is the check.  Not part of the PS2 build (it lives outside src/). */
#include "common.h"
#include "platform/hudanchor.h"

extern u8 D_00651C00[], D_00648790[], D_00648630[], D_00655F80[], D_006694B0[], D_006562C0[];
extern u8 D_00668120[], D_006510A0[], D_0065FB30[], D_00669070[], D_006697C0[];
extern u8 D_00351E10[];
extern u8 D_00650F40[], D_00650DE0[], D_00662560[], D_006627E0[], D_00668E20[], D_00667DF0[];

const KH1HudAnchor kh1_hud_anchors[] = {
    /* gauge.nostrict.c: Sora's HP / MP (right, bottom), the party's (right, top), kind 3, the
     * world map's (grows left past 341 from the right edge) */
    { D_00651C00, 1, "gauges" },
    /* cmdmenu: the top list, its sub lists and the kind 5 frame, x 16 .. 164 */
    { D_00648790, -1, "command menu" },
    { D_00648630, -1, "command menu (lists)" },
    /* notice.c / banner.c: (160, 344) .. (366, 368), straddling 171: centre */
    { D_00655F80, 0, "notice" },
    { D_006694B0, 0, "banner" },
    /* popup: columns from (16, 16), growing right */
    { D_006562C0, -1, "party pop-ups" },
    /* tgtgauge.c: fixed at x 16 (not a marker, 5.3.1), growing right */
    { D_00668120, -1, "target gauge" },
    /* marker.nostrict_nofill.c func_0023cb30: the sign over the target gauge */
    { D_006510A0, -1, "target sign" },
    /* counter.nostrict.c: (25, 238), above the command menu */
    { D_0065FB30, -1, "counter" },
    /* timer.c: the minigame's MgHud x / y (an overlay's) plus (0, 15) .. (243, 78) */
    { D_00669070, -1, "minigame timer" },
    /* oneshot.c: (131, 284) .. (195, 302), next to the command menu (a guess: the rule says centre) */
    { D_006697C0, -1, "one-shot" },
};
const s32 kh1_hud_nanchors = sizeof kh1_hud_anchors / sizeof kh1_hud_anchors[0];
const void *const kh1_hud_staging = D_00351E10;
const u32 kh1_hud_staging_size = 0x9070; /* src/data/data_0035.s's piece */

/* session 93: the markers over 3D, which send their own environments and are not anchored (they come
 * out of the wide projection in place): listed so tools/host/hudcheck.py can tell that every
 * environment src/hud sends is in one list or the other, and a new HUD file cannot be missed */
const KH1HudMarker kh1_hud_markers[] = {
    { D_00650F40, "the target's mark (marker.c, a guess: lock-on)" },
    { D_00650DE0, "markers over actors (marker.nofill.c)" },
    { D_00662560, "actor marks (actmark)" },
    { D_006627E0, "damage numbers (dmgnum)" },
    { D_00668E20, "labels (lblnum)" },
    { D_00667DF0, "party marks (partymark)" },
};
const s32 kh1_hud_nmarkers = sizeof kh1_hud_markers / sizeof kh1_hud_markers[0];
