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

/* the six bits of VU1's CLIPW of a register against its own w (vu_clipw()'s) */
static __inline__ u32 nat_clipbits(uint32x4_t u) {
    static const u32 wp[4] = { 1, 4, 16, 0 }, wn[4] = { 2, 8, 32, 0 };
    uint32x4_t lim = vdupq_n_u32(0x7F7FFFFFu), ex = vdupq_n_u32(0x7F800000u);
    uint32x4_t m = vandq_u32(vminq_u32(vandq_u32(u, vdupq_n_u32(0x7FFFFFFFu)), lim), vtstq_u32(u, ex));
    uint32x4_t gt = vcgtq_u32(m, vu_lane(m, 3)), neg = vreinterpretq_u32_s32(vshrq_n_s32(vreinterpretq_s32_u32(u), 31));
    uint32x4_t b = vorrq_u32(vandq_u32(vbicq_u32(gt, neg), VU_LD(wp)), vandq_u32(vandq_u32(gt, neg), VU_LD(wn)));
    uint32x2_t h = vadd_u32(vget_low_u32(b), vget_high_u32(b));
    h = vpadd_u32(h, h);
    return vget_lane_u32(h, 0);
}
/* FCOR: every bit outside x set */
static __inline__ u16 nat_fcor(u32 fc, u32 x) { return (u16)(((fc | x) & 0xFFFFFF) == 0xFFFFFF); }

/* P0, from 00c (and 04e, its branch there): the map renderer, a strip of vertices at TOP (a header qword, the
 * vertex count in x; each vertex the position (w its flags), the colour as integers, ST in 20.12).  The
 * program is software-pipelined: each pass transforms one vertex into view space (vf13-16) and the one
 * before it into clip space (vf01-04), projects the one before that, and tests the triangle of the last three
 * view-space vertices: CLIPW of each against its w, the vertex's flags ANDed with the MAC flags of the cross
 * product's z times the flags word as a float (the strip's winding), the ADC set (XYZF2's w to vi12) for a
 * back face or a vertex flagged 0 or a triangle wholly outside one plane.  Written here pass for pass in the
 * translation's order.  A triangle that crosses a plane goes to the program's clipper (05e on), which this does
 * not do: there it gives up, before the kick, and the translation runs the whole run again from the start (its
 * writes so far are the translation's own, to the same places: the output is after the input, so nothing it
 * reads was changed) */
