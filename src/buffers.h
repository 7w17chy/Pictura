#ifndef __BUFFERS_H__
#define __BUFFERS_H__

typedef struct IndexBuffer {
  unsigned int handle;
  unsigned short is_bound;
} IndexBuffer;

void createIndexBuffer(IndexBuffer *ib, unsigned int size, unsigned int indices[]);

// ------------------------------

typedef struct VertexBuffer {
  unsigned int handle;
  unsigned short is_bound;
} VertexBuffer;

void createVertexBuffer(VertexBuffer *vb, int size, float positions[]);

#endif
