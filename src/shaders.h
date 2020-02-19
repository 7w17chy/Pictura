#ifndef __SHADERS_H__
#define __SHADERS_H__

typedef struct Shader {
  unsigned int handle;
  unsigned short is_bound;
} Shader;

void createShader(Shader *shader, char vertexShader[], char fragmentShader[]);
int compileShader(unsigned int type, char source[]);
void bindShader(Shader *shader);
void deleteShaderProgram(Shader *shader);

#endif
