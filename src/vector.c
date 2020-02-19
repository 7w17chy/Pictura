// why this doesn't work: realloc/malloc don't return a pointer to a new buffer,
// they return 0 if they succeeded and some negative value if they failed!

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

static void resizeVecChar(VectorChar *vec, size_t newsize)
{
  vec->buff = (char*) realloc(vec->buff, newsize);
  vec->size += newsize;
}

void pushToVecChar(VectorChar *vec, char *val)
{
  vec->ptr += 1;

  if (vec->ptr > vec->size)
    resizeVecChar(vec, sizeof(char) * 5);

  vec->buff[vec->ptr] = *val;
}

// ------------------------------------

static void resizeVecInt(VectorInt *vec, size_t newsize)
{
  realloc(vec->buff, newsize)
  vec->size += newsize;
}

void pushToVecInt(VectorInt *vec, int *val)
{
  vec->ptr += 1;

  if (vec->ptr > vec->size)
    resizeVecChar(vec, sizeof(int) * 5);

  vec->buff[vec->ptr] = *val;
}

void initVecInt(VectorInt *vec, size_t size)
{
  vec->size = size;
  vec->buff = (int*) malloc(size);
  vec->ptr = 0;
}
