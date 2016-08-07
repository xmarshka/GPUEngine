#pragma once

#include<geDE/Export.h>
#include<geCore/Dtemplates.h>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<typeinfo>
#include<functional>
#include<memory>
#include<geDE/TypeRegister.h>

namespace ge{
  namespace de{
    class TypeRegister;
    class Function;
    class AtomicFunction;

    class GEDE_EXPORT Resource{
      friend class Function;
      friend class AtomicFunction;
      public:
        inline Resource(
            std::shared_ptr<TypeRegister>const&manager = nullptr                   ,
            TypeId                             id      = TypeRegister::UNREGISTERED);
        virtual ~Resource();
        inline std::shared_ptr<TypeRegister>const&getManager()const;
        virtual void*getData()const = 0;
        virtual void const*getDataAddress()const = 0;
        inline TypeId getId()const;
        virtual std::shared_ptr<Resource> operator[](size_t elem) = 0;
        virtual size_t getNofElements()const=0;
        virtual std::string data2Str()const=0;
        template<typename T>
          Resource& operator=(const T&data);
        template<typename T>
          operator T&()const;
        template<typename T>
          operator T*()const;
        template<typename T>
          operator T**()const;
        void setProducer(std::shared_ptr<Function>const&f);
        Ticks getTicks()const;
        void updateTicks();
        template<typename T>
          void update(T const&value);
        bool hasSignalingSource(Function*fce)const;
        bool hasSignalingTarget(Function*fce)const;
        size_t nofSignalingSources()const;
        size_t nofSignalingTargets()const;
      protected:
        std::set<Function*>_signalingSources;
        std::set<Function*>_signalingTargets;
        Ticks _ticks = 1;
        std::shared_ptr<TypeRegister>_manager = nullptr;
        TypeId _id = TypeRegister::UNREGISTERED;
        std::shared_ptr<Function>_producer = nullptr;
        void _setSignalingDirty();
        void _addSignalingSource(Function*f);
        void _removeSignalingSource(Function*f);
        void _addSignalingTarget(Function*f);
        void _removeSignalingTarget(Function*f);
        virtual void operator()();
    };

    inline Resource::Resource(
        std::shared_ptr<TypeRegister>const&manager,
        TypeId               id     ){
      PRINT_CALL_STACK(manager,id);
      assert(this!=nullptr);
      this->_manager = manager;
      this->_id = id;
    }

    inline std::shared_ptr<TypeRegister>const&Resource::getManager()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_manager;
    }

    inline TypeId Resource::getId()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_id;
    }

    template<typename T>
      Resource& Resource::operator=(const T&data){
        PRINT_CALL_STACK(data);
        assert(this!=nullptr);
        assert(this->getData()!=nullptr);
        *((T*)this->getData()) = data;
        return *this;
      }

    template<typename T>
      Resource::operator T&()const{
        PRINT_CALL_STACK();
        assert(this!=nullptr);
        assert(this->getData()!=nullptr);
        return *((T*)this->getData());
      }

    template<typename T>
      Resource::operator T*()const{
        PRINT_CALL_STACK();
        assert(this!=nullptr);
        assert(this->getData()!=nullptr);
        return *(T**)this->getData();
      }

    
    template<typename T>
      Resource::operator T**()const{
        PRINT_CALL_STACK();
        assert(this!=nullptr);
        return (T**)this->getData();//this->getDataAddress();
      }

    inline void Resource::_addSignalingSource(Function*f){
      PRINT_CALL_STACK(f);
      assert(this!=nullptr);
      assert(f!=nullptr);
      this->_signalingSources.insert(f);
    }

    inline void Resource::_removeSignalingSource(Function*f){
      PRINT_CALL_STACK(f);
      assert(this!=nullptr);
      assert(f!=nullptr);
      this->_signalingSources.erase(f);
    }

    inline void Resource::_addSignalingTarget(Function*f){
      PRINT_CALL_STACK(f);
      assert(this!=nullptr);
      assert(f!=nullptr);
      this->_signalingTargets.insert(f);
    }

    inline void Resource::_removeSignalingTarget(Function*f){
      PRINT_CALL_STACK(f);
      assert(this!=nullptr);
      assert(f!=nullptr);
      this->_signalingTargets.erase(f);
    }
    inline Ticks Resource::getTicks()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_ticks;
    }
    inline void Resource::updateTicks(){
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      this->_ticks++;
    }
    template<typename T>
      inline void Resource::update(T const&value){
        PRINT_CALL_STACK(value);
        assert(this!=nullptr);
        (T&)*this = value;
        this->updateTicks();
      }

    inline bool Resource::hasSignalingSource(Function*statement)const{
      PRINT_CALL_STACK(statement);
      assert(this!=nullptr);
      return this->_signalingSources.count(statement)!=0;
    }

    inline bool Resource::hasSignalingTarget(Function*statement)const{
      PRINT_CALL_STACK(statement);
      assert(this!=nullptr);
      return this->_signalingTargets.count(statement)!=0;
    }


    inline size_t Resource::nofSignalingSources()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_signalingSources.size();
    }

    inline size_t Resource::nofSignalingTargets()const{
      PRINT_CALL_STACK();
      assert(this!=nullptr);
      return this->_signalingTargets.size();
    }


  }
}
