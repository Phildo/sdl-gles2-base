#include "do_math.h"
#include "math.h"

float randf()
{
  return (rand()%256)/256.0f;
}

float  lensqrfv2(fv2 v) { return (v.x*v.x) + (v.y*v.y); }
double lensqrdv2(dv2 v) { return (v.x*v.x) + (v.y*v.y); }
float  lensqrfv3(fv3 v) { return (v.x*v.x) + (v.y*v.y) + (v.z*v.z); }
double lensqrdv3(dv3 v) { return (v.x*v.x) + (v.y*v.y) + (v.z*v.z); }
float  lensqrfv4(fv4 v) { return (v.x*v.x) + (v.y*v.y) + (v.z*v.z) + (v.w*v.w); }
double lensqrdv4(dv4 v) { return (v.x*v.x) + (v.y*v.y) + (v.z*v.z) + (v.w*v.w); }

float  lenfv2(fv2 v) { return sqrt((v.x*v.x) + (v.y*v.y)); }
double lendv2(dv2 v) { return sqrt((v.x*v.x) + (v.y*v.y)); }
float  lenfv3(fv3 v) { return sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z)); }
double lendv3(dv3 v) { return sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z)); }
float  lenfv4(fv4 v) { return sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z) + (v.w*v.w)); }
double lendv4(dv4 v) { return sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z) + (v.w*v.w)); }

fv2 normfv2(fv2 v) { float l = lenfv2(v); return fv2{ v.x/l, v.y/l };  }
dv2 normdv2(dv2 v) { float l = lendv2(v); return dv2{ v.x/l, v.y/l };  }
fv3 normfv3(fv3 v) { float l = lenfv3(v); return fv3{ v.x/l, v.y/l, v.z/l };  }
dv3 normdv3(dv3 v) { float l = lendv3(v); return dv3{ v.x/l, v.y/l, v.z/l };  }
fv4 normfv4(fv4 v) { float l = lenfv4(v); return fv4{ v.x/l, v.y/l, v.z/l, v.w/l };  }
dv4 normdv4(dv4 v) { float l = lendv4(v); return dv4{ v.x/l, v.y/l, v.z/l, v.w/l };  }

#define LERP(s,e,t) (s+(t*(e-s)))
float  lerpf(float  s, float  e, float  t) { return LERP(s,e,t); }
double lerpd(double s, double e, double t) { return LERP(s,e,t); }
fv2 lerpfv2(fv2 s, fv2 e, float  t) { return fv2{ LERP(s.x,e.x,t), LERP(s.y,e.y,t) }; }
dv2 lerpdv2(dv2 s, dv2 e, double t) { return dv2{ LERP(s.x,e.x,t), LERP(s.y,e.y,t) }; }
fv3 lerpfv3(fv3 s, fv3 e, float  t) { return fv3{ LERP(s.x,e.x,t), LERP(s.y,e.y,t), LERP(s.z,e.z,t) }; }
dv3 lerpdv3(dv3 s, dv3 e, double t) { return dv3{ LERP(s.x,e.x,t), LERP(s.y,e.y,t), LERP(s.z,e.z,t) }; }
fv4 lerpfv4(fv4 s, fv4 e, float  t) { return fv4{ LERP(s.x,e.x,t), LERP(s.y,e.y,t), LERP(s.z,e.z,t), LERP(s.w,e.w,t) }; }
dv4 lerpdv4(dv4 s, dv4 e, double t) { return dv4{ LERP(s.x,e.x,t), LERP(s.y,e.y,t), LERP(s.z,e.z,t), LERP(s.w,e.w,t) }; }
#undef LERP

fv2 mulfv2(fv2 v, float  o) { return fv2 { v.x*o, v.y*o }; }
dv2 muldv2(dv2 v, double o) { return dv2 { v.x*o, v.y*o }; }
fv3 mulfv3(fv3 v, float  o) { return fv3 { v.x*o, v.y*o, v.z*o }; }
dv3 muldv3(dv3 v, double o) { return dv3 { v.x*o, v.y*o, v.z*o }; }
fv4 mulfv4(fv4 v, float  o) { return fv4 { v.x*o, v.y*o, v.z*o, v.w*o }; }
dv4 muldv4(dv4 v, double o) { return dv4 { v.x*o, v.y*o, v.z*o, v.w*o }; }

