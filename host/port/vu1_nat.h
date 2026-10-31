/* session 150: VU1 programs written by hand as C (vu1_nat.h: included by vu1.c, after the FMAC helpers).  Each one
 * does what the program does, step for step in the same arithmetic as the translated C (vu1_tr.c): every
 * FMAC the same NEON operation with the same fin() / fout() clamps, Q through qop(), the MAC flag through
 * vu_ek() with the scalar form where it answers 0.  So the registers, VU memory and the kicks come out
 * bit for bit the translation's (KH1_HOST_VU1TR=2 / vu1tr=2 compares them with the interpreter, as it does
 * the translation).  What it saves is the translation's: the VU's registers kept in NEON registers across a
 * vertex instead of stored and reloaded for every instruction, the per-instruction counting, and the
 * branches the VU needed to pick a matrix that C picks once.
 *
 * kh1_vu1_native: 1 (the default) runs these where there is one; 0 the translation; 2 each run of one compared with
 * the translation from the same state (vu1.c nat_check) */
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

/* P11, from 007: P18 with a near-plane cull and a guard band.  The same record stream and output; per vertex,
 * after the matrix: w - 1 negative (SUB.w's MAC flag) culls it (CLIP set to 0x3F, the ADC, no STQ or XYZ
 * written); else as P18, plus CLIPW of (x - 2048, y - 2048, 0) against 2048, the ADC also when any of the last
 * three vertices is outside it.  The program is scheduled without stalls, so its cycles are its pairs */
static __inline__ u32 nat_clipbits(uint32x4_t u);
static int nat_11(u32 pc) {
    u32 np = 3, nv = 0, q = 0, mcull = 0, cl = clip_last;
    int lastc = 0, isi = 0;
    uint32x4_t v26, v27, v28 = VU_LD(vf[28]), v29 = VU_LD(vf[29]);
    uint32x4_t v30 = VU_LD(vf[30]), v31 = VU_LD(vf[31]), a = VU_LD(acc), rgba = VU_LD(vf[1]);
    uint32x4_t xyz = VU_LD(vu_lanes[0xe]), xy = VU_LD(vu_lanes[0xc]), lx, ly;
    uint32x4_t g = vsetq_lane_u32(0x45000000u, vdupq_n_u32(0), 3); /* (0, 0, 0, 2048) */
    float32x4_t c0 = vdupq_n_f32(0), c1 = c0, c2 = c0, c3 = c0, k2048 = vdupq_n_f32(2048.0f);
    u16 i1, i2, i3, i4, i5, i7 = 0, s = 0xFFFF;
    if (pc != 7) return 0;
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
            if (nv) {
                if (lastc)
                    mac_now = mcull;
                else /* the last vertex's MSUB in full: its MAC flag and vf30's xyz */
                    mac_now = nat_cross_last(lx, ly, a, xyz, &v30);
                vi[7] = i7;
                clip_now = cl;
                q_reg = q;
                if (isi) { /* a vertex not culled: vf26 / vf27 its edge and position (else the run's own, not fin()'d) */
                    i_reg = 0x45000000u;
                    VU_ST(vf[26], v26);
                    VU_ST(vf[27], v27);
                }
            }
            clip_last = cl;
            vi[1] = i1; vi[2] = i2; vi[3] = i3; vi[4] = i4; vi[5] = i5;
            VU_ST(vf[28], v28); VU_ST(vf[29], v29);
            VU_ST(vf[30], v30); VU_ST(vf[31], v31); VU_ST(acc, a);
            mem[i3 & (DATA_QW - 1)][0] = vi[13];
            np += 10;
            st.insns += np;
            st.cycles += np;
            kick(vi[11]);
            tpc = 7 & (MICRO_N - 1);
            return 1;
        }
        /* 02f-034: a GIF tag and z vertices (at least one), CLIP 0 */
        i7 = (u16)mem[i2 & (DATA_QW - 1)][3];
        cl = 0;
        VU_ST(mem[i3 & (DATA_QW - 1)], v31);
        i3 = (u16)(i3 + 1);
        np += 6;
        v31 = vfo(vsubq_f32(vfin(v31), vfin(v31))); /* 048, each vertex: vf31 - vf31 */
        for (;;) {
            uint32x4_t n = VU_LD(mem[i2 & (DATA_QW - 1)]), p = VU_LD(mem[(i2 + 1) & (DATA_QW - 1)]);
            uint32x4_t t = VU_LD(mem[(i2 + 2) & (DATA_QW - 1)]);
            float32x4_t pf, qq;
            u32 w, m;
            int sl = i7 == 0 ? 5 : i7 == 1 ? 12 : 19;
            i2 = (u16)(i2 + 3);
            np += sl == 5 ? 6 : 9;
            if (s != (u16)sl) {
                s = (u16)sl;
                c0 = vfin(VU_LD(vf[sl]));
                c1 = vfin(VU_LD(vf[sl + 1]));
                c2 = vfin(VU_LD(vf[sl + 2]));
                c3 = vfin(VU_LD(vf[sl + 3]));
            }
            /* 03a-03d (or the slot's): the matrix; RGBA out */
            pf = vfin(p);
            VU_ST(mem[(i3 + 1) & (DATA_QW - 1)], rgba);
            a = vfo(vmulq_f32(c0, vdupq_lane_f32(vget_low_f32(pf), 0)));
            a = vfo(vaddq_f32(nat_f(a), vmulq_f32(c1, vdupq_lane_f32(vget_low_f32(pf), 1))));
            a = vfo(vaddq_f32(nat_f(a), vmulq_f32(c2, vdupq_lane_f32(vget_high_f32(pf), 0))));
            v28 = vfo(vaddq_f32(nat_f(a), vmulq_f32(c3, vdupq_lane_f32(vget_high_f32(pf), 1))));
            /* 049-050: Q = 1 / w; w - 1's MAC flag (vf00.w is 1; w is fout()'s) */
            w = vgetq_lane_u32(v28, 3);
            q = nat_rcp(w);
            m = 0;
            fout(fin(w) - 1.0f, 3, &m);
            i1 = (u16)(i5 & vi[14]);
            i5 = (u16)(i5 + 1);
            np += 11;
            nv++;
            if (m & 0x10) { /* 051-053, 071-076: culled */
                lastc = 1;
                mcull = m;
                cl = 0x3F;
                v29 = n;
                v30 = t;
                i1 = (u16)(vi[13] | vi[12]);
                np += 9;
            } else {
                uint32x4_t v;
                u32 mm;
                lastc = 0;
                isi = 1;
                /* 054-05c: STQ and xyzw times Q, (x, y) - 2048, the edge (z 0, w 2048) */
                qq = nat_f(vdupq_n_u32(q));
                v28 = vfo(vmulq_f32(nat_f(v28), qq));
                v30 = vfo(vmulq_f32(vfin(t), qq));
                VU_ST(mem[i3 & (DATA_QW - 1)], v30);
                v31 = vbslq_u32(xy, vfo(vsubq_f32(nat_f(v28), k2048)), vdupq_n_u32(0));
                v29 = vbslq_u32(xy, vfo(vsubq_f32(nat_f(v28), nat_f(v27))), g);
                /* 060: CLIPW of vf31 against 2048 */
                v = vbslq_u32(xyz, v31, g);
                cl = ((cl << 6) | nat_clipbits(v)) & 0xFFFFFF;
                /* 062-067: the cross product's z sign, operands by parity */
                if (i1) { lx = v26; ly = v29; } else { lx = v29; ly = v26; }
                mm = nat_cross_z(lx, ly, xyz, &a);
                v27 = v28;
                v26 = v29;
                v28 = vbslq_u32(xyz, vreinterpretq_u32_s32(vcvtq_s32_f32(vmulq_n_f32(nat_f(v28), 16.0f))), v28);
                {
                    u32 *o = mem[(i3 + 2) & (DATA_QW - 1)];
                    vst1q_lane_u32(o, v28, 0);
                    vst1q_lane_u32(o + 1, v28, 1);
                    vst1q_lane_u32(o + 2, v28, 2);
                }
                np += 21;
                if (cl & 0x3FFFF) { /* off the guard band */
                    i1 = (u16)(vi[13] | vi[12]);
                    np += 6;
                } else {
                    i1 = (u16)((mm & 0x20 ? vi[13] : 0) | vi[12]);
                    np += 5 + (mm & 0x20 ? 6 : 5);
                }
            }
            i4 = (u16)(i4 - 1);
            i3 = (u16)(i3 + 3);
            i7 = (u16)mem[i2 & (DATA_QW - 1)][3];
            mem[(i3 - 1) & (DATA_QW - 1)][3] = i1;
            if (!i4) break;
            np += 4;
        }
    }
}

