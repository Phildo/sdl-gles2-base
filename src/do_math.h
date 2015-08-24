#ifndef DO_MATH_H
#define DO_MATH_H

#include <stdlib.h>

float randf();

typedef struct { float  x; float  y; }                     fv2;
typedef struct { double x; double y; }                     dv2;
typedef struct { float  x; float  y; float  z; }           fv3;
typedef struct { double x; double y; double z; }           dv3;
typedef struct { double x; double y; double z; double w; } dv4;
typedef struct { float  x; float  y; float  z; float  w; } fv4;

float  lensqrfv2(fv2 v);
double lensqrdv2(dv2 v);
float  lensqrfv3(fv3 v);
double lensqrdv3(dv3 v);
float  lensqrfv4(fv4 v);
double lensqrdv4(dv4 v);

float  lenfv2(fv2 v);
double lendv2(dv2 v);
float  lenfv3(fv3 v);
double lendv3(dv3 v);
float  lenfv4(fv4 v);
double lendv4(dv4 v);

fv2 normfv2(fv2 v);
dv2 normdv2(dv2 v);
fv3 normfv3(fv3 v);
dv3 normdv3(dv3 v);
fv4 normfv4(fv4 v);
dv4 normdv4(dv4 v);

float  lerpf(float  s, float  e, float  t);
double lerpd(double s, double e, double t);
fv2 lerpfv2(fv2 s, fv2 e, float  t);
dv2 lerpdv2(dv2 s, dv2 e, double t);
fv3 lerpfv3(fv3 s, fv3 e, float  t);
dv3 lerpdv3(dv3 s, dv3 e, double t);
fv4 lerpfv4(fv4 s, fv4 e, float  t);
dv4 lerpdv4(dv4 s, dv4 e, double t);

fv2 mulfv2(fv2 v, float  o);
dv2 muldv2(dv2 v, double o);
fv3 mulfv3(fv3 v, float  o);
dv3 muldv3(dv3 v, double o);
fv4 mulfv4(fv4 v, float  o);
dv4 muldv4(dv4 v, double o);

fv2 divfv2(fv2 v, float  o);
dv2 divdv2(dv2 v, double o);
fv3 divfv3(fv3 v, float  o);
dv3 divdv3(dv3 v, double o);
fv4 divfv4(fv4 v, float  o);
dv4 divdv4(dv4 v, double o);

fv2 addfv2(fv2 a, fv2 b);
dv2 adddv2(dv2 a, dv2 b);
fv3 addfv3(fv3 a, fv3 b);
dv3 adddv3(dv3 a, dv3 b);
fv4 addfv4(fv4 a, fv4 b);
dv4 adddv4(dv4 a, dv4 b);

fv2 subfv2(fv2 a, fv2 b);
dv2 subdv2(dv2 a, dv2 b);
fv3 subfv3(fv3 a, fv3 b);
dv3 subdv3(dv3 a, dv3 b);
fv4 subfv4(fv4 a, fv4 b);
dv4 subdv4(dv4 a, dv4 b);

float  dotfv2(fv2 a, fv2 b);
double dotdv2(dv2 a, dv2 b);
float  dotfv3(fv3 a, fv3 b);
double dotdv3(dv3 a, dv3 b);
float  dotfv4(fv4 a, fv4 b);
double dotdv4(dv4 a, dv4 b);

fv3 crossfv3(fv3 a, fv3 b);
dv3 crossdv3(dv3 a, dv3 b);

typedef struct { float  x[2]; float  y[2]; } fm2;
typedef struct { double x[2]; double y[2]; } dm2;
typedef struct { float  x[3]; float  y[3]; float  z[3]; } fm3;
typedef struct { double x[3]; double y[3]; double z[3]; } dm3;
typedef struct { float  x[4]; float  y[4]; float  z[4]; float  w[4]; } fm4;
typedef struct { double x[4]; double y[4]; double z[4]; double w[4]; } dm4;

fm3 promotefm2(fm2 m);
dm3 promotedm2(dm2 m);
fm4 promotefm3(fm3 m);
dm4 promotedm3(dm3 m);

fm2 mulfm2(fm2 a, fm2 b);
dm2 muldm2(dm2 a, dm2 b);
fm3 mulfm3(fm3 a, fm3 b);
dm3 muldm3(dm3 a, dm3 b);
fm4 mulfm4(fm4 a, fm4 b);
dm4 muldm4(dm4 a, dm4 b);

fm2 zerofm2();
dm2 zerodm2();
fm3 zerofm3();
dm3 zerodm3();
fm4 zerofm4();
dm4 zerodm4();

fm2 identityfm2();
dm2 identitydm2();
fm3 identityfm3();
dm3 identitydm3();
fm4 identityfm4();
dm4 identitydm4();

fm2 translatefm2(fm2 m, fv2 v);
dm2 translatedm2(dm2 m, dv2 v);
fm3 translatefm3(fm3 m, fv3 v);
dm3 translatedm3(dm3 m, dv3 v);
fm4 translatefm4(fm4 m, fv4 v);
dm4 translatedm4(dm4 m, dv4 v);

fm2 scalefm2(fm2 m, fv2 v);
dm2 scaledm2(dm2 m, dv2 v);
fm3 scalefm3(fm3 m, fv3 v);
dm3 scaledm3(dm3 m, dv3 v);
fm4 scalefm4(fm4 m, fv4 v);
dm4 scaledm4(dm4 m, dv4 v);

fm2 rotatefm2(float t);
dm2 rotatedm2(double t);
fm3 rotatefm3(fv3 v, float t);
dm3 rotatedm3(dv3 v, double t);
fm4 rotate3dfm4(fv3 v, float t);
dm4 rotate3ddm4(dv3 v, double t);

fv2 matmulfv2(fm2 m, fv2 v);
dv2 matmuldv2(dm2 m, dv2 v);
fv3 matmulfv3(fm3 m, fv3 v);
dv3 matmuldv3(dm3 m, dv3 v);
fv4 matmulfv4(fm4 m, fv4 v);
dv4 matmuldv4(dm4 m, dv4 v);

fm4 lookAtfm4(fv3 eye, fv3 center, fv3 up);
dm4 lookAtdm4(dv3 eye, dv3 center, dv3 up);

fm4 perspectivefm4(float fovy, float aspect, float zNear, float zFar);
dm4 perspectivedm4(double fovy, double aspect, double zNear, double zFar);

fm4 orthofm4(float left, float right, float bottom, float top, float zNear, float zFar);
dm4 orthodm4(double left, double right, double bottom, double top, double zNear, double zFar);

#endif