fv2 divfv2(fv2 v, float  o) { return fv2 { v.x/o, v.y/o }; }
dv2 divdv2(dv2 v, double o) { return dv2 { v.x/o, v.y/o }; }
fv3 divfv3(fv3 v, float  o) { return fv3 { v.x/o, v.y/o, v.z/o }; }
dv3 divdv3(dv3 v, double o) { return dv3 { v.x/o, v.y/o, v.z/o }; }
fv4 divfv4(fv4 v, float  o) { return fv4 { v.x/o, v.y/o, v.z/o, v.w/o }; }
dv4 divdv4(dv4 v, double o) { return dv4 { v.x/o, v.y/o, v.z/o, v.w/o }; }

fv2 addfv2(fv2 a, fv2 b) { return fv2 { a.x+b.x, a.y+b.y }; }
dv2 adddv2(dv2 a, dv2 b) { return dv2 { a.x+b.x, a.y+b.y }; }
fv3 addfv3(fv3 a, fv3 b) { return fv3 { a.x+b.x, a.y+b.y, a.z+b.z }; }
dv3 adddv3(dv3 a, dv3 b) { return dv3 { a.x+b.x, a.y+b.y, a.z+b.z }; }
fv4 addfv4(fv4 a, fv4 b) { return fv4 { a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w }; }
dv4 adddv4(dv4 a, dv4 b) { return dv4 { a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w }; }

fv2 subfv2(fv2 a, fv2 b) { return fv2 { a.x-b.x, a.y-b.y }; }
dv2 subdv2(dv2 a, dv2 b) { return dv2 { a.x-b.x, a.y-b.y }; }
fv3 subfv3(fv3 a, fv3 b) { return fv3 { a.x-b.x, a.y-b.y, a.z-b.z }; }
dv3 subdv3(dv3 a, dv3 b) { return dv3 { a.x-b.x, a.y-b.y, a.z-b.z }; }
fv4 subfv4(fv4 a, fv4 b) { return fv4 { a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w }; }
dv4 subdv4(dv4 a, dv4 b) { return dv4 { a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w }; }

float  dotfv2(fv2 a, fv2 b) { return (a.x*b.x) + (a.y*b.y); }
double dotdv2(dv2 a, dv2 b) { return (a.x*b.x) + (a.y*b.y); }
float  dotfv3(fv3 a, fv3 b) { return (a.x*b.x) + (a.y*b.y) + (a.z*b.z); }
double dotdv3(dv3 a, dv3 b) { return (a.x*b.x) + (a.y*b.y) + (a.z*b.z); }
float  dotfv4(fv4 a, fv4 b) { return (a.x*b.x) + (a.y*b.y) + (a.z*b.z) + (a.w*b.w); }
double dotdv4(dv4 a, dv4 b) { return (a.x*b.x) + (a.y*b.y) + (a.z*b.z) + (a.w*b.w); }

fv3 crossfv3(fv3 a, fv3 b) { return fv3 { (a.y*b.z)-(a.z*b.y), (a.z*b.x)-(a.x*b.z), (a.x*b.y)-(a.y*b.x) }; }
dv3 crossdv3(dv3 a, dv3 b) { return dv3 { (a.y*b.z)-(a.z*b.y), (a.z*b.x)-(a.x*b.z), (a.x*b.y)-(a.y*b.x) }; }

fm3 promotefm2(fm2 m)
{
  return fm3
    { { m.x[0], m.x[1], 0.f },
      { m.y[0], m.y[1], 0.f },
      {    0.f,    0.f, 1.f } };
}
dm3 promotedm2(dm2 m)
{
  return dm3
    { { m.x[0], m.x[1], 0.  },
      { m.y[0], m.y[1], 0.  },
      {    0. ,    0. , 1.  } };
}
fm4 promotefm3(fm3 m)
{
  return fm4
    { { m.x[0], m.x[1], m.x[2], 0.f },
      { m.y[0], m.y[1], m.y[2], 0.f },
      { m.z[0], m.z[1], m.z[2], 0.f },
      {    0.f,    0.f,    0.f, 1.f } };
}
dm4 promotedm3(dm3 m)
{
  return dm4
    { { m.x[0], m.x[1], m.x[2], 0.  },
      { m.y[0], m.y[1], m.y[2], 0.  },
      { m.z[0], m.z[1], m.z[2], 0.  },
      {    0. ,    0. ,    0. , 1.  } };
}

