#pragma once

#include<geCore/Export.h>

namespace ge{
  namespace core{
    class FunctionRegister;
    GECORE_EXPORT void registerStdNumericFunctions(
        std::shared_ptr<FunctionRegister>const&fr);
  }
}