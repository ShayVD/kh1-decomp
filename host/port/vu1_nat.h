/* session 150: VU1 programs written by hand as C (vu1_nat.h: included by vu1.c, after the FMAC helpers).  Each one
 * does what the program does, step for step in the same arithmetic as the translated C (vu1_tr.c): every
 * FMAC the same NEON operation with the same fin() / fout() clamps, Q through qop(), the MAC flag through
 * vu_ek() with the scalar form where it answers 0.  So the registers, VU memory and the kicks come out
 * bit for bit the translation's (KH1_HOST_VU1TR=2 / vu1tr=2 compares them with the interpreter, as it does
 * the translation).  What it saves is the translation's: the VU's registers kept in NEON registers across a
 * vertex instead of stored and reloaded for every instruction, the per-instruction counting, and the
 * branches the VU needed to pick a matrix that C picks once.
 *
 * kh1_vu1_native: 1 (the default) runs these where there is one; 0 the translation */
int kh1_vu1_native = 1;

#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
/* (y, z, x, -) and (z, x, y, -): the cross product's operands (the w lane is outside every dest here) */
static __inline__ uint32x4_t nat_yzx(uint32x4_t v) {
    uint32x2_t lo = vget_low_u32(v), hi = vget_high_u32(v);
    return vcombine_u32(vext_u32(lo, hi, 1), lo);
}
static __inline__ uint32x4_t nat_zxy(uint32x4_t v) {
    uint32x2_t lo = vget_low_u32(v), hi = vget_high_u32(v);
    return vcombine_u32(vzip_u32(hi, lo).val[0], vrev64_u32(lo));
}
static __inline__ float32x4_t nat_f(uint32x4_t v) { return vreinterpretq_f32_u32(v); }
static __inline__ uint32x4_t nat_u(float32x4_t v) { return vreinterpretq_u32_f32(v); }

/* P18, from 007: the 3D renderer's record stream at TOP (op 0 a matrix into one of three slots, op 1 a GIF
 * tag and that many vertices of (normal, slot), position, STQ; anything else the end).  Each vertex: the
 * slot's matrix times the position, Q = 1 / w, xyz and STQ times Q, the screen edge from the last vertex,
 * its cross product with the one before for the ADC bit (the sign of z, the parity alternating the
 * operands), XYZ to 12.4.  Out at TOP + 0x1E0: tag, then STQ, RGBA (vf01), XYZF2 per vertex; the end the
 * EOP word, the kick, back to 007 */
