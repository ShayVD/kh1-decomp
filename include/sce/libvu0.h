/* Declarations of SCE libvu0 functions as linked into the game ELF.
 * Hand-written from the public function signatures; no SDK headers are
 * copied into this repository. Addresses are in functions.tsv (named in
 * session 45 from their code, docs/sdk.md); the code is src/sdk/libvu0/vu0.s.
 * The vector / matrix types are spelled as the plain pointers they decay to:
 * a vector is f32 [4] (quadword aligned), a matrix f32 [4][4], row-major with
 * the translation in row 3. */
#ifndef KH1_SCE_LIBVU0_H
#define KH1_SCE_LIBVU0_H

void sceVu0ApplyMatrix(float *v0, float (*m0)[4], float *v1);
void sceVu0MulMatrix(float (*m0)[4], float (*m1)[4], float (*m2)[4]);
void sceVu0OuterProduct(float *v0, float *v1, float *v2);
float sceVu0InnerProduct(float *v0, float *v1);
void sceVu0Normalize(float *v0, float *v1);
void sceVu0TransposeMatrix(float (*m0)[4], float (*m1)[4]);
void sceVu0InversMatrix(float (*m0)[4], float (*m1)[4]);
void sceVu0DivVector(float *v0, float *v1, float q);
void sceVu0DivVectorXYZ(float *v0, float *v1, float q);
void sceVu0InterVector(float *v0, float *v1, float *v2, float t);
void sceVu0AddVector(float *v0, float *v1, float *v2);
void sceVu0SubVector(float *v0, float *v1, float *v2);
void sceVu0MulVector(float *v0, float *v1, float *v2);
void sceVu0ScaleVector(float *v0, float *v1, float t);
void sceVu0TransMatrix(float (*m0)[4], float (*m1)[4], float *tv);
void sceVu0CopyVector(float *v0, float *v1);
void sceVu0CopyMatrix(float (*m0)[4], float (*m1)[4]);
void sceVu0FTOI4Vector(int *v0, float *v1);
void sceVu0FTOI0Vector(int *v0, float *v1);
void sceVu0ITOF4Vector(float *v0, int *v1);
void sceVu0ITOF0Vector(float *v0, int *v1);
void sceVu0UnitMatrix(float (*m0)[4]);
void sceVu0RotMatrixZ(float (*m0)[4], float (*m1)[4], float rz);
void sceVu0RotMatrixX(float (*m0)[4], float (*m1)[4], float rx);
void sceVu0RotMatrixY(float (*m0)[4], float (*m1)[4], float ry);
void sceVu0RotMatrix(float (*m0)[4], float (*m1)[4], float *rot);
void sceVu0ClampVector(float *v0, float *v1, float min, float max);
void sceVu0CameraMatrix(float (*m)[4], float *p, float *zd, float *yd);
void sceVu0NormalLightMatrix(float (*m)[4], float *l0, float *l1, float *l2);
void sceVu0LightColorMatrix(float (*m)[4], float *c0, float *c1, float *c2, float *a);
void sceVu0ViewScreenMatrix(float (*m)[4], float scrz, float ax, float ay, float cx, float cy,
                            float zmin, float zmax, float nearz, float farz);
void sceVu0DropShadowMatrix(float (*m)[4], float *lp, float a, float b, float c, int mode);
void sceVu0RotTransPersN(int *v0, float (*m0)[4], float *v1, int n, int mode);
void sceVu0RotTransPers(int *v0, float (*m0)[4], float *v1, int mode);
void sceVu0CopyVectorXYZ(float *v0, float *v1);
void sceVu0InterVectorXYZ(float *v0, float *v1, float *v2, float t);
void sceVu0ScaleVectorXYZ(float *v0, float *v1, float s);
int sceVu0ClipScreen(float *v0);
int sceVu0ClipScreen3(float *v0, float *v1, float *v2);
int sceVu0ClipAll(float *minv, float *maxv, float (*ms)[4], float *vm, int n);
void sceVpu0Reset(void);

#endif /* KH1_SCE_LIBVU0_H */
