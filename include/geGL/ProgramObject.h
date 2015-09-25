#ifndef _PROGRAMOBJECT_H_
#define _PROGRAMOBJECT_H_

#include<geGL/OpenGL.h>
#include<geGL/OpenGLObject.h>
#include<stdarg.h>
#include<vector>
#include<map>
#include<set>
#include<geGL/ShaderObject.h>
#include<geGL/ShaderObjectParameter.h>
#include<geGL/ShaderObjectSubroutine.h>
#include<geGL/ProgramObjectMacro.h>
#include<geGL/BufferObject.h>
#include<geGL/TextureObject.h>
#include<geCore/dtemplates.h>

namespace ge{
  namespace gl{
    class GEGL_EXPORT Program: public OpenGLObject{
      protected:
        std::set<std::shared_ptr<Shader>>_shaders;
      public:
        Program();
        ~Program();
        GLboolean isProgram();
        void attachShader(std::shared_ptr<Shader>const&shader);
        void detachShader(std::shared_ptr<Shader>const&shader);
        void link();
        void use();
    };

    /**
     * @brief Initialise shader manager
     */
    GEGL_EXPORT void initShadersAndPrograms();
    /**
     * @brief Function converts complex type (GL_FLOAT_VEC3 to GL_FLOAT)
     *
     * @param Type OpenGL Type GL_FLOAT_VEC2, ...
     *
     * @return GL_FLOAT, ...
     */
    GEGL_EXPORT GLenum complexType2SimpleType(GLenum Type);
    /**
     * @brief Function converts complex type (GL_FLOAT_VEC3 to 3)
     *
     * @param Type OpenGL Type GL_FLOAT_VEC2, ...
     *
     * @return 2, ...
     */
    GEGL_EXPORT GLint complexType2Size(GLenum Type);
    /**
     * @brief This class represents shader program
     */
    class GEGL_EXPORT ProgramObject: public OpenGLObject
    {
      private:
        int _floatMatrixType2Index(GLenum type);
        int _doubleMatrixType2Index(GLenum type);

        template<typename...>
          void _typeStringConstructor(){}
        template<typename... ARGS>
          void _typeStringConstructor(GLenum type,std::string shader,ARGS...args){
            std::shared_ptr<ShaderObject>s;
            try{
              s=std::make_shared<ShaderObject>(type,shader);
            }catch(std::string&e){
              std::cerr<<e<<std::endl;
              return;
            }
            glAttachShader(this->getId(),s->getId());
            this->_shaders.push_back(s);
            this->_typeStringConstructor(args...);
          }

        template<typename...>
          void _sharedShaderConstructor(){}
        template<typename... ARGS>
          void _sharedShaderConstructor(std::shared_ptr<ShaderObject>const&shader,ARGS...args){
            glAttachShader(this->getId(),shader->getId());
            this->_shaders.push_back(shader);
            this->_sharedShaderConstructor(args...);
          }

        template<typename...>
          void _copyStringList2Vector(std::vector<std::string>&){}
        template<typename TYPE>
          void _copyStringList2Vector(std::vector<std::string>&,unsigned){}
        template<typename...ARGS>
          void _copyStringList2Vector(std::vector<std::string>&vec,std::string shader,ARGS...args){
            vec.push_back(shader);
            this->_copyStringList2Vector(vec,args...);
          }

        template<typename...>
          void _copyVersionProfile(unsigned&versionOut,std::string&profileOut,unsigned version = 0,std::string profile=""){
            versionOut = version;
            profileOut = profile;
          }
        template<typename...ARGS>
          void _copyVersionProfile(unsigned&versionOut,std::string&profileOut,std::string,ARGS...args){
            this->_copyVersionProfile(versionOut,profileOut,args...);
          }

        template<typename...>
          void _stringListConstructor(){}
        template<typename...ARGS>
          void _stringListConstructor(std::string shader,ARGS...args){
            std::vector<std::string>shaderStrings;
            unsigned version;
            std::string profile;
            this->_copyStringList2Vector(shaderStrings,shader,args...);
            this->_copyVersionProfile(version,profile,args...);
            this->sortAndCompileShaders(shaderStrings,version,profile);
          }

        template<typename...ARGS>
          void _resolveConstructorArgs(GLenum type,std::string shader,ARGS...args){
            this->_typeStringConstructor(type,shader,args...);
          }
        template<typename...ARGS>
          void _resolveConstructorArgs(std::shared_ptr<ShaderObject>const&shader,ARGS...args){
            this->_sharedShaderConstructor(shader,args...);
          }
        template<typename...ARGS>
          void _resolveConstructorArgs(std::string shader,ARGS...args){
            this->_stringListConstructor(shader,args...);
          }