static int nat_18(u32 pc) {
    u32 np = 3, nv = 0, m = 0, q = 0;
    uint32x4_t v26, v27, v28 = VU_LD(vf[28]), v29 = VU_LD(vf[29]);
    uint32x4_t v30 = VU_LD(vf[30]), v31 = VU_LD(vf[31]), a = VU_LD(acc), rgba = VU_LD(vf[1]);
    uint32x4_t xyz = VU_LD(vu_lanes[0xe]), xy = VU_LD(vu_lanes[0xc]), lx, ly;
    float32x4_t c0 = vdupq_n_f32(0), c1 = c0, c2 = c0, c3 = c0;
    u16 i1, i2, i3, i4, i5, i7 = 0, s = 0xFFFF;
    if (pc != 7) return 0;
    /* every value the loop makes is fout()'s (finite, no denormal), which fin() leaves as it is: only what
     * comes from VU memory and the registers the run starts with go through fin() */
    v26 = nat_u(vfin(VU_LD(vf[26])));
    v27 = nat_u(vfin(VU_LD(vf[27])));
    lx = ly = v26;
    i2 = (u16)top;
    i3 = (u16)(i2 + 0x1E0);
    vi[11] = i3;
    for (;;) {
        const u32 *h = mem[i2 & (DATA_QW - 1)];
        u16 op = (u16)h[0];
        i4 = (u16)h[2];
        i5 = (u16)h[3];
        i1 = (u16)(op - 1);
        np += 5;
        if (!op) { /* a matrix into slot z (0, 1, else 2): vf05-08, vf12-15, vf19-22 */
            int r = i4 == 0 ? 5 : i4 == 1 ? 12 : 19;
            np += i4 == 0 ? 8 : 11;
            i4 = (u16)(i4 - 1);
            i2 = (u16)(i2 + 8);
            memcpy(vf[r], mem[(i2 - 7) & (DATA_QW - 1)], 16);
            memcpy(vf[r + 1], mem[(i2 - 6) & (DATA_QW - 1)], 16);
            memcpy(vf[r + 2], mem[(i2 - 5) & (DATA_QW - 1)], 16);
            memcpy(vf[r + 3], mem[(i2 - 4) & (DATA_QW - 1)], 16);
            if (s == (u16)r) s = 0xFFFF;
            continue;
        }
        i2 = (u16)(i2 + 1);
        v31 = VU_LD(mem[i2 & (DATA_QW - 1)]);
        i2 = (u16)(i2 + 1);
        np += 3;
        if (op != 1) { /* the end: the EOP word, the kick */
            if (nv) { /* the last vertex's MSUB in full: its MAC flag and vf30's xyz (each vertex needed only z's sign) */
                u32 u[4], c[4], mm = 0;
                VU_ST(c, a);
                if (!vu_ek(u, K_MSUB, nat_f(nat_yzx(ly)), nat_f(nat_zxy(lx)), c, 0xe, &mm)) {
                    u32 xs[4], ys[4];
                    VU_ST(xs, lx);
                    VU_ST(ys, ly);
                    mm = 0;
                    u[0] = fout(fin(c[0]) - fin(ys[1]) * fin(xs[2]), 0, &mm);
                    u[1] = fout(fin(c[1]) - fin(ys[2]) * fin(xs[0]), 1, &mm);
                    u[2] = fout(fin(c[2]) - fin(ys[0]) * fin(xs[1]), 2, &mm);
                }
                v30 = vbslq_u32(xyz, VU_LD(u), v30);
                vi[7] = i7;
                mac_now = mm;
                q_reg = q;
                i_reg = 0x45000000u;
                VU_ST(vf[26], v26);
                VU_ST(vf[27], v27);
            }
            vi[1] = i1; vi[2] = i2; vi[3] = i3; vi[4] = i4; vi[5] = i5;
            VU_ST(vf[28], v28); VU_ST(vf[29], v29);
            VU_ST(vf[30], v30); VU_ST(vf[31], v31); VU_ST(acc, a);
            mem[i3 & (DATA_QW - 1)][0] = vi[13];
            np += 10;
            st.insns += np;
            st.cycles += np + nv * 7;
            kick(vi[11]);
            tpc = 7 & (MICRO_N - 1);
            return 1;
        }
        /* a GIF tag and z vertices (at least one: z counts down to 0 after the first) */
        i7 = (u16)mem[i2 & (DATA_QW - 1)][3];
        VU_ST(mem[i3 & (DATA_QW - 1)], v31);
        i3 = (u16)(i3 + 1);
        np += 5;
        v31 = vfo(vsubq_f32(vfin(v31), vfin(v31))); /* 047, each vertex: vf31 - vf31 */
        for (;;) {
            uint32x4_t n = VU_LD(mem[i2 & (DATA_QW - 1)]), p = VU_LD(mem[(i2 + 1) & (DATA_QW - 1)]);
            uint32x4_t t = VU_LD(mem[(i2 + 2) & (DATA_QW - 1)]), x, y;
            uint32x4_t mul;
            float32x4_t pf, qq, pr, r;
            u32 w, rz, pz;
            int sl = i7 == 0 ? 5 : i7 == 1 ? 12 : 19;
            i2 = (u16)(i2 + 3);
            np += sl == 5 ? 6 : 9;
            i7 = (u16)(i7 - 1);
            if (s != (u16)sl) {
                s = (u16)sl;
                c0 = vfin(VU_LD(vf[sl]));
                c1 = vfin(VU_LD(vf[sl + 1]));
                c2 = vfin(VU_LD(vf[sl + 2]));
                c3 = vfin(VU_LD(vf[sl + 3]));
            }
            /* 039-03c (or the slot's): ACC = M.x * p.x + M.y * p.y + M.z * p.z, vf28 = ACC + M.w * p.w */
            pf = vfin(p);
            VU_ST(mem[(i3 + 1) & (DATA_QW - 1)], rgba);
            a = vfo(vmulq_f32(c0, vdupq_lane_f32(vget_low_f32(pf), 0)));
            a = vfo(vaddq_f32(nat_f(a), vmulq_f32(c1, vdupq_lane_f32(vget_low_f32(pf), 1))));
            a = vfo(vaddq_f32(nat_f(a), vmulq_f32(c2, vdupq_lane_f32(vget_high_f32(pf), 0))));
            v28 = vfo(vaddq_f32(nat_f(a), vmulq_f32(c3, vdupq_lane_f32(vget_high_f32(pf), 1))));
            /* 048-04a: Q = 1 / w, qop()'s (vf00.w is 1; w is fout()'s, fin() leaves it) */
            w = vgetq_lane_u32(v28, 3);
            if (w & 0x7FFFFFFF) {
                Fu f;
                f.u = w;
                f.f = 1.0f / f.f;
                q = fo(f.f);
            } else
                q = 0x7F7FFFFF | (w & 0x80000000);
            i1 = (u16)(i5 & vi[14]);
            i5 = (u16)(i5 + 1);
            /* 04c / 04d: xyzw, STQ times Q */
            qq = nat_f(vdupq_n_u32(q));
            v28 = vfo(vmulq_f32(nat_f(v28), qq));
            v30 = vfo(vmulq_f32(vfin(t), qq));
            /* 050 / 051: the edge from the last vertex, z 0 (vf28 - vf28 of a finite vf28) */
            v29 = vbslq_u32(xy, vfo(vsubq_f32(nat_f(v28), nat_f(v27))), vbslq_u32(xyz, vdupq_n_u32(0), n));
            VU_ST(mem[i3 & (DATA_QW - 1)], v30);
            /* 052-055: the cross product of this edge and the last, the operands by parity.  ACC's xyz from the
             * MUL; of the MSUB only z's sign (the ADC), as vu_ek() makes it where z is not a flushed 0 or a 0
             * product (the run's last vertex is done in full at the end) */
            if (i1) { x = v26; y = v29; } else { x = v29; y = v26; }
            mul = vfo(vmulq_f32(nat_f(nat_yzx(x)), nat_f(nat_zxy(y))));
            a = vbslq_u32(xyz, mul, a);
            pr = vmulq_f32(nat_f(nat_yzx(y)), nat_f(nat_zxy(x)));
            r = vsubq_f32(nat_f(mul), pr);
            rz = vgetq_lane_u32(nat_u(r), 2);
            pz = vgetq_lane_u32(nat_u(pr), 2);
            if (!(rz << 1) || !(pz << 1)) { /* z 0: the MAC flag as vu_ek() / the scalar form make it */
                u32 u[4], c[4], mm = 0;
                VU_ST(c, a);
                if (!vu_ek(u, K_MSUB, nat_f(nat_yzx(y)), nat_f(nat_zxy(x)), c, 0xe, &mm)) {
                    u32 xs[4], ys[4];
                    VU_ST(xs, x);
                    VU_ST(ys, y);
                    mm = 0;
                    fout(fin(c[2]) - fin(ys[0]) * fin(xs[1]), 2, &mm);
                }
                m = mm;
            } else
                m = rz >> 31 << 5;
            lx = x;
            ly = y;
            v27 = v28;
            /* 056: XYZ to 12.4 */
            v26 = v29;
            v28 = vbslq_u32(xyz, vreinterpretq_u32_s32(vcvtq_s32_f32(vmulq_n_f32(nat_f(v28), 16.0f))), v28);
            i4 = (u16)(i4 - 1);
            i1 = (u16)((m & 0x20 ? vi[13] : 0) | vi[12]);
            np += 7 + 6 + 2 + (m & 0x20 ? 12 : 11);
            nv++;
            {
                u32 *o = mem[(i3 + 2) & (DATA_QW - 1)];
                vst1q_lane_u32(o, v28, 0);
                vst1q_lane_u32(o + 1, v28, 1);
                vst1q_lane_u32(o + 2, v28, 2);
            }
            i3 = (u16)(i3 + 3);
            i7 = (u16)mem[i2 & (DATA_QW - 1)][3];
            mem[(i3 - 1) & (DATA_QW - 1)][3] = i1;
            if (!i4) break;
            np += 4;
        }
    }
}

