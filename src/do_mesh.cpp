#include "do_mesh.h"

int numVertsReqForRectMesh(int nrows, int ncols)
{
  return (nrows+1)*(ncols+1);
}
int numIndsReqForRectMesh(int nrows, int ncols)
{
  return (nrows*ncols*2*3);
}
void genfv2RectMeshVerts(fv2 a, fv2 b, int nrows, int ncols, fv2 *vbuff)
{
  int nvcols = ncols+1;
  int nvrows = nrows+1;

  for(int i = 0; i < nvrows; i++)
    for(int j = 0; j < nvcols; j++)
      vbuff[(i*nvcols)+j] = fv2{ lerpf(a.x,b.x,(1.0f/ncols)*j), lerpf(a.x,b.x,(1.0f/nrows)*i) };
}
void genRectMeshInds(int nrows, int ncols, int *ibuff)
{
  int nvcols = ncols+1;
  //int nvrows = nrows+1; //unused

  for(int i = 0; i < nrows; i++)
  {
    for(int j = 0; j < ncols; j++)
    {
      //                               y            x
      ibuff[(((i*ncols)+j)*6)+0] = ((i+0)*nvcols)+(j+0);
      ibuff[(((i*ncols)+j)*6)+1] = ((i+0)*nvcols)+(j+1);
      ibuff[(((i*ncols)+j)*6)+2] = ((i+1)*nvcols)+(j+0);
      ibuff[(((i*ncols)+j)*6)+3] = ((i+1)*nvcols)+(j+0);
      ibuff[(((i*ncols)+j)*6)+4] = ((i+0)*nvcols)+(j+1);
      ibuff[(((i*ncols)+j)*6)+5] = ((i+1)*nvcols)+(j+1);
    }
  }
}

