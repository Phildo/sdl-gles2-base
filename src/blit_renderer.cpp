#include "blit_renderer.h"

#include "do_math.h"
#include "do_mesh.h"

void initBlitRenderer(blit_renderer *br)
{
  //      2   4   8  16  32  64 128 256 512 1024 2048
  int n = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2;// * 2 *  2 *  2;
  br->texture_width = n;
  br->texture_height = n;

  //fill in-mem buffs
  fv2 *position_buff   = (fv2 *)malloc(sizeof(fv2)*numVertsReqForRectMesh(1,1));
  fv2 *texture_uv_buff = (fv2 *)malloc(sizeof(fv2)*numVertsReqForRectMesh(1,1));
  int *index_buff      = (int *)malloc(sizeof(int)*numIndsReqForRectMesh(1,1));
  genfv2RectMeshVerts({ -1.f, -1.f }, { 1.f, 1.f }, 1, 1, position_buff);
  genfv2RectMeshVerts(  { 0.f, 0.f }, { 1.f, 1.f }, 1, 1, texture_uv_buff);
  genRectMeshInds(1, 1, index_buff);

  br->gl_program_id = compileProgram("texture2d");
  glUseProgram(br->gl_program_id);
  br->gl_position_attrib_id = glGetAttribLocation(br->gl_program_id, "position");
  br->gl_texture_uv_attrib_id = glGetAttribLocation(br->gl_program_id, "texture_uv");
  br->gl_texture_unif_id = glGetUniformLocation(br->gl_program_id, "texture");

  glGenBuffers(1, &br->gl_position_buff_id);
  glBindBuffer(GL_ARRAY_BUFFER, br->gl_position_buff_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fv2)*numVertsReqForRectMesh(1,1), position_buff, GL_STATIC_DRAW);
  glVertexAttribPointer(br->gl_position_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(br->gl_position_attrib_id);

  glGenBuffers(1, &br->gl_texture_uv_buff_id);
  glBindBuffer(GL_ARRAY_BUFFER, br->gl_texture_uv_buff_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fv2)*numVertsReqForRectMesh(1,1), texture_uv_buff, GL_STATIC_DRAW);
  glVertexAttribPointer(br->gl_texture_uv_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(br->gl_texture_uv_attrib_id);

  glGenBuffers(1, &br->gl_index_buff_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, br->gl_index_buff_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*numIndsReqForRectMesh(1,1), index_buff, GL_STATIC_DRAW);

  br->gl_texture_active_n = 0;
  glActiveTexture(GL_TEXTURE0+br->gl_texture_active_n);
  glGenTextures(1, &br->gl_texture_buff_id);
  glBindTexture(GL_TEXTURE_2D, br->gl_texture_buff_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  char *texture_data = (char *)malloc(sizeof(char)*3*br->texture_width*br->texture_height);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,br->texture_width,br->texture_height,0,GL_RGB,GL_UNSIGNED_BYTE,texture_data);

  glUniform1i(br->gl_texture_unif_id, br->gl_texture_active_n);

  free(position_buff);
  free(texture_uv_buff);
  free(index_buff);
}

void renderBlitRenderer(blit_renderer *br, int width, int height)
{
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(br->gl_program_id);

  glBindBuffer(GL_ARRAY_BUFFER, br->gl_position_buff_id);
  glVertexAttribPointer(br->gl_position_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, br->gl_texture_uv_buff_id);
  glVertexAttribPointer(br->gl_texture_uv_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, br->gl_index_buff_id);

  glActiveTexture(GL_TEXTURE0+br->gl_texture_active_n);
  glBindTexture(GL_TEXTURE_2D, br->gl_texture_buff_id);

  glViewport(0,0,width,height);
  glDrawElements(GL_TRIANGLES, numIndsReqForRectMesh(1,1), GL_UNSIGNED_INT, (void*)0);
}

