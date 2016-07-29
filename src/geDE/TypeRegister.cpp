#include<geDE/TypeRegister.h>

#include<geDE/AtomicResource.h>
#include<sstream>
#include<memory>
#include<cassert>
#include<cstring>
#include<vector>

#include<geCore/ErrorPrinter.h>
#include<geDE/TypeDescription.h>
#include<geDE/AtomicDescription.h>
#include<geDE/PtrDescription.h>
#include<geDE/ArrayDescription.h>
#include<geDE/StructDescription.h>
#include<geDE/FceDescription.h>
#include<geDE/MemFceDescription.h>
#include<geDE/VoidDescription.h>
#include<geDE/AnyDescription.h>

using namespace ge::de;

class Function;

TypeRegister::TypeRegister(){
  this->addCompositeType(keyword<Any>(),{ANY});
  auto Void   = this->addAtomicType(keyword<void       >(),0                  );(void)Void;
  auto Bool   = this->addAtomicType(keyword<bool       >(),sizeof(bool       ));
  auto I8     = this->addAtomicType(keyword<int8_t     >(),sizeof(int8_t     ));
  auto I16    = this->addAtomicType(keyword<int16_t    >(),sizeof(int16_t    ));
  auto I32    = this->addAtomicType(keyword<int32_t    >(),sizeof(int32_t    ));
  auto I64    = this->addAtomicType(keyword<int64_t    >(),sizeof(int64_t    ));
  auto U8     = this->addAtomicType(keyword<uint8_t    >(),sizeof(uint8_t    ));
  auto U16    = this->addAtomicType(keyword<uint16_t   >(),sizeof(uint16_t   ));
  auto U32    = this->addAtomicType(keyword<uint32_t   >(),sizeof(uint32_t   ));
  auto U64    = this->addAtomicType(keyword<uint64_t   >(),sizeof(uint64_t   ));
  auto F32    = this->addAtomicType(keyword<float      >(),sizeof(float      ));
  auto F64    = this->addAtomicType(keyword<double     >(),sizeof(double     ));
  auto String = this->addAtomicType(keyword<std::string>(),sizeof(std::string),[](void*ptr){new(ptr)std::string();},[](void*ptr){((std::string*)ptr)->~basic_string();});
  this->addCompositeType("vec2",{ARRAY,2,F32});
  this->addCompositeType("vec3",{ARRAY,3,F32});
  this->addCompositeType("vec4",{ARRAY,4,F32});
  this->addCompositeType("ivec2",{ARRAY,2,I32});
  this->addCompositeType("ivec3",{ARRAY,3,I32});
  this->addCompositeType("ivec4",{ARRAY,4,I32});
  this->addCompositeType("uvec2",{ARRAY,2,U32});
  this->addCompositeType("uvec3",{ARRAY,3,U32});
  this->addCompositeType("uvec4",{ARRAY,4,U32});
  this->addToStrFunction(Bool,  [](void*ptr){if((bool&)ptr)return std::string("true");else return std::string("false");});
  this->addToStrFunction(I8 ,   [](void*ptr){std::stringstream ss;ss<<*(int8_t  *)ptr;return ss.str();});
  this->addToStrFunction(I16,   [](void*ptr){std::stringstream ss;ss<<*(int16_t *)ptr;return ss.str();});
  this->addToStrFunction(I32,   [](void*ptr){std::stringstream ss;ss<<*(int32_t *)ptr;return ss.str();});
  this->addToStrFunction(I64,   [](void*ptr){std::stringstream ss;ss<<*(int64_t *)ptr;return ss.str();});
  this->addToStrFunction(U8 ,   [](void*ptr){std::stringstream ss;ss<<*(uint8_t *)ptr;return ss.str();});
  this->addToStrFunction(U16,   [](void*ptr){std::stringstream ss;ss<<*(uint16_t*)ptr;return ss.str();});
  this->addToStrFunction(U32,   [](void*ptr){std::stringstream ss;ss<<*(uint32_t*)ptr;return ss.str();});
  this->addToStrFunction(U64,   [](void*ptr){std::stringstream ss;ss<<*(uint64_t*)ptr;return ss.str();});
  this->addToStrFunction(F32,   [](void*ptr){std::stringstream ss;ss<<*(float   *)ptr;return ss.str();});
  this->addToStrFunction(F64,   [](void*ptr){std::stringstream ss;ss<<*(double  *)ptr;return ss.str();});
  this->addToStrFunction(String,[](void*ptr){std::stringstream ss;ss<<"\""<<*(std::string*)ptr<<"\"";return ss.str();});
}

