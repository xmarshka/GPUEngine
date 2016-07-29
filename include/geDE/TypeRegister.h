#pragma once

#include<geDE/Export.h>
//#include<geCore/Dtemplates.h>
#include<geCore/CallStackPrinter.h>
#include<geDE/Types.h>
#include<geDE/Keyword.h>

#include<vector>
#include<map>
#include<set>
#include<iostream>
#include<memory>

namespace ge{
  namespace de{
    class Any;
    class Resource;
    class TypeDescription;
    class AtomicDescription;
    class PtrDescription;
    class ArrayDescription;
    class StructDescription;
    class FceDescription;
    class MemFceDescription;
    class VoidDescription;
    class AnyDescription;
    class GEDE_EXPORT TypeRegister: public std::enable_shared_from_this<TypeRegister>{
      friend class TypeDescription;
      friend class AtomicDescription;
      friend class PtrDescription;
      friend class ArrayDescription;
      friend class StructDescription;
      friend class FceDescription;
      friend class MemFceDescription;
      friend class VoidDescription;
      friend class AnyDescription;
      public:
        using ToStr = std::string(*)(void*);
        enum TypeType{
          UNREGISTERED = 0,
          ATOMIC       = 1,
          PTR          = 2,
          ARRAY        = 3,
          STRUCT       = 4,
          FCE          = 5,
          MEMFCE       = 6,
          VOID         = 7,
          ANY          = 8,
          TYPEID       = 9,
        };
        TypeRegister();
        virtual ~TypeRegister();
        TypeId addAtomicType(
              std::string const&name                 ,
              size_t      const&size                 ,
              CDPtr       const&constructor = nullptr,
              CDPtr       const&destructor  = nullptr);
        TypeId addPtrType(
            std::string const&name     ,
            TypeId      const&innerType);
        TypeId addArrayType(
            std::string const&name     ,
            TypeId      const&innerType,
            size_t      const&size     );
        TypeId addStructType(
            std::string        const&name    ,
            std::vector<TypeId>const&elements);
        TypeId addFceType(
            std::string        const&name      ,
            TypeId             const&returnType,
            std::vector<TypeId>const&args      );
        TypeId addMemFceType(
            std::string        const&name      ,
            TypeId             const&returnType,
            TypeId             const&classType ,
            std::vector<TypeId>const&args      );
        TypeId addVoidType(
            std::string const&name);
        TypeId addAnyType(
            std::string const&name);

        TypeId addCompositeType(
            std::string           const&name       ,
            TypeDescriptionVector const&description);
        size_t getNofTypes()const;
        std::string type2Str(size_t typeIndex)const;
        TypeType                    getTypeIdType         (TypeId id)const;
        size_t                      getNofStructElements  (TypeId id)const;
        TypeId                      getStructElementTypeId(TypeId id,size_t index)const;
        size_t                      getArraySize          (TypeId id)const;
        TypeId                      getArrayElementTypeId (TypeId id)const;
        TypeId                      getPtrType            (TypeId id)const;
        TypeId                      getFceReturnTypeId    (TypeId id)const;
        size_t                      getNofFceArgs         (TypeId id)const;
        TypeId                      getFceArgTypeId       (TypeId id,size_t index)const;
        TypeId                      getMemFceReturnTypeId (TypeId id)const;
        TypeId                      getMemFceClassTypeId  (TypeId id)const;
        size_t                      getNofMemFceArgs      (TypeId id)const;
        TypeId                      getMemFceArgTypeId    (TypeId id,size_t index)const;
        TypeId                      getTypeId             (std::string const&name)const;
        std::string const&          getTypeIdName         (TypeId id)const;
        std::set<std::string>const& getTypeIdSynonyms     (TypeId id)const;
        bool                        hasSynonyms           (TypeId id)const;
        bool                        areSynonyms           (std::string const&name0,std::string const&name1)const;
        size_t                      computeTypeIdSize     (TypeId id)const;
        bool                        areConvertible        (TypeId a,TypeId b)const;
        void*alloc(TypeId id)const;
        void free(void*ptr)const;
        void*construct(TypeId id)const;
        void destroy(void*ptr,TypeId id)const;
        std::string data2Str(void*ptr,TypeId id)const;
        void addToStrFunction(TypeId id,ToStr const&fce = nullptr);
        std::shared_ptr<Resource>sharedResource(TypeId id)const;
        std::shared_ptr<Resource>sharedResource(std::string const&name)const;
        std::shared_ptr<Resource>sharedEmptyResource(TypeId id)const;
        std::shared_ptr<Resource>sharedEmptyResource(std::string const&name)const;
        void addDestructor (TypeId id,CDPtr const&destructor  = nullptr);
        void addConstructor(TypeId id,CDPtr const&constructor = nullptr);
      protected:
        std::vector<TypeDescription*> _types;
        std::map<TypeId,std::set<std::string>>_typeId2Synonyms;
        std::map<std::string,TypeId>_name2TypeId;
        TypeId _vectorIndex2TypeId(TypeId const&index)const;
        TypeId _typeId2VectorIndex(TypeId const&id   )const;
        void _bindTypeIdWithName(TypeId id,std::string const&name);
        TypeId _typeExists(
            TypeDescriptionVector const&description,
            size_t                     &i);
        TypeId _typeIdExists(
            TypeDescriptionVector const&description,
            size_t                     &i);
        TypeId _addType(
            std::string           const&name       ,
            TypeDescriptionVector const&description,
            size_t                     &i          );
        TypeId _addTypeId(
            std::string           const&name       ,
            TypeDescriptionVector const&description,
            size_t                     &i          );
        void _callConstructors(void*ptr,TypeId id)const;
        void _callDestructors (void*ptr,TypeId id)const;
        TypeDescription*_getDescription(TypeId id)const;
        TypeId _addTypeByDescription(std::string const&name,TypeDescription*d);
        bool _checkIfTypeNameExists(
            TypeId&result,
            std::string const&name,
            TypeDescription*d,
            std::string const&errFceName,
            std::string const&errMsg);
        bool _checkIfTypeDescriptionExists(
            TypeId&result,
            std::string const&name,
            TypeDescription*d);
        TypeId _checkAndAddTypeByDescription(
            std::string const&name,
            TypeDescription*d,
            std::string const&errFceName,
            std::string const&errMsg);
    };


#define GE_DE_ADD_KEYWORD(type,name)\
    template<>inline std::string keyword<type>(){return name;}

    GE_DE_ADD_KEYWORD(void       ,"void"  )
    GE_DE_ADD_KEYWORD(bool       ,"bool"  )
    GE_DE_ADD_KEYWORD(int8_t     ,"i8"    )
    GE_DE_ADD_KEYWORD(int16_t    ,"i16"   )
    GE_DE_ADD_KEYWORD(int32_t    ,"i32"   )
    GE_DE_ADD_KEYWORD(int64_t    ,"i64"   )
    GE_DE_ADD_KEYWORD(uint8_t    ,"u8"    )
    GE_DE_ADD_KEYWORD(uint16_t   ,"u16"   )
    GE_DE_ADD_KEYWORD(uint32_t   ,"u32"   )
    GE_DE_ADD_KEYWORD(uint64_t   ,"u64"   )
    GE_DE_ADD_KEYWORD(float      ,"f32"   )
    GE_DE_ADD_KEYWORD(double     ,"f64"   )
    GE_DE_ADD_KEYWORD(std::string,"string")
    GE_DE_ADD_KEYWORD(Any        ,"any"   )
  }
}