fm2 mulfm2(fm2 a, fm2 b)
{
  return fm2
    { { a.x[0]*b.x[0]+a.x[1]*b.y[0], a.x[0]*b.x[1]+a.x[1]*b.y[1] },
      { a.y[0]*b.x[0]+a.y[1]*b.y[0], a.y[0]*b.x[1]+a.y[1]*b.y[1] } };
}
dm2 muldm2(dm2 a, dm2 b)
{
  return dm2
    { { a.x[0]*b.x[0]+a.x[1]*b.y[0], a.x[0]*b.x[1]+a.x[1]*b.y[1] },
      { a.y[0]*b.x[0]+a.y[1]*b.y[0], a.y[0]*b.x[1]+a.y[1]*b.y[1] } };
}
fm3 mulfm3(fm3 a, fm3 b)
{
  return fm3
    { { a.x[0]*b.x[0]+a.x[1]*b.y[0]+a.x[2]*b.z[0], a.x[0]*b.x[1]+a.x[1]*b.y[1]+a.x[2]*b.z[1], a.x[0]*b.x[2]+a.x[1]*b.y[2]+a.x[2]*b.z[2] },
      { a.y[0]*b.x[0]+a.y[1]*b.y[0]+a.y[2]*b.z[0], a.y[0]*b.x[1]+a.y[1]*b.y[1]+a.y[2]*b.z[1], a.y[0]*b.x[2]+a.y[1]*b.y[2]+a.y[2]*b.z[2] },
      { a.z[0]*b.x[0]+a.z[1]*b.y[0]+a.z[2]*b.z[0], a.z[0]*b.x[1]+a.z[1]*b.y[1]+a.z[2]*b.z[1], a.z[0]*b.x[2]+a.z[1]*b.y[2]+a.z[2]*b.z[2] } };
}
dm3 muldm3(dm3 a, dm3 b)
{
  return dm3
    { { a.x[0]*b.x[0]+a.x[1]*b.y[0]+a.x[2]*b.z[0], a.x[0]*b.x[1]+a.x[1]*b.y[1]+a.x[2]*b.z[1], a.x[0]*b.x[2]+a.x[1]*b.y[2]+a.x[2]*b.z[2] },
      { a.y[0]*b.x[0]+a.y[1]*b.y[0]+a.y[2]*b.z[0], a.y[0]*b.x[1]+a.y[1]*b.y[1]+a.y[2]*b.z[1], a.y[0]*b.x[2]+a.y[1]*b.y[2]+a.y[2]*b.z[2] },
      { a.z[0]*b.x[0]+a.z[1]*b.y[0]+a.z[2]*b.z[0], a.z[0]*b.x[1]+a.z[1]*b.y[1]+a.z[2]*b.z[1], a.z[0]*b.x[2]+a.z[1]*b.y[2]+a.z[2]*b.z[2] } };
}
fm4 mulfm4(fm4 a, fm4 b)
{
  return fm4
    { { a.x[0]*b.x[0]+a.x[1]*b.y[0]+a.x[2]*b.z[0]+a.x[3]*b.w[0], a.x[0]*b.x[1]+a.x[1]*b.y[1]+a.x[2]*b.z[1]+a.x[3]*b.w[1], a.x[0]*b.x[2]+a.x[1]*b.y[2]+a.x[2]*b.z[2]+a.x[3]*b.w[2], a.x[0]*b.x[3]+a.x[1]*b.y[3]+a.x[2]*b.z[3]+a.x[3]*b.w[3] },
      { a.y[0]*b.x[0]+a.y[1]*b.y[0]+a.y[2]*b.z[0]+a.y[3]*b.w[0], a.y[0]*b.x[1]+a.y[1]*b.y[1]+a.y[2]*b.z[1]+a.y[3]*b.w[1], a.y[0]*b.x[2]+a.y[1]*b.y[2]+a.y[2]*b.z[2]+a.y[3]*b.w[2], a.y[0]*b.x[3]+a.y[1]*b.y[3]+a.y[2]*b.z[3]+a.y[3]*b.w[3] },
      { a.z[0]*b.x[0]+a.z[1]*b.y[0]+a.z[2]*b.z[0]+a.z[3]*b.w[0], a.z[0]*b.x[1]+a.z[1]*b.y[1]+a.z[2]*b.z[1]+a.z[3]*b.w[1], a.z[0]*b.x[2]+a.z[1]*b.y[2]+a.z[2]*b.z[2]+a.z[3]*b.w[2], a.z[0]*b.x[3]+a.z[1]*b.y[3]+a.z[2]*b.z[3]+a.z[3]*b.w[3] },
      { a.w[0]*b.x[0]+a.w[1]*b.y[0]+a.w[2]*b.z[0]+a.w[3]*b.w[0], a.w[0]*b.x[1]+a.w[1]*b.y[1]+a.w[2]*b.z[1]+a.w[3]*b.w[1], a.w[0]*b.x[2]+a.w[1]*b.y[2]+a.w[2]*b.z[2]+a.w[3]*b.w[2], a.w[0]*b.x[3]+a.w[1]*b.y[3]+a.w[2]*b.z[3]+a.w[3]*b.w[3] } };
}
dm4 muldm4(dm4 a, dm4 b)
{
  return dm4
    { { a.x[0]*b.x[0]+a.x[1]*b.y[0]+a.x[2]*b.z[0]+a.x[3]*b.w[0], a.x[0]*b.x[1]+a.x[1]*b.y[1]+a.x[2]*b.z[1]+a.x[3]*b.w[1], a.x[0]*b.x[2]+a.x[1]*b.y[2]+a.x[2]*b.z[2]+a.x[3]*b.w[2], a.x[0]*b.x[3]+a.x[1]*b.y[3]+a.x[2]*b.z[3]+a.x[3]*b.w[3] },
      { a.y[0]*b.x[0]+a.y[1]*b.y[0]+a.y[2]*b.z[0]+a.y[3]*b.w[0], a.y[0]*b.x[1]+a.y[1]*b.y[1]+a.y[2]*b.z[1]+a.y[3]*b.w[1], a.y[0]*b.x[2]+a.y[1]*b.y[2]+a.y[2]*b.z[2]+a.y[3]*b.w[2], a.y[0]*b.x[3]+a.y[1]*b.y[3]+a.y[2]*b.z[3]+a.y[3]*b.w[3] },
      { a.z[0]*b.x[0]+a.z[1]*b.y[0]+a.z[2]*b.z[0]+a.z[3]*b.w[0], a.z[0]*b.x[1]+a.z[1]*b.y[1]+a.z[2]*b.z[1]+a.z[3]*b.w[1], a.z[0]*b.x[2]+a.z[1]*b.y[2]+a.z[2]*b.z[2]+a.z[3]*b.w[2], a.z[0]*b.x[3]+a.z[1]*b.y[3]+a.z[2]*b.z[3]+a.z[3]*b.w[3] },
      { a.w[0]*b.x[0]+a.w[1]*b.y[0]+a.w[2]*b.z[0]+a.w[3]*b.w[0], a.w[0]*b.x[1]+a.w[1]*b.y[1]+a.w[2]*b.z[1]+a.w[3]*b.w[1], a.w[0]*b.x[2]+a.w[1]*b.y[2]+a.w[2]*b.z[2]+a.w[3]*b.w[2], a.w[0]*b.x[3]+a.w[1]*b.y[3]+a.w[2]*b.z[3]+a.w[3]*b.w[3] } };
}

