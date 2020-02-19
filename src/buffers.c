#include <GL/gl.h>
#include <stdio.h>

#include "buffers.h"

/* void createIndexBuffer(IndexBuffer *ib, unsigned int size, unsigned int indices[]) */
/* { */
/*   unsigned int ibo; */
/*   glGenBuffers(1, &ibo); */
/*   // element buffer: 'synonym' for index buffer? */
/*   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); */
/*   glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), indices, GL_STATIC_DRAW); */
/*   ib->handle = ibo; */
/*   ib->is_bound = 1; */
/* } */

void createIndexBuffer(IndexBuffer *ib, unsigned int size, unsigned int indices[])
{
  glGenBuffers(1, &(ib->handle));
  // element buffer: 'synonym' for index buffer?
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->handle);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), indices, GL_STATIC_DRAW);
  ib->is_bound = 1;
}

void createVertexBuffer(VertexBuffer *vb, int size, float positions[])
{
  glGenBuffers(1, &(vb->handle));
  glBindBuffer(GL_ARRAY_BUFFER, vb->handle);
  glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), positions, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
  glEnableVertexAttribArray(0);
  vb->is_bound = 1;
}