/* P12, from 007: P18's record stream and output with the lighting and a guard band.  A matrix record is seven
 * qwords (the slot's matrix, then its three light rows: vf09-11, vf16-18, vf23-25); per vertex the light rows
 * times the normal, max 0, times vf01-03 plus vf04 (w: vf04.w, max 0), min 255, FTOI0 is the RGBA.  Then as
 * P18, plus a CLIPW of (x - 2048, y - 2048, z through 20.12 - 2048) against 2048: the ADC also when any of the
 * last three vertices is off it */
static int nat_12(u32 pc) {
    u32 np = 3, nv = 0, q = 0, cl = clip_last;
    int grp = 0;
    uint32x4_t v26, v27, v28 = VU_LD(vf[28]), v29 = VU_LD(vf[29]);
    uint32x4_t v30 = VU_LD(vf[30]), v31 = VU_LD(vf[31]), a = VU_LD(acc);
    uint32x4_t xyz = VU_LD(vu_lanes[0xe]), xy = VU_LD(vu_lanes[0xc]), lx, ly, zero = vdupq_n_u32(0);
    float32x4_t c0 = vdupq_n_f32(0), c1 = c0, c2 = c0, c3 = c0, l0 = c0, l1 = c0, l2 = c0;
    float32x4_t f1 = vfin(VU_LD(vf[1])), f2 = vfin(VU_LD(vf[2])), f3 = vfin(VU_LD(vf[3])), f4 = vfin(VU_LD(vf[4]));
    float32x4_t k255 = vdupq_n_f32(255.0f), k2048 = vdupq_n_f32(2048.0f), one = vdupq_n_f32(1.0f);
    u32 w4 = vf[4][3];
    u16 i1, i2, i3, i4, i5, i7 = vi[7], i9 = vi[9], i10 = vi[10], i13 = vi[13], s = 0xFFFF;
    if (pc != 7) return 0;
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
        if (!op) { /* a matrix and its light rows into slot z (0, 1, else 2): vf05-11, vf12-18, vf19-25 */
            int r = i4 == 0 ? 5 : i4 == 1 ? 12 : 19, k;
            np += i4 == 0 ? 11 : 14;
            i4 = (u16)(i4 - 1);
            i2 = (u16)(i2 + 8);
            for (k = 0; k < 7; k++) memcpy(vf[r + k], mem[(i2 - 7 + k) & (DATA_QW - 1)], 16);
            if (s == (u16)r) s = 0xFFFF;
            continue;
        }
        i2 = (u16)(i2 + 1);
        v31 = VU_LD(mem[i2 & (DATA_QW - 1)]);
        i2 = (u16)(i2 + 1);
        np += 3;
        if (op != 1) { /* the end: the EOP word, the kick */
            if (grp) {
                mac_now = nat_cross_last(lx, ly, a, xyz, &v30);
                clip_now = cl;
                q_reg = q;
                i_reg = 0x45000000u;
                VU_ST(vf[26], v26);
                VU_ST(vf[27], v27);
            }
            clip_last = cl;
            vi[1] = i1; vi[2] = i2; vi[3] = i3; vi[4] = i4; vi[5] = i5;
            vi[7] = i7; vi[9] = i9; vi[10] = i10; vi[13] = i13;
            if (grp) vi[14] = 1;
            VU_ST(vf[28], v28); VU_ST(vf[29], v29);
            VU_ST(vf[30], v30); VU_ST(vf[31], v31); VU_ST(acc, a);
            mem[i3 & (DATA_QW - 1)][0] = i13;
            np += 10;
            st.insns += np;
            st.cycles += np + nv * 19;
            kick(vi[11]);
            tpc = 7 & (MICRO_N - 1);
            return 1;
        }
        /* 038-03e: a GIF tag and z vertices (at least one), CLIP 0 */
        grp = 1;
        i7 = (u16)mem[i2 & (DATA_QW - 1)][3];
        cl = 0;
        i10 = 0;
        VU_ST(mem[i3 & (DATA_QW - 1)], v31);
        i3 = (u16)(i3 + 1);
        np += 7;
        for (;;) {
            uint32x4_t n = VU_LD(mem[i2 & (DATA_QW - 1)]), p = VU_LD(mem[(i2 + 1) & (DATA_QW - 1)]);
            uint32x4_t t = VU_LD(mem[(i2 + 2) & (DATA_QW - 1)]), v, col;
            float32x4_t pf, nf, qq, cf;
            u32 mm;
            int sl = i7 == 0 ? 5 : i7 == 1 ? 12 : 19;
            i2 = (u16)(i2 + 3);
            np += sl == 5 ? 9 : 12;
            if (s != (u16)sl) {
                s = (u16)sl;
                c0 = vfin(VU_LD(vf[sl]));
                c1 = vfin(VU_LD(vf[sl + 1]));
                c2 = vfin(VU_LD(vf[sl + 2]));
                c3 = vfin(VU_LD(vf[sl + 3]));
                l0 = vfin(VU_LD(vf[sl + 4]));
                l1 = vfin(VU_LD(vf[sl + 5]));
                l2 = vfin(VU_LD(vf[sl + 6]));
            }
            /* 044-04a (or the slot's): the light rows times the normal; w vf04's; the matrix */
            nf = vfin(n);
            a = vfo(vmulq_f32(l0, vdupq_lane_f32(vget_low_f32(nf), 0)));
            a = vfo(vaddq_f32(nat_f(a), vmulq_f32(l1, vdupq_lane_f32(vget_low_f32(nf), 1))));
            v29 = vfo(vaddq_f32(nat_f(a), vmulq_f32(l2, vdupq_lane_f32(vget_high_f32(nf), 0))));
            v29 = vsetq_lane_u32(w4, v29, 3);
            i9 = (u16)(i10 & 3);
            pf = vfin(p);
            a = vfo(vmulq_f32(c0, vdupq_lane_f32(vget_low_f32(pf), 0)));
            a = vfo(vaddq_f32(nat_f(a), vmulq_f32(c1, vdupq_lane_f32(vget_low_f32(pf), 1))));
            a = vfo(vaddq_f32(nat_f(a), vmulq_f32(c2, vdupq_lane_f32(vget_high_f32(pf), 0))));
            v28 = vfo(vaddq_f32(nat_f(a), vmulq_f32(c3, vdupq_lane_f32(vget_high_f32(pf), 1))));
            i13 = 0x8000;
            q = nat_rcp(vgetq_lane_u32(v28, 3));
            /* 05d-064: max 0, the colour matrix plus vf04, min 255, FTOI0 */
            cf = vfin(v29);
            v29 = vfo(nat_f(vflush(vbslq_u32(vcgtq_f32(cf, vdupq_n_f32(0)), nat_u(cf), zero))));
            cf = nat_f(v29);
            col = vfo(vmulq_f32(f1, vdupq_lane_f32(vget_low_f32(cf), 0)));
            col = vfo(vaddq_f32(nat_f(col), vmulq_f32(f2, vdupq_lane_f32(vget_low_f32(cf), 1))));
            col = vfo(vaddq_f32(nat_f(col), vmulq_f32(f3, vdupq_lane_f32(vget_high_f32(cf), 0))));
            a = vbslq_u32(xyz, col, a);
            v29 = vbslq_u32(xyz, vfo(vaddq_f32(nat_f(col), vmulq_f32(f4, one))), v29);
            cf = nat_f(v29);
            v29 = vfo(nat_f(vflush(vbslq_u32(vcltq_f32(cf, k255), v29, nat_u(k255)))));
            v29 = vreinterpretq_u32_s32(vcvtq_s32_f32(nat_f(v29)));
            /* 065-06a: STQ and xyzw times Q, out with the colour */
            qq = nat_f(vdupq_n_u32(q));
            v30 = vfo(vmulq_f32(vfin(t), qq));
            v28 = vfo(vmulq_f32(nat_f(v28), qq));
            i1 = (u16)(i5 & 1);
            i5 = (u16)(i5 + 1);
            VU_ST(mem[i3 & (DATA_QW - 1)], v30);
            VU_ST(mem[(i3 + 1) & (DATA_QW - 1)], v29);
            /* 06a-06f: x y + 0, z through 20.12, xyz - 2048; CLIPW against 2048 */
            v = vbslq_u32(xy, vfo(vaddq_f32(nat_f(v28), vdupq_n_f32(0))), v30);
            {
                int32x4_t zi = vcvtq_s32_f32(vmulq_n_f32(nat_f(v28), 1.0f));
                uint32x4_t zf = vreinterpretq_u32_f32(vmulq_n_f32(vcvtq_f32_s32(zi), 1.0f / 4096.0f));
                v = vbslq_u32(VU_LD(vu_lanes[0x2]), zf, v);
            }
            i10 = (u16)(i10 + 1);
            v = vbslq_u32(xyz, vfo(vsubq_f32(nat_f(v), k2048)), v);
            cl = ((cl << 6) | nat_clipbits(vsetq_lane_u32(0x45000000u, v, 3))) & 0xFFFFFF;
            /* 070-075: the screen edge (zw 0), the cross product with the last one, operands by parity */
            v29 = vbslq_u32(xy, vfo(vsubq_f32(nat_f(v28), nat_f(v27))), zero);
            v30 = vbslq_u32(xyz, v, v30);
            if (i1) { lx = v26; ly = v29; } else { lx = v29; ly = v26; }
            mm = nat_cross_z(lx, ly, xyz, &a);
            v27 = v28;
            v26 = v29;
            /* 076-083: the ADC when off the guard band or the cross product's z is negative; XYZ to 12.4 */
            i7 = 0x20;
            i4 = (u16)(i4 - 1);
            if (cl & 0x3FFFF) {
                i1 = (u16)(i13 | vi[12]);
                np += 23 + 4 + 7 + 4;
            } else {
                i1 = (u16)((mm & 0x20 ? i13 : 0) | vi[12]);
                np += 23 + 4 + (mm & 0x20 ? 10 : 9) + 4;
            }
            v28 = vbslq_u32(xyz, vreinterpretq_u32_s32(vcvtq_s32_f32(vmulq_n_f32(nat_f(v28), 16.0f))), v28);
            {
                u32 *o = mem[(i3 + 2) & (DATA_QW - 1)];
                o[3] = i1;
                vst1q_lane_u32(o, v28, 0);
                vst1q_lane_u32(o + 1, v28, 1);
                vst1q_lane_u32(o + 2, v28, 2);
            }
            i3 = (u16)(i3 + 3);
            nv++;
            if (!i4) break;
            np += 5;
            i7 = (u16)mem[i2 & (DATA_QW - 1)][3];
        }
    }
}

