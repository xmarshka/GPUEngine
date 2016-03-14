#ifndef GE_CORE_IDOF_H
#define GE_CORE_IDOF_H

#include <map>
#include <string>

namespace ge {
namespace core {


typedef unsigned _idof_t;
#define idof_t ge::core::_idof_t


template<typename T=void> // template only avoids the need to put the function to the cpp file
std::map<std::string,std::map<std::string,unsigned>>& idof_get_global_register()
{
   static std::map<std::string,std::map<std::string,idof_t>> r;
   return r;
}


#if defined(_MSC_VER) && _MSC_VER<1900 // MSVC 2013 workaround (it does not support constexpr
                                       // and passing string as 
                                       // struct id_name { const char* chars = #_id_name_; };
                                       // does not seem to work.
                                       // So, we provide alternative solution (little less optimal)
                                       // that allow us to use even this compiler)


static idof_t idof_lookup(const char* id_chars,const char* register_chars)
{
#if 0 // debug
   std::cout<<"Init entry \""<<id_chars<<"\" on \""<<register_chars<<'\"'<<std::endl;
#endif
   auto& globalRegister=idof_get_global_register();
   auto& localRegister=globalRegister[register_chars];
   auto it=localRegister.find(id_chars);
   if(it!=localRegister.end())
      return it->second;
   idof_t& x=localRegister[id_chars];
   x=idof_t(localRegister.size());
#if 0 // debug
   std::cout<<"Created entry \""<<id_chars<<"\": "<<x<<std::endl;
#endif
   return x;
}


#define idof_2(_name_,_register_name_) \
[]() -> unsigned { \
   static idof_t id = ge::core::idof_lookup(#_name_,#_register_name_); \
   return id; \
}()


#else // full blown optimal solution using all template features


template<unsigned count,template<unsigned...> class meta_functor,unsigned... indices>
struct idof_apply_range
{
   typedef typename idof_apply_range<count-1,meta_functor,count-1,indices...>::result result;
};


template<template<unsigned...> class meta_functor,unsigned... indices>
struct idof_apply_range<0,meta_functor,indices...>
{
   typedef typename meta_functor<indices...>::result result;
};


template<char... str>
struct idof_string
{
   static constexpr const char chars[sizeof...(str)+1] = {str...,'\0'};
};


template<char... str>
constexpr const char idof_string<str...>::chars[sizeof...(str)+1];


template<typename lambda_str_type>
struct idof_string_builder
{
   template<unsigned... indices>
   struct produce
   {
      typedef idof_string<lambda_str_type{}.chars[indices]...> result;
   };
};


template<typename id_name,typename register_name>
class idof_template {
public:
   static unsigned id;
};


template<typename id_name,typename register_name>
unsigned idof_template<id_name,register_name>::id = []()->idof_t {
      auto id_chars=id_name{}.chars;
      auto register_chars=register_name{}.chars;
#if 0 // debug
      std::cout<<"Init \""<<id_chars<<"\" on \""<<register_chars<<'\"'<<std::endl;
#endif
      auto& globalRegister=idof_get_global_register();
      auto& localRegister=globalRegister[register_chars];
      auto it=localRegister.find(id_chars);
      if(it!=localRegister.end())
         return it->second;
      idof_t& x=localRegister[id_chars];
      x=idof_t(localRegister.size());
#if 0 // debug
      std::cout<<"Created entry \""<<id_chars<<"\": "<<x<<std::endl;
#endif
      return x;
   }();


#define idof_2(_id_name_,_register_name_) \
([]() -> idof_t { \
   struct id_name { const char* chars = #_id_name_; }; \
   struct register_name { const char* chars = #_register_name_; }; \
   return ge::core::idof_template< \
      ge::core::idof_apply_range<sizeof(#_id_name_)-1, \
         ge::core::idof_string_builder<id_name      >::produce>::result, \
      ge::core::idof_apply_range<sizeof(#_register_name_)-1, \
         ge::core::idof_string_builder<register_name>::produce>::result \
      >::id; \
}())


#endif // MSVC 2013 workaround and optimal template solution


#define idof_1(_name_) \
   idof_2(_name_,)

#define idof_get_macro(_1,_2,_3,_macro_name_,...) _macro_name_
#define idof_msvc_workaround(x) x

// note1: last parameter "true" kills warning about "ISO C99 requires rest arguments to be used" on g++ (seen on version 4.8.2)
// note2: second parameter "true" is just empty argument, offsetting the rest of arguments
// note3: idof_msvc_workaround workarounds different expansion behaviour of MSVC (seen on version 2015.0 (no update))
#define idof(...) \
   idof_msvc_workaround(idof_get_macro( \
         __VA_ARGS__,true,idof_2,idof_1,true)(__VA_ARGS__))

} // namespace core
} // namespace ge

#endif /* GE_CORE_IDOF_H */