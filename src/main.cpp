#include "defines.h"

#include <stdlib.h>

#include <SDL.h>
#include "SDL_image.h"

#if DO_PLATFORM == DO_PLATFORM_MAC
#include <OpenGL/gl.h>
#elif DO_PLATFORM == DO_PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include "logger.h"

int main(int argc, char* argv[])
{
  log_data = new Log(); // ugh

  SDL_Window* window = 0;
  SDL_GLContext gl = 0;

  SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  IMG_Init(IMG_INIT_PNG);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

  SDL_DisplayMode mode;
  SDL_GetDisplayMode(0,0,&mode);
  int width = mode.w;
  int height = mode.h;

  do_log("Width = %d, Height = %d.",width,height);

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

  window = SDL_CreateWindow(NULL,0,0,width,height,SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE);

  if(window == 0)
  {
    do_log("Failed to create window.");
    SDL_Quit();
    return 1;
  }

  gl = SDL_GL_CreateContext(window);

  Uint8 done = 0;
  SDL_Event event;
  int count = 0;
  while(!done)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN)
      {
        done = 1;
      }
    }

    do_log("%d",count++);

    glClearColor((rand()%256)/256.0f,(rand()%256)/256.0f,(rand()%256)/256.0f,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    SDL_GL_SwapWindow(window);
    SDL_Delay(10);
  }

  IMG_Quit();
  SDL_Quit();
  exit(0);
  return 0;
}