      protected:
        std::vector<std::shared_ptr<ShaderObject>> _shaders       ;///<list of shaders
        std::map<std::string,ShaderObjectParameter>_attributeList ;///<list of attributes
        std::map<std::string,ShaderObjectParameter>_uniformList   ;///<list of uniforms
        std::map<std::string,BufferParams>         _bufferList    ;///<list of buffers
        std::vector<std::string>                   _bufferNames   ;///<list of buffer names
        ShaderObjectSubroutine                     _subroutines[6];///<subroutines in shaders
        std::map<std::string,SamplerParam>         _samplerList   ;///<sampler parameters
        void createShaderProgram_Prologue();  ///<prologue of creating of shader prg.
        void createShaderProgram_Epilogue();  ///<epilogue of creating of shader prg.
        void getParameterList();              ///<obtain shader parameters
        void getSubroutineUniformList();      ///<obtain shader subroutines
        void getBufferList();                 ///<obtain shader buffers
        std::string getProgramInfo(GLuint ID);///<obtain program info log
        void deleteProgram();                 ///<delete shader program
        void compileShaders(
            unsigned     numShaders,
            std::string *shaders,
            std::string *defs,
            unsigned     version,
            std::string  profile);
        void sortAndCompileShaders(
            std::vector<std::string>strings,
            unsigned     version,
            std::string  profile);
        /*
           void _createProgram(
           std::vector<std::string>& data         ,
           unsigned                  version = 0  ,
           std::string               profile = "" );
           bool        _isShader       (std::string data);///<has to contain void main() in some form
           bool        _isFile         (std::string data);///<has to exist
           std::string _composeShaderSource(std::vector<std::string>&data,unsigned version=0,std::string profile="");
           std::string _getShaderSource(std::string data);///<if its file open it and return its content
           unsigned    _getShaderSourceTypeMask(std::string data);///if it can be vs gp or fs it returns 0x1|0x8|0x10
           */
      public:
        std::string uniformsToStr();
        GLint workGroupSize[3];///< work group size
        void setSeparable    ();
        void resetSeparable  ();
        void setRetrievable  ();
        void resetRetrievable();
        template<typename...ARGS>
          ProgramObject(ARGS...args){
            this->_resolveConstructorArgs(args...);
          }
        /**
         * @brief Sets version of every shader in shader program
         *
         * @param version version
         * @param profile profile
         */
        void setVersion(unsigned version,std::string profile);
        /**
         * @brief Sets version in specific shader of shader program 
         *
         * @param type shader type
         * @param version version
         * @param profile profile
         */
        void setVersion(GLenum type,unsigned version,std::string profile);
        /**
         * @brief Appends definitions after version in every shader of program
         *
         * @param defs definitions
         */
        void appendAfterVersion(std::string defs);
        /**
         * @brief Appends definitions after version in specific shader
         *
         * @param type type of shader
         * @param defs definitions
         */
        void appendAfterVersion(GLenum type,std::string defs);
        /**
         * @brief Relink program
         */
        void relink();
        /**
         * @brief Destructor
         */
        ~ProgramObject();
        /**
         * @brief Return shader program uniform location
         *
         * @param name name of uniform
         *
         * @return returns parameter ID
         */
        GLint operator[](std::string name);
        /**
         * Ziska identifikator atributu
         * @param attributeName jmeno atributu
         * @return vracu identifikator atributu
         */
        GLint getAttribute(std::string attributeName);
        /**
         * @brief Returns attribute type
         *
         * @param attributeName attribute name
         *
         * @return type of attribute
         */
        GLenum getAttributeType(std::string attributeName);
        /**
         * @brief Returns size of attribute's array
         *
         * @param attributeName attribute name
         *
         * @return size of attribute's array
         */
        GLint getAttributeSize(std::string attributeName);
        /**
         * Ziska identifikator uniformni promenne
         * @param uniformName jmeno uniformni promenne
         * @return vracu identifikator uniformni promenne
         */
        GLint getUniform(std::string uniformName);
        /**
         * @brief Returns uniform type
         *
         * @param uniformName uniform name
         *
         * @return type of uniform
         */
        GLenum getUniformType(std::string uniformName);
        /**
         * @brief Returns size of uniform's array
         *
         * @param uniformName uniform name
         *
         * @return size of uniform's array
         */
        GLint getUniformSize(std::string uniformName);
        /**
         * @brief gets buffer binding index
         *
         * @param name name of buffer
         *
         * @return binding index
         */
        GLuint getBuffer(std::string name);
        /**
         * @brief gets number of buffers
         *
         * @return number of buffers
         */
        unsigned getNofBuffers();
        /**
         * @brief gets name of buffer
         *
         * @param i index of buffer
         *
         * @return name of buffer
         */
        std::string getBufferName(unsigned i);
        /**
         * @brief gets buffer property
         *
         * @param name name of buffer
         * @param property property type
         *
         * @return value of buffer property
         */
        GLint getBufferProperty(std::string name,BufferParams::Properties property);
        /**
         * @brief gets buffer params
         *
         * @param name name of buffer
         *
         * @return buffer params
         */
        BufferParams getBufferParams(std::string name);
        /**
         * @brief Sets this shader as active
         */
        void use();
        void bindSSBO(std::string name,ge::gl::BufferObject*buffer);
        void bindSSBO(std::string name,ge::gl::BufferObject*buffer,GLintptr offset,GLsizeiptr size);
        GLenum getSamplerBinding(std::string uniform);
        void bindTexture(std::string uniform,ge::gl::TextureObject*texture);
        void bindImage(
            std::string           uniform                ,
            ge::gl::TextureObject*texture                ,
            GLint                 level   = 0            ,
            GLenum                format  = 0            ,
            GLenum                access  = GL_READ_WRITE,
            GLboolean             layered = GL_FALSE     ,
            GLint                 layer   = 0            );

