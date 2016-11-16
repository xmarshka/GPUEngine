#pragma once

#include<iostream>

namespace ge{
  namespace parser{
    /**
     * @brief token represents one lexem. Tokens are produced by lexical analysis
     */
    class Token{
      public:
        using Type = size_t;
        using Data = std::string;
        inline Token(Type const& type,Data const& rawData = "");
        inline Token();
        Data rawData;
        Type type;
    };

    inline Token::Token(){
      this->type = 0;
      this->rawData = "";
    }

    inline Token::Token(Type const& type,Data const& rawData){
      this->type = type;
      this->rawData = rawData;
    }

  }
}