/* P10, from 006: a strip of positions only (XYZ2 at 12.4, the ADC word 0).  Its record stream at TOP: op 0 a matrix
 * into slot z (vf05-08, vf12-15, vf19-22), op 1 a GIF tag and z positions (w picks the slot; the position's own w
 * is not read, the matrix's w row is added once), anything else the end.  Software-pipelined: a pass takes one
 * position through its matrix, divides the one before by its w and writes the one before that.  The program
 * assumes z >= 3; with fewer its count wraps as a u16, as here */
static int nat_10(u32 pc) {
    u32 np = 3, cy = 0, q = 0, ng = 0;
    u16 i1, i2, i3, i4, i7 = vi[7];
    uint32x4_t v25 = VU_LD(vf[25]), v26 = VU_LD(vf[26]), v27 = VU_LD(vf[27]), v28 = VU_LD(vf[28]);
    uint32x4_t v31 = VU_LD(vf[31]), a = VU_LD(acc), xyz = VU_LD(vu_lanes[0xe]);
    float32x4_t c[3][4], one = vdupq_n_f32(1.0f);
    u32 have = 0;
    static const u16 slot_r[3] = { 5, 12, 19 };
    int full = 1;
    if (pc != 6) return 0;
    i2 = (u16)top;
    i3 = (u16)(i2 + 0x200);
    vi[11] = i3;
#define NAT10_XF(v) do { /* the slot i7 picks (i7 counts down as the program's ibeq / iaddi do) */ \
        int r_ = i7 == 0 ? 0 : i7 == 1 ? 1 : 2; \
        const float32x4_t *m_; \
        float32x4_t p_ = vfin(v); \
        np += r_ ? 10 : 7; \
        i7 = (u16)(i7 - 1); \
        if (!(have >> r_ & 1)) { \
            have |= 1u << r_; \
            c[r_][0] = vfin(VU_LD(vf[slot_r[r_]])); \
            c[r_][1] = vfin(VU_LD(vf[slot_r[r_] + 1])); \
            c[r_][2] = vfin(VU_LD(vf[slot_r[r_] + 2])); \
            c[r_][3] = vfin(VU_LD(vf[slot_r[r_] + 3])); \
        } \
        m_ = c[r_]; \
        a = vfo(vmulq_f32(m_[0], vdupq_lane_f32(vget_low_f32(p_), 0))); \
        a = vfo(vaddq_f32(nat_f(a), vmulq_f32(m_[1], vdupq_lane_f32(vget_low_f32(p_), 1)))); \
        a = vfo(vaddq_f32(nat_f(a), vmulq_f32(m_[2], vdupq_lane_f32(vget_high_f32(p_), 0)))); \
        nw_ = vfo(vaddq_f32(nat_f(a), vmulq_f32(m_[3], one))); \
    } while (0)
    for (;;) {
        const u32 *h = mem[i2 & (DATA_QW - 1)];
        u16 op;
        if (full) { /* 009-00c */
            i1 = (u16)h[0];
            i4 = (u16)h[2];
            np += 4;
        }
        full = 1;
        op = i1;
        i1 = (u16)(i1 - 1);
        np += 2;
        if (!op) { /* 01a-02e: a matrix into slot z */
            int r = i4 == 0 ? 0 : i4 == 1 ? 1 : 2;
            np += r ? 11 : 8;
            i4 = (u16)(i4 - 1);
            i2 = (u16)(i2 + 5);
            memcpy(vf[slot_r[r]], mem[(i2 - 4) & (DATA_QW - 1)], 16);
            memcpy(vf[slot_r[r] + 1], mem[(i2 - 3) & (DATA_QW - 1)], 16);
            memcpy(vf[slot_r[r] + 2], mem[(i2 - 2) & (DATA_QW - 1)], 16);
            memcpy(vf[slot_r[r] + 3], mem[(i2 - 1) & (DATA_QW - 1)], 16);
            have &= ~(1u << r);
            continue;
        }
        i2 = (u16)(i2 + 1);
        v31 = VU_LD(mem[i2 & (DATA_QW - 1)]);
        i2 = (u16)(i2 + 1);
        np += 3;
        if (op != 1) { /* the end: the EOP word, the kick */
            vi[1] = i1; vi[2] = i2; vi[3] = i3; vi[4] = i4; vi[7] = i7;
            VU_ST(vf[25], v25); VU_ST(vf[26], v26); VU_ST(vf[27], v27); VU_ST(vf[28], v28);
            VU_ST(vf[31], v31); VU_ST(acc, a);
            if (ng) q_reg = q;
            mem[i3 & (DATA_QW - 1)][0] = vi[13];
            np += 10;
            st.insns += np;
            st.cycles += np + cy;
            kick(vi[11]);
            tpc = 6 & (MICRO_N - 1);
            return 1;
        }
        /* 02f-031: the GIF tag out, the first position */
        ng++;
        i7 = (u16)mem[i2 & (DATA_QW - 1)][3];
        v27 = VU_LD(mem[i2 & (DATA_QW - 1)]);
        i2 = (u16)(i2 + 1);
        VU_ST(mem[i3 & (DATA_QW - 1)], v31);
        i3 = (u16)(i3 + 1);
        np += 3;
        cy += 1;
        { /* 032-042: the first position through its matrix; the second loaded */
            uint32x4_t nw_;
            u16 s7 = i7;
            i7 = (u16)mem[i2 & (DATA_QW - 1)][3];
            {
                u16 t7 = i7;
                i7 = s7;
                NAT10_XF(v27);
                i7 = t7;
            }
            np -= 1; /* 6 / 9 pairs */
            v28 = VU_LD(mem[i2 & (DATA_QW - 1)]);
            i2 = (u16)(i2 + 1);
            v27 = nw_;
        }
        { /* 043-054: the second through its matrix, Q = 1 / the first's w */
            uint32x4_t nw_;
            i4 = (u16)(i4 - 1);
            q = nat_rcp(vgetq_lane_u32(v27, 3));
            v26 = v27;
            NAT10_XF(v28);
            v27 = nw_;
            i7 = (u16)mem[i2 & (DATA_QW - 1)][3];
        }
        /* 055-05b: the third loaded, the first projected */
        v28 = VU_LD(mem[i2 & (DATA_QW - 1)]);
        i2 = (u16)(i2 + 1);
        i4 = (u16)(i4 - 1);
        v26 = vfo(vmulq_f32(nat_f(v26), nat_f(vdupq_n_u32(q))));
        np += 7;
        cy += 1;
        for (;;) { /* 05c-074 */
            uint32x4_t nw_;
            v25 = vbslq_u32(xyz, vreinterpretq_u32_s32(vcvtq_s32_f32(vmulq_n_f32(nat_f(v26), 16.0f))), v25);
            np -= 1; /* 6 / 9 pairs with 05c-05d */
            q = nat_rcp(vgetq_lane_u32(v27, 3));
            v26 = v27;
            NAT10_XF(v28);
            v27 = nw_;
            mem[i3 & (DATA_QW - 1)][3] = 0;
            i3 = (u16)(i3 + 1);
            i7 = (u16)mem[i2 & (DATA_QW - 1)][3];
            v28 = VU_LD(mem[i2 & (DATA_QW - 1)]);
            i2 = (u16)(i2 + 1);
            i4 = (u16)(i4 - 1);
            {
                u32 *o = mem[(i3 - 1) & (DATA_QW - 1)];
                vst1q_lane_u32(o, v25, 0);
                vst1q_lane_u32(o + 1, v25, 1);
                vst1q_lane_u32(o + 2, v25, 2);
            }
            v26 = vfo(vmulq_f32(nat_f(v26), nat_f(vdupq_n_u32(q))));
            np += 8; /* 06d-074 */
            if (!i4) break;
            cy += 2;
        }
        /* 075-089: the last two out, the next header read; on at 00d */
        q = nat_rcp(vgetq_lane_u32(v27, 3));
        v25 = vbslq_u32(xyz, vreinterpretq_u32_s32(vcvtq_s32_f32(vmulq_n_f32(nat_f(v26), 16.0f))), v25);
        mem[i3 & (DATA_QW - 1)][3] = 0;
        i3 = (u16)(i3 + 1);
        v26 = v27;
        i2 = (u16)(i2 - 1);
        {
            u32 *o = mem[(i3 - 1) & (DATA_QW - 1)];
            vst1q_lane_u32(o, v25, 0);
            vst1q_lane_u32(o + 1, v25, 1);
            vst1q_lane_u32(o + 2, v25, 2);
        }
        mem[i3 & (DATA_QW - 1)][3] = 0;
        i3 = (u16)(i3 + 1);
        i1 = (u16)mem[i2 & (DATA_QW - 1)][0];
        i4 = (u16)mem[i2 & (DATA_QW - 1)][2];
        { /* 080: vf26 times Q with its MAC flag (the run's) */
            u32 m = 0, u[4], t[4];
            VU_ST(t, v26);
            if (!vu_opbe(u, K_MUL, t, &q, acc, 0xf, &m)) {
                f32 r0 = fin(t[0]) * fin(q);
                f32 r1 = fin(t[1]) * fin(q);
                f32 r2 = fin(t[2]) * fin(q);
                f32 r3 = fin(t[3]) * fin(q);
                u[0] = fout(r0, 0, &m);
                u[1] = fout(r1, 1, &m);
                u[2] = fout(r2, 2, &m);
                u[3] = fout(r3, 3, &m);
            }
            mac_now = m;
            v26 = VU_LD(u);
        }
        v25 = vbslq_u32(xyz, vreinterpretq_u32_s32(vcvtq_s32_f32(vmulq_n_f32(nat_f(v26), 16.0f))), v25);
        {
            u32 *o = mem[(i3 - 1) & (DATA_QW - 1)];
            vst1q_lane_u32(o, v25, 0);
            vst1q_lane_u32(o + 1, v25, 1);
            vst1q_lane_u32(o + 2, v25, 2);
        }
        np += 21;
        cy += 1;
        full = 0;
    }
