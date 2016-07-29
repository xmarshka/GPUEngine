#include<geDE/ResourceFactory.h>
#include<geDE/FunctionRegister.h>
#include<geDE/TypeRegister.h>

using namespace ge::de;

std::shared_ptr<Resource>ResourceFactory::operator()(
    std::shared_ptr<FunctionRegister>const&fr){
  this->_first=this->_uses==0;
  std::shared_ptr<Resource>res;
  if(!this->_result)
    this->_result = fr->getTypeRegister()->sharedResource(this->_type);
  res=this->_result;
  this->_uses++;
  if(this->_uses==this->_maxUses){
    this->_uses   = 0      ;
    this->_result = nullptr;
  }
  return res;
}