TypeRegister::~TypeRegister(){
  assert(this!=nullptr);
  for(auto const&x:this->_types)
    delete x;
}


TypeId TypeRegister::_addTypeByDescription(std::string const&name,TypeDescription*d){
  assert(this!=nullptr);
  TypeId id = this->_vectorIndex2TypeId(this->_types.size());
  this->_types.push_back(d);
  this->_bindTypeIdWithName(id,name);
  return id;
}

bool TypeRegister::_checkIfTypeNameExists(
    TypeId&result,
    std::string const&name,
    TypeDescription*d,
    std::string const&errFceName,
    std::string const&errMsg){
  assert(this!=nullptr);
  auto ii = this->_name2TypeId.find(name);
  if(ii==this->_name2TypeId.end())return false;
  if(!d->equal(this->_getDescription(ii->second))){
    ge::core::printError(errFceName,errMsg);
    delete d;
    result = UNREGISTERED;
    return true;
  }
  delete d;
  result = ii->second;
  return true;
}


bool TypeRegister::_checkIfTypeDescriptionExists(
    TypeId&result,
    std::string const&name,
    TypeDescription*d){
  assert(this!=nullptr);
  TypeId index = 0;
  for(auto const&x:this->_types){
    if(d->equal(x)){
      TypeId id = this->_vectorIndex2TypeId(index);
      assert(this->_typeId2Synonyms.count(id)!=0);
      if(name!="")this->_typeId2Synonyms.at(id).insert(name);
      delete d;
      result = id;
      return true;
    }
    index++;
  }
  return false;
}

TypeId TypeRegister::_checkAndAddTypeByDescription(
    std::string const&name,
    TypeDescription*d,
    std::string const&errFceName,
    std::string const&errMsg){
  assert(this!=nullptr);
  TypeId id;
  if(this->_checkIfTypeNameExists(id,name,d,errFceName,errMsg))
    return id;

  if(this->_checkIfTypeDescriptionExists(id,name,d))
    return id;

  return this->_addTypeByDescription(name,d);
}


TypeId TypeRegister::addAtomicType(
    std::string const&name       ,
    size_t      const&size       ,
    CDPtr       const&constructor,
    CDPtr       const&destructor ){
  assert(this!=nullptr);
  auto newDesc = new AtomicDescription(size,constructor,destructor);
  assert(newDesc!=nullptr);

  TypeId id;
  if(this->_checkIfTypeNameExists(id,name,newDesc,GE_CORE_FCENAME,"Atomic type named "+name+" already exists and is different"))
    return id;

  if(constructor!=nullptr&&destructor!=nullptr)
    if(this->_checkIfTypeDescriptionExists(id,name,newDesc))
      return id;

  return this->_addTypeByDescription(name,newDesc);
}

TypeId TypeRegister::addPtrType(
    std::string const&name,
    TypeId      const&innerType){
  assert(this!=nullptr);
  auto newDesc = new PtrDescription(innerType);
  assert(newDesc!=nullptr);
  return this->_checkAndAddTypeByDescription(name,newDesc,GE_CORE_FCENAME,"Ptr type named "+name+" already exists and is different");
}

TypeId TypeRegister::addArrayType(
    std::string const&name     ,
    TypeId      const&innerType,
    size_t      const&size     ){
  assert(this!=nullptr);
  auto newDesc = new ArrayDescription(innerType,size);
  assert(newDesc!=nullptr);
  return this->_checkAndAddTypeByDescription(name,newDesc,GE_CORE_FCENAME,"Array type named "+name+" already exists and is different");
}