        /**
         * @brief Sets subroutine with name SubroutineName as active in Uniform
         *
         * @param shaderType type of shader
         * @param uniform uniform name
         * @param subroutineName subroutine name
         */
        void setSubroutine(GLenum shader,std::string uniform,unsigned offSet,std::string subroutine);
        void set(std::string name,GLsizei count,GLboolean transpose,const GLfloat*value);
        void set(std::string name,GLsizei count,GLboolean transpose,const GLdouble*value);
        void setdsa(std::string name,GLsizei count,GLboolean transpose,const GLfloat*value);
        void setdsa(std::string name,GLsizei count,GLboolean transpose,const GLdouble*value);
        void set(std::string name,GLfloat v0);
        void set(std::string name,GLfloat v0,GLfloat v1);
        void set(std::string name,GLfloat v0,GLfloat v1,GLfloat v2);
        void set(std::string name,GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3);
        void set(std::string name,GLdouble v0);
        void set(std::string name,GLdouble v0,GLdouble v1);
        void set(std::string name,GLdouble v0,GLdouble v1,GLdouble v2);
        void set(std::string name,GLdouble v0,GLdouble v1,GLdouble v2,GLdouble v3);
        void set(std::string name,GLint v0);
        void set(std::string name,GLint v0,GLint v1);
        void set(std::string name,GLint v0,GLint v1,GLint v2);
        void set(std::string name,GLint v0,GLint v1,GLint v2,GLint v3);
        void set(std::string name,GLuint v0);
        void set(std::string name,GLuint v0,GLuint v1);
        void set(std::string name,GLuint v0,GLuint v1,GLuint v2);
        void set(std::string name,GLuint v0,GLuint v1,GLuint v2,GLuint v3);
        void set(std::string name,GLboolean v0);
        void set(std::string name,GLboolean v0,GLboolean v1);
        void set(std::string name,GLboolean v0,GLboolean v1,GLboolean v2);
        void set(std::string name,GLboolean v0,GLboolean v1,GLboolean v2,GLboolean v3);
        void set(std::string name,GLsizei count,const GLfloat*  v);
        void set(std::string name,GLsizei count,const GLdouble* v);
        void set(std::string name,GLsizei count,const GLint*    v);
        void set(std::string name,GLsizei count,const GLuint*   v);
        void set(std::string name,GLsizei count,const GLboolean*v);
        void setdsa(std::string name,GLfloat v0);
        void setdsa(std::string name,GLfloat v0,GLfloat v1);
        void setdsa(std::string name,GLfloat v0,GLfloat v1,GLfloat v2);
        void setdsa(std::string name,GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3);
        void setdsa(std::string name,GLdouble v0);
        void setdsa(std::string name,GLdouble v0,GLdouble v1);
        void setdsa(std::string name,GLdouble v0,GLdouble v1,GLdouble v2);
        void setdsa(std::string name,GLdouble v0,GLdouble v1,GLdouble v2,GLdouble v3);
        void setdsa(std::string name,GLint v0);
        void setdsa(std::string name,GLint v0,GLint v1);
        void setdsa(std::string name,GLint v0,GLint v1,GLint v2);
        void setdsa(std::string name,GLint v0,GLint v1,GLint v2,GLint v3);
        void setdsa(std::string name,GLuint v0);
        void setdsa(std::string name,GLuint v0,GLuint v1);
        void setdsa(std::string name,GLuint v0,GLuint v1,GLuint v2);
        void setdsa(std::string name,GLuint v0,GLuint v1,GLuint v2,GLuint v3);
        void setdsa(std::string name,GLboolean v0);
        void setdsa(std::string name,GLboolean v0,GLboolean v1);
        void setdsa(std::string name,GLboolean v0,GLboolean v1,GLboolean v2);
        void setdsa(std::string name,GLboolean v0,GLboolean v1,GLboolean v2,GLboolean v3);
        void setdsa(std::string name,GLsizei count,const GLfloat*  v);
        void setdsa(std::string name,GLsizei count,const GLdouble* v);
        void setdsa(std::string name,GLsizei count,const GLint*    v);
        void setdsa(std::string name,GLsizei count,const GLuint*   v);
        void setdsa(std::string name,GLsizei count,const GLboolean*v);
    };
  }//gl
}//ge

#endif//_PROGRAMOBJECT_H_
