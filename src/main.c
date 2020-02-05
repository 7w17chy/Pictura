#include <GL/glew.h> // must be included first!
#include <GLFW/glfw3.h>
#include <stdio.h>

// number of postions for a vertex -> triangle in this context
#define POS 6

int createVB(int size, float positions[]);
int createShader(char vertexShader[], char fragmentShader[]);
int compileShader(unsigned int type, char source[]);

int main(void)
{
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  // only can be called after opengl context has been created
  if (glewInit() != GLEW_OK)
    printf("Well, now...\n");

  // print opengl version to validate it's actually working
  printf("%s\n", glGetString(GL_VERSION));

  // vertex postions for a triangle
  float positions[POS] = {
     -0.5f, -0.5f,
      0.0f,  0.5f,
      0.5f, -0.5f
  };

  // create a vertex buffer with the positions
  unsigned int buffer = createVB(POS, positions);

  char vertexSource[] =
    "#version 330 core\n"
    "layout(location = 0) in vec4 postion;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = postion;\n"
    "}\n";

  char fragmentSource[] =
    "#version 330 core\n"
    "layout(location = 0) out vec4 color;\n"
    "void main()\n"
    "{\n"
    "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

  unsigned int shader = createShader(vertexSource, fragmentSource);
  glUseProgram(shader);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    // issue draw call
    glDrawArrays(GL_TRIANGLES, 0, (POS/2));

       /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

int createVB(int size, float positions[])
{
  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), positions, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
  glEnableVertexAttribArray(0);
  return buffer;
}

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

int createShader(char vertexShader[], char fragmentShader[])
{
  unsigned int program = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  // can be deleted, because they have been linked and put into one program, 'program'
  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}
