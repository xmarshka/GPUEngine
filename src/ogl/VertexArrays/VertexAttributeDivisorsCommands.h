#ifndef _VERTEXATTRIBUTEDIVISORS_H_
#define _VERTEXATTRIBUTEDIVISORS_H_

#include"../../ogl/Standard/OpenGL.h"

namespace ge
{
  namespace ogl
  {
    class VertexBindingDivisor: public Command
    {
      public:
        GLuint bindingIndex;
        GLuint divisor;
        VertexBindingDivisor(
            GLuint bindingIndex,
            GLuint divisor);
        void apply();
    };
    class VertexAttribDivisor: public Command
    {
      public:
        GLuint index;
        GLuint divisor;
        VertexAttribDivisor(
            GLuint index,
            GLuint divisor);
        void apply();
    };
  }//ogl
}//ge

#endif//_VERTEXATTRIBUTEDIVISORS_H_
