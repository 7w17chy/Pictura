#ifndef VECTOR_H_
#define VECTOR_H_

typedef struct VectorChar {
  // current size of the vector
  unsigned int size;

  // pointer to the actual array
  char *buff;

  // index in buff_ptr
  unsigned int ptr;
} VectorChar;

static void resizeVecChar(VectorChar *vec, size_t newsize);
void pushToVecChar(VectorChar *vec, char *val);

// ----------------------------------------------------

typedef struct VectorInt {
  // current size of the vector
  unsigned int size;

  // pointer to the actual array
  int *buff;

  // index in buff_ptr
  unsigned int ptr;
} VectorInt;

static void resizeVecInt(VectorInt *vec, size_t newsize);
void pushToVecInt(VectorInt *vec, int *val);
void initVecInt(VectorInt *vec, size_t size);

#endif