fm2 zerofm2()
{
  return fm2
    { { 0.f, 0.f },
      { 0.f, 0.f } };
}
dm2 zerodm2()
{
  return dm2
    { { 0. , 0.  },
      { 0. , 0.  } };
}
fm3 zerofm3()
{
  return fm3
    { { 0.f, 0.f, 0.f },
      { 0.f, 0.f, 0.f },
      { 0.f, 0.f, 0.f } };
}
dm3 zerodm3()
{
  return dm3
    { { 0. , 0. , 0.  },
      { 0. , 0. , 0.  },
      { 0. , 0. , 0.  } };
}
fm4 zerofm4()
{
  return fm4
    { { 0.f, 0.f, 0.f, 0.f },
      { 0.f, 0.f, 0.f, 0.f },
      { 0.f, 0.f, 0.f, 0.f },
      { 0.f, 0.f, 0.f, 0.f } };
}
dm4 zerodm4()
{
  return dm4
    { { 0. , 0. , 0. , 0.  },
      { 0. , 0. , 0. , 0.  },
      { 0. , 0. , 0. , 0.  },
      { 0. , 0. , 0. , 0.  } };
}

fm2 identityfm2()
{
  return fm2
    { { 1.f, 0.f },
      { 0.f, 1.f } };
}
dm2 identitydm2()
{
  return dm2
    { { 1. , 0.  },
      { 0. , 1.  } };
}
fm3 identityfm3()
{
  return fm3
    { { 1.f, 0.f, 0.f },
      { 0.f, 1.f, 0.f },
      { 0.f, 0.f, 1.f } };
}
dm3 identitydm3()
{
  return dm3
    { { 1. , 0. , 0.  },
      { 0. , 1. , 0.  },
      { 0. , 0. , 1.  } };
}
fm4 identityfm4()
{
  return fm4
    { { 1.f, 0.f, 0.f, 0.f },
      { 0.f, 1.f, 0.f, 0.f },
      { 0.f, 0.f, 1.f, 0.f },
      { 0.f, 0.f, 0.f, 1.f } };
}
dm4 identitydm4()
{
  return dm4
    { { 1. , 0. , 0. , 0.  },
      { 0. , 1. , 0. , 0.  },
      { 0. , 0. , 1. , 0.  },
      { 0. , 0. , 0. , 1.  } };
}