/* the cross product's z sign for the ADC (P13 / P18): ACC's xyz from the OPMULA, of the OPMSUB only z's sign, as
 * vu_ek() makes it where z is not a flushed 0 or a 0 product (the run's last vertex is done in full at the end,
 * nat_cross_last) */
static __inline__ u32 nat_cross_z(uint32x4_t x, uint32x4_t y, uint32x4_t xyz, uint32x4_t *a) {
    uint32x4_t mul = vfo(vmulq_f32(nat_f(nat_yzx(x)), nat_f(nat_zxy(y))));
    float32x4_t pr = vmulq_f32(nat_f(nat_yzx(y)), nat_f(nat_zxy(x))), r;
    u32 rz, pz;
    *a = vbslq_u32(xyz, mul, *a);
    r = vsubq_f32(nat_f(mul), pr);
    rz = vgetq_lane_u32(nat_u(r), 2);
    pz = vgetq_lane_u32(nat_u(pr), 2);
    if (!(rz << 1) || !(pz << 1)) { /* z 0: the MAC flag as vu_ek() / the scalar form make it */
        u32 u[4], c[4], mm = 0;
        VU_ST(c, *a);
        if (!vu_ek(u, K_MSUB, nat_f(nat_yzx(y)), nat_f(nat_zxy(x)), c, 0xe, &mm)) {
            u32 xs[4], ys[4];
            VU_ST(xs, x);
            VU_ST(ys, y);
            mm = 0;
            fout(fin(c[2]) - fin(ys[0]) * fin(xs[1]), 2, &mm);
        }
        return mm;
    }
    return rz >> 31 << 5;
}
/* the last vertex's OPMSUB in full: its MAC flag, and its xyz into *v */
static __inline__ u32 nat_cross_last(uint32x4_t x, uint32x4_t y, uint32x4_t a, uint32x4_t xyz, uint32x4_t *v) {
    u32 u[4], c[4], mm = 0;
    VU_ST(c, a);
    if (!vu_ek(u, K_MSUB, nat_f(nat_yzx(y)), nat_f(nat_zxy(x)), c, 0xe, &mm)) {
        u32 xs[4], ys[4];
        VU_ST(xs, x);
        VU_ST(ys, y);
        mm = 0;
        u[0] = fout(fin(c[0]) - fin(ys[1]) * fin(xs[2]), 0, &mm);
        u[1] = fout(fin(c[1]) - fin(ys[2]) * fin(xs[0]), 1, &mm);
        u[2] = fout(fin(c[2]) - fin(ys[0]) * fin(xs[1]), 2, &mm);
    }
    *v = vbslq_u32(xyz, VU_LD(u), *v);
    return mm;
}
/* Q = 1 / w as qop(0x38, vf00.w, w) for a w that is fout()'s (fin() leaves it) */
static __inline__ u32 nat_rcp(u32 w) {
    Fu f;
    if (!(w & 0x7FFFFFFF)) return 0x7F7FFFFF | (w & 0x80000000);
    f.u = w;
    f.f = 1.0f / f.f;
    return fo(f.f);
}

