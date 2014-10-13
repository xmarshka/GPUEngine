#ifndef GE_GL_BUFFEROBJECT
#define GE_GL_BUFFEROBJECT

#include <geGL/Standard/OpenGL.h>
#include <geCore/Object.h>

#include <list>

#define BUFFEROBJECT_DEFAULT_MUTABLE      true
#define BUFFEROBJECT_DEFAULT_DATA         NULL
#define BUFFEROBJECT_DEFAULT_ID           0
#define BUFFEROBJECT_DEFAULT_TARGET       GL_ARRAY_BUFFER
#define BUFFEROBJECT_DEFAULT_EMPTY_TARGET 0
#define BUFFEROBJECT_DEFAULT_OFFSET       0
#define BUFFEROBJECT_DEFAULT_SIZE         0
#define BUFFEROBJECT_DEFAULT_USAGE        GL_STATIC_DRAW
#define BUFFEROBJECT_DEFAULT_FLAGS        0
#define BUFFEROBJECT_DEFAULT_MAPFLAGS     0
#define BUFFEROBJECT_DEFAULT_DATASOURCE   NULL
#define BUFFEROBJECT_DEFAULT_READBUFFER   GL_COPY_READ_BUFFER
#define BUFFEROBJECT_DEFAULT_WRITEBUFFER  GL_COPY_WRITE_BUFFER
#define BUFFEROBJECT_DEFAULT_READOFFSET   0
#define BUFFEROBJECT_DEFAULT_WRITEOFFSET  0
#define BUFFEROBJECT_DEFAULT_CLEARBUFFER  GL_COPY_WRITE_BUFFER
#define BUFFEROBJECT_DEFAULT_CLEAROFFSET  0
#define BUFFEROBJECT_DEFAULT_NOF_BUFFERS  1

namespace ge
{
   namespace gl
{
/**
 * Abstraction of the OpenGL Buffer Object.
 * Uses Direct State Access. It's internal data pointer can be used either for
 * mapping or as client-side data storage (not both).
 */
class GE_EXPORT BufferObject// : public ge::core::Object
{
public:
   BufferObject();
   BufferObject(const BufferObject& buf/*, const ge::core::CopyOp& copyop = ge::core::CopyOp::SHALLOW_COPY*/);
   virtual ~BufferObject();

   //class GE_EXPORT Mapping
   //{
   //public:
   //   Mapping(GLintptr offset, GLsizeiptr size, GLbitfield flags, GLuint bufferObject, void* data_)
   //      : _size(size)
   //      , _flags(flags)
   //      , _offset(offset)
   //      , _bufferObject(bufferObject)
   //      , data(data_)
   //      //, _myPlace()
   //   {

   //   }

   //   void *data;

   //   template <typename T> T* getData(){ return static_cast<T*> (_data); }
   //   //virtual void setPlace(const std::list<Mapping>::iterator& place){ _myPlace = place; }
   //protected:
   //   GLsizeiptr _size;
   //   GLbitfield _flags;
   //   GLintptr _offset;
   //   GLuint _bufferObject;
   //   //std::list<Mapping>::iterator _myPlace;

   //};

   //META_GE_Object(BufferObject)

   virtual void allocateClientSideBuffer(
         GLsizeiptr size, 
         void* dataSource = BUFFEROBJECT_DEFAULT_DATASOURCE);
   virtual void freeClientSideBuffer();
   virtual void createAndInitGLBO(
         GLenum target, 
         GLenum     usage    = BUFFEROBJECT_DEFAULT_USAGE, 
         bool       mutable_ = BUFFEROBJECT_DEFAULT_MUTABLE,
         GLbitfield flags    = BUFFEROBJECT_DEFAULT_FLAGS);
   virtual void createAndInitGLBO(
         GLenum      target, 
         GLsizeiptr  size, 
         GLenum      usage    = BUFFEROBJECT_DEFAULT_USAGE, 
         void       *data     = BUFFEROBJECT_DEFAULT_DATA, 
         bool        mutable_ = BUFFEROBJECT_DEFAULT_MUTABLE,
         GLbitfield  flags    = BUFFEROBJECT_DEFAULT_FLAGS);
   virtual void deleteGLObject();
   virtual void map(
         GLintptr   offset   = BUFFEROBJECT_DEFAULT_OFFSET, 
         GLsizeiptr size     = BUFFEROBJECT_DEFAULT_SIZE, 
         GLenum     mapFlags = BUFFEROBJECT_DEFAULT_MAPFLAGS);
   virtual void unmap();
   //virtual const Mapping *createMapping(GLintptr offset, GLsizeiptr size, GLbitfield flags);
   //virtual void destroyMapping(Mapping &mapping);
   virtual GLboolean isMapped();
   virtual void bind();
   virtual void unbind();
   virtual void bind(GLenum target);
   virtual void bindRange(GLenum target,GLuint index,GLintptr offset,GLsizeiptr size);
   virtual void bindBase(GLenum Target,GLuint index);
   virtual void unbind(GLenum target);
   virtual void unbindRange(GLenum target,GLuint index);
   virtual void unbindBase(GLenum target,GLuint index);
   virtual void copy(BufferObject*buffer);
   virtual void flushMapped(GLenum target,GLintptr offset,GLsizeiptr length);
   virtual void invalidate(GLintptr offset,GLsizeiptr length);
   virtual void invalidate();
   virtual void clear(
         GLenum        internalFormat,
         GLenum        format,
         GLenum        type,
         const GLvoid *Data = BUFFEROBJECT_DEFAULT_DATA);
   virtual void clear(
         GLenum        internalFormat,
         GLintptr      offset,
         GLsizeiptr    size,
         GLenum        format,
         GLenum        type,
         const GLvoid *Data = BUFFEROBJECT_DEFAULT_DATA);
   virtual void operator &=(BufferObject*buffer);

   inline void* data(){ return _data; }
   inline GLsizeiptr size(){return _size;}
   inline GLuint getId(){ return this->_id; }
protected:
   //FIXME change to _id ?
   GLuint     _id; ///< Buffer Object OpenGL ID
   GLenum     _target;
   GLsizeiptr _size;
   GLenum     _usage;
   GLbitfield _flags;
   bool       _mutable;
   void*      _data; ///< Designed to be used with this buffer object only. If you use this pointer for e.g. mapping it to another BO you could crash the app.
   //std::list<Mapping> _mappings;
};


}
}

#endif //GE_GL_BUFFEROBJECT