fm2 translatefm2(fm2 m, fv2 v)
{
  return fm2
    { { m.x[0], m.x[1]+v.x },
      { m.y[0], m.y[1]+v.y } };
}
dm2 translatedm2(dm2 m, dv2 v)
{
  return dm2
    { { m.x[0], m.x[1]+v.x },
      { m.y[0], m.y[1]+v.y } };
}
fm3 translatefm3(fm3 m, fv3 v)
{
  return fm3
    { { m.x[0], m.x[1], m.x[2]+v.x },
      { m.y[0], m.y[1], m.y[2]+v.y },
      { m.z[0], m.z[1], m.z[2]+v.z } };
}
dm3 translatedm3(dm3 m, dv3 v)
{
  return dm3
    { { m.x[0], m.x[1], m.x[2]+v.x },
      { m.y[0], m.y[1], m.y[2]+v.y },
      { m.z[0], m.z[1], m.z[2]+v.z } };
}
fm4 translatefm4(fm4 m, fv4 v)
{
  return fm4
    { { m.x[0], m.x[1], m.x[2], m.x[3]+v.x },
      { m.y[0], m.y[1], m.y[2], m.y[3]+v.y },
      { m.z[0], m.z[1], m.z[2], m.z[3]+v.z },
      { m.w[0], m.w[1], m.w[2], m.w[3]+v.w } };
}
dm4 translatedm4(dm4 m, dv4 v)
{
  return dm4
    { { m.x[0], m.x[1], m.x[2], m.x[3]+v.x },
      { m.y[0], m.y[1], m.y[2], m.y[3]+v.y },
      { m.z[0], m.z[1], m.z[2], m.z[3]+v.z },
      { m.w[0], m.w[1], m.w[2], m.w[3]+v.w } };
}

fm2 scalefm2(fm2 m, fv2 v)
{
  return fm2
    { { m.x[0]*v.x, m.x[1]     },
      { m.y[0],     m.y[1]*v.y } };
}
dm2 scaledm2(dm2 m, dv2 v)
{
  return dm2
    { { m.x[0]*v.x, m.x[1]     },
      { m.y[0]    , m.y[1]*v.y } };
}
fm3 scalefm3(fm3 m, fv3 v)
{
  return fm3
    { { m.x[0]*v.x, m.x[1]    , m.x[2]     },
      { m.y[0]    , m.y[1]*v.y, m.y[2]     },
      { m.z[0]    , m.z[1]    , m.z[2]*v.z } };
}
dm3 scaledm3(dm3 m, dv3 v)
{
  return dm3
    { { m.x[0]*v.x, m.x[1]    , m.x[2]     },
      { m.y[0]    , m.y[1]*v.y, m.y[2]     },
      { m.z[0]    , m.z[1]    , m.z[2]*v.z } };
}
fm4 scalefm4(fm4 m, fv4 v)
{
  return fm4
    { { m.x[0]*v.x, m.x[1]    , m.x[2]    , m.x[3]     },
      { m.y[0]    , m.y[1]*v.y, m.y[2]    , m.y[3]     },
      { m.z[0]    , m.z[1]    , m.z[2]*v.z, m.z[3]     },
      { m.w[0]    , m.w[1]    , m.w[2]    , m.w[3]*v.w } };
}
dm4 scaledm4(dm4 m, dv4 v)
{
  return dm4
    { { m.x[0]*v.x, m.x[1]    , m.x[2]    , m.x[3]     },
      { m.y[0]    , m.y[1]*v.y, m.y[2]    , m.y[3]     },
      { m.z[0]    , m.z[1]    , m.z[2]*v.z, m.z[3]     },
      { m.w[0]    , m.w[1]    , m.w[2]    , m.w[3]*v.w } };
}

