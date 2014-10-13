#ifndef _PROGRAMOBJECT_HPP_
#define _PROGRAMOBJECT_HPP_

#include<GL/glew.h>

#include<stdarg.h>
#include<vector>
#include<map>
#include<geGL/ShaderObject.h>
#include<geGL/ShaderObjectParameter.h>
#include<geGL/ShaderObjectSubroutine.h>
#include<geGL/ProgramObjectMacro.h>

namespace ge{
  namespace gl{
  /**
   * @brief This class represents shader program
   */
  class ProgramObject
  {
    protected:
      std::vector<GLuint>                        _shaderList;    ///<list of shader object
      std::vector<ShaderObject*>                 _shaders;       ///<list of shaders
      std::map<std::string,ShaderObjectParameter>_attributeList; ///<list of attributes
      std::map<std::string,ShaderObjectParameter>_uniformList;   ///<list of uniforms
      ShaderObjectSubroutine                     _subroutines[6];///subroutines in shaders
      GLuint                                     _id;            ///<id of shader program
      void createShaderProgram_Prologue();  ///<prologue of creating of shader prg.
      void createShaderProgram_Epilogue();  ///<epilogue of creating of shader prg.
      void getParameterList();              ///<obtain shader parameters
      void getSubroutineUniformList();      ///<obtain shader subroutines
      std::string getProgramInfo(GLuint ID);///<obtain program info log
      void deleteProgram();                 ///<delete shader program
      void compileShaders(
          unsigned     numShaders,
          std::string *shaders,
          std::string *defs,
          unsigned     version,
          std::string  profile);
      void sortAndCompileShaders(
          unsigned     numStrings,
          std::string *strings,
          unsigned     version,
          std::string  profile);
    public:
      /**
       * @brief Initialise shader manager
       */
      static void initShaderManager();
      /**
       * @brief Function converts complex type (GL_FLOAT_VEC3 to GL_FLOAT)
       *
       * @param Type OpenGL Type GL_FLOAT_VEC2, ...
       *
       * @return GL_FLOAT, ...
       */
      static GLenum complexType2SimpleType(GLenum Type);
      /**
       * @brief Function converts complex type (GL_FLOAT_VEC3 to 3)
       *
       * @param Type OpenGL Type GL_FLOAT_VEC2, ...
       *
       * @return 2, ...
       */
      static GLint complexType2Size(GLenum Type);
      GLint workGroupSize[3];///< work group size
      void setSeparable    ();
      void resetSeparable  ();
      void setRetrievable  ();
      void resetRetrievable();
      /**
       * Constructor
       * @param shader list of shaders
       * @param num number of shaders
       */
      ProgramObject(ShaderObject**shader,unsigned num);
      /**
       * Constructor
       * @param num number of shaders
       */
      ProgramObject(unsigned num,...);
      /**
       * @brief Constructor
       *
       * @param shader0 shader 0
       * @param version version of shader
       * @param profile profile version of shader
       */
      ProgramObject(
          std::string shader0,
          unsigned    version=0,
          std::string profile="");
      /**
       * @brief Constructor
       *
       * @param shader0 shader 0
       * @param shader1 shader 1
       * @param version version of shader
       * @param profile profile version of shader
       */
      ProgramObject(
          std::string shader0,
          std::string shader1,
          unsigned    version=0,
          std::string profile="");
      /**
       * @brief Constructor
       *
       * @param shader0 shader 0
       * @param shader1 shader 1
       * @param shader2 shader 2
       * @param version version of shader
       * @param profile profile version of shader
       */
      ProgramObject(
          std::string shader0,
          std::string shader1,
          std::string shader2,
          unsigned    version=0,
          std::string profile="");
      /**
       * @brief Constructor
       *
       * @param shader0 shader 0
       * @param shader1 shader 1
       * @param shader2 shader 2
       * @param shader3 shader 3
       * @param version version of shader
       * @param profile profile version of shader
       */
      ProgramObject(
          std::string shader0,
          std::string shader1,
          std::string shader2,
          std::string shader3,
          unsigned    version=0,
          std::string profile="");
      /**
       * @brief Constructor
       *
       * @param shader0 shader 0
       * @param shader1 shader 1
       * @param shader2 shader 2
       * @param shader3 shader 3
       * @param shader4 shader 4
       * @param version version of shader
       * @param profile profile version of shader
       */
      ProgramObject(
          std::string shader0,
          std::string shader1,
          std::string shader2,
          std::string shader3,
          std::string shader4,
          unsigned    version=0,
          std::string profile="");
      ProgramObject(
          std::string shader0,
          std::string shader1,
          std::string shader2,
          std::string shader3,
          std::string shader4,
          std::string shader5,
          unsigned    version=0,
          std::string profile="");
      ProgramObject(
          std::string shader0,
          std::string shader1,
          std::string shader2,
          std::string shader3,
          std::string shader4,
          std::string shader5,
          std::string shader6,
          unsigned    version=0,
          std::string profile="");
      ProgramObject(
          std::string shader0,
          std::string shader1,
          std::string shader2,
          std::string shader3,
          std::string shader4,
          std::string shader5,
          std::string shader6,
          std::string shader7,
          unsigned    version=0,
          std::string profile="");
      ProgramObject(
          std::string shader0,
          std::string shader1,
          std::string shader2,
          std::string shader3,
          std::string shader4,
          std::string shader5,
          std::string shader6,
          std::string shader7,
          std::string shader8,
          unsigned    version=0,
          std::string profile="");
      ProgramObject(
          std::string shader0,
          std::string shader1,
          std::string shader2,
          std::string shader3,
          std::string shader4,
          std::string shader5,
          std::string shader6,
          std::string shader7,
          std::string shader8,
          std::string shader9,
          unsigned    version=0,
          std::string profile="");
      /**
       * @brief Constructor
       *
       * @param type0 type of shader0
       * @param shader0 text of shader0
       */
      ProgramObject(
          GLenum type0,std::string shader0);
      /**
       * @brief Constructor
       *
       * @param type0 type of shader0
       * @param shader0 text of shader0
       * @param type1 type of shader1
       * @param shader1 test of shader1
       */
      ProgramObject(
          GLenum type0,std::string shader0,
          GLenum type1,std::string shader1);
      /**
       * @brief Constructor
       *
       * @param type0 type of shader0
       * @param shader0 text of shader0
       * @param type1 type of shader1
       * @param shader1 test of shader1
       * @param type2 type of shader2
       * @param shader2 text of shader2
       */
      ProgramObject(
          GLenum type0,std::string shader0,
          GLenum type1,std::string shader1,
          GLenum type2,std::string shader2);
      /**
       * @brief Constructor
       *
       * @param type0 type of shader0
       * @param shader0 text of shader0
       * @param type1 type of shader1
       * @param shader1 test of shader1
       * @param type2 type of shader2
       * @param shader2 text of shader2
       * @param type3 type of shader3
       * @param shader3 text of shader3
       */
      ProgramObject(
          GLenum type0,std::string shader0,
          GLenum type1,std::string shader1,
          GLenum type2,std::string shader2,
          GLenum type3,std::string shader3);
      /**
       * @brief Constructor
       *
       * @param type0 type of shader0
       * @param shader0 text of shader0
       * @param type1 type of shader1
       * @param shader1 test of shader1
       * @param type2 type of shader2
       * @param shader2 text of shader2
       * @param type3 type of shader3
       * @param shader3 text of shader3
       * @param type4 type of shader4
       * @param shader4 text of shader4
       */
      ProgramObject(
          GLenum type0,std::string shader0,
          GLenum type1,std::string shader1,
          GLenum type2,std::string shader2,
          GLenum type3,std::string shader3,
          GLenum type4,std::string shader4);

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
       * @brief This method return ID of linked shader program
       *
       * @return ID of linked shader program
       */
      GLuint getId();
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
      GLuint getAttribute(std::string attributeName);
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
      GLuint getUniform(std::string uniformName);
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
       * @brief Sets this shader as active
       */
      void use();
      /**
       * @brief Sets subroutine with name SubroutineName as active in Uniform
       *
       * @param shaderType type of shader
       * @param uniform uniform name
       * @param subroutineName subroutine name
       */
      void setSubroutine(
          GLenum      shaderType,
          std::string uniform,
          unsigned    offSet,
          std::string subroutineName);
      void set(
          std::string  uniformName,
          GLsizei      count,
          GLboolean    transpose,
          GLfloat     *value);
      void set(
          std::string  uniformName,
          GLsizei      count,
          GLboolean    transpose,
          GLdouble    *value);

