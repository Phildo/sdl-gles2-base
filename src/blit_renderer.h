#ifndef BLIT_RENDERER_H
#define BLIT_RENDERER_H

#include "do_gl.h"

struct blit_renderer
{
  GLuint gl_program_id;

  GLuint gl_position_buff_id;   GLuint gl_position_attrib_id;
  GLuint gl_texture_uv_buff_id; GLuint gl_texture_uv_attrib_id;
  GLuint gl_index_buff_id;
  GLuint gl_texture_buff_id; GLuint gl_texture_unif_id; GLuint gl_texture_active_n;

  int texture_width;
  int texture_height;
};

void initBlitRenderer(blit_renderer *br);
void renderBlitRenderer(blit_renderer *br, int width, int height);

#endif