#undef NAT10_XF
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

/* P0's clipper (05e-111 and its subroutines), on the VU's own registers (vf[], vi[], acc): a triangle that crosses
 * a plane, cut against five planes in turn (a polygon of up to nine vertices in the buffers at 58 and 80), then
 * transformed, projected and kicked as a fan of its own (at 30).  Few triangles come here, so it is written with
 * the translation's operations (vu_op() and the rest), instruction for instruction in its order.  *np counts the
 * pairs, *cx the stall cycles; it answers the MAC flag of its last FMAC whose flag the program can read */
#define NAT_M(r) (mem[(r) & (DATA_QW - 1)])
/* mulx.w t, s, vf30x, with its MAC flag (123 / 131) */
static u32 nat_mulw30(u32 *t, const u32 *s) {
    u32 m = 0, u[4];
    if (!vu_opbel(u, K_MUL, s, vf[30], 0, acc, 0x1, &m)) {
        f32 r3 = fin(s[3]) * fin(vf[30][0]);
        u[3] = fout(r3, 3, &m);
    }
    vu_put(t, u, 0x1);
    return m;
}
/* add.xyzw t, t, s, with its MAC flag (15a / 175) */
static u32 nat_addf(u32 *t, const u32 *s) {
    u32 m = 0, u[4];
    if (!vu_ope(u, K_ADD, t, s, acc, 0xf, &m)) {
        int k;
        for (k = 0; k < 4; k++) {
            f32 r = fin(t[k]) + fin(s[k]);
            u[k] = fout(r, k, &m);
        }
    }
    vu_put(t, u, 0xf);
    return m;
}
static void nat_mr32(u32 *t) {
    u32 l0 = t[1], l1 = t[2], l2 = t[3], l3 = t[0];
    t[0] = l0; t[1] = l1; t[2] = l2; t[3] = l3;
}
/* 140 / 15b: where the edge from p to o crosses the plane (vi13 the axis: vf25 / vf26 turned until it is x), into
 * vf25-27; 140 (o the vertex in) puts p out first.  p4: P4's copy (125 / 140), whose first SUB leaves vf27.w */
static u32 nat_cross(u32 (*p)[4], u32 (*o)[4], int put, u32 *np, u32 *cx, int p4) {
    u32 u[4];
    for (;;) {
        int z = vi[13] == vi[0];
        vi[13] = (u16)(vi[13] - 1);
        if (z) break;
        nat_mr32(vf[25]);
        nat_mr32(vf[26]);
        *np += 5;
    }
    vu_op(u, K_SUB, vf[26], vf[25], acc, 1, 1, 1);
    vu_put(vf[27], u, p4 ? 0xe : 0xf);
    vu_op(vf[26], K_SUB, o[1], p[1], acc, 1, 1, 1);
    q_reg = qop(0x38, vf[25][0], vf[27][0]);
    vu_op(vf[27], K_SUB, o[2], p[2], acc, 1, 1, 1);
    vu_op(vf[25], K_SUB, o[0], p[0], acc, 1, 1, 1);
    vu_opb(u, K_ADD, vf[0], &q_reg, acc, 1, 1, 1);
    vu_put(vf[29], u, 0x8);
    if (put) {
        int k;
        for (k = 0; k < 3; k++) {
            vu_put(NAT_M(vi[9]), p[k], 0xf);
            vi[9] = (u16)(vi[9] + 1);
        }
    }
    vf[29][0] = absf(vf[29][0]);
    vu_opbl(vf[25], K_MUL, vf[25], vf[29], 0, acc, 1, 1, 1);
    vu_opbl(vf[26], K_MUL, vf[26], vf[29], 0, acc, 1, 1, 1);
    vu_opbl(vf[27], K_MUL, vf[27], vf[29], 0, acc, 1, 1, 1);
    vu_op(vf[25], K_ADD, vf[25], p[0], acc, 1, 1, 1);
    vu_op(vf[26], K_ADD, vf[26], p[1], acc, 1, 1, 1);
    *np += 2 + 22;
    *cx += 7; /* 145 / 160, 14b / 166 (WAITQ), and 136 / 12c after the return */
    return nat_addf(vf[27], p[2]);
}
/* 11a: the edge from the vertex at vi8 - 3 (vf17-19) to the one at vi8 (vf21-23): the first kept, and where it
 * crosses the plane (bit vi5 of the first's CLIPW, vi6 of the second's; vf30.x the side).  p4: P4's copy (0ff) */
static u32 nat_edge(u32 *np, u32 *cx, int p4) {
    u32 m, i;
    vu_op(vf[17], K_ADD, vf[20], vf[21], acc, 1, 1, 1);
    vu_put(vf[21], NAT_M(vi[8]), 0xf);
    vi[8] = (u16)(vi[8] + 1);
    vu_op(vf[18], K_ADD, vf[20], vf[22], acc, 1, 1, 1);
    vu_put(vf[22], NAT_M(vi[8]), 0xf);
    vi[8] = (u16)(vi[8] + 1);
    vu_op(vf[19], K_ADD, vf[20], vf[23], acc, 1, 1, 1);
    vu_put(vf[23], NAT_M(vi[8]), 0xf);
    vi[8] = (u16)(vi[8] + 1);
    vi[13] = (u16)(vi[0] + vi[7]);
    clip_last = vu_clipw(vf[17], vf[17]);
    clip_last = vu_clipw(vf[21], vf[21]);
    {
        u32 u[4];
        vu_opbl(u, K_MUL, vf[17], vf[30], 0, acc, 1, 1, 1);
        vu_put(vf[26], u, 0x1);
    }
    m = nat_mulw30(vf[25], vf[21]);
    vi[1] = (u16)(clip_last & 0xFFF);
    vi[3] = (u16)(vi[1] & vi[5]);
    vi[4] = (u16)(vi[1] & vi[6]);
    *np += 14;
    if (vi[3] != vi[0]) { /* the first outside */
        *np += 2;
        if (vi[4] != vi[0]) { /* both: nothing */
            *np += 2;
            return m;
        }
        vu_opbl(vf[25], K_SUB, vf[21], vf[25], 3, acc, 1, 1, 1);
        vi[1] = p4 ? 0x111 : 0x12c;
        vu_opbl(vf[26], K_SUB, vf[17], vf[26], 3, acc, 1, 1, 1);
        vi[11] = (u16)(vi[11] + 1);
        *np += 2 + 4;
        m = nat_cross(&vf[21], &vf[17], 0, np, cx, p4);
    } else {
        {
            u32 u[4];
            vu_opbl(u, K_MUL, vf[17], vf[30], 0, acc, 1, 1, 1);
            vu_put(vf[25], u, 0x1);
        }
        m = nat_mulw30(vf[26], vf[21]);
        *np += 2;
        if (vi[4] == vi[0]) { /* both inside: the first */
            for (i = 0; i < 3; i++) {
                vu_put(NAT_M(vi[9]), vf[17 + i], 0xf);
                vi[9] = (u16)(vi[9] + 1);
            }
            vi[11] = (u16)(vi[11] + 1);
            *np += 4 + 2;
            return m;
        }
        vu_opbl(vf[25], K_SUB, vf[17], vf[25], 3, acc, 1, 1, 1);
        vi[1] = p4 ? 0x11b : 0x136;
        vu_opbl(vf[26], K_SUB, vf[21], vf[26], 3, acc, 1, 1, 1);
        vi[11] = (u16)(vi[11] + 2);
        *np += 4 + 4;
        m = nat_cross(&vf[17], &vf[21], 1, np, cx, p4);
    }
    for (i = 0; i < 3; i++) {
        vu_put(NAT_M(vi[9]), vf[25 + i], 0xf);
        vi[9] = (u16)(vi[9] + 1);
    }
    return m;
}
/* p4: P4's clipper (054-0f4, its subroutines at 0f7 on): the same planes, with vi15 the link, vf06 / vf07 in
 * the buffer for vf23 / vf24 and only vi3 / vi7 / vi10 kept on the stack (vf23 / vf24 are free in P4), and its own
 * fan (0cd-0ee): no back-face test, each vertex projected and put out as the next is transformed */
