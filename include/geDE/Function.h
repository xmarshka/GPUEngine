#pragma once

#include<geDE/Statement.h>
#include<geDE/FunctionRegister.h>

namespace ge{
  namespace de{

    // function: Resource compositor
    // function: selector of element of Resource

    class Resource;
    class AtomicFunction;
    class Nullary;
    class GEDE_EXPORT Function: public Statement{
      friend class AtomicFunction;
      public:
        using InputIndex = size_t;
        using Ticks      = uint64_t;
        inline Function(
            std::shared_ptr<FunctionRegister>const&fr,
            FunctionRegister::FunctionID           id);
        virtual inline ~Function();
        inline FunctionRegister::FunctionID getId()const;
        virtual bool bindInput (
            std::shared_ptr<FunctionRegister>const&fr                ,
            InputIndex                             i                 ,
            std::shared_ptr<Function>        const&function = nullptr) = 0;
        virtual bool bindOutput(
            std::shared_ptr<FunctionRegister>const&fr                ,
            std::shared_ptr<Resource>        const&data     = nullptr) = 0;
        virtual bool bindOutput(
            std::shared_ptr<FunctionRegister>const&fr                ,
            std::shared_ptr<Nullary>         const&nullary  = nullptr) = 0;
        virtual bool hasInput (InputIndex i)const = 0;
        virtual bool hasOutput(            )const = 0; 
        virtual std::shared_ptr<Resource>const&getInputData (InputIndex i)const = 0;
        virtual std::shared_ptr<Resource>const&getOutputData(            )const = 0;
        virtual std::shared_ptr<Function>const&getInputFunction(InputIndex i)const = 0;
        virtual inline std::string doc()const;
      protected:
        Statement*_outputSignaling = nullptr;
        FunctionRegister::FunctionID     _id;
        bool _inputBindingCheck (
            std::shared_ptr<FunctionRegister>const&fr      ,
            InputIndex                             i       ,
            std::shared_ptr<Function>        const&function)const;
        bool _outputBindingCheck(
            std::shared_ptr<FunctionRegister>const&fr      ,
            std::shared_ptr<Resource>        const&resource)const;
    };

    inline Function::Function(
        std::shared_ptr<FunctionRegister>const&,
        FunctionRegister::FunctionID id):Statement(FUNCTION){
      this->_id = id;
    }

    inline Function::~Function(){
    }

    FunctionRegister::FunctionID Function::getId()const{
      return this->_id;
    }

    inline std::string Function::doc()const{
      assert(this!=nullptr);
      return"";
    }

  }
}