TypeId TypeRegister::addStructType(
    std::string        const&name     ,
    std::vector<TypeId>const&elements){
  assert(this!=nullptr);
  auto newDesc = new StructDescription(elements);
  assert(newDesc!=nullptr);
  return this->_checkAndAddTypeByDescription(name,newDesc,GE_CORE_FCENAME,"Struct type named "+name+" already exists and is different");
}

TypeId TypeRegister::addFceType(
    std::string        const&name      ,
    TypeId             const&returnType,
    std::vector<TypeId>const&elements  ){
  assert(this!=nullptr);
  auto newDesc = new FceDescription(returnType,elements);
  assert(newDesc!=nullptr);
  return this->_checkAndAddTypeByDescription(name,newDesc,GE_CORE_FCENAME,"Fce type named "+name+" already exists and is different");
}

TypeId TypeRegister::addMemFceType(
    std::string        const&name      ,
    TypeId             const&returnType,
    TypeId             const&classType ,
    std::vector<TypeId>const&elements  ){
  assert(this!=nullptr);
  auto newDesc = new MemFceDescription(returnType,classType,elements);
  assert(newDesc!=nullptr);
  return this->_checkAndAddTypeByDescription(name,newDesc,GE_CORE_FCENAME,"MemFce type named "+name+" already exists and is different");
}


//MemFce
//Void

TypeId TypeRegister::addAnyType(
    std::string        const&name){
  assert(this!=nullptr);
  auto newDesc = new AnyDescription();
  assert(newDesc!=nullptr);
  return this->_checkAndAddTypeByDescription(name,newDesc,GE_CORE_FCENAME,"Any type named "+name+" already exists and is different");
}




void TypeRegister::_bindTypeIdWithName(TypeId id,std::string const&name){
  assert(this!=nullptr);
  if(name==""){
    auto ii = this->_typeId2Synonyms.find(id);
    if(ii!=this->_typeId2Synonyms.end())return;
    std::stringstream ss;
    ss<<"type"<<id;
    this->_typeId2Synonyms[id].insert(ss.str());
    this->_name2TypeId[ss.str()]=id;
    return;
  }
  this->_typeId2Synonyms[id].insert(name);
  this->_name2TypeId[name]=id;
}

TypeId TypeRegister::_typeExists(
    TypeDescriptionVector const&description,
    size_t                 &i){
  assert(this!=nullptr);
  if(i>=description.size())return UNREGISTERED;
  switch(description[i]){
    case UNREGISTERED:return UNREGISTERED;
    case ATOMIC      :return UNREGISTERED;
    case PTR         :{PtrDescription      desc;return desc.findInRegister(this,description,i);}
    case ARRAY       :{ArrayDescription    desc;return desc.findInRegister(this,description,i);}
    case STRUCT      :{StructDescription   desc;return desc.findInRegister(this,description,i);}
    case FCE         :{FceDescription      desc;return desc.findInRegister(this,description,i);}
    case MEMFCE      :{MemFceDescription   desc;return desc.findInRegister(this,description,i);}
    case VOID        :{VoidDescription     desc;return desc.findInRegister(this,description,i);}
    case ANY         :{AnyDescription      desc;return desc.findInRegister(this,description,i);}
    default          :return this->_typeIdExists(description,i);
  }
}

TypeId TypeRegister::_typeIdExists(
    TypeDescriptionVector const&description,
    size_t                 &i){
  assert(this!=nullptr);
  if(i>=description.size())return UNREGISTERED;
  if(description[i]<TYPEID)return UNREGISTERED;
  if(this->_typeId2VectorIndex(description[i])>=this->_types.size())
    return UNREGISTERED;
  return description[i++];
}

TypeId TypeRegister::addCompositeType(
    std::string        const&name       ,
    TypeDescriptionVector  const&description){
  assert(this!=nullptr);
  size_t i=0;
  return this->_addType(name,description,i);
}