fm2 rotatefm2(float t)
{
  float cost = cos(t);
  float sint = sin(t);
  return fm2
    { { cost, -sint },
      { sint, cost } };
}
dm2 rotatedm2(double t)
{
  float cost = cos(t);
  float sint = sin(t);
  return dm2
    { { cost, -sint },
      { sint, cost } };
}
fm3 rotatefm3(fv3 v, float t)
{
  float cost = cos(t);
  float oneminuscost = 1.f - cost;
  float sint = sin(t);
  float xx = v.x*v.x;
  float xy = v.x*v.y;
  float xz = v.x*v.z;
  float yy = v.y*v.y;
  float yz = v.y*v.z;
  float zz = v.z*v.z;
  return fm3
    { {     (cost)+(xx*oneminuscost), (xy*oneminuscost)-(v.z*sint), (xz*oneminuscost)+(v.y*sint) },
      { (xy*oneminuscost)+(v.z*sint),     (cost)+(yy*oneminuscost), (yz*oneminuscost)-(v.x*sint) },
      { (xz*oneminuscost)-(v.y*sint), (yz*oneminuscost)+(v.x*sint),     (cost)+(zz*oneminuscost) } };
}
dm3 rotatedm3(dv3 v, double t)
{
  double cost = cos(t);
  double oneminuscost = 1. - cost;
  double sint = sin(t);
  double xx = v.x*v.x;
  double xy = v.x*v.y;
  double xz = v.x*v.z;
  double yy = v.y*v.y;
  double yz = v.y*v.z;
  double zz = v.z*v.z;
  return dm3
    { {     (cost)+(xx*oneminuscost), (xy*oneminuscost)-(v.z*sint), (xz*oneminuscost)+(v.y*sint) },
      { (xy*oneminuscost)+(v.z*sint),     (cost)+(yy*oneminuscost), (yz*oneminuscost)-(v.x*sint) },
      { (xz*oneminuscost)-(v.y*sint), (yz*oneminuscost)+(v.x*sint),     (cost)+(zz*oneminuscost) } };
}
fm4 rotate3dfm4(fv3 v, float t)
{
  float cost = cos(t);
  float oneminuscost = 1.f - cost;
  float sint = sin(t);
  float xx = v.x*v.x;
  float xy = v.x*v.y;
  float xz = v.x*v.z;
  float yy = v.y*v.y;
  float yz = v.y*v.z;
  float zz = v.z*v.z;
  return fm4
    { {     (cost)+(xx*oneminuscost), (xy*oneminuscost)-(v.z*sint), (xz*oneminuscost)+(v.y*sint), 0.f },
      { (xy*oneminuscost)+(v.z*sint),     (cost)+(yy*oneminuscost), (yz*oneminuscost)-(v.x*sint), 0.f },
      { (xz*oneminuscost)-(v.y*sint), (yz*oneminuscost)+(v.x*sint),     (cost)+(zz*oneminuscost), 0.f },
      {                          0.f,                          0.f,                          0.f, 1.f } };
}
dm4 rotate3ddm4(dv3 v, double t)
{
  double cost = cos(t);
  double oneminuscost = 1. - cost;
  double sint = sin(t);
  double xx = v.x*v.x;
  double xy = v.x*v.y;
  double xz = v.x*v.z;
  double yy = v.y*v.y;
  double yz = v.y*v.z;
  double zz = v.z*v.z;
  return dm4
    { {     (cost)+(xx*oneminuscost), (xy*oneminuscost)-(v.z*sint), (xz*oneminuscost)+(v.y*sint), 0. },
      { (xy*oneminuscost)+(v.z*sint),     (cost)+(yy*oneminuscost), (yz*oneminuscost)-(v.x*sint), 0. },
      { (xz*oneminuscost)-(v.y*sint), (yz*oneminuscost)+(v.x*sint),     (cost)+(zz*oneminuscost), 0. },
      {                           0.,                           0.,                           0., 1. } };
}

