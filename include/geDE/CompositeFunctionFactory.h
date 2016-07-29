#pragma once

#include<vector>
#include<geDE/FunctionFactory.h>

namespace ge{
  namespace de{
    class FunctionNodeFactory;
    class FunctionRegister;

    class GEDE_EXPORT CompositeFunctionFactory: public FunctionFactory{
      public:
        using FactoryInput = std::tuple<
          std::shared_ptr<FunctionFactory>,
          size_t                          >;
        enum FceInputParts{
          FACTORY = 0,
          INPUT   = 1,
        };
        using FactoryInputList = std::vector<FactoryInput>;
        CompositeFunctionFactory(std::string const&name = "",Uses maxUses = 1);
        virtual ~CompositeFunctionFactory();
        inline std::shared_ptr<FunctionFactory>const&getInputFactory(size_t input)const;
        void setFactory(std::shared_ptr<StatementFactory>const&fac);
        void setInputFactories(std::vector<FactoryInputList>const&inputs);
        virtual std::shared_ptr<Statement>_do(std::shared_ptr<FunctionRegister>const&fr)override;
        virtual TypeId getOutputType(std::shared_ptr<FunctionRegister>const&fr)const override;
        virtual size_t getNofInputs(std::shared_ptr<FunctionRegister>const&fr)const override;
        virtual TypeId getInputType(std::shared_ptr<FunctionRegister>const&fr,size_t i)const override;
      protected:
        std::shared_ptr<FunctionNodeFactory>_factory = nullptr;
        std::vector<FactoryInputList> _inputs;
    };
  }
}
