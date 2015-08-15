#ifndef DO_MATH_H
#define DO_MATH_H

typedef struct { float x; float y; } fv2;
typedef struct { float x; float y; float z; } fv3;
typedef struct { float x; float y; float z; float w; } fv4;
typedef struct { double x; double y; } dv2;
typedef struct { double x; double y; double z; } dv3;
typedef struct { double x; double y; double z; double w; } dv4;

float lerpf(float s, float e, float t) { return s+(t*(e-s)); }
double lerpd(double s, double e, double t) { return s+(t*(e-s)); }
fv2 lerpfv2(fv2 s, fv2 e, float t)
{
  return fv2{
    s.x+(t*(e.x-s.x)),
    s.y+(t*(e.y-s.y))
  };
}
dv2 lerpdv2(dv2 s, dv2 e, double t)
{
  return dv2{
    s.x+(t*(e.x-s.x)),
    s.y+(t*(e.y-s.y))
  };
}
fv3 lerpfv3(fv3 s, fv3 e, float t)
{
  return fv3{
    s.x+(t*(e.x-s.x)),
    s.y+(t*(e.y-s.y)),
    s.z+(t*(e.z-s.z))
  };
}
dv3 lerpdv3(dv3 s, dv3 e, double t)
{
  return dv3{
    s.x+(t*(e.x-s.x)),
    s.y+(t*(e.y-s.y)),
    s.z+(t*(e.z-s.z))
  };
}
fv4 lerpfv4(fv4 s, fv4 e, float t)
{
  return fv4{
    s.x+(t*(e.x-s.x)),
    s.y+(t*(e.y-s.y)),
    s.z+(t*(e.z-s.z)),
    s.w+(t*(e.w-s.w))
  };
}
dv4 lerpdv4(dv4 s, dv4 e, double t)
{
  return dv4{
    s.x+(t*(e.x-s.x)),
    s.y+(t*(e.y-s.y)),
    s.z+(t*(e.z-s.z)),
    s.w+(t*(e.w-s.w))
  };
}

#endif