//code more or less stolen from glm
// glm-repo/glm/gtc/matrix_transform.inl : lookAt
fm4 lookAtfm4(fv3 eye, fv3 center, fv3 up)
{
  fv3 f = normfv3(subfv3(center,eye));
  fv3 s = normfv3(crossfv3(f,up));
  fv3 u = crossfv3(s,f);

  fm4 r = identityfm4();
  r.x[0] = s.x;
  r.y[0] = s.y;
  r.z[0] = s.z;
  r.x[1] = u.x;
  r.y[1] = u.y;
  r.z[1] = u.z;
  r.x[2] = -f.x;
  r.y[2] = -f.y;
  r.z[2] = -f.z;
  r.w[0] = -dotfv3(s, eye);
  r.w[1] = -dotfv3(u, eye);
  r.w[2] =  dotfv3(f, eye);
  return r;
}
dm4 lookAtdm4(dv3 eye, dv3 center, dv3 up)
{
  dv3 f = normdv3(subdv3(center,eye));
  dv3 s = normdv3(crossdv3(f,up));
  dv3 u = crossdv3(s,f);

  dm4 r = identitydm4();
  r.x[0] = s.x;
  r.y[0] = s.y;
  r.z[0] = s.z;
  r.x[1] = u.x;
  r.y[1] = u.y;
  r.z[1] = u.z;
  r.x[2] = -f.x;
  r.y[2] = -f.y;
  r.z[2] = -f.z;
  r.w[0] = -dotdv3(s, eye);
  r.w[1] = -dotdv3(u, eye);
  r.w[2] =  dotdv3(f, eye);
  return r;
}

//code more or less stolen from glm
// glm-repo/glm/gtc/matrix_transform.inl : perspective
fm4 perspective(float fovy, float aspect, float zNear, float zFar)
{
  float tanHalfFovy = tan(fovy / 2.f);

  fm4 r = zerofm4();
  r.x[0] = 1.f / (aspect * tanHalfFovy);
  r.y[1] = 1.f / (tanHalfFovy);
  r.z[2] = - (zFar + zNear) / (zFar - zNear);
  r.z[3] = - 1.f;
  r.w[2] = - (2.f * zFar * zNear) / (zFar - zNear);
  return r;
}
dm4 perspective(double fovy, double aspect, double zNear, double zFar)
{
  double tanHalfFovy = tan(fovy / 2.f);

  dm4 r = zerodm4();
  r.x[0] = 1.  / (aspect * tanHalfFovy);
  r.y[1] = 1.  / (tanHalfFovy);
  r.z[2] = - (zFar + zNear) / (zFar - zNear);
  r.z[3] = - 1. ;
  r.w[2] = - (2.  * zFar * zNear) / (zFar - zNear);
  return r;
}

//code more or less stolen from glm
// glm-repo/glm/gtc/matrix_transform.inl : ortho
fm4 ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
  fm4 r = identityfm4();
  r.x[0] = 2.f / (right - left);
  r.y[1] = 2.f / (top - bottom);
  r.z[2] = -2.f / (zFar - zNear);
  r.w[0] = -(right + left) / (right - left);
  r.w[1] = -(top + bottom) / (top - bottom);
  r.w[2] = -(zFar + zNear) / (zFar - zNear);
  return r;
}
dm4 ortho(double left, double right, double bottom, double top, double zNear, double zFar)
{
  dm4 r = identitydm4();
  r.x[0] = 2.f / (right - left);
  r.y[1] = 2.f / (top - bottom);
  r.z[2] = -2.f / (zFar - zNear);
  r.w[0] = -(right + left) / (right - left);
  r.w[1] = -(top + bottom) / (top - bottom);
  r.w[2] = -(zFar + zNear) / (zFar - zNear);
  return r;
}

