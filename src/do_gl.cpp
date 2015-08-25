#include "do_gl.h"

#include "logger.h"

GLuint compileProgram(const char * program_file_name)
{
  //holy jank
  char *vs_file_name = (char *)malloc(500);
  char *fs_file_name = (char *)malloc(500);

  int write_ind_a = 0;
  int write_ind_b = 0;
  #if DO_PLATFORM == DO_PLATFORM_ANDROID
  const char *prefix = "shaders/";
  #else
  const char *prefix = "../assets/shaders/";
  #endif
  const char *vpostfix = ".vert";
  const char *fpostfix = ".frag";

  write_ind_b = 0;
  while(prefix[write_ind_b] != '\0')
  {
    vs_file_name[write_ind_a] = prefix[write_ind_b];
    fs_file_name[write_ind_a] = prefix[write_ind_b];
    write_ind_a++;
    write_ind_b++;
  }
  write_ind_b = 0;
  while(program_file_name[write_ind_b] != '\0')
  {
    vs_file_name[write_ind_a] = program_file_name[write_ind_b];
    fs_file_name[write_ind_a] = program_file_name[write_ind_b];
    write_ind_a++;
    write_ind_b++;
  }
  write_ind_b = 0;
  while(vpostfix[write_ind_b] != '\0')
  {
    vs_file_name[write_ind_a] = vpostfix[write_ind_b];
    fs_file_name[write_ind_a] = fpostfix[write_ind_b];
    write_ind_a++;
    write_ind_b++;
  }
  vs_file_name[write_ind_a] = '\0';
  fs_file_name[write_ind_a] = '\0';

  do_log("compiling %s and %s...",vs_file_name,fs_file_name);

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

  glGetProgramiv(gl_program_id, GL_LINK_STATUS, &err);
  if(err == GL_FALSE)
  {
    do_log("Error linking VS & FS : %s & %s",vs_file_name,fs_file_name);
    return 0;
  }

  if(!gl_program_id)
  {
    do_log("Program compiled and linked, but still invalid.");
    return 0;
  }

  glDeleteShader(gl_vs_id);
  glDeleteShader(gl_fs_id);

  return gl_program_id;
}

int initGL(SDL_Window **win_p, SDL_GLContext *gl_p, int *win_w, int *win_h)
{
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
  *win_w = 1024;
  *win_h = 512;
  #elif DO_PLATFORM == DO_PLATFORM_ANDROID
  *win_w = mode.w;
  *win_h = mode.h;
  #endif

  #if DO_PLATFORM == DO_PLATFORM_MAC
  *win_p = SDL_CreateWindow("Fish", 0,0,*win_w,*win_h, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI); //Have to explicitly allow HIGHDPI in Info.plist!
  #elif DO_PLATFORM == DO_PLATFORM_ANDROID
  *win_p = SDL_CreateWindow("Fish", 0,0,*win_w,*win_h, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI);
  #endif
  if(*win_p == 0)
  {
    do_log("Failed to create window.");
    SDL_Quit();
    return 1;
  }

  *gl_p = SDL_GL_CreateContext(*win_p);
  if(!*gl_p)
  {
    do_log("Failed to init context:%s",SDL_GetError());
    SDL_Quit();
    return 1;
  }

  #if DO_PLATFORM != DO_PLATFORM_ANDROID
  GLenum err = glewInit();
  if(err != GLEW_OK)
  {
    do_log("Failed to init glew:%s",glewGetErrorString(err));
    SDL_Quit();
    return 1;
  }

  if(!GLEW_ARB_framebuffer_object)
  {
    do_log("Framebuffer ARB extension not available");
    SDL_Quit();
    return 1;
  }
  #endif

  do_log("GL Renderer: %s", glGetString(GL_RENDERER));
  do_log("GL Version: %s", glGetString(GL_VERSION));

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_BACK);
  glEnable(GL_TEXTURE_2D);

  return 0;
}

void checkGLErrorMark(const char *c)
{
  do_log("checking %s",c);
  checkGLError();
}

void checkGLError()
{
  GLenum e = glGetError();
  switch(e)
  {
    case GL_NO_ERROR:
      do_log("None"); break;
    case GL_INVALID_ENUM:
      do_log("An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag."); break;
    case GL_INVALID_VALUE:
      do_log("A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag."); break;
    case GL_INVALID_OPERATION:
      do_log("The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag."); break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      do_log("The command is trying to render to or read from the framebuffer while the currently bound framebuffer is not framebuffer complete (i.e. the return value from glCheckFramebufferStatus is not GL_FRAMEBUFFER_COMPLETE). The offending command is ignored and has no other side effect than to set the error flag."); break;
    case GL_OUT_OF_MEMORY:
      do_log("There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded."); break;
  }
}

void checkGLFramebufferError()
{
  GLenum e = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  switch(e)
  {
    case GL_FRAMEBUFFER_COMPLETE:
      do_log("complete!"); break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
      do_log("Not all framebuffer attachment points are framebuffer attachment complete. This means that at least one attachment point with a renderbuffer or texture attached has its attached object no longer in existence or has an attached image with a width or height of zero, or the color attachment point has a non-color-renderable image attached, or the depth attachment point has a non-depth-renderable image attached, or the stencil attachment point has a non-stencil-renderable image attached."); break;
              //Color-renderable formats include GL_RGBA4, GL_RGB5_A1, and GL_RGB565. GL_DEPTH_COMPONENT16 is the only depth-renderable format. GL_STENCIL_INDEX8 is the only stencil-renderable format.
    //case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
      //do_log("Not all attached images have the same width and height."); break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
      do_log("No images are attached to the framebuffer."); break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
      do_log("unsupported..."); break;
  }
}

