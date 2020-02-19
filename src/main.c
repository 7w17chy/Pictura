#include <GL/glew.h> // must be included first!
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "shaders.h"
#include "logging.h"
#include "buffers.h"

int main(void)
{
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
  if (!window) {
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
  float positions[] = {
     -0.5f, -0.5f,
      0.5f, -0.5f,
      0.5f,  0.5f,
     -0.5f,  0.5f
  };

  // indices for the index buffer
  unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
  };

  // create a vertex buffer with the positions
  VertexBuffer buffer;
  createVertexBuffer(&buffer, 8, positions);

  // create index buffer and bind it
  IndexBuffer ibo;
  createIndexBuffer(&ibo, 6, indices);

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

  // create one shader program out of a vertex and a fragment shader and bind it
  Shader shader;
  createShader(&shader, vertexSource, fragmentSource);
  bindShader(&shader);

  // initialise debugging capabilities
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(errorOccurredGL, NULL);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    // issue draw call for vertex buffer
    //glDrawArrays(GL_TRIANGLES, 0, (POS/2));

    // issure draw call for use with index buffer
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  deleteShaderProgram(&shader);
  glfwTerminate();
  return 0;
}