TypeId TypeRegister::_addType(
    std::string       const&name       ,
    TypeDescriptionVector const&description,
    size_t                 &i          ){
  assert(this!=nullptr);
  size_t old = i;
  auto id = this->_typeExists(description,i);
  if(id != UNREGISTERED){
    auto ii = this->_name2TypeId.find(name);
    if(ii != this->_name2TypeId.end()){
      if(ii->second != id){
        std::cerr<<"ERROR: TypeRegister::_addType() - ";
        std::cerr<<"name "<<name<<" is already used with different type: "<<ii->second;
        std::cerr<<std::endl;
        i = old;
        return UNREGISTERED;
      }
      return id;
    }
    this->_bindTypeIdWithName(id,name);
    return id;
  }
  if(i>=description.size())return UNREGISTERED;
  switch(description[i]){
    case UNREGISTERED:return UNREGISTERED;
    case ATOMIC      :return UNREGISTERED;
    case PTR         :return TypeDescription::checkAndBindType(this,name,description,new PtrDescription   (),i);
    case ARRAY       :return TypeDescription::checkAndBindType(this,name,description,new ArrayDescription (),i);
    case STRUCT      :return TypeDescription::checkAndBindType(this,name,description,new StructDescription(),i);
    case FCE         :return TypeDescription::checkAndBindType(this,name,description,new FceDescription   (),i);
    case MEMFCE      :return TypeDescription::checkAndBindType(this,name,description,new MemFceDescription(),i);
    case VOID        :return TypeDescription::checkAndBindType(this,name,description,new VoidDescription  (),i);
    case ANY         :return TypeDescription::checkAndBindType(this,name,description,new AnyDescription   (),i);
    default          :return this->_addTypeId(name,description,i);
  }
}

TypeId TypeRegister::_addTypeId(
    std::string       const&name       ,
    TypeDescriptionVector const&description,
    size_t                 &i          ){
  assert(this!=nullptr);
  if(i>=description.size())return UNREGISTERED;
  if(description[i]<TYPEID)return UNREGISTERED;
  if(this->_typeId2VectorIndex(description[i])>=this->_types.size())return UNREGISTERED;
  if(name!=""){
    auto ii = this->_name2TypeId.find(name);
    if(ii != this->_name2TypeId.end()){
      if(ii->second != description[i]){
        std::cerr<<"ERROR: TypeRegister::_addTypeId() - ";
        std::cerr<<"name "<<name<<" is already used with different type: "<<ii->second<<" aka "<<ii->first;
        std::cerr<<std::endl;
        return UNREGISTERED;
      }
      return description[i++];
    }
    this->_bindTypeIdWithName(description[i],name);
  }
  return description[i++];
}

TypeId TypeRegister::_vectorIndex2TypeId(TypeId const&index)const{
  return index+TYPEID;
}

TypeId TypeRegister::_typeId2VectorIndex(TypeId const&id)const{
  return id-TYPEID;
}


size_t TypeRegister::getNofTypes()const{
  assert(this!=nullptr);
  return this->_types.size();
}

std::string TypeRegister::type2Str(size_t index)const{
  assert(this!=nullptr);
  assert(index<this->_types.size());
  return this->_types.at(index)->toStr(this,this->_vectorIndex2TypeId(index));
}

TypeRegister::TypeType TypeRegister::getTypeIdType(TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::getTypeIdType",id);
  assert(this!=nullptr);
  return this->_getDescription(id)->type;
}

TypeId TypeRegister::getPtrType(TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == PTR);
  return ((PtrDescription*)d)->innerType;
}

size_t TypeRegister::getArraySize(TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == ARRAY);
  return ((ArrayDescription*)d)->size;
}

TypeId TypeRegister::getArrayElementTypeId(TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == ARRAY);
  return ((ArrayDescription*)d)->elementType;
}

size_t TypeRegister::getNofStructElements(TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == STRUCT);
  return ((StructDescription*)d)->elementTypes.size();
}

TypeId TypeRegister::getStructElementTypeId(TypeId id,size_t index)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == STRUCT);
  assert(index<((StructDescription*)d)->elementTypes.size());
  return ((StructDescription*)d)->elementTypes.at(index);
}

TypeId TypeRegister::getFceReturnTypeId(TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == FCE);
  return ((FceDescription*)d)->returnType;
}

size_t TypeRegister::getNofFceArgs(TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == FCE);
  return ((FceDescription*)d)->argumentTypes.size();
}

