/* xs_dumbo.x func_00f21ca8: matched by hand. */
#include "ovl.h"

void func_00f21ca8(OvlVec *v, s32 n) {
    s32 i;

    for (i = 0; i < n; i++)
        if (v[i][1] > 10.0f)
            break;
    if (i != n)
        for (i = 0; i < n; i++)
            v[i][1] -= 10.0f;
    for (i = 0; i < n; i++)
        if (v[i][1] < -10.0f)
            break;
    if (i != n)
        for (i = 0; i < n; i++)
            v[i][1] += 10.0f;
    for (i = 0; i < n; i++)
        if (v[i][0] > 10.0f)
            break;
    if (i != n)
        for (i = 0; i < n; i++)
            v[i][0] -= 10.0f;
    for (i = 0; i < n; i++)
        if (v[i][0] < -10.0f)
            break;
    if (i != n)
        for (i = 0; i < n; i++)
            v[i][0] += 10.0f;
}
