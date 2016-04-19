#pragma once

#include<utility>
#include<tuple>
#include<geCore/Export.h>
#include<geCore/TypeRegister.h>
#include<geCore/statement.h>
#include<geCore/Namer.h>

namespace ge{
  namespace core{
    class StatementFactory;
    class Statement;
    class Function;

    class GECORE_EXPORT FunctionRegister: public std::enable_shared_from_this<FunctionRegister>{
      public:
        typedef void(*Implementation)();
        using InputIndex = size_t;
        using FunctionID = size_t;
      protected:
        using FunctionDefinition = std::tuple<
          TypeRegister::TypeID,
          std::string,
          std::shared_ptr<StatementFactory>>;
        enum FunctionDefinitionParts{
          TYPE       = 0,
          NAME       = 1,
          FACTORY    = 2,
        };
        std::shared_ptr<Namer>       _namer;
        std::shared_ptr<TypeRegister>_typeRegister;
        std::map<FunctionID,FunctionDefinition>_functions;
        std::map<FunctionID,Implementation>_implementations;
        std::map<std::string,FunctionID>_name2Function;
        inline FunctionDefinition      & _getDefinition(FunctionID id);
        inline FunctionDefinition const& _getDefinition(FunctionID id)const;
        std::string _genDefaultName(InputIndex i)const;
      public:
        inline FunctionRegister(
            std::shared_ptr<TypeRegister>const&typeRegister,
            std::shared_ptr<Namer>const&namer);
        inline ~FunctionRegister();
        FunctionID addFunction(
            TypeRegister::TypeID type,
            std::string          name,
            std::shared_ptr<StatementFactory>const&factory);
        inline TypeRegister::TypeID             getType   (FunctionID id)const;
        inline std::string                      getName   (FunctionID id)const;
        inline std::shared_ptr<StatementFactory>getFactory(FunctionID id)const;
        inline FunctionID getFunctionId(std::string name)const;
        inline InputIndex getNofInputs(FunctionID id)const;
        inline std::string getOutputName(FunctionID id)const;
        inline std::string getInputName(FunctionID id,InputIndex input)const;
        inline TypeRegister::TypeID getInputType(FunctionID id,InputIndex input)const;
        inline TypeRegister::TypeID getOutputType(FunctionID id)const;
        inline InputIndex getInputIndex(FunctionID id,std::string name)const;
        inline void setInputName(FunctionID id,InputIndex input,std::string name);
        inline void setOutputName(FunctionID id,std::string name);
        inline std::shared_ptr<TypeRegister>const&getTypeRegister()const;
        inline void addImplementation(FunctionID id,Implementation impl);
        inline void addImplementation(std::string name,Implementation impl);
        inline Implementation getImplementation(FunctionID id)const;
        inline Implementation getImplementation(std::string name)const;
        std::shared_ptr<Function>sharedFunction(FunctionID id)const;
        std::shared_ptr<Function>sharedFunction(std::string name)const;
        std::shared_ptr<Statement>sharedStatement(FunctionID id)const;
        std::shared_ptr<Statement>sharedStatement(std::string name)const;
        std::shared_ptr<StatementFactory>sharedFactory(FunctionID id,StatementFactory::Uses maxUses = 1)const;
        std::shared_ptr<StatementFactory>sharedFactory(std::string name,StatementFactory::Uses maxUses = 1)const;
        std::string str()const;
    };

    inline FunctionRegister::FunctionRegister(
        std::shared_ptr<TypeRegister>const&typeRegister,
        std::shared_ptr<Namer>const&namer){
      assert(typeRegister!=nullptr);
      this->_typeRegister = typeRegister;
      this->_functions[0]=FunctionDefinition(
          TypeRegister::getTypeTypeId<TypeRegister::Unregistered>(),
          "unregistered",
          nullptr);
      this->_namer = namer;
    }


    inline FunctionRegister::~FunctionRegister(){
    }

    inline FunctionRegister::FunctionDefinition &FunctionRegister::_getDefinition(FunctionID id){
      assert(this!=nullptr);
      auto ii=this->_functions.find(id);
      if(ii==this->_functions.end()){
        ge::core::printError("FunctionRegister::_getDefinition","there is no such function id",id);
        return this->_functions.find(0)->second;
      }
      return ii->second;
    }

    
    inline FunctionRegister::FunctionDefinition const&FunctionRegister::_getDefinition(FunctionID id)const{
      assert(this!=nullptr);
      auto ii=this->_functions.find(id);
      if(ii==this->_functions.end()){
        ge::core::printError("FunctionRegister::_getDefinition","there is no such function id",id);
        return this->_functions.find(0)->second;
      }
      return ii->second;
    }