TypeId TypeRegister::getFceArgTypeId(TypeId id,size_t index)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == FCE);
  assert(index<((FceDescription*)d)->argumentTypes.size());
  return ((FceDescription*)d)->argumentTypes.at(index);
}

TypeId TypeRegister::getMemFceReturnTypeId (TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == MEMFCE);
  return ((MemFceDescription*)d)->returnType;
}

TypeId TypeRegister::getMemFceClassTypeId  (TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == MEMFCE);
  return ((MemFceDescription*)d)->classType;
}

size_t TypeRegister::getNofMemFceArgs      (TypeId id)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == MEMFCE);
  return ((MemFceDescription*)d)->argumentTypes.size();
}

TypeId TypeRegister::getMemFceArgTypeId    (TypeId id,size_t index)const{
  assert(this!=nullptr);
  auto d = this->_getDescription(id);
  assert(d!=nullptr);
  assert(d->type == MEMFCE);
  assert(index<((MemFceDescription*)d)->argumentTypes.size());
  return ((MemFceDescription*)d)->argumentTypes.at(index);
}


TypeId TypeRegister::getTypeId(std::string const&name)const{
  assert(this!=nullptr);
  if(this->_name2TypeId.count(name)==0){
    ge::core::printError("TypeRegister::getTypeId","there is no such type",name);
    return UNREGISTERED;
  }
  return this->_name2TypeId.find(name)->second;
}

std::string const& TypeRegister::getTypeIdName(TypeId id)const{
  assert(this!=nullptr);
  assert(this->_typeId2Synonyms.count(id)!=0);
  return *this->_typeId2Synonyms.find(id)->second.begin();
}

std::set<std::string>const& TypeRegister::getTypeIdSynonyms(TypeId id)const{
  assert(this!=nullptr);
  assert(this->_typeId2Synonyms.count(id)!=0);
  return this->_typeId2Synonyms.find(id)->second;
}

bool TypeRegister::hasSynonyms(TypeId id)const{
  assert(this!=nullptr);
  assert(this->_typeId2Synonyms.count(id)!=0);
  return this->_typeId2Synonyms.find(id)->second.size()>1;
}

bool TypeRegister::areSynonyms(std::string const&name0,std::string const&name1)const{
  assert(this!=nullptr);
  if(this->_name2TypeId.count(name0)==0)return false;
  if(this->_name2TypeId.count(name1)==0)return false;
  return this->getTypeId(name0)==this->getTypeId(name1);
}


size_t TypeRegister::computeTypeIdSize(TypeId id)const{
  PRINT_CALL_STACK(id);
  assert(this!=nullptr);
  return this->_getDescription(id)->byteSize(this);
}


bool TypeRegister::areConvertible(TypeId a,TypeId b)const{
  assert(this!=nullptr);
  if(a==b)return true;
  if(this->getTypeIdType(a)==ANY)return true;
  if(this->getTypeIdType(b)==ANY)return true;
  if(this->getTypeIdType(a)==ARRAY)
    return this->areConvertible(this->getArrayElementTypeId(a),b);
  if(this->getTypeIdType(b)==ARRAY)
    return this->areConvertible(a,this->getArrayElementTypeId(b));

  return false;
  //if(a==b)return true;
  //if(this->getTypeIdType(a)==ANY)return true;
  //if(this->getTypeIdType(b)==ANY)return true;
  //if(this->getTypeIdType(a)==ARRAY){
  //  if(this->getTypeIdType(b)==PTR)
  //    return this->getArrayElementTypeId(a) == this->getPtrType(b);
  //}
  //if(this->getTypeIdType(a)==PTR){
  //  if(this->getTypeIdType(b)==ARRAY)
  //    return this->getArrayElementTypeId(b) == this->getPtrType(a);
  //}
  //return false;
}

void*TypeRegister::alloc(TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::alloc",id);
  assert(this!=nullptr);
  size_t size = this->computeTypeIdSize(id);
  uint8_t*ptr=new uint8_t[size];
  std::memset(ptr,0,size);
  return ptr;
}

void TypeRegister::free(void*ptr)const{
  PRINT_CALL_STACK("TypeRegister::free",ptr);
  assert(this!=nullptr);
  delete[]((uint8_t*)ptr);
}

