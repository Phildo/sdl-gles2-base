#ifndef RENDERER_H
#define RENDERER_H

#include "do_gl.h"
#include "do_math.h"

struct renderer
{
  GLuint gl_program_id;

  GLuint gl_position_buff_id;   GLuint gl_position_attrib_id;
  GLuint gl_color_buff_id;      GLuint gl_color_attrib_id;
  GLuint gl_texture_uv_buff_id; GLuint gl_texture_uv_attrib_id;
  GLuint gl_index_buff_id;
  GLuint gl_texture_buff_id;    GLuint gl_texture_unif_id;      GLuint gl_texture_active_n;
  GLuint gl_model_mat_unif_id;
  GLuint gl_model_rot_mat_unif_id;
  GLuint gl_view_mat_unif_id;
  GLuint gl_proj_mat_unif_id;
  GLuint gl_time_unif_id;

  int nrows;
  int ncols;
  float time;
  fv3 eye;
  fv3 up;
};

void initRenderer(renderer *r);
void updateRenderer(renderer *r);
void renderRenderer(renderer *r, int width, int height);

#endif