    inline TypeRegister::TypeID FunctionRegister::getType(FunctionID id)const{
      assert(this!=nullptr);
      return std::get<TYPE>(this->_getDefinition(id));
    }

    inline std::string FunctionRegister::getName(FunctionID id)const{
      assert(this!=nullptr);
      return std::get<NAME>(this->_getDefinition(id));
    }

    inline std::shared_ptr<StatementFactory>FunctionRegister::getFactory(FunctionID id)const{
      assert(this!=nullptr);
      return std::get<FACTORY>(this->_getDefinition(id));
    }

    inline FunctionRegister::FunctionID FunctionRegister::getFunctionId(std::string name)const{
      assert(this!=nullptr);
      auto ii=this->_name2Function.find(name);
      if(ii==this->_name2Function.end()){
        ge::core::printError("FunctionRegister::getFunctionId","there is no such function name",name);
        return 0;
      }
      return ii->second;
    }

    inline FunctionRegister::InputIndex FunctionRegister::getNofInputs(FunctionID id)const{
      assert(this!=nullptr);
      assert(this->_typeRegister!=nullptr);
      auto t=this->getType(id);
      if(t==TypeRegister::getTypeTypeId<TypeRegister::Unregistered>()){
        ge::core::printError("FunctionRegister::getNofInputs","there is no such function",id);
        return 0;
      }
      return this->_typeRegister->getNofFceArgs(t);
    }

    inline std::string FunctionRegister::getOutputName(FunctionID id)const{
      assert(this!=nullptr);
      assert(this->_namer!=nullptr);
      return this->_namer->getFceOutputName(id);
    }

    inline std::string FunctionRegister::getInputName(FunctionID id,InputIndex input)const{
      assert(this!=nullptr);
      assert(this->_namer!=nullptr);
      return this->_namer->getFceInputName(id,input);
    }

    inline TypeRegister::TypeID FunctionRegister::getInputType(FunctionID id,InputIndex input)const{
      assert(this!=nullptr);
      assert(this->_typeRegister!=nullptr);
      auto type = this->getType(id);
      return this->_typeRegister->getFceArgTypeId(type,input);
    }

    inline TypeRegister::TypeID FunctionRegister::getOutputType(FunctionID id)const{
      assert(this!=nullptr);
      assert(this->_typeRegister!=nullptr);
      auto type = this->getType(id);
      return this->_typeRegister->getFceReturnTypeId(type);
    }


    inline FunctionRegister::InputIndex FunctionRegister::getInputIndex(FunctionID id,std::string name)const{
      assert(this!=nullptr);
      assert(this->_namer!=nullptr);
      return this->_namer->getFceInput(id,name);
    }

    inline void FunctionRegister::setInputName(FunctionID id,InputIndex input,std::string name){
      assert(this!=nullptr);
      assert(this->_namer!=nullptr);
      this->_namer->setFceInputName(id,input,name);
    }

    inline void FunctionRegister::setOutputName(FunctionID id,std::string name){
      assert(this!=nullptr);
      assert(this->_namer!=nullptr);
      this->_namer->setFceOutputName(id,name);
    }

    inline std::shared_ptr<TypeRegister>const&FunctionRegister::getTypeRegister()const{
      assert(this!=nullptr);
      return this->_typeRegister;
    }

    inline void FunctionRegister::addImplementation(FunctionID id,Implementation impl){
      assert(this!=nullptr);
      this->_implementations[id]=impl;
    }
    
    inline void FunctionRegister::addImplementation(std::string name,Implementation impl){
      assert(this!=nullptr);
      this->addImplementation(this->getFunctionId(name),impl);
    }

    inline FunctionRegister::Implementation FunctionRegister::getImplementation(FunctionID id)const{
      assert(this!=nullptr);
      assert(this->_implementations.count(id)!=0);
      return this->_implementations.find(id)->second;
    }

    inline FunctionRegister::Implementation FunctionRegister::getImplementation(std::string name)const{
      assert(this!=nullptr);
      return this->getImplementation(this->getFunctionId(name));
    }


  }
}
