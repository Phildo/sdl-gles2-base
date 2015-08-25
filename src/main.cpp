#include "defines.h"

#include <stdlib.h>

#include "do_gl.h" //includes SDL as well
#include "do_math.h"
#include "do_mesh.h"
#include "logger.h"

#include "blit_renderer.h"
#include "renderer.h"

int main(int argc, char* argv[])
{
  log_data = new Log(); // ugh

  SDL_Window* window = 0;
  SDL_GLContext gl = 0;
  int win_w;
  int win_h;
  if(initGL(&window, &gl, &win_w, &win_h) == 1) return 1;

  GLuint gl_depth_buff_id;
  GLuint gl_framebuffer_id;

  blit_renderer br; initBlitRenderer(&br);
  renderer r;       initRenderer(&r);

  glGenRenderbuffers(1, &gl_depth_buff_id);
  glBindRenderbuffer(GL_RENDERBUFFER, gl_depth_buff_id);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, br.texture_width, br.texture_height);

  glGenFramebuffers(1, &gl_framebuffer_id);
  glBindFramebuffer(GL_FRAMEBUFFER, gl_framebuffer_id);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, br.gl_texture_buff_id, 0);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, gl_depth_buff_id);

  Uint8 done = 0;
  SDL_Event event;

  while(!done)
  {
    while(SDL_PollEvent(&event))
    {
      if(
        false
        || event.type == SDL_QUIT
        || event.type == SDL_KEYDOWN
      #if DO_PLATFORM == DO_PLATFORM_ANDROID
        || event.type == SDL_FINGERDOWN
      #endif
      )
      {
        done = 1;
      }
    }

    updateRenderer(&r);

    //draw into FB
    glBindFramebuffer(GL_FRAMEBUFFER, gl_framebuffer_id);
    renderRenderer(&r,br.texture_width,br.texture_height);

    //blit FB
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    renderBlitRenderer(&br,win_w,win_h);

    SDL_GL_SwapWindow(window);

    SDL_Delay(10);
  }

  SDL_GL_DeleteContext(gl);
  IMG_Quit();
  SDL_Quit();
  exit(0);
  return 0;
}

