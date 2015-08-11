#include "defines.h"

#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>
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
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
  #elif DO_PLATFORM == DO_PLATFORM_ANDROID
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  #endif
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

  SDL_DisplayMode mode;
  SDL_GetDisplayMode(0,0,&mode);
  do_log("Width = %d, Height = %d.",mode.w,mode.h);

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

  do_log("GL Renderer: %s", glGetString(GL_RENDERER), glGetString(GL_VERSION));
  do_log("GL Version: %s", glGetString(GL_VERSION));

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  //GLuint gl_fb_id;
  GLuint gl_program_id;
  GLuint gl_vs_id;
  GLuint gl_fs_id;
  GLuint gl_pos_attrib_id;
  GLuint gl_pos_buff_id;


  char vs_file[2048];
  char *vs_file_p = &vs_file[0];
  char fs_file[2048];
  char *fs_file_p = &fs_file[0];

  FILE *fp;
  int i,c;

  fp = fopen("../src/shaders/white2d.vert", "r");
  if(!fp)
  {
    do_log("Can't find/open file:%s","../src/shaders/white2d.vert");
    SDL_Quit();
    return 1;
  }
  c = 0; for(i = 0; i < 2048 && c != EOF; i++) { c = fgetc(fp); if(c != EOF) vs_file[i] = (char)c; else vs_file[i] = '\0'; }

  fp = fopen("../src/shaders/white2d.frag", "r");
  if(!fp)
  {
    do_log("Can't find/open file:%s","../src/shaders/white2d.frag");
    SDL_Quit();
    return 1;
  }
  c = 0; for(i = 0; i < 2048 && c != EOF; i++) { c = fgetc(fp); if(c != EOF) fs_file[i] = (char)c; else fs_file[i] = '\0'; }

  gl_vs_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(gl_vs_id, 1, &vs_file_p, NULL);
  glCompileShader(gl_vs_id);

  gl_fs_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(gl_fs_id, 1, &fs_file_p, NULL);
  glCompileShader(gl_fs_id);

  GLint err;
  glGetShaderiv(gl_vs_id, GL_COMPILE_STATUS, &err);
  if(err == GL_FALSE)
  {
    int l;
    glGetShaderInfoLog(gl_vs_id, 2048, &l, vs_file_p);
    do_log("Error compiling VS:%s\n%s","../src/shaders/white2d.vert",vs_file);
    SDL_Quit();
    return 1;
  }

  glGetShaderiv(gl_fs_id, GL_COMPILE_STATUS, &err);
  if(err == GL_FALSE)
  {
    int l;
    glGetShaderInfoLog(gl_fs_id, 2048, &l, fs_file_p);
    do_log("Error compiling FS:%s\n%s","../src/shaders/white2d.frag",fs_file);
    SDL_Quit();
    return 1;
  }

  gl_program_id = glCreateProgram();
  glAttachShader(gl_program_id, gl_vs_id);
  glAttachShader(gl_program_id, gl_fs_id);
  glLinkProgram(gl_program_id);

  glGetProgramiv(gl_fs_id, GL_LINK_STATUS, &err);
  if(err == GL_FALSE)
  {
    do_log("Error linking VS & FS : %s & %s","../src/shaders/white2d.vert","../src/shaders/white2d.frag");
    SDL_Quit();
    return 1;
  }

  glDeleteShader(gl_vs_id);
  glDeleteShader(gl_fs_id);

  glUseProgram(gl_program_id);

  gl_pos_attrib_id = glGetAttribLocation(gl_program_id, "position");

  //pos buff
  float verts[] = {0.0,0.0,0.5,1.0,1.0,0.0};
  glGenBuffers(1, &gl_pos_buff_id);
  glBindBuffer(GL_ARRAY_BUFFER, gl_pos_buff_id);
  glVertexAttribPointer(gl_pos_attrib_id, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(gl_pos_attrib_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*2*3, verts, GL_STATIC_DRAW);

  //glGenFramebuffers(1, &gl_fb_id);
  //glBindFramebuffer(GL_FRAMEBUFFER, gl_fb_id);

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

    //glClearColor((rand()%256)/256.0f,(rand()%256)/256.0f,(rand()%256)/256.0f,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glDrawArrays(GL_TRIANGLES,0,3*3);

    SDL_GL_SwapWindow(window);
    SDL_Delay(10);
  }

  SDL_GL_DeleteContext(gl);
  IMG_Quit();
  SDL_Quit();
  exit(0);
  return 0;
}

