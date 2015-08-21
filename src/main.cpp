#include "defines.h"

#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

#if DO_PLATFORM == DO_PLATFORM_MAC
#include "GL/glew.h"
#include <SDL_opengl.h>
#elif DO_PLATFORM == DO_PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include "do_math.h"
#include "logger.h"

#include "mesh.h"
#include "do_gl.h"

int main(int argc, char* argv[])
{
  log_data = new Log(); // ugh

  SDL_Window* window = 0;
  SDL_GLContext gl = 0;
  int win_w;
  int win_h;
  if(initGL(&window, &gl, &win_w, &win_h) == 1) return 1; //in do_gl


  fv2 *qblit_position_buff   = (fv2 *)malloc(sizeof(fv2)*numVertsReqForRectMesh(1,1));
  fv2 *qblit_texture_uv_buff = (fv2 *)malloc(sizeof(fv2)*numVertsReqForRectMesh(1,1));
  int *qblit_index_buff      = (int *)malloc(sizeof(int)*numIndsReqForRectMesh(1,1));
  genfv2RectMeshVerts({ -1.f, -1.f }, { 1.f, 1.f }, 1, 1, qblit_position_buff);
  genfv2RectMeshVerts(  { 0.f, 0.f }, { 1.f, 1.f }, 1, 1, qblit_texture_uv_buff);
  genRectMeshInds(1, 1, qblit_index_buff);

  GLuint gl_qblit_program_id;

  GLuint gl_qblit_position_buff_id;   GLuint gl_qblit_position_attrib_id;
  GLuint gl_qblit_texture_uv_buff_id; GLuint gl_qblit_texture_uv_attrib_id;
  GLuint gl_qblit_index_buff_id;
  GLuint gl_qblit_texture_buff_id;    GLuint gl_qblit_texture_unif_id;      GLuint gl_qblit_texture_active_n;

  gl_qblit_program_id = compileProgram("texture2d");
  glUseProgram(gl_qblit_program_id);
  gl_qblit_position_attrib_id = glGetAttribLocation(gl_qblit_program_id, "position");
  gl_qblit_texture_uv_attrib_id = glGetAttribLocation(gl_qblit_program_id, "texture_uv");
  gl_qblit_texture_unif_id = glGetUniformLocation(gl_qblit_program_id, "texture");

  glGenBuffers(1, &gl_qblit_position_buff_id);
  glBindBuffer(GL_ARRAY_BUFFER, gl_qblit_position_buff_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fv2)*numVertsReqForRectMesh(1,1), qblit_position_buff, GL_STATIC_DRAW);
  glVertexAttribPointer(gl_qblit_position_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(gl_qblit_position_attrib_id);

  glGenBuffers(1, &gl_qblit_texture_uv_buff_id);
  glBindBuffer(GL_ARRAY_BUFFER, gl_qblit_texture_uv_buff_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fv2)*numVertsReqForRectMesh(1,1), qblit_texture_uv_buff, GL_STATIC_DRAW);
  glVertexAttribPointer(gl_qblit_texture_uv_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(gl_qblit_texture_uv_attrib_id);

  glGenBuffers(1, &gl_qblit_index_buff_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_qblit_index_buff_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*numIndsReqForRectMesh(1,1), qblit_index_buff, GL_STATIC_DRAW);

  gl_qblit_texture_active_n = 0;
  glActiveTexture(GL_TEXTURE0+gl_qblit_texture_active_n);
  glGenTextures(1, &gl_qblit_texture_buff_id);
  glBindTexture(GL_TEXTURE_2D, gl_qblit_texture_buff_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  int qblit_texture_width = 32;
  int qblit_texture_height = 32;
  char *qblit_texture_data = (char *)malloc(sizeof(char)*3*qblit_texture_width*qblit_texture_height);
  //char *qblit_texture_data = NULL;
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,qblit_texture_width,qblit_texture_height,0,GL_RGB,GL_UNSIGNED_BYTE,qblit_texture_data);

  glUniform1i(gl_qblit_texture_unif_id, gl_qblit_texture_active_n);

  int nrows = 1;
  int ncols = 2;
  fv2 *position_buff   = (fv2 *)malloc(sizeof(fv2)*numVertsReqForRectMesh(nrows,ncols));
  fv3 *color_buff      = (fv3 *)malloc(sizeof(fv3)*numVertsReqForRectMesh(nrows,ncols));
  fv2 *texture_uv_buff = (fv2 *)malloc(sizeof(fv2)*numVertsReqForRectMesh(nrows,ncols));
  int *index_buff      = (int *)malloc(sizeof(int)*numIndsReqForRectMesh(nrows,ncols));
  genfv2RectMeshVerts({ -0.9f, -0.9f }, { 0.9f, 0.9f }, nrows, ncols, position_buff);
  genfv2RectMeshVerts(    { 0.f, 0.f },   { 1.f, 1.f }, nrows, ncols, texture_uv_buff);
  genRectMeshInds(nrows, ncols, index_buff);
  for(int i = 0; i < numVertsReqForRectMesh(nrows,ncols); i++)
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

  GLuint gl_framebuffer_id;
  GLuint gl_program_id;

  GLuint gl_position_buff_id;   GLuint gl_position_attrib_id;
  GLuint gl_color_buff_id;      GLuint gl_color_attrib_id;
  GLuint gl_texture_uv_buff_id; GLuint gl_texture_uv_attrib_id;
  GLuint gl_index_buff_id;
  GLuint gl_texture_buff_id;    GLuint gl_texture_unif_id;      GLuint gl_texture_active_n;
  GLuint gl_time_unif_id;

  glGenFramebuffers(1, &gl_framebuffer_id);
  glBindFramebuffer(GL_FRAMEBUFFER, gl_framebuffer_id);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gl_qblit_texture_buff_id, 0);

  gl_program_id = compileProgram("color2d");
  glUseProgram(gl_program_id);
  gl_position_attrib_id = glGetAttribLocation(gl_program_id, "position");
  gl_color_attrib_id = glGetAttribLocation(gl_program_id, "color");
  gl_texture_uv_attrib_id = glGetAttribLocation(gl_program_id, "texture_uv");
  gl_time_unif_id = glGetUniformLocation(gl_program_id, "time");
  gl_texture_unif_id = glGetUniformLocation(gl_program_id, "texture");

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
  glVertexAttribPointer(gl_texture_uv_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(gl_texture_uv_attrib_id);

  glGenBuffers(1, &gl_index_buff_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_index_buff_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*numIndsReqForRectMesh(nrows,ncols), index_buff, GL_STATIC_DRAW);

  gl_texture_active_n = 1;
  glActiveTexture(GL_TEXTURE0+gl_texture_active_n);
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

  glUniform1i(gl_texture_unif_id, gl_texture_active_n);

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

    //draw into FB
    glBindFramebuffer(GL_FRAMEBUFFER, gl_framebuffer_id);

    glClearColor(randf(),randf(),randf(),1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(gl_program_id);
    glBindBuffer(GL_ARRAY_BUFFER, gl_position_buff_id);
    glVertexAttribPointer(gl_position_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, gl_color_buff_id);
    glVertexAttribPointer(gl_color_attrib_id, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, gl_texture_uv_buff_id);
    glVertexAttribPointer(gl_texture_uv_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_index_buff_id);

    glActiveTexture(GL_TEXTURE0+gl_texture_active_n);
    glBindTexture(GL_TEXTURE_2D, gl_texture_buff_id);

    glUniform1f(gl_time_unif_id,randf());

    glViewport(0,0,qblit_texture_width,qblit_texture_height);
    glDrawElements(GL_TRIANGLES, numIndsReqForRectMesh(nrows,ncols), GL_UNSIGNED_INT, (void*)0);



    //blit FB
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(gl_qblit_program_id);

    glBindBuffer(GL_ARRAY_BUFFER, gl_qblit_position_buff_id);
    glVertexAttribPointer(gl_qblit_position_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, gl_qblit_texture_uv_buff_id);
    glVertexAttribPointer(gl_qblit_texture_uv_attrib_id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_qblit_index_buff_id);

    glActiveTexture(GL_TEXTURE0+gl_qblit_texture_active_n);
    glBindTexture(GL_TEXTURE_2D, gl_qblit_texture_buff_id);

    glViewport(0,0,win_w,win_h);
    glDrawElements(GL_TRIANGLES, numIndsReqForRectMesh(1,1), GL_UNSIGNED_INT, (void*)0);

    SDL_GL_SwapWindow(window);

    SDL_Delay(10);
  }

  SDL_GL_DeleteContext(gl);
  IMG_Quit();
  SDL_Quit();
  exit(0);
  return 0;
}