      DEFDEFFCE(1,f);
      DEFDEFFCE(2,f);
      DEFDEFFCE(3,f);
      DEFDEFFCE(4,f);
      DEFDEFFCE(1,d);
      DEFDEFFCE(2,d);
      DEFDEFFCE(3,d);
      DEFDEFFCE(4,d);
      DEFDEFFCE(1,i);
      DEFDEFFCE(2,i);
      DEFDEFFCE(3,i);
      DEFDEFFCE(4,i);
      DEFDEFFCE(1,ui);
      DEFDEFFCE(2,ui);
      DEFDEFFCE(3,ui);
      DEFDEFFCE(4,ui);
      DEFDEFFCE(1,boolean);
      DEFDEFFCE(2,boolean);
      DEFDEFFCE(3,boolean);
      DEFDEFFCE(4,boolean);
      DEFDEFFCEV(f);
      DEFDEFFCEV(d);
      DEFDEFFCEV(i);
      DEFDEFFCEV(ui);
      DEFDEFFCEV(boolean);

      void setdsa(
          std::string  uniformName,
          GLsizei      count,
          GLboolean    transpose,
          GLfloat     *value);
      void setdsa(
          std::string  uniformName,
          GLsizei      count,
          GLboolean    transpose,
          GLdouble    *value);

      DEFDEFDSAFCE(1,f);
      DEFDEFDSAFCE(2,f);
      DEFDEFDSAFCE(3,f);
      DEFDEFDSAFCE(4,f);
      DEFDEFDSAFCE(1,d);
      DEFDEFDSAFCE(2,d);
      DEFDEFDSAFCE(3,d);
      DEFDEFDSAFCE(4,d);
      DEFDEFDSAFCE(1,i);
      DEFDEFDSAFCE(2,i);
      DEFDEFDSAFCE(3,i);
      DEFDEFDSAFCE(4,i);
      DEFDEFDSAFCE(1,ui);
      DEFDEFDSAFCE(2,ui);
      DEFDEFDSAFCE(3,ui);
      DEFDEFDSAFCE(4,ui);
      DEFDEFDSAFCE(1,boolean);
      DEFDEFDSAFCE(2,boolean);
      DEFDEFDSAFCE(3,boolean);
      DEFDEFDSAFCE(4,boolean);
      DEFDEFDSAFCEV(f);
      DEFDEFDSAFCEV(d);
      DEFDEFDSAFCEV(i);
      DEFDEFDSAFCEV(ui);
      DEFDEFDSAFCEV(boolean);

  };
}//gl
}//ge

#endif//_PROGRAMOBJECT_HPP_