static u32 nat_clip(u32 *np, u32 *cx, int p4) {
    /* the five planes: the bits of the two ends, vf30.x, the axis, the buffer to cut from (into the other) */
    static const u16 pl[5][4] = {
        { 0x800, 0x20, 2, 0x58 }, { 0x80, 2, 0, 0x80 }, { 0x40, 1, 0, 0x58 }, { 0x200, 8, 1, 0x80 }, { 0x100, 4, 1, 0x58 },
    };
    static const u32 side[5] = { 0xBF800000u, 0xBF800000u, 0x3F800000u, 0xBF800000u, 0x3F800000u };
    u32 m = 0, u[4], k;
    int p;
    /* 05e-064: vf23 / vf24 and vi2 / vi3 / vi7 / vi10 kept on the stack at vi14 (P4: vi3 / vi7 / vi10) */
    if (!p4) {
        vi[14] = (u16)(vi[14] - 1);
        vu_put(NAT_M(vi[14]), vf[23], 0xf);
        vi[14] = (u16)(vi[14] - 1);
        vu_put(NAT_M(vi[14]), vf[24], 0xf);
    }
    vi[14] = (u16)(vi[14] - 1);
    if (!p4) NAT_M(vi[14])[0] = vi[2];
    NAT_M(vi[14])[1] = vi[3];
    NAT_M(vi[14])[2] = vi[7];
    NAT_M(vi[14])[3] = vi[10];
    /* 065-07f: the triangle into the buffer at 58 (each vertex the view-space position, the colour, ST; the first
     * again after the last), the colours and STs as floats */
    vi[8] = 0x58;
    vi[9] = 0x80;
    vu_put(NAT_M(vi[8] + 0), vf[22], 0xf);
    vu_put(NAT_M(vi[8] + 3), vf[p4 ? 6 : 23], 0xf);
    vu_put(NAT_M(vi[8] + 6), vf[p4 ? 7 : 24], 0xf);
    vu_put(NAT_M(vi[8] + 9), vf[22], 0xf);
    vu_put(vf[22], NAT_M(vi[7] - 9), 0xf);
    vu_put(vf[23], NAT_M(vi[7] - 6), 0xf);
    vu_put(vf[24], NAT_M(vi[7] - 3), 0xf);
    vu_put(vf[25], NAT_M(vi[3] - 7), 0xf);
    vu_itof(u, vf[22], 0);
    vu_put(vf[26], NAT_M(vi[3] - 4), 0xf);
    vu_put(vf[22], u, 0xf);
    vu_itof(u, vf[23], 0);
    vu_put(vf[27], NAT_M(vi[3] - 1), 0xf);
    vu_put(vf[23], u, 0xf);
    vu_itof(u, vf[24], 0);
    vi[5] = 0x800;
    vu_put(vf[24], u, 0xf);
    for (k = 25; k <= 27; k++) {
        vu_itof(u, vf[k], 2);
        vu_put(vf[k], u, 0xc);
    }
    for (k = 25; k <= 27; k++) {
        vu_opbl(u, K_ADD, vf[0], vf[0], 3, acc, 1, 1, 1);
        vu_put(vf[k], u, 0x2);
    }
    vu_opbl(vf[20], K_MUL, vf[20], vf[0], 0, acc, 1, 1, 1);
    vu_put(NAT_M(vi[8] + 2), vf[25], 0xf);
    vu_put(NAT_M(vi[8] + 5), vf[26], 0xf);
    vu_put(NAT_M(vi[8] + 8), vf[27], 0xf);
    vu_put(NAT_M(vi[8] + 11), vf[25], 0xf);
    vu_put(NAT_M(vi[8] + 1), vf[22], 0xf);
    vu_put(NAT_M(vi[8] + 4), vf[23], 0xf);
    vu_put(NAT_M(vi[8] + 7), vf[24], 0xf);
    vu_put(NAT_M(vi[8] + 10), vf[22], 0xf);
    *np += p4 ? 31 : 34;
    *cx += 1; /* 078 (P4 06b) */
    /* 080-0d9: the planes */
    for (p = 0; p < 5; p++) {
        u16 src = pl[p][3], dst = (u16)(src ^ (0x58 ^ 0x80));
        vf[30][0] = side[p];
        vi[6] = pl[p][1];
        vi[7] = pl[p][2];
        vi[8] = src;
        for (k = 21; k <= 23; k++) {
            vu_put(vf[k], NAT_M(vi[8]), 0xf);
            vi[8] = (u16)(vi[8] + 1);
        }
        vi[9] = dst;
        vi[10] = p ? vi[11] : 3;
        vi[11] = 0;
        *np += 9;
        do {
            vi[10] = (u16)(vi[10] - 1);
            m = nat_edge(np, cx, p4);
            *np += 5;
        } while (vi[10] != vi[0]);
        if (p4) vi[15] = (u16)(0x7c + 0x12 * p + 7); /* the link of the plane's bal to 0f7 */
        /* 112: the first vertex out again after the last */
        vi[8] = dst;
        vu_put(vf[21], NAT_M(vi[8] + 0), 0xf);
        vu_put(vf[22], NAT_M(vi[8] + 1), 0xf);
        vu_put(vf[23], NAT_M(vi[8] + 2), 0xf);
        for (k = 21; k <= 23; k++) {
            vu_put(NAT_M(vi[9]), vf[k], 0xf);
            vi[9] = (u16)(vi[9] + 1);
        }
        *np += 2 + 8 + 2;
        if (p < 4) vi[5] = pl[p + 1][0];
        else vi[8] = 0x80;
        if (vi[11] == vi[0]) goto done;
    }
    if (p4) {
        /* 0cd-0da: the polygon's first vertex into clip space, a GIF tag kicked alone, then the fan's */
        vi[3] = (u16)(vi[0] + vi[8]);
        vu_put(vf[20], NAT_M(vi[3]), 0xf);
        vi[10] = (u16)(vi[0] + vi[11]);
        vi[15] = 0x30;
        vi[7] = (u16)(vi[15] + 2);
        vu_opbl(acc, K_MUL, vf[1], vf[20], 0, acc, 1, 1, 1);
        vi[11] = 0x7fff;
        vu_opbl(acc, K_MADD, vf[2], vf[20], 1, acc, 1, 1, 1);
        vi[11] = (u16)(vi[11] + 1);
        vu_opbl(acc, K_MADD, vf[3], vf[20], 2, acc, 1, 1, 1);
        NAT_M(vi[15])[0] = vi[11];
        vu_opbl(vf[26], K_MADD, vf[4], vf[20], 3, acc, 1, 1, 1);
        vi[11] = (u16)(vi[10] + 0x7fff);
        vi[11] = (u16)(vi[11] + 1);
        kick(vi[15]);
        q_reg = qop(0x38, vf[0][3], vf[26][3]);
        NAT_M(vi[15])[0] = vi[11];
        *np += 14;
        *cx += 5; /* 0db (WAITQ) */
        /* 0db-0ed: each vertex projected and put out, the next into clip space */
        for (;;) {
            vu_opb(vf[25], K_MUL, vf[26], &q_reg, acc, 1, 1, 1);
            vu_put(vf[29], NAT_M(vi[3] + 2), 0xf);
            vu_put(vf[20], NAT_M(vi[3] + 3), 0xf);
            vu_put(vf[27], NAT_M(vi[3] + 1), 0xf);
            vi[3] = (u16)(vi[3] + 3);
            vu_opb(u, K_MUL, vf[29], &q_reg, acc, 1, 1, 1);
            vi[10] = (u16)(vi[10] - 1);
            vu_put(vf[29], u, 0xe);
            vu_opbl(acc, K_MUL, vf[1], vf[20], 0, acc, 1, 1, 1);
            vi[7] = (u16)(vi[7] + 3);
            vu_opb(u, K_MUL, vf[0], &i_reg, acc, 1, 1, 1);
            vu_put(vf[25], u, 0x1);
            vu_opbl(acc, K_MADD, vf[2], vf[20], 1, acc, 1, 1, 1);
            vu_opbl(acc, K_MADD, vf[3], vf[20], 2, acc, 1, 1, 1);
            m = 0;
            if (!vu_opbel(u, K_MADD, vf[4], vf[20], 3, acc, 0xf, &m)) {
                for (k = 0; k < 4; k++) u[k] = fout(fin(acc[k]) + fin(vf[4][k]) * fin(vf[20][3]), (int)k, &m);
            }
            vu_put(NAT_M(vi[7] - 4), vf[29], 0xf);
            vu_put(vf[26], u, 0xf);
            vu_ftoi(u, vf[25], 1);
            vu_put(vf[25], u, 0xf);
            vu_ftoi(u, vf[27], 0);
            vu_put(vf[27], u, 0xf);
            q_reg = qop(0x38, vf[0][3], vf[26][3]);
            vu_put(NAT_M(vi[7] - 2), vf[25], 0xf);
            vu_put(NAT_M(vi[7] - 3), vf[27], 0xf);
            *np += 19;
            if (vi[10] == vi[0]) break;
            *cx += 2; /* 0db (WAITQ) again */
        }
        kick(vi[15]);
        *np += 1;
        *cx += 1; /* 0ef's DIV: the one at 0e9 still running */
        goto done;
    }
    /* 0da-0e8: the polygon's first vertex into clip space, a GIF tag kicked alone, then the fan's (vi11 the count) */
    vi[3] = (u16)(vi[0] + vi[8]);
    vu_put(vf[20], NAT_M(vi[3]), 0xf);
    vi[10] = (u16)(vi[0] + vi[11]);
    vi[2] = 0x30;
    vi[7] = (u16)(vi[2] + 2);
    vu_opbl(acc, K_MUL, vf[1], vf[20], 0, acc, 1, 1, 1);
    vi[11] = 0x7fff;
    vu_opbl(acc, K_MADD, vf[2], vf[20], 1, acc, 1, 1, 1);
    vi[11] = (u16)(vi[11] + 1);
    vu_opbl(acc, K_MADD, vf[3], vf[20], 2, acc, 1, 1, 1);
    NAT_M(vi[2])[0] = vi[11];
    vu_opbl(vf[25], K_MADD, vf[4], vf[20], 3, acc, 1, 1, 1);
    vi[4] = 3;
    vi[11] = (u16)(vi[10] + 0x7fff);
    vi[11] = (u16)(vi[11] + 1);
    kick(vi[2]);
    q_reg = qop(0x38, vf[0][3], vf[25][3]);
    NAT_M(vi[2])[0] = vi[11];
    *np += 15;
    *cx += 5; /* 0e8 (WAITQ) */
    /* 0e9-106: each vertex projected and put out, the next into clip space; from the third on the fan's triangle
     * tested (the flags word ANDed with the MAC flag of its cross product's z times the flags word as a float):
     * a back face drops the polygon */
    for (;;) {
        int pos;
        vu_put(vf[9], vf[10], 0xf);
        vu_put(vf[10], vf[11], 0xf);
        vu_opb(vf[25], K_MUL, vf[25], &q_reg, acc, 1, 1, 1);
        vu_put(vf[29], NAT_M(vi[3] + 2), 0xf);
        vu_put(vf[27], NAT_M(vi[3] + 1), 0xf);
        vi[10] = (u16)(vi[10] - 1);
        vu_op(vf[21], K_SUB, vf[10], vf[9], acc, 1, 1, 1);
        vi[3] = (u16)(vi[3] + 3);
        vu_op(vf[26], K_SUB, vf[25], vf[9], acc, 1, 1, 1);
        vu_put(vf[11], vf[25], 0xf);
        vu_opb(u, K_MUL, vf[0], &i_reg, acc, 1, 1, 1);
        vu_put(vf[20], NAT_M(vi[3]), 0xf);
        vu_put(vf[25], u, 0x1);
        vu_ftoi(u, vf[27], 0);
        vi[4] = (u16)(vi[4] - 1);
        vu_put(vf[27], u, 0xf);
        vu_opb(u, K_MUL, vf[29], &q_reg, acc, 1, 1, 1);
        vi[8] = (u16)(vf[8][3]);
        vu_put(vf[29], u, 0xe);
        { /* opmula.xyz ACC, vf26, vf21 */
            u32 sa[4] = { vf[26][1], vf[26][2], vf[26][0], 0 };
            u32 sb[4] = { vf[21][2], vf[21][0], vf[21][1], 0 };
            if (!vu_ope(u, K_MUL, sa, sb, acc, 0xe, 0)) {
                u[0] = fo(fin(vf[26][1]) * fin(vf[21][2]));
                u[1] = fo(fin(vf[26][2]) * fin(vf[21][0]));
                u[2] = fo(fin(vf[26][0]) * fin(vf[21][1]));
            }
            vu_put(acc, u, 0xe);
        }
        vu_ftoi(u, vf[25], 1);
        vu_put(vf[25], u, 0xf);
        { /* opmsub.xyz vf26, vf21, vf26 */
            u32 sa[4] = { vf[21][1], vf[21][2], vf[21][0], 0 };
            u32 sb[4] = { vf[26][2], vf[26][0], vf[26][1], 0 };
            if (!vu_ope(u, K_MSUB, sa, sb, acc, 0xe, 0)) {
                u[0] = fo(fin(acc[0]) - fin(vf[21][1]) * fin(vf[26][2]));
                u[1] = fo(fin(acc[1]) - fin(vf[21][2]) * fin(vf[26][0]));
                u[2] = fo(fin(acc[2]) - fin(vf[21][0]) * fin(vf[26][1]));
            }
            vu_put(NAT_M(vi[7]), vf[27], 0xf);
            vu_put(vf[26], u, 0xe);
        }
        vu_opbl(acc, K_MUL, vf[1], vf[20], 0, acc, 1, 1, 1);
        vu_put(NAT_M(vi[7] - 1), vf[29], 0xf);
        vu_opbl(acc, K_MADD, vf[2], vf[20], 1, acc, 1, 1, 1);
        vi[13] = (u16)(vi[0] + vi[8]);
        vu_opbl(acc, K_MADD, vf[3], vf[20], 2, acc, 1, 1, 1);
        vu_put(NAT_M(vi[7] + 1), vf[25], 0xf);
        vu_opbl(vf[25], K_MADD, vf[4], vf[20], 3, acc, 1, 1, 1);
        vi[7] = (u16)(vi[7] + 3);
        m = 0;
        if (!vu_opbel(u, K_MUL, vf[26], vf[8], 3, acc, 0x2, &m)) {
            f32 r2 = fin(vf[26][2]) * fin(vf[8][3]);
            u[2] = fout(r2, 2, &m);
        }
        vu_put(vf[26], u, 0x2);
        q_reg = qop(0x38, vf[0][3], vf[25][3]);
        pos = (s16)vi[4] > 0;
        vi[13] = (u16)(vi[13] & m);
        *np += 23;
        if (!pos) {
            *np += 2;
            if (vi[13] != vi[0]) { /* a back face */
                *np += 2;
                goto done;
            }
        }
        *np += 2;
        if (vi[10] == vi[0]) {
            kick(vi[2]);
            *np += 1;
            if (pos) *cx += 1; /* 107's DIV: the one at 0fd still running */
            break;
        }
    }
done:
    /* 107-10f: Q again, vi2 / vi3 / vi7 / vi10 and vf24 / vf23 back from the stack, vf20.w 1 (P4 0ef-0f4: vi3 / vi7 /
     * vi10) */
    q_reg = qop(0x38, vf[0][3], vf[28][3]);
    if (p4) {
        vi[3] = (u16)NAT_M(vi[14])[1];
        vi[7] = (u16)NAT_M(vi[14])[2];
        vi[10] = (u16)NAT_M(vi[14])[3];
        vi[14] = (u16)(vi[14] + 1);
        vf[20][3] = vf[0][3];
        *np += 6;
        return m;
    }
    vi[2] = (u16)NAT_M(vi[14])[0];
    vi[3] = (u16)NAT_M(vi[14])[1];
    vi[7] = (u16)NAT_M(vi[14])[2];
    vi[10] = (u16)NAT_M(vi[14])[3];
    vi[14] = (u16)(vi[14] + 1);
    vu_put(vf[24], NAT_M(vi[14]), 0xf);
    vi[14] = (u16)(vi[14] + 1);
    vu_put(vf[23], NAT_M(vi[14]), 0xf);
    vi[14] = (u16)(vi[14] + 1);
    vf[20][3] = vf[0][3];
    *np += 9;
    return m;
}

