#include "renderer.h"

#include "do_math.h"
#include "do_mesh.h"

void initRenderer(renderer *r)
{
  r->nrows = 1;
  r->ncols = 2;
  fv2 *position_buff   = (fv2 *)malloc(sizeof(fv2)*numVertsReqForRectMesh(r->nrows,r->ncols));
  fv3 *color_buff      = (fv3 *)malloc(sizeof(fv3)*numVertsReqForRectMesh(r->nrows,r->ncols));
  fv2 *texture_uv_buff = (fv2 *)malloc(sizeof(fv2)*numVertsReqForRectMesh(r->nrows,r->ncols));
  int *index_buff      = (int *)malloc(sizeof(int)*numIndsReqForRectMesh(r->nrows,r->ncols));
  genfv2RectMeshVerts({ -0.9f, -0.9f }, { 0.9f, 0.9f }, r->nrows, r->ncols, position_buff);
  genfv2RectMeshVerts(    { 0.f, 0.f },   { 1.f, 1.f }, r->nrows, r->ncols, texture_uv_buff);
  genRectMeshInds(r->nrows, r->ncols, index_buff);
  for(int i = 0; i < numVertsReqForRectMesh(r->nrows,r->ncols); i++)
  {
    if(i == 0)
    {
      color_buff[i].x = 1.f;
      color_buff[i].y = 0.f;
      color_buff[i].z = 0.f;
    }
    else if(i == 1)
    {
      color_buff[i].x = 0.f;
      color_buff[i].y = 1.f;
      color_buff[i].z = 0.f;
    }
    else if(i == 2)
    {
      color_buff[i].x = 1.f;
      color_buff[i].y = 1.f;
      color_buff[i].z = 0.f;
    }
    else if(i == 3)
    {
      color_buff[i].x = 0.f;
      color_buff[i].y = 0.f;
      color_buff[i].z = 1.f;
    }
    else if(i == 4)
    {
      color_buff[i].x = 1.f;
      color_buff[i].y = 0.f;
      color_buff[i].z = 1.f;
    }
    else if(i == 5)
    {
      color_buff[i].x = 0.f;
      color_buff[i].y = 1.f;
      color_buff[i].z = 1.f;
    }
    else if(i == 6)
    {
      color_buff[i].x = 1.f;
      color_buff[i].y = 1.f;
      color_buff[i].z = 1.f;
    }
    else
    {
      color_buff[i].x = randf();
      color_buff[i].y = randf();
      color_buff[i].z = randf();
    }
  }

  r->gl_program_id = compileProgram("color3d");
  glUseProgram(r->gl_program_id);
  r->gl_position_attrib_id = glGetAttribLocation(r->gl_program_id, "position");
  r->gl_color_attrib_id = glGetAttribLocation(r->gl_program_id, "color");
  r->gl_texture_uv_attrib_id = glGetAttribLocation(r->gl_program_id, "texture_uv");
  r->gl_model_mat_unif_id = glGetUniformLocation(r->gl_program_id, "model_mat");
  r->gl_model_rot_mat_unif_id = glGetUniformLocation(r->gl_program_id, "model_rot_mat");
  r->gl_view_mat_unif_id = glGetUniformLocation(r->gl_program_id, "view_mat");
  r->gl_proj_mat_unif_id = glGetUniformLocation(r->gl_program_id, "proj_mat");
  r->gl_time_unif_id = glGetUniformLocation(r->gl_program_id, "time");
  r->gl_texture_unif_id = glGetUniformLocation(r->gl_program_id, "texture");

  glGenBuffers(1, &r->gl_position_buff_id);
  glBindBuffer(GL_ARRAY_BUFFER, r->gl_position_buff_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fv2)*numVertsReqForRectMesh(r->nrows,r->ncols), position_buff, GL_STATIC_DRAW);
  glVertexAttribPointer(r->gl_position_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(r->gl_position_attrib_id);

  glGenBuffers(1, &r->gl_color_buff_id);
  glBindBuffer(GL_ARRAY_BUFFER, r->gl_color_buff_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fv3)*numVertsReqForRectMesh(r->nrows,r->ncols), color_buff, GL_STATIC_DRAW);
  glVertexAttribPointer(r->gl_color_attrib_id, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(r->gl_color_attrib_id);

  glGenBuffers(1, &r->gl_texture_uv_buff_id);
  glBindBuffer(GL_ARRAY_BUFFER, r->gl_texture_uv_buff_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fv2)*numVertsReqForRectMesh(r->nrows,r->ncols), texture_uv_buff, GL_STATIC_DRAW);
  glVertexAttribPointer(r->gl_texture_uv_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(r->gl_texture_uv_attrib_id);

  glGenBuffers(1, &r->gl_index_buff_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->gl_index_buff_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*numIndsReqForRectMesh(r->nrows,r->ncols), index_buff, GL_STATIC_DRAW);

  r->gl_texture_active_n = 1;
  glActiveTexture(GL_TEXTURE0+r->gl_texture_active_n);
  glGenTextures(1, &r->gl_texture_buff_id);
  glBindTexture(GL_TEXTURE_2D, r->gl_texture_buff_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  int texture_width = 256;
  int texture_height = 256;
  char *texture_data = (char *)malloc(sizeof(char)*3*texture_width*texture_height);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture_width,texture_height,0,GL_RGB,GL_UNSIGNED_BYTE,texture_data);

  glUniform1i(r->gl_texture_unif_id, r->gl_texture_active_n);


  r->time = 0.0f;
  r->eye = fv3{0.f,0.f,10.f};
  r->up  = fv3{0.f,1.f,0.f};
}

void updateRenderer(renderer *r)
{
  r->time += 0.0001f;
  r->eye = matmulfv3(rotatefm3(r->up,r->time),r->eye);
}

void renderRenderer(renderer *r, int width, int height)
{
  glClearColor(randf(),randf(),randf(),1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(r->gl_program_id);
  glBindBuffer(GL_ARRAY_BUFFER, r->gl_position_buff_id);
  glVertexAttribPointer(r->gl_position_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, r->gl_color_buff_id);
  glVertexAttribPointer(r->gl_color_attrib_id, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, r->gl_texture_uv_buff_id);
  glVertexAttribPointer(r->gl_texture_uv_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->gl_index_buff_id);

  glActiveTexture(GL_TEXTURE0+r->gl_texture_active_n);
  glBindTexture(GL_TEXTURE_2D, r->gl_texture_buff_id);

  glUniform1f(r->gl_time_unif_id,r->time);
  fm4 m;
  m = identityfm4();
  glUniformMatrix4fv(r->gl_model_mat_unif_id, 1, GL_FALSE, &m.x[0]);
  glUniformMatrix4fv(r->gl_model_rot_mat_unif_id, 1, GL_FALSE, &m.x[0]);

  m = lookAtfm4(r->eye, fv3{0.f,0.f,0.f}, r->up);
  glUniformMatrix4fv(r->gl_view_mat_unif_id, 1, GL_FALSE, &m.x[0]);
  m = perspectivefm4(20.f, 1.f, 1.f, 100.f);
  glUniformMatrix4fv(r->gl_proj_mat_unif_id, 1, GL_FALSE, &m.x[0]);

  glViewport(0,0,width,height);
  glDrawElements(GL_TRIANGLES, numIndsReqForRectMesh(r->nrows,r->ncols), GL_UNSIGNED_INT, (void*)0);
}

