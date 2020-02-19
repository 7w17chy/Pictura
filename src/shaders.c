#include <GL/gl.h>
#include <stdio.h>

#include "shaders.h"

int compileShader(unsigned int type, char source[])
{
  unsigned int id = glCreateShader(type);
  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);

  int result;
  // i: integer, v: it wants a pointer
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE)
  {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    printf("ERROR: Shader did not compile successfully!\nError code: %s", message);
    glDeleteShader(id);
    return -1;
  }

  return id;
}

void createShader(Shader *shader, char vertexShader[], char fragmentShader[])
{
  shader->handle = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(shader->handle, vs);
  glAttachShader(shader->handle, fs);
  glLinkProgram(shader->handle);
  glValidateProgram(shader->handle);

  // can be deleted, because they have been linked and put into one program, 'program'
  glDeleteShader(vs);
  glDeleteShader(fs);
}

void bindShader(Shader *shader)
{
  glUseProgram(shader->handle);
}

void deleteShaderProgram(Shader *shader)
{
  glDeleteProgram(shader->handle);
}
