#ifndef _DRAWCOMMANDS_H_
#define _DRAWCOMMANDS_H_

#include"OpenGL.h"

namespace ge
{
  namespace ogl
  {
    class DrawArrays: public Command
    {
      public:
        GLenum  mode;
        GLint   first;
        GLsizei count;
        DrawArrays(GLenum mode,GLint first,GLsizei count);
        void apply();
    };
    class DrawArraysInstancedBaseInstance: public Command
    {
      public:
        GLenum  mode;
        GLint   first;
        GLsizei count;
        GLsizei instanceCount;
        GLuint  baseInstance;
        DrawArraysInstancedBaseInstance(
            GLenum  mode,
            GLint   first,
            GLsizei count,
            GLsizei instanceCount,
            GLuint  baseInstance);
        void apply();
    };
    class DrawArraysInstanced: public Command
    {
      public:
        GLenum  mode;
        GLint   first;
        GLsizei count;
        GLsizei instanceCount;
        DrawArraysInstanced(
            GLenum  mode,
            GLint   first,
            GLsizei count,
            GLsizei instanceCount);
        void apply();
    };
    class DrawArraysIndirect: public Command
    {
      public:
        GLenum   mode;
        GLvoid * indirect;
        DrawArraysIndirect(GLenum mode,GLvoid*indirect);
        void apply();
    };
    class MultiDrawArrays: public Command
    {
      public:
        GLenum    mode;
        GLint   * first;
        GLsizei * count;
        GLsizei   drawCount;
        MultiDrawArrays(
            GLenum    mode,
            GLint   * first,
            GLsizei * count,
            GLsizei   drawCount);
        void apply();
    };
    class MultiDrawArraysIndirect: public Command
    {
      public:
        GLenum   mode;
        GLvoid * indirect;
        GLsizei  drawCount;
        GLsizei  stride;
        MultiDrawArraysIndirect(
            GLenum   mode,
            GLvoid * indirect,
            GLsizei  drawCount,
            GLsizei  stride);
        void apply();
    };
    class DrawElements: public Command
    {
      public:
        GLenum   mode;
        GLsizei  count;
        GLenum   type;
        GLvoid * indices;
        void DrawElements(
            GLenum   mode;
            GLsizei  count;
            GLenum   type;
            GLvoid * indices);
        void apply();
    };
    class DrawElementsInstancedBaseInstance: public Command
    {
      public:
        GLenum    mode;
        GLsizei   count;
        GLenum    type;
        GLvoid  * indices;
        GLsizei   instanceCount;
        GLuint    baseInstance;
        void DrawElementsInstancedBaseInstance(
            GLenum    mode;
            GLsizei   count;
            GLenum    type;
            GLvoid  * indices;
            GLsizei   instanceCount;
            GLuint    baseInstance);
        void apply();
    };
    class DrawElementsInstanced: public Command
    {
      public:
        GLenum    mode;
        GLsizei   count;
        GLenum    type;
        GLvoid  * indices;
        GLsizei   instanceCount;
        DrawElementsInstanced(
            GLenum    mode;
            GLsizei   count;
            GLenum    type;
            GLvoid  * indices;
            GLsizei   instanceCount);
        void apply();
    };
    class MultiDrawElements: public Command
    {
      public:
        GLenum     mode;
        GLsizei *  count;
        GLenum     type;
        GLvoid  ** indices;
        GLsizei    drawCount;
        void MultiDrawElements(
            GLenum     mode,
            GLsizei *  count,
            GLenum     type,
            GLvoid  ** indices,
            GLsizei    drawCount);
        void apply();
    };
    class DrawRangeElements: public Command
    {
      public:
        GLenum   mode;
        GLuint   start;
        GLuint   end;
        GLsizei  count;
        GLenum   type;
        GLvoid * indices;
        void DrawRangeElements(
            GLenum   mode,
            GLuint   start,
            GLuint   end,
            GLsizei  count,
            GLenum   type,
            GLvoid * indices);
        void apply();
    };
    class DrawElementsBaseVertex: public Command
    {
      public:
        GLenum   mode;
        GLsizei  count;
        GLenum   type;
        GLvoid * indices;
        GLint    baseVertex;
        DrawElementsBaseVertex(
            GLenum   mode,
            GLsizei  count,
            GLenum   type,
            GLvoid * indices,
            GLint    baseVertex);
        void apply();
    };
    class DrawRangeElementsBaseVertex: public Command
    {
      public:
        GLenum   mode;
        GLsizei  count;
        GLenum   type;
        GLvoid * indices;
        GLsizei  instanceCount;
        GLint    baseVertex;
        void DrawRangeElementsBaseVertex(
            GLenum   mode,
            GLsizei  count
            GLenum   type,
            GLvoid * indices,
            GLsizei  instanceCount,
            GLint    baseVertex);
        void apply();
    };
    class DrawElementsInstanceBaseVertex: public Command
    {
      public:
        GLenum   mode;
        GLsizei  count;
        GLenum   type;
        GLvoid * indices;
        GLsizei  instanceCount;
        GLint    baseVertex;
        void DrawElementsInstanceBaseVertex(
            GLenum   mode,
            GLsizei  count,
            GLenum   type,
            GLvoid * indices,
            GLsizei  instanceCount,
            GLint    baseVertex);
        void apply();
    };
    void DrawElementsInstancedBaseVertexBaseInstance: public Command
    {
      public:
        GLenum mode;
        GLsizei count;
        GLenum type;
        GLvoid * indices;
        GLsizei  instanceCount;
        GLint    baseVertex;
        GLuint   baseInstance;
        void DrawElementsInstancedBaseVertexBaseInstance(
            GLenum mode;
            GLsizei count;
            GLenum type;
            GLvoid * indices;
            GLsizei  instanceCount;
            GLint    baseVertex;
            GLuint   baseInstance);
        void apply();
    };
    class DrawElementsIndirect: public Command
    {
      public:
        GLenum   mode;
        GLenum   type;
        GLvoid * indirect;
        void DrawElementsIndirect(
            GLenum   mode;
            GLenum   type;
            GLvoid * indirect);
        void apply();
    };
    class MultiDrawElementsIndirect: public Command
    {
      public:
        GLenum   mode;
        GLenum   type;
        GLvoid * indirect;
        GLsizei  drawCount;
        GLsizei  stride;
        void MultiDrawElementsIndirect(
            GLenum   mode;
            GLenum   type;
            GLvoid * indirect;
            GLsizei  drawCount;
            GLsizei  stride);
        void apply();
    };
    class MultiDrawElementsBaseVertex: public Command
    {
      public:
        GLenum     mode;
        GLsizei  * count;
        GLenum     type;
        GLvoid  ** indices;
        GLsizei    drawCount;
        GLint    * baseVertex;
        void MultiDrawElementsBaseVertex(
            GLenum     mode;
            GLsizei  * count;
            GLenum     type;
            GLvoid  ** indices;
            GLsizei    drawCount;
            GLint    * baseVertex);
        void apply();
    };
  }//namespace ogl
}//namespace ge


#endif//_DRAWCOMMANDS_H_