/* P0, from 00c (and 04e, its branch there): the map renderer, a strip of vertices at TOP (a header qword, the
 * vertex count in x; each vertex the position (w its flags), the colour as integers, ST in 20.12).  The
 * program is software-pipelined: each pass transforms one vertex into view space (vf13-16) and the one
 * before it into clip space (vf01-04), projects the one before that, and tests the triangle of the last three
 * view-space vertices: CLIPW of each against its w, the vertex's flags ANDed with the MAC flags of the cross
 * product's z times the flags word as a float (the strip's winding), the ADC set (XYZF2's w to vi12) for a
 * back face or a vertex flagged 0 or a triangle wholly outside one plane.  Written here pass for pass in the
 * translation's order.  A triangle that crosses a plane goes to the program's clipper (05e on, nat_clip()) */
static int nat_0(u32 pc) {
    u32 np, m = 0, q, fc = 0, wI, it = 0, cx = 0, b22, b23, b24;
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
                if (!cull) { /* the clipper, on the VU's registers; then the ADC on the triangle as for a cull */
                    vi[1] = i1; vi[2] = i2; vi[3] = i3; vi[4] = i4; vi[5] = i5; vi[6] = i6; vi[7] = i7; vi[10] = i10;
                    vi[11] = i11; vi[12] = i12; vi[13] = i13;
                    VU_ST(vf[5], v5); VU_ST(vf[6], v6); VU_ST(vf[7], v7); VU_ST(vf[8], v8); VU_ST(vf[9], v9);
                    VU_ST(vf[12], v12); VU_ST(vf[20], v20); VU_ST(vf[21], v21); VU_ST(vf[22], v22); VU_ST(vf[23], v23);
                    VU_ST(vf[24], v24); VU_ST(vf[25], v25); VU_ST(vf[26], v26); VU_ST(vf[27], v27); VU_ST(vf[28], v28);
                    VU_ST(vf[29], v29); VU_ST(acc, a);
                    m = nat_clip(&np, &cx, 0);
                    fc = clip_last;
                    i1 = vi[1]; i2 = vi[2]; i3 = vi[3]; i4 = vi[4]; i5 = vi[5]; i6 = vi[6]; i7 = vi[7]; i10 = vi[10];
                    i11 = vi[11]; i12 = vi[12]; i13 = vi[13];
                    v5 = VU_LD(vf[5]); v6 = VU_LD(vf[6]); v7 = VU_LD(vf[7]); v8 = VU_LD(vf[8]); v9 = VU_LD(vf[9]);
                    v12 = VU_LD(vf[12]); v20 = VU_LD(vf[20]); v21 = VU_LD(vf[21]); v22 = VU_LD(vf[22]);
                    v23 = VU_LD(vf[23]); v24 = VU_LD(vf[24]); v25 = VU_LD(vf[25]); v26 = VU_LD(vf[26]);
                    v27 = VU_LD(vf[27]); v28 = VU_LD(vf[28]); v29 = VU_LD(vf[29]); a = VU_LD(acc);
                    cull = 1;
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
    st.cycles += np + 15 + 3 * it + cx; /* the stalls: 01f / 021 / 022, 026, 02e; the clipper's */
    kick(i2);
    tpc = 0x4e & (MICRO_N - 1);
    return 1;
}

/* 039: vf28 = ACC + vf04 * vf05.w, the FMAC whose MAC flag the run leaves: as vu_opbel() / the scalar form make
 * it, NEON's result where no field or product is 0 (only the run's last one's flag is needed, nat_4 redoes it) */
static __inline__ uint32x4_t nat_madd4w(uint32x4_t a, float32x4_t p3, uint32x4_t v5) {
    float32x4_t p = vmulq_f32(p3, vdupq_lane_f32(vget_high_f32(vfin(v5)), 1)), r = vaddq_f32(vfin(a), p);
    uint32x4_t abs7 = vdupq_n_u32(0x7FFFFFFFu), z = vdupq_n_u32(0);
    uint32x4_t zz = vorrq_u32(vceqq_u32(vandq_u32(nat_u(p), abs7), z), vceqq_u32(vandq_u32(nat_u(r), abs7), z));
    uint32x2_t any = vorr_u32(vget_low_u32(zz), vget_high_u32(zz));
    if (vget_lane_u32(vpmax_u32(any, any), 0)) {
        u32 m = 0, u[4], c[4], b[4];
        VU_ST(c, a);
        VU_ST(b, v5);
        if (!vu_opbel(u, K_MADD, vf[4], b, 3, c, 0xf, &m)) {
            int k;
            for (k = 0; k < 4; k++) u[k] = fout(fin(c[k]) + fin(vf[4][k]) * fin(b[3]), k, &m);
        }
        return VU_LD(u);
    }
    return vfo(r);
}

/* P4, from 00c (045 branches there): the map renderer without the back-face test, as P0's main loop otherwise: a
 * strip (the position with its flags in w, the colour as integers, ST in 20.12), software-pipelined (a vertex into
 * view space, the one before into clip space and projected), CLIPW of the last three, the ADC for a vertex flagged
 * 0 or a triangle wholly outside one plane.  A triangle that crosses a plane goes to the program's clipper (054,
 * nat_clip()'s P4 form; session 151: most of P4's runs clip one, so the main loop alone, session 151's first
 * nat_4, was taken out), then the ADC on it as for a cull.  A strip whose input and output would wrap round VU
 * memory is left to the translation */
static int nat_4(u32 pc) {
    u32 np, q, fc = clip_last, wI, b22, b6, b7, cx = 0, mclip = 0;
    int clipped = 0; /* the clipper ran after the pass's 039: its MAC flag is the run's so far */
    u16 i1 = vi[1], i2, i3, i4, i5, i6, i7, i10, i11, i12, i13 = vi[13];
    uint32x4_t v5, v6, v7, v8 = VU_LD(vf[8]), v20, v22, v26 = VU_LD(vf[26]), v27 = VU_LD(vf[27]), v28, v29, a;
    uint32x4_t xyz = VU_LD(vu_lanes[0xe]), xy = VU_LD(vu_lanes[0xc]), l5 = vdupq_n_u32(0), la = l5;
    float32x4_t W[4], P[4], c31 = vfin(VU_LD(vf[31])), pf;
    if (pc == 0x45) np = 2;
    else if (pc == 0xc) np = 0;
    else return 0;
    i1 = (u16)top;
    i10 = (u16)(mem[i1 & (DATA_QW - 1)][0] & 0x7FFF);
    if (!i10 || i10 * 7u + 8 > DATA_QW) return 0;
    {
        int k;
        for (k = 0; k < 4; k++) {
            W[k] = vfin(VU_LD(vf[13 + k]));
            P[k] = vfin(VU_LD(vf[1 + k]));
        }
        { Fu f; f.u = vf[0][3]; wI = fo(f.f * fin(i_reg)); } /* muli.w vf28, vf00, I */
    }
    /* 00c-022: the first vertex into view and clip space, the GIF tag */
    i3 = (u16)(i1 + 1);
    v20 = vbslq_u32(xyz, VU_LD(mem[i3 & (DATA_QW - 1)]), VU_LD(vf[0]));
    i11 = 0x7FFF;
    i4 = i5 = i6 = 0xFFFE;
    pf = vfin(v20);
    a = vfo(vmulq_f32(W[0], vdupq_lane_f32(vget_low_f32(pf), 0)));
    a = vfo(vaddq_f32(nat_f(a), vmulq_f32(W[1], vdupq_lane_f32(vget_low_f32(pf), 1))));
    a = vfo(vaddq_f32(nat_f(a), vmulq_f32(W[2], vdupq_lane_f32(vget_high_f32(pf), 0))));
    v5 = vfo(vaddq_f32(nat_f(a), vmulq_f32(W[3], vdupq_lane_f32(vget_high_f32(pf), 1))));
    v29 = VU_LD(mem[i1 & (DATA_QW - 1)]);
    i2 = (u16)(i3 + i10 * 4);
    v22 = v6 = v7 = VU_LD(vf[0]);
    b22 = b6 = b7 = nat_clipbits(v22);
    pf = nat_f(v5);
    a = vfo(vmulq_f32(P[0], vdupq_lane_f32(vget_low_f32(pf), 0)));
    a = vfo(vaddq_f32(nat_f(a), vmulq_f32(P[1], vdupq_lane_f32(vget_low_f32(pf), 1))));
    a = vfo(vaddq_f32(nat_f(a), vmulq_f32(P[2], vdupq_lane_f32(vget_high_f32(pf), 0))));
    v28 = vfo(vaddq_f32(nat_f(a), vmulq_f32(P[3], vdupq_lane_f32(vget_high_f32(pf), 1))));
    VU_ST(mem[i2 & (DATA_QW - 1)], v29);
    i7 = (u16)(i2 + 2);
    i12 = (u16)(i11 + 0xFF1);
    q = nat_rcp(vgetq_lane_u32(v28, 3));
    np += 23;
    for (;;) {
        float32x4_t qq = nat_f(vdupq_n_u32(q));
        int cull;
        /* 023-02b */
        v6 = v7;
        v7 = v5;
        b6 = b7;
        b7 = nat_clipbits(v7);
        v28 = vfo(vmulq_f32(vfin(v28), qq));
        v29 = VU_LD(mem[(i3 + 1) & (DATA_QW - 1)]);
        fc = (fc << 18 | b22 << 12 | b6 << 6 | b7) & 0xFFFFFF;
        v26 = vbslq_u32(xy, VU_LD(mem[(i3 + 2) & (DATA_QW - 1)]), v26);
        v20 = vbslq_u32(xyz, VU_LD(mem[(i3 + 3) & (DATA_QW - 1)]), v20);
        v8 = VU_LD(mem[i3 & (DATA_QW - 1)]);
        v28 = vsetq_lane_u32(wI, v28, 3);
        i3 = (u16)(i3 + 3);
        v29 = nat_u(vcvtq_f32_s32(vreinterpretq_s32_u32(v29)));
        i7 = (u16)(i7 + 3);
        v26 = vbslq_u32(xy, nat_u(vmulq_n_f32(vcvtq_f32_s32(vreinterpretq_s32_u32(v26)), 1.0f / 4096.0f)), v26);
        /* 02c-034: the next vertex into view space; XYZF2 and the colour */
        pf = vfin(v20);
        a = vfo(vmulq_f32(W[0], vdupq_lane_f32(vget_low_f32(pf), 0)));
        i1 = (u16)((fc & 0x3F) != 0);
        v27 = vreinterpretq_u32_s32(vcvtq_s32_f32(vmulq_n_f32(vfin(v28), 16.0f)));
        i4 = i5;
        v29 = vfo(vmulq_f32(nat_f(v29), c31));
        i5 = i6;
        a = vfo(vaddq_f32(nat_f(a), vmulq_f32(W[1], vdupq_lane_f32(vget_low_f32(pf), 1))));
        i6 = i1;
        a = vfo(vaddq_f32(nat_f(a), vmulq_f32(W[2], vdupq_lane_f32(vget_high_f32(pf), 0))));
        i13 = (u16)vgetq_lane_u32(v8, 3);
        v5 = vfo(vaddq_f32(nat_f(a), vmulq_f32(W[3], vdupq_lane_f32(vget_high_f32(pf), 1))));
        VU_ST(mem[(i7 - 2) & (DATA_QW - 1)], v27);
        v26 = vsetq_lane_u32(0x3F800000u, v26, 2); /* addw.z vf26, vf00, vf00w */
        i4 = (u16)(i4 + i5);
        v29 = vreinterpretq_u32_s32(vcvtq_s32_f32(vfin(v29)));
        i4 = (u16)(i4 + i6);
        i10 = (u16)(i10 - 1);
        /* 035-03d: into clip space; ST times Q; Q of the next */
        pf = nat_f(v5);
        a = vfo(vmulq_f32(P[0], vdupq_lane_f32(vget_low_f32(pf), 0)));
        v26 = vbslq_u32(xyz, vfo(vmulq_f32(vfin(v26), qq)), v26);
        a = vfo(vaddq_f32(nat_f(a), vmulq_f32(P[1], vdupq_lane_f32(vget_low_f32(pf), 1))));
        VU_ST(mem[(i7 - 3) & (DATA_QW - 1)], v29);
        a = vfo(vaddq_f32(nat_f(a), vmulq_f32(P[2], vdupq_lane_f32(vget_high_f32(pf), 0))));
        v28 = nat_madd4w(a, P[3], v5);
        la = a;
        l5 = v5;
        clipped = 0;
        VU_ST(mem[(i7 - 4) & (DATA_QW - 1)], v26);
        i1 = (u16)((fc & 0x20820) != 0);
        q = nat_rcp(vgetq_lane_u32(v28, 3));
        np += 27;
        if (!i13) {
            cull = 1;
        } else {
            np += 2;
            if ((s16)i4 > 0) { /* 047-053: a vertex off the screen: culled when all three are outside one plane */
                np += 2;
                if (i1) {
                    i1 = nat_fcor(fc, 0xfdf7df);
                    np += 3;
                    cull = i1;
                } else {
                    static const u32 pl[4] = { 0xffbefb, 0xffdf7d, 0xffefbe, 0xfdf7df };
                    int k;
                    i1 = nat_fcor(fc, 0xff7df7);
                    np += 1;
                    cull = 0;
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
                if (!cull) { /* 054: the clipper, on the VU's registers; then the ADC on the triangle as for a cull */
                    vi[1] = i1; vi[2] = i2; vi[3] = i3; vi[4] = i4; vi[5] = i5; vi[6] = i6; vi[7] = i7; vi[10] = i10;
                    vi[11] = i11; vi[12] = i12; vi[13] = i13;
                    VU_ST(vf[5], v5); VU_ST(vf[6], v6); VU_ST(vf[7], v7); VU_ST(vf[8], v8); VU_ST(vf[20], v20);
                    VU_ST(vf[22], v22); VU_ST(vf[26], v26); VU_ST(vf[27], v27); VU_ST(vf[28], v28);
                    VU_ST(vf[29], v29); VU_ST(acc, a);
                    mclip = nat_clip(&np, &cx, 1);
                    clipped = 1;
                    fc = clip_last;
                    i1 = vi[1]; i2 = vi[2]; i3 = vi[3]; i4 = vi[4]; i5 = vi[5]; i6 = vi[6]; i7 = vi[7]; i10 = vi[10];
                    i11 = vi[11]; i12 = vi[12]; i13 = vi[13];
                    v5 = VU_LD(vf[5]); v6 = VU_LD(vf[6]); v7 = VU_LD(vf[7]); v8 = VU_LD(vf[8]); v20 = VU_LD(vf[20]);
                    v22 = VU_LD(vf[22]); v26 = VU_LD(vf[26]); v27 = VU_LD(vf[27]); v28 = VU_LD(vf[28]);
                    v29 = VU_LD(vf[29]); a = la = VU_LD(acc);
                    cull = 1;
                }
            } else
                cull = 0;
        }
        if (cull) { /* 0f5 / 0f6: the ADC */
            mem[(i7 - 2) & (DATA_QW - 1)][3] = i12;
            np += 2;
        }
        /* 040 / 041 */
        np += 2;
        v22 = v6;
        b22 = b6;
        if (!i10) break;
    }
    /* 042-044: the kick */
    np += 3;
    if (clipped)
        mac_now = mclip;
    else {
        u32 m = 0, u[4], c[4], b[4];
        VU_ST(c, la);
        VU_ST(b, l5);
        if (!vu_opbel(u, K_MADD, vf[4], b, 3, c, 0xf, &m)) {
            int k;
            m = 0;
            for (k = 0; k < 4; k++) fout(fin(c[k]) + fin(vf[4][k]) * fin(b[3]), k, &m);
        }
        mac_now = m;
    }
    vi[1] = i1; vi[2] = i2; vi[3] = i3; vi[4] = i4; vi[5] = i5; vi[6] = i6; vi[7] = i7; vi[10] = i10;
    vi[11] = i11; vi[12] = i12; vi[13] = i13;
    VU_ST(vf[5], v5); VU_ST(vf[6], v6); VU_ST(vf[7], v7); VU_ST(vf[8], v8); VU_ST(vf[20], v20);
    VU_ST(vf[22], v22); VU_ST(vf[26], v26); VU_ST(vf[27], v27); VU_ST(vf[28], v28); VU_ST(vf[29], v29);
    VU_ST(acc, la);
    clip_last = clip_now = fc;
    q_reg = q;
    st.insns += np;
    st.cycles += np + 6 + cx; /* 022's WAITQ; the clipper's */
    kick(i2);
    tpc = 0x45 & (MICRO_N - 1);
    return 1;
}

#endif

/* the program numbers (tools/vu/find_vu1.py's) that have one.  A native run answers 0, before it changes
 * anything, for an entry or a case it does not do, and the translation runs it */
static int (*nat_run(int num))(u32) {
    if (!kh1_vu1_native) return 0;
#if defined(__ARM_NEON) && !defined(KH1_VU1_SCALAR)
    if (num == 0) return nat_0;
    if (num == 4) return nat_4;
    if (num == 10) return nat_10;
    if (num == 11) return nat_11;
    if (num == 12) return nat_12;
    if (num == 13) return nat_13;
    if (num == 18) return nat_18;
#endif
    return 0;
}
