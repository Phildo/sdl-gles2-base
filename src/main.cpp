#include "defines.h"

#include <stdlib.h>

#include <SDL.h>
#include "SDL_image.h"

#include <SDL_opengl.h>

#include "logger.h"

int main(int argc, char* argv[])
{
  log_data = new Log(); // ugh

  SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  IMG_Init(IMG_INIT_PNG);

  SDL_version compiled;
  SDL_VERSION(&compiled);
  printf("SDL Compiled Version:  %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch);

  SDL_version linked;
  SDL_GetVersion(&linked);
  printf("SDL Linked Version:    %d.%d.%d\n", linked.major, linked.minor, linked.patch);

  #if DO_PLATFORM == DO_PLATFORM_MAC
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  #elif DO_PLATFORM == DO_PLATFORM_ANDROID
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  #endif
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

  SDL_DisplayMode mode;
  SDL_GetDisplayMode(0,0,&mode);
  do_log("Width = %d, Height = %d.",mode.w,mode.h);

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);

  SDL_Window* window = 0;
  #if DO_PLATFORM == DO_PLATFORM_MAC
  window = SDL_CreateWindow("Fish", 0,0,1024,512, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI); //Have to explicitly allow HIGHDPI in Info.plist!
  #elif DO_PLATFORM == DO_PLATFORM_ANDROID
  window = SDL_CreateWindow("Fish", 0,0,mode.w,mode.h, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI);
  #endif
  if(window == 0)
  {
    do_log("Failed to create window.");
    SDL_Quit();
    return 1;
  }

  SDL_GLContext gl = 0;
  gl = SDL_GL_CreateContext(window);
  if(!gl)
  {
    do_log("Failed to init context:%s",SDL_GetError());
    SDL_Quit();
    return 1;
  }

  Uint8 done = 0;
  SDL_Event event;
  while(!done)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN)
      {
        done = 1;
      }
    }

    glClearColor((rand()%256)/256.0f,(rand()%256)/256.0f,(rand()%256)/256.0f,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    SDL_GL_SwapWindow(window);
    SDL_Delay(10);
  }

  SDL_GL_DeleteContext(gl);
  IMG_Quit();
  SDL_Quit();
  exit(0);
  return 0;
}

