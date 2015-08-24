#ifndef DO_MESH_H
#define DO_MESH_H

#include "do_math.h"

int numVertsReqForRectMesh(int nrows, int ncols);
int numIndsReqForRectMesh(int nrows, int ncols);
void genfv2RectMeshVerts(fv2 a, fv2 b, int nrows, int ncols, fv2 *vbuff);
void genRectMeshInds(int nrows, int ncols, int *ibuff);

#endif

