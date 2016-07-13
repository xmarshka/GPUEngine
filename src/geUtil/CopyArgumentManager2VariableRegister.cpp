#include<geUtil/CopyArgumentManager2VariableRegister.h>
#include<geDE/VariableRegister.h>
#include<geDE/FunctionRegister.h>
#include<geDE/Resource.h>
#include<geDE/AtomicResource.h>
#include<geDE/StdFunctions.h>

using namespace ge::de;
using namespace ge::util;

void ArgData2Description(
    TypeRegister::DescriptionVector&descriptor,
    ArgData*data,
    std::shared_ptr<TypeRegister>const&tr){
  ArgData::Type type=data->getType();
  switch(type){
    case ArgData::BOOL:
      descriptor.push_back(tr->getTypeId(TypeRegister::getTypeKeyword<bool>()));
      return;
    case ArgData::I8:
      descriptor.push_back(tr->getTypeId(TypeRegister::getTypeKeyword<int8_t>()));
      return;
    case ArgData::I16:
      descriptor.push_back(tr->getTypeId(TypeRegister::getTypeKeyword<int16_t>()));
      return;
    case ArgData::I32:
      descriptor.push_back(tr->getTypeId(TypeRegister::getTypeKeyword<int32_t>()));
      return;
    case ArgData::I64:
      descriptor.push_back(tr->getTypeId(TypeRegister::getTypeKeyword<int64_t>()));
      return;
    case ArgData::U8:
      descriptor.push_back(tr->getTypeId(TypeRegister::getTypeKeyword<uint8_t>()));
      return;
    case ArgData::U16:
      descriptor.push_back(tr->getTypeId(TypeRegister::getTypeKeyword<uint16_t>()));
      return;
    case ArgData::U32:
      descriptor.push_back(tr->getTypeId(TypeRegister::getTypeKeyword<uint32_t>()));
      return;
    case ArgData::U64:
      descriptor.push_back(tr->getTypeId(TypeRegister::getTypeKeyword<uint64_t>()));
      return;
    case ArgData::F32:
      descriptor.push_back(tr->getTypeId(TypeRegister::getTypeKeyword<float>()));
      return;
    case ArgData::F64:
      descriptor.push_back(tr->getTypeId(TypeRegister::getTypeKeyword<double>()));
      return;
    case ArgData::STRING:
      descriptor.push_back(tr->getTypeId(TypeRegister::getTypeKeyword<std::string>()));
      return;
    case ArgData::ARRAY:
      descriptor.push_back(TypeRegister::ARRAY);
      descriptor.push_back((unsigned)((ArrayData*)data)->size());
      ArgData2Description(descriptor,(*((ArrayData*)data))[0],tr);
      return;
    case ArgData::STRUCT:
      descriptor.push_back(TypeRegister::STRUCT);
      descriptor.push_back((unsigned)((StructData*)data)->size());
      for(unsigned i=0;i<((StructData*)data)->size();++i)
        ArgData2Description(descriptor,(*((StructData*)data))[i],tr);
      return;
  }
}

void ArgData2Resource(std::shared_ptr<Resource>const&ac,ArgData*data){
  ArgData::Type type=data->getType();
  switch(type){
    case ArgData::BOOL:
      *std::dynamic_pointer_cast<AtomicResource>(ac)=((BaseData<bool>*)data)->get();
      return;
    case ArgData::I8:
      *std::dynamic_pointer_cast<AtomicResource>(ac)=((BaseData<char>*)data)->get();
      return;
    case ArgData::I16:
      *std::dynamic_pointer_cast<AtomicResource>(ac)=((BaseData<short>*)data)->get();
      return;
    case ArgData::I32:
      *std::dynamic_pointer_cast<AtomicResource>(ac)=((BaseData<int>*)data)->get();
      return;
    case ArgData::I64:
      *std::dynamic_pointer_cast<AtomicResource>(ac)=((BaseData<int long long>*)data)->get();
      return;
    case ArgData::U8:
      *std::dynamic_pointer_cast<AtomicResource>(ac)=((BaseData<unsigned char>*)data)->get();
      return;
    case ArgData::U16:
      *std::dynamic_pointer_cast<AtomicResource>(ac)=((BaseData<unsigned short>*)data)->get();
      return;
    case ArgData::U32:
      *std::dynamic_pointer_cast<AtomicResource>(ac)=((BaseData<unsigned int>*)data)->get();
      return;
    case ArgData::U64:
      *std::dynamic_pointer_cast<AtomicResource>(ac)=((BaseData<unsigned long long>*)data)->get();
      return;
    case ArgData::F32:
      *std::dynamic_pointer_cast<AtomicResource>(ac)=((BaseData<float>*)data)->get();
      return;
    case ArgData::F64:
      *std::dynamic_pointer_cast<AtomicResource>(ac)=((BaseData<double>*)data)->get();
      return;
    case ArgData::STRING:
      *std::dynamic_pointer_cast<AtomicResource>(ac)=((BaseData<std::string>*)data)->get();
      return;
    case ArgData::ARRAY:
      for(unsigned i=0;i<((ArrayData*)data)->size();++i)
        ArgData2Resource((*std::dynamic_pointer_cast<::AtomicResource>(ac))[i],(*((ArrayData*)data))[i]);
      return;
    case ArgData::STRUCT:
      for(unsigned i=0;i<((StructData*)data)->size();++i)
        ArgData2Resource((*std::dynamic_pointer_cast<::AtomicResource>(ac))[i],(*((StructData*)data))[i]);
      return;
  }
}

void ge::util::copyArgumentManager2VariableRegister(
    std::shared_ptr<VariableRegister>const&vr,
    ArgumentManager const&argm,
    std::shared_ptr<FunctionRegister>const&fr){
  auto tr = fr->getTypeRegister();
  for(auto const&x:argm){
    TypeRegister::DescriptionVector typeDescriptor;
    ArgData2Description(typeDescriptor,x.second,tr);
    std::shared_ptr<Resource>sac=tr->sharedResource(tr->addCompositeType("",typeDescriptor));
    ArgData2Resource(sac,x.second);
    auto var = std::make_shared<ge::de::Nullary>(fr,fr->getFunctionId("Nullary"));
    var->bindOutput(fr,sac);
    vr->insert(x.first,var);
  }
}