static int nat_0(u32 pc) {
    u32 np, m = 0, q, fc = 0, clip0 = clip_last, wI, it = 0, b22, b23, b24;
    u16 i1, i2, i3, i4, i5, i6, i7, i10, i11, i12, i13 = vi[13];
    uint32x4_t v5 = VU_LD(vf[5]), v6 = VU_LD(vf[6]), v7 = VU_LD(vf[7]), v8 = VU_LD(vf[8]), v9 = VU_LD(vf[9]);
    uint32x4_t v12, v20, v21 = VU_LD(vf[21]), v22, v23, v24, v25 = VU_LD(vf[25]), v26 = VU_LD(vf[26]);
    uint32x4_t v27 = VU_LD(vf[27]), v28, v29, a, xyz = VU_LD(vu_lanes[0xe]), xy = VU_LD(vu_lanes[0xc]);
    float32x4_t W[4], P[4], c31 = vfin(VU_LD(vf[31])), pf;
    if (pc == 0x4e) np = 2;
    else if (pc == 0xc) np = 0;
    else return 0;
    {
        int k;
        for (k = 0; k < 4; k++) {
            W[k] = vfin(VU_LD(vf[13 + k]));
            P[k] = vfin(VU_LD(vf[1 + k]));
        }
        { Fu f; f.u = vf[0][3]; wI = fo(f.f * fin(i_reg)); } /* muli.w vf28, vf00, I */
    }
    /* 00c-026: the first vertex into view and clip space, the GIF tag */
    i1 = (u16)top;
    i3 = (u16)(i1 + 1);
    v20 = vbslq_u32(xyz, VU_LD(mem[i3 & (DATA_QW - 1)]), VU_LD(vf[0]));
    i11 = 0x7FFF;
    i10 = (u16)mem[i1 & (DATA_QW - 1)][0];
    i4 = i5 = i6 = 0xFFFE;
    pf = vfin(v20);
    a = vfo(vmulq_f32(W[0], vdupq_lane_f32(vget_low_f32(pf), 0)));
    a = vfo(vaddq_f32(nat_f(a), vmulq_f32(W[1], vdupq_lane_f32(vget_low_f32(pf), 1))));
    a = vfo(vaddq_f32(nat_f(a), vmulq_f32(W[2], vdupq_lane_f32(vget_high_f32(pf), 0))));
    i10 = (u16)(i10 & i11);
    v12 = vfo(vaddq_f32(nat_f(a), vmulq_f32(W[3], vdupq_lane_f32(vget_high_f32(pf), 1))));
    v29 = VU_LD(mem[i1 & (DATA_QW - 1)]);
    i2 = (u16)(i3 + i10);
    v22 = v23 = v24 = VU_LD(vf[0]);
    b22 = b23 = b24 = nat_clipbits(v22);
    pf = nat_f(v12);
    a = vfo(vmulq_f32(P[0], vdupq_lane_f32(vget_low_f32(pf), 0)));
    a = vfo(vaddq_f32(nat_f(a), vmulq_f32(P[1], vdupq_lane_f32(vget_low_f32(pf), 1))));
    a = vfo(vaddq_f32(nat_f(a), vmulq_f32(P[2], vdupq_lane_f32(vget_high_f32(pf), 0))));
    v28 = vfo(vaddq_f32(nat_f(a), vmulq_f32(P[3], vdupq_lane_f32(vget_high_f32(pf), 1))));
    i2 = (u16)(i2 + i10 + i10 + i10);
    v29 = vsetq_lane_u32(mem[48][2], v29, 2);
    VU_ST(mem[i2 & (DATA_QW - 1)], v29);
    v29 = vextq_u32(v29, v29, 2); /* mr32 twice */
    mem[48][1] = vgetq_lane_u32(v29, 1);
    i7 = (u16)(i2 + 2);
    i12 = (u16)(i11 + 0xFF1);
    q = nat_rcp(vgetq_lane_u32(v28, 3));
    np += 27;
    for (;;) {
        float32x4_t qq = nat_f(vdupq_n_u32(q));
        int cull;
        it++;
        /* 027-02f */
        v23 = v24;
        v24 = v12;
        b23 = b24;
        b24 = nat_clipbits(v24);
        v28 = vfo(vmulq_f32(vfin(v28), qq));
        v29 = VU_LD(mem[(i3 + 1) & (DATA_QW - 1)]);
        /* 02a-02c: CLIPW of the three (each vertex's bits worked out once, as it arrives) */
        clip_last = fc = (clip_last << 18 | b22 << 12 | b23 << 6 | b24) & 0xFFFFFF;
        v9 = vbslq_u32(xy, VU_LD(mem[(i3 + 2) & (DATA_QW - 1)]), v9);
        v5 = v6;
        v6 = v7;
        v28 = vsetq_lane_u32(wI, v28, 3);
        v8 = VU_LD(mem[i3 & (DATA_QW - 1)]);
        v29 = nat_u(vcvtq_f32_s32(vreinterpretq_s32_u32(v29)));
        v7 = v28;
        v9 = vbslq_u32(xy, nat_u(vmulq_n_f32(vcvtq_f32_s32(vreinterpretq_s32_u32(v9)), 1.0f / 4096.0f)), v9);
        v20 = vbslq_u32(xyz, VU_LD(mem[(i3 + 3) & (DATA_QW - 1)]), v20);
        /* 030-038 */
        v25 = vfo(vsubq_f32(vfin(v6), vfin(v5)));
        i3 = (u16)(i3 + 3);
        v27 = vreinterpretq_u32_s32(vcvtq_s32_f32(vmulq_n_f32(vfin(v28), 16.0f)));
        i7 = (u16)(i7 + 3);
        v29 = vfo(vmulq_f32(vfin(v29), c31));
        v21 = vfo(vsubq_f32(vfin(v7), vfin(v5)));
        pf = vfin(v20);
        a = vfo(vmulq_f32(W[0], vdupq_lane_f32(vget_low_f32(pf), 0)));
        VU_ST(mem[(i7 - 2) & (DATA_QW - 1)], v27);
        a = vfo(vaddq_f32(nat_f(a), vmulq_f32(W[1], vdupq_lane_f32(vget_low_f32(pf), 1))));
        a = vfo(vaddq_f32(nat_f(a), vmulq_f32(W[2], vdupq_lane_f32(vget_high_f32(pf), 0))));
        i1 = (u16)((fc & 0x3F) != 0);
        v9 = vsetq_lane_u32(0x3F800000u, v9, 2); /* addw.z vf09, vf00, vf00w */
        v12 = vfo(vaddq_f32(nat_f(a), vmulq_f32(W[3], vdupq_lane_f32(vget_high_f32(pf), 1))));
        i4 = i5;
        /* 039 / 03a: the cross product of the triangle's edges (no flags) */
        {
            float32x4_t x1 = vfin(nat_yzx(v21)), x2 = vfin(nat_zxy(v21)), y1 = vfin(nat_yzx(v25)), y2 = vfin(nat_zxy(v25));
            float32x4_t p2 = vmulq_f32(y1, x2);
            uint32x4_t abs7 = vdupq_n_u32(0x7FFFFFFFu), z = vdupq_n_u32(0), bad;
            uint32x2_t any;
            a = vbslq_u32(xyz, vfo(vmulq_f32(x1, y2)), a);
            bad = vandq_u32(vceqq_u32(vandq_u32(nat_u(p2), abs7), z),
                            vandq_u32(vtstq_u32(nat_u(y1), abs7), vtstq_u32(nat_u(x2), abs7)));
            bad = vandq_u32(bad, xyz);
            any = vorr_u32(vget_low_u32(bad), vget_high_u32(bad));
            if (vget_lane_u32(vpmax_u32(any, any), 0)) { /* a 0 product of two non-0 factors: vu_ek()'s scalar form */
                u32 c[4], s21[4], s25[4];
                VU_ST(c, a);
                VU_ST(s21, v21);
                VU_ST(s25, v25);
                v21 = vsetq_lane_u32(fo(fin(c[0]) - fin(s25[1]) * fin(s21[2])), v21, 0);
                v21 = vsetq_lane_u32(fo(fin(c[1]) - fin(s25[2]) * fin(s21[0])), v21, 1);
                v21 = vsetq_lane_u32(fo(fin(c[2]) - fin(s25[0]) * fin(s21[1])), v21, 2);
            } else
                v21 = vbslq_u32(xyz, vfo(vsubq_f32(vfin(a), p2)), v21);
        }
        i5 = i6;
        i6 = i1;
        /* 03b-040 */
        v26 = vbslq_u32(xyz, vfo(vmulq_f32(vfin(v9), qq)), v26);
        i13 = (u16)vgetq_lane_u32(v8, 3);
        v29 = vreinterpretq_u32_s32(vcvtq_s32_f32(vfin(v29)));
        i4 = (u16)(i4 + i5);
        pf = nat_f(v12);
        a = vfo(vmulq_f32(P[0], vdupq_lane_f32(vget_low_f32(pf), 0)));
        i4 = (u16)(i4 + i6);
        a = vfo(vaddq_f32(nat_f(a), vmulq_f32(P[1], vdupq_lane_f32(vget_low_f32(pf), 1))));
        i10 = (u16)(i10 - 1);
        a = vfo(vaddq_f32(nat_f(a), vmulq_f32(P[2], vdupq_lane_f32(vget_high_f32(pf), 0))));
        VU_ST(mem[(i7 - 4) & (DATA_QW - 1)], v26);
        v28 = vfo(vaddq_f32(nat_f(a), vmulq_f32(P[3], vdupq_lane_f32(vget_high_f32(pf), 1))));
        VU_ST(mem[(i7 - 3) & (DATA_QW - 1)], v29);
        /* 041: z times the flags word as a float, with its MAC flag */
        m = 0;
        v21 = vsetq_lane_u32(fout(fin(vgetq_lane_u32(v21, 2)) * fin(vgetq_lane_u32(v8, 3)), 2, &m), v21, 2);
        /* 042-048 */
        i1 = (u16)((fc & 0x20820) != 0);
        q = nat_rcp(vgetq_lane_u32(v28, 3));
        np += 30;
        if (!i13) {
            cull = 1;
        } else {
            int out = (s16)i4 > 0;
            i13 = (u16)(i13 & m);
            np += 2;
            if (out) { /* 050-05d: a vertex off the screen: culled when all three are outside one plane */
                np += 2;
                if (i1) {
                    i1 = nat_fcor(fc, 0xfdf7df);
                    np += 3;
                    cull = i1;
                } else {
                    static const u32 pl[4] = { 0xffbefb, 0xffdf7d, 0xffefbe, 0xfdf7df };
                    int k;
                    np += 2;
                    i1 = nat_fcor(fc, 0xff7df7);
                    cull = i13 != 0;
                    for (k = 0; !cull && k < 4; k++) {
                        cull = i1 != 0;
                        i1 = nat_fcor(fc, pl[k]);
                        np += 2;
                    }
                    if (!cull) {
                        cull = i1 != 0;
                        np += 2;
                    }
                }
                if (!cull) { /* the clipper: the translation does this run */
                    clip_last = clip0;
                    return 0;
                }
            } else {
                np += 2;
                cull = i13 != 0;
            }
        }
        if (cull) { /* 110 / 111: the ADC */
            mem[(i7 - 2) & (DATA_QW - 1)][3] = i12;
            np += 2;
        }
        /* 049 / 04a */
        np += 2;
        v22 = v23;
        b22 = b23;
        if (!i10) break;
    }
    /* 04b-04d: the kick */
    np += 3;
    vi[1] = i1; vi[2] = i2; vi[3] = i3; vi[4] = i4; vi[5] = i5; vi[6] = i6; vi[7] = i7; vi[10] = i10;
    vi[11] = i11; vi[12] = i12; vi[13] = i13;
    VU_ST(vf[5], v5); VU_ST(vf[6], v6); VU_ST(vf[7], v7); VU_ST(vf[8], v8); VU_ST(vf[9], v9); VU_ST(vf[12], v12);
    VU_ST(vf[20], v20); VU_ST(vf[21], v21); VU_ST(vf[22], v22); VU_ST(vf[23], v23); VU_ST(vf[24], v24);
    VU_ST(vf[25], v25); VU_ST(vf[26], v26); VU_ST(vf[27], v27); VU_ST(vf[28], v28); VU_ST(vf[29], v29);
    VU_ST(acc, a);
    mac_now = m;
    clip_now = fc;
    q_reg = q;
    st.insns += np;
    st.cycles += np + 15 + 3 * it; /* the stalls: 01f / 021 / 022, 026, 02e */
    kick(i2);
    tpc = 0x4e & (MICRO_N - 1);
    return 1;
}
#endif

/* the program numbers (tools/vu/find_vu1.py's) that have one.  A native run answers 0 for an entry or a case it
 * does not do, and the translation runs it from the start: it has changed nothing the translation reads (P0's
 * writes so far are the translation's own, to the same places) */
static int (*nat_run(int num))(u32) {
    if (!kh1_vu1_native) return 0;
#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
    if (num == 0) return nat_0;
    if (num == 13) return nat_13;
    if (num == 18) return nat_18;
#endif
    return 0;
}
