#include "defines.h"

#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

#if DO_PLATFORM == DO_PLATFORM_MAC
#include <SDL_opengl.h>
#elif DO_PLATFORM == DO_PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include "do_math.h"
#include "logger.h"

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

GLuint compileProgram(const char * vs_file_name, const char * fs_file_name)
{
  SDL_RWops *io;
  char vs_file[2048];
  char fs_file[2048];
  char *vs_file_p = &vs_file[0];
  char *fs_file_p = &fs_file[0];

  GLuint gl_vs_id;
  GLuint gl_fs_id;
  GLuint gl_program_id;

  io = SDL_RWFromFile(vs_file_name,"r");
  if(!io)
  {
    do_log("Can't find/open file:%s\n%s",vs_file_name,SDL_GetError());
    return 0;
  }
  vs_file[(int)SDL_RWread(io, vs_file, 1, sizeof(vs_file))] = '\0';
  SDL_RWclose(io);

  io = SDL_RWFromFile(fs_file_name,"r");
  if(!io)
  {
    do_log("Can't find/open file:%s\n%s",fs_file_name,SDL_GetError());
    return 0;
  }
  fs_file[(int)SDL_RWread(io, fs_file, 1, sizeof(fs_file))] = '\0';
  SDL_RWclose(io);

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
    do_log("Error compiling VS:%s\n%s",vs_file_name,vs_file);
    SDL_Quit();
    return 0;
  }

  glGetShaderiv(gl_fs_id, GL_COMPILE_STATUS, &err);
  if(err == GL_FALSE)
  {
    int l;
    glGetShaderInfoLog(gl_fs_id, 2048, &l, fs_file_p);
    do_log("Error compiling FS:%s\n%s",fs_file_name,fs_file);
    return 0;
  }

  gl_program_id = glCreateProgram();
  glAttachShader(gl_program_id, gl_vs_id);
  glAttachShader(gl_program_id, gl_fs_id);
  glLinkProgram(gl_program_id);

  glGetProgramiv(gl_fs_id, GL_LINK_STATUS, &err);
  if(err == GL_FALSE)
  {
    do_log("Error linking VS & FS : %s & %s",vs_file_name,fs_file_name);
    return 0;
  }

  glDeleteShader(gl_vs_id);
  glDeleteShader(gl_fs_id);

  return gl_program_id;
}

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

  #if DO_PLATFORM == DO_PLATFORM_MAC
  int win_w = 1024;
  int win_h = 512;
  #elif DO_PLATFORM == DO_PLATFORM_ANDROID
  int win_w = mode.w;
  int win_h = mode.h;
  #endif

  SDL_Window* window = 0;
  #if DO_PLATFORM == DO_PLATFORM_MAC
  window = SDL_CreateWindow("Fish", 0,0,win_w,win_h, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI); //Have to explicitly allow HIGHDPI in Info.plist!
  #elif DO_PLATFORM == DO_PLATFORM_ANDROID
  window = SDL_CreateWindow("Fish", 0,0,win_w,win_h, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI);
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

  do_log("GL Renderer: %s", glGetString(GL_RENDERER));
  do_log("GL Version: %s", glGetString(GL_VERSION));

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glViewport(0, 0, win_w, win_h);

  //GLuint gl_fb_id;
  GLuint gl_program_id;
  GLuint gl_position_buff_id;
  GLuint gl_color_buff_id;
  GLuint gl_texture_uv_buff_id;
  GLuint gl_index_buff_id;
  GLuint gl_texture_buff_id;
  GLuint gl_position_attrib_id;
  GLuint gl_color_attrib_id;
  GLuint gl_texture_uv_attrib_id;
  GLuint gl_time_unif_id;
  GLuint gl_texture_unif_id;

  #if DO_PLATFORM == DO_PLATFORM_ANDROID
  gl_program_id = compileProgram("shaders/texture2d.vert", "shaders/texture2d.frag");
  #else
  gl_program_id = compileProgram("../assets/shaders/texture2d.vert", "../assets/shaders/texture2d.frag");
  #endif
  if(!gl_program_id)
  {
    SDL_Quit();
    return 0;
  }
  glUseProgram(gl_program_id);
  gl_position_attrib_id = glGetAttribLocation(gl_program_id, "position");
  gl_color_attrib_id = glGetAttribLocation(gl_program_id, "color");
  gl_texture_uv_attrib_id = glGetAttribLocation(gl_program_id, "texture_uv");
  gl_time_unif_id = glGetUniformLocation(gl_program_id, "time");
  gl_texture_unif_id = glGetUniformLocation(gl_program_id, "texture");

  int nrows = 2;
  int ncols = 2;
  fv2 *position_buff   = (fv2 *)malloc(sizeof(fv2)*numVertsReqForRectMesh(nrows,ncols));
  fv3 *color_buff      = (fv3 *)malloc(sizeof(fv3)*numVertsReqForRectMesh(nrows,ncols));
  fv2 *texture_uv_buff = (fv2 *)malloc(sizeof(fv2)*numVertsReqForRectMesh(nrows,ncols));
  int *index_buff      = (int *)malloc(sizeof(int)*numIndsReqForRectMesh(nrows,ncols));
  fv2 a = { -0.9f, -0.9f };
  fv2 b = {  0.9f,  0.9f };
  genfv2RectMeshVerts(a, b, nrows, ncols, position_buff);
  a = { 0.f, 0.f };
  b = { 1.f, 1.f };
  genfv2RectMeshVerts(a, b, nrows, ncols, texture_uv_buff);
  genRectMeshInds(nrows, ncols, index_buff);
  for(int i = 0; i < numVertsReqForRectMesh(nrows,ncols); i++)
  {
    color_buff[i].x = randf();
    color_buff[i].y = randf();
    color_buff[i].z = randf();
  }

  glGenBuffers(1, &gl_position_buff_id);
  glBindBuffer(GL_ARRAY_BUFFER, gl_position_buff_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fv2)*numVertsReqForRectMesh(nrows,ncols), position_buff, GL_STATIC_DRAW);
  glVertexAttribPointer(gl_position_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(gl_position_attrib_id);

  glGenBuffers(1, &gl_color_buff_id);
  glBindBuffer(GL_ARRAY_BUFFER, gl_color_buff_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fv3)*numVertsReqForRectMesh(nrows,ncols), color_buff, GL_STATIC_DRAW);
  glVertexAttribPointer(gl_color_attrib_id, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(gl_color_attrib_id);

  glGenBuffers(1, &gl_texture_uv_buff_id);
  glBindBuffer(GL_ARRAY_BUFFER, gl_texture_uv_buff_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fv2)*numVertsReqForRectMesh(nrows,ncols), texture_uv_buff, GL_STATIC_DRAW);
  glVertexAttribPointer(gl_texture_uv_attrib_id, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(gl_texture_uv_attrib_id);

  glGenBuffers(1, &gl_index_buff_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_index_buff_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*numIndsReqForRectMesh(nrows,ncols), index_buff, GL_STATIC_DRAW);

  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &gl_texture_buff_id);
  glBindTexture(GL_TEXTURE_2D, gl_texture_buff_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  int texture_width = 256;
  int texture_height = 256;
  char *texture_data = (char *)malloc(sizeof(char)*3*texture_width*texture_height);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture_width,texture_height,0,GL_RGB,GL_UNSIGNED_BYTE,texture_data);

  glUniform1i(gl_texture_unif_id, 0);

  glViewport(0,0,win_w,win_h);
  glClearColor(randf(),randf(),randf(),1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glDrawElements(GL_TRIANGLES, numIndsReqForRectMesh(nrows,ncols), GL_UNSIGNED_INT, (void*)0);

  SDL_GL_SwapWindow(window);

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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniform1f(gl_time_unif_id,randf());
    glDrawElements(GL_TRIANGLES, numIndsReqForRectMesh(nrows,ncols), GL_UNSIGNED_INT, (void*)0);
    SDL_GL_SwapWindow(window);

    SDL_Delay(10);
  }

  SDL_GL_DeleteContext(gl);
  IMG_Quit();
  SDL_Quit();
  exit(0);
  return 0;
}