void*TypeRegister::construct(TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::construct",id);
  assert(this!=nullptr);
  auto ptr=this->alloc(id);
  this->_callConstructors(ptr,id);
  return ptr;
}

void TypeRegister::destroy(void*ptr,TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::destroy",ptr,id);
  this->_callDestructors(ptr,id);
  this->free(ptr);
}

void TypeRegister::_callConstructors(void*ptr,TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::_callConstructors",ptr,id);
  assert(this!=nullptr);
  this->_getDescription(id)->callConstructor((TypeRegister*)this,ptr);
}

void TypeRegister::_callDestructors(void*ptr,TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::_callDestructors",ptr,id);
  assert(this!=nullptr);
  this->_getDescription(id)->callDestructor((TypeRegister*)this,ptr);
}

std::string TypeRegister::data2Str(void*ptr,TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::data2Str",ptr,id);
  assert(this!=nullptr);
  return this->_getDescription(id)->data2Str(this,ptr);
}

void TypeRegister::addToStrFunction(TypeId id,ToStr const&fce){
  PRINT_CALL_STACK("TypeRegister::addToStrFunction",id,fce);
  assert(this!=nullptr);
  this->_getDescription(id)->data2StrPtr = fce;
}


TypeDescription*TypeRegister::_getDescription(TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::_getDescription",id);
  assert(this!=nullptr);
  assert(this->_typeId2VectorIndex(id)<this->_types.size());
  return this->_types.at(this->_typeId2VectorIndex(id));
}

void TypeRegister::addDestructor(TypeId id,CDPtr const&destructor){
  PRINT_CALL_STACK("TypeRegister::addDestructor",id,destructor);
  assert(this!=nullptr);
  assert(this->_getDescription(id)->type == ATOMIC);// || this->_getDescription(id)->type == PTR);
  if(this->_getDescription(id)->type == ATOMIC)
    ((AtomicDescription*)this->_getDescription(id))->destructor = destructor;
  //if(this->_getDescription(id)->type == PTR)
  //  ((PtrDescription*)this->_getDescription(id))->destructor = destructor;
}

void TypeRegister::addConstructor(TypeId id,CDPtr const&constructor){
  PRINT_CALL_STACK("TypeRegister::addConstructor",id,constructor);
  assert(this!=nullptr);
  assert(this->_getDescription(id)->type == ATOMIC);// || this->_getDescription(id)->type == PTR);
  if(this->_getDescription(id)->type == ATOMIC)
    ((AtomicDescription*)this->_getDescription(id))->constructor = constructor;
  //if(this->_getDescription(id)->type == PTR)
  //  ((PtrDescription*)this->_getDescription(id))->constructor = constructor;
}

std::shared_ptr<Resource>TypeRegister::sharedResource(TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::sharedResource",id);
  assert(this!=nullptr);
  return std::make_shared<AtomicResource>(std::const_pointer_cast<TypeRegister>(this->shared_from_this()),this->construct(id),id);
}

std::shared_ptr<Resource>TypeRegister::sharedResource(std::string const&name)const{
  PRINT_CALL_STACK("TypeRegister::sharedResource",name);
  assert(this!=nullptr);
  auto id = this->getTypeId(name);
  return this->sharedResource(id);
}

std::shared_ptr<Resource>TypeRegister::sharedEmptyResource(TypeId id)const{
  PRINT_CALL_STACK("TypeRegister::sharedEmptyResource",id);
  assert(this!=nullptr);

  return std::shared_ptr<AtomicResource>(new AtomicResource(std::const_pointer_cast<TypeRegister>(this->shared_from_this()),id)
      ,[](AtomicResource*ac){ac->getManager()->destroy(ac->getData(),ac->getId());delete ac;});
  //,[destructor](AtomicResource*ac){destructor((unsigned char*)ac->getData());delete(unsigned char*)ac->getData();delete ac;});
}

std::shared_ptr<Resource>TypeRegister::sharedEmptyResource(std::string const&name)const{
  PRINT_CALL_STACK("TypeRegister::sharedEmptyResource",name);
  assert(this!=nullptr);
  return this->sharedEmptyResource(this->getTypeId(name));
}


