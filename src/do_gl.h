#ifndef DO_GL_H
#define DO_GL_H

#include <SDL.h>
#include <SDL_image.h>

#if DO_PLATFORM == DO_PLATFORM_MAC
#include "GL/glew.h"
#include <SDL_opengl.h>
#elif DO_PLATFORM == DO_PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

GLuint compileProgram(const char * program_file_name);
int initGL(SDL_Window **win_p, SDL_GLContext *gl_p, int *win_w, int *win_h);

#endif