/* P13, from 006: the skinned renderer.  Its record stream at TOP: op 0 a matrix (w 0: into slot z, vf05-08 /
 * vf12-15 / vf19-22; w 1: the bone palette is this record; else nothing), op 1 a GIF tag and z vertices, op 2 a
 * stream of bone indices (bytes of the words, x y z w, at the record; z its qwords), anything else the end.  A
 * vertex: (?, ?, ?, n) and n pre-weighted positions, then STQ; each position goes through its index's matrix
 * (0 / 1 the slots, 0x100 + k the palette's k-th, loaded into slot 2) and the products are summed in ACC.  Then as
 * P18 (Q, STQ, the screen edge, the ADC from the cross product's sign), plus a guard band: ADC also when any of
 * the last three vertices has x, y or z / 4096 off by more than 2046 from 2046 (CLIPW against 2046) */
static int nat_13(u32 pc) {
    u32 np = 3, nv = 0, m = 0, q = 0, l9;
    u16 i1 = vi[1], i2, i3, i4 = vi[4], i5 = vi[5], i6 = vi[6], i7 = vi[7], i8 = vi[8], i9 = vi[9], i10 = vi[10], i15 = vi[15];
    uint32x4_t v26, v27, v28 = VU_LD(vf[28]), v29 = VU_LD(vf[29]);
    uint32x4_t v30 = VU_LD(vf[30]), v31 = VU_LD(vf[31]), a = VU_LD(acc), rgba = VU_LD(vf[1]);
    uint32x4_t xyz = VU_LD(vu_lanes[0xe]), xy = VU_LD(vu_lanes[0xc]), lx, ly, zero = vdupq_n_u32(0);
    float32x4_t c[3][4], p0 = vmulq_f32(vfin(VU_LD(vf[0])), vdupq_n_f32(0));
    u32 have = 0; /* the slots whose fin()'d matrix is in c */
    static const u16 slot_r[3] = { 5, 12, 19 };
    if (pc != 6) return 0;
    l9 = i9 & (MICRO_N - 1);
    if (l9 != 0x21 && l9 != 0x25 && l9 != 0x29 && l9 != 0x2d) return 0; /* the translation's JR goes wherever */
    v26 = nat_u(vfin(VU_LD(vf[26])));
    v27 = nat_u(vfin(VU_LD(vf[27])));
    lx = ly = v26;
    i2 = (u16)top;
    i3 = (u16)(i2 + 0x1E0);
    vi[11] = i3;
    for (;;) {
        const u32 *h = mem[i2 & (DATA_QW - 1)];
        i1 = (u16)h[0];
        i4 = (u16)h[2];
        i5 = (u16)h[3];
        i2 = (u16)(i2 + 1);
        i1 = (u16)(i1 - 1);
        v31 = VU_LD(mem[i2 & (DATA_QW - 1)]);
        i2 = (u16)(i2 + 1);
        np += 7;
        if (i1 == 0) goto group;
        np += 6;
        if ((s16)i1 < 0) { /* op 0 */
            int tk = i5 == 0;
            i1 = (u16)(i1 - 1);
            i2 = (u16)(i2 + 6);
            i5 = (u16)(i5 - 1);
            if (tk) { /* a matrix into slot z */
                int r;
                tk = i4 == 0;
                i4 = (u16)(i4 - 1);
                r = tk ? 0 : i4 == 0 ? 1 : 2;
                np += r ? 10 : 7;
                memcpy(vf[slot_r[r]], mem[(i2 - 7) & (DATA_QW - 1)], 16);
                memcpy(vf[slot_r[r] + 1], mem[(i2 - 6) & (DATA_QW - 1)], 16);
                memcpy(vf[slot_r[r] + 2], mem[(i2 - 5) & (DATA_QW - 1)], 16);
                memcpy(vf[slot_r[r] + 3], mem[(i2 - 4) & (DATA_QW - 1)], 16);
                have &= ~(1u << r);
            } else if (np += 3, i5 == 0) {
                i6 = (u16)(i2 - 8); /* the palette */
                np += 2;
            }
            continue;
        }
        i1 = (u16)(i1 - 1);
        i2 = (u16)(i2 - 1);
        mem[i3 & (DATA_QW - 1)][0] = vi[13];
        if (i1 == 0) { /* op 2: the index stream */
            i8 = i2;
            i2 = (u16)(i2 + i4);
            i9 = 0x21;
            np += 4;
            continue;
        }
        /* the end */
        np += 9;
        st.insns += np;
        st.cycles += np + nv * 12;
        if (nv) {
            mac_now = nat_cross_last(lx, ly, a, xyz, &v30);
            clip_now = clip_last;
            q_reg = q;
            i_reg = 0x44ffc000u;
            VU_ST(vf[26], v26);
            VU_ST(vf[27], v27);
        }
        vi[1] = i1; vi[2] = i2; vi[3] = i3; vi[4] = i4; vi[5] = i5; vi[6] = i6; vi[7] = i7; vi[8] = i8;
        vi[9] = i9; vi[10] = i10; vi[15] = i15;
        VU_ST(vf[28], v28); VU_ST(vf[29], v29); VU_ST(vf[30], v30); VU_ST(vf[31], v31); VU_ST(acc, a);
        kick(vi[11]);
        tpc = 6 & (MICRO_N - 1);
        return 1;
    group:
        /* 053: a GIF tag and z vertices */
        i10 = (u16)mem[i2 & (DATA_QW - 1)][3];
        clip_last = 0;
        v29 = VU_LD(mem[i2 & (DATA_QW - 1)]);
        v28 = VU_LD(mem[(i2 + 1) & (DATA_QW - 1)]);
        i2 = (u16)(i2 + 2);
        VU_ST(mem[i3 & (DATA_QW - 1)], v31);
        i3 = (u16)(i3 + 1);
        np += 6;
        v31 = vfo(vsubq_f32(vfin(v31), vfin(v31))); /* 08e, each vertex: vf31 - vf31 */
        for (;;) {
            int bone = 0;
            uint32x4_t v, e;
            float32x4_t pf, qq;
            u32 cl[4], mm;
            /* the bones: 058-08b */
            for (;;) {
                const float32x4_t *mc;
                int r;
                u32 *w = mem[i8 & (DATA_QW - 1)];
                switch ((i9 & (MICRO_N - 1)) >> 2 & 3) { /* 021-030: the next index, x y z w */
                case 0: i7 = (u16)w[0]; i9 = 0x25; break;
                case 1: i7 = (u16)w[1]; i9 = 0x29; break;
                case 2: i7 = (u16)w[2]; i9 = 0x2d; break;
                default: i7 = (u16)w[3]; i8 = (u16)(i8 + 1); i9 = 0x21; break;
                }
                i7 = (u16)(i7 - 0x100);
                if (bone) {
                    v28 = VU_LD(mem[i2 & (DATA_QW - 1)]);
                    i2 = (u16)(i2 + 1);
                }
                i15 = bone ? 0x80 : 0x65;
                if ((s16)i7 >= 0) { /* 04d: the palette's matrix into slot 2 */
                    i7 = (u16)(i7 + i6);
                    memcpy(vf[19], mem[(i7 + 1) & (DATA_QW - 1)], 16);
                    memcpy(vf[20], mem[(i7 + 2) & (DATA_QW - 1)], 16);
                    memcpy(vf[21], mem[(i7 + 3) & (DATA_QW - 1)], 16);
                    memcpy(vf[22], mem[(i7 + 4) & (DATA_QW - 1)], 16);
                    have &= ~4u;
                    r = 2;
                    np += 10;
                } else {
                    i7 = (u16)(i7 + 0x100);
                    r = i7 == 0 ? 0 : i7 == 1 ? 1 : 2;
                    i7 = (u16)(i7 - 1);
                    np += r ? 11 : 8;
                }
                if (!(have >> r & 1)) {
                    have |= 1u << r;
                    c[r][0] = vfin(VU_LD(vf[slot_r[r]]));
                    c[r][1] = vfin(VU_LD(vf[slot_r[r] + 1]));
                    c[r][2] = vfin(VU_LD(vf[slot_r[r] + 2]));
                    c[r][3] = vfin(VU_LD(vf[slot_r[r] + 3]));
                }
                mc = c[r];
                np += 12;
                pf = vfin(v28);
                if (!bone)
                    a = vfo(vmulq_f32(mc[0], vdupq_lane_f32(vget_low_f32(pf), 0)));
                else
                    a = vfo(vaddq_f32(nat_f(a), vmulq_f32(mc[0], vdupq_lane_f32(vget_low_f32(pf), 0))));
                a = vfo(vaddq_f32(nat_f(a), vmulq_f32(mc[1], vdupq_lane_f32(vget_low_f32(pf), 1))));
                a = vfo(vaddq_f32(nat_f(a), vmulq_f32(mc[2], vdupq_lane_f32(vget_high_f32(pf), 0))));
                a = vfo(vaddq_f32(nat_f(a), vmulq_f32(mc[3], vdupq_lane_f32(vget_high_f32(pf), 1))));
                i10 = (u16)(i10 - 1);
                bone = 1;
                if (!i10) break;
            }
            /* 071: vf28 = ACC + vf00 * I (I 0) */
            v28 = vfo(vaddq_f32(nat_f(a), p0));
            /* 08c-095 */
            VU_ST(mem[(i3 + 1) & (DATA_QW - 1)], rgba);
            q = nat_rcp(vgetq_lane_u32(v28, 3));
            v30 = VU_LD(mem[i2 & (DATA_QW - 1)]);
            i2 = (u16)(i2 + 1);
            qq = nat_f(vdupq_n_u32(q));
            v30 = vfo(vmulq_f32(vfin(v30), qq));
            v28 = vfo(vmulq_f32(nat_f(v28), qq));
            VU_ST(mem[i3 & (DATA_QW - 1)], v30);
            /* 096-09a: the guard band test's vector, x y + 0, z through 20.12, w 2046, xyz - 2046 */
            i1 = (u16)(i5 & 1);
            i5 = (u16)(i5 + 1);
            v = vbslq_u32(xy, vfo(vaddq_f32(nat_f(v28), nat_f(v31))), v30);
            {
                int32x4_t zi = vcvtq_s32_f32(vmulq_n_f32(vfin(v28), 1.0f));
                uint32x4_t zf = vreinterpretq_u32_f32(vmulq_n_f32(vcvtq_f32_s32(zi), 1.0f / 4096.0f));
                v = vbslq_u32(VU_LD(vu_lanes[0x2]), zf, v);
            }
            v = vsetq_lane_u32(0x44ffc000u, v, 3);
            v = vbslq_u32(xyz, vfo(vsubq_f32(nat_f(v), vdupq_n_f32(2046.0f))), v);
            /* 09b / 09c: the screen edge, zw 0 */
            e = vfo(vsubq_f32(nat_f(v28), nat_f(v27)));
            v29 = vbslq_u32(xy, e, zero);
            VU_ST(cl, v);
            clip_last = vu_clipw(cl, cl);
            v30 = v;
            /* 09f-0a3 */
            if (i1) { lx = v26; ly = v29; } else { lx = v29; ly = v26; }
            mm = nat_cross_z(lx, ly, xyz, &a);
            v27 = v28;
            v26 = v29;
            /* 0a4-0ab: the ADC, when off the guard band or the cross product's z is negative */
            i7 = 0x20;
            i1 = (u16)(((clip_last & 0x3FFFF) || (mm & 0x20) ? vi[13] : 0) | vi[12]);
            np += 31 + (clip_last & 0x3FFFF ? 1 : mm & 0x20 ? 4 : 3);
            m = mm;
            v28 = vbslq_u32(xyz, vreinterpretq_u32_s32(vcvtq_s32_f32(vmulq_n_f32(nat_f(v28), 16.0f))), v28);
            {
                u32 *o = mem[(i3 + 2) & (DATA_QW - 1)];
                o[3] = i1;
                vst1q_lane_u32(o, v28, 0);
                vst1q_lane_u32(o + 1, v28, 1);
                vst1q_lane_u32(o + 2, v28, 2);
            }
            i4 = (u16)(i4 - 1);
            i3 = (u16)(i3 + 3);
            nv++;
            if (!i4) break;
            np += 4;
            i10 = (u16)mem[i2 & (DATA_QW - 1)][3];
            v29 = VU_LD(mem[i2 & (DATA_QW - 1)]);
            v28 = VU_LD(mem[(i2 + 1) & (DATA_QW - 1)]);
            i2 = (u16)(i2 + 2);
        }
    }
}
#endif

/* the program numbers (tools/vu/find_vu1.py's) that have one; a native run answers 0, having changed nothing, for an
 * entry it does not do (the translation runs it) */
static int (*nat_run(int num))(u32) {
    if (!kh1_vu1_native) return 0;
#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
    if (num == 13) return nat_13;
    if (num == 18) return nat_18;
#endif
    return 0;
}
