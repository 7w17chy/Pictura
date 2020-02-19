#ifndef __LOGGING_H__
#define __LOGGING_H__

// this function is going to be called by 'glDebugMessageCallback'
void GLAPIENTRY errorOccurredGL(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const GLchar* message,
                                const void* userParam);

#endif
