// some includes need to be placed before GE_SG_ATTRIB_STORAGE_H define
// to prevent problems of circular includes
#include <geSG/AttribConfig.h>

#ifndef GE_SG_ATTRIB_STORAGE_H
#define GE_SG_ATTRIB_STORAGE_H

#include <memory>
#include <geSG/Export.h>
#include <geSG/AllocationManagers.h>

namespace ge
{
   namespace sg
   {
      class AttribReference;


      /** \brief AttribStorage class maintains vertex attributes,
       *  indices and draw commands data of scene objects.
       */
      class GESG_EXPORT AttribStorage {
      protected:

         bool _privateFlag;
         BlockAllocationManager _vertexAllocationManager;  ///< Allocation manager of blocks of vertices.
         BlockAllocationManager _indexAllocationManager;   ///< Allocation manager of blocks of indices.
         AttribConfigRef _attribConfig;        ///< Configuration and formats of OpenGL attributes stored in this AttribStorage.
         RenderingContext* _renderingContext;

      public:

         AttribStorage() = delete;
         AttribStorage(const AttribConfigRef &config,unsigned numVertices,unsigned numIndices);
         virtual ~AttribStorage();

         virtual void bind() = 0;

         virtual bool allocData(AttribReference &r,int numVertices,int numIndices);
         virtual bool reallocData(AttribReference &r,int numVertices,int numIndices,
                                  bool preserveContent=true);
         virtual void freeData(AttribReference &r);

         virtual void uploadVertices(AttribReference &r,const void*const *attribs,
                                     int fromIndex=0,int numVertices=-1) = 0;
         virtual void uploadIndices(AttribReference &r,const void *indices,
                                    int fromIndex=0,int numIndices=-1) = 0;

         inline const BlockAllocation& getVertexAllocationBlock(unsigned id) const; ///< Returns vertex data allocation block at index id.
         inline const BlockAllocation& getIndexAllocationBlock(unsigned id) const;  ///< Returns index data allocation block at index id.
         inline BlockAllocation& getVertexAllocationBlock(unsigned id);  ///< Returns vertex data allocation block at index id. If modifying returned data, the care must be taken to not break internal data consistency.
         inline BlockAllocation& getIndexAllocationBlock(unsigned id);   ///< Returns index data allocation block at index id. If modifying returned data, the care must be taken to not break internal data consistency.

         inline const AttribConfigRef& getAttribConfig() const;
         inline RenderingContext* getRenderingContext() const;
         inline bool isPrivate() const;

         inline unsigned getNumVerticesTotal() const;              ///< Returns total number of vertices that can be stored in this AttribStorage.
         inline unsigned getNumVerticesAvailable() const;          ///< Returns number of vertices that are available in this AttribStorage.
         inline unsigned getNumVerticesAvailableAtTheEnd() const;  ///< Returns number of vertices that are available at the end of the AttribStorage.
         inline unsigned getFirstVertexAvailableAtTheEnd() const;  ///< Returns index of the first available vertex at the end of the AttribStorage.
         inline unsigned getIdOfVertexBlockAtTheEnd() const;       ///< Returns id (index to _vertexAllocationManager) of the last allocated block at the end of the AttribStorage.
         inline unsigned getNumIndicesTotal() const;               ///< Returns total number of indices that can be stored in this AttribStorage.
         inline unsigned getNumIndicesAvailable() const;           ///< Returns number of indices that are available in this AttribStorage.
         inline unsigned getNumIndicesAvailableAtTheEnd() const;   ///< Returns number of indices that are available at the end of the AttribStorage.
         inline unsigned getFirstIndexAvailableAtTheEnd() const;   ///< Returns index of the first available index at the end of the AttribStorage.
         inline unsigned getIdOfIndicesBlockAtTheEnd() const;      ///< Returns id (index to _indexAllocationManager) of the last allocated block at the end of the AttribStorage.
         inline BlockAllocationManager& getVertexAllocationManager();
         inline BlockAllocationManager& getIndexAllocationManager();
         inline const BlockAllocationManager& getVertexAllocationManager() const;
         inline const BlockAllocationManager& getIndexAllocationManager() const;

         virtual void cancelAllAllocations();

         class Factory {
         public:
            virtual std::shared_ptr<AttribStorage> create(const AttribConfigRef &config,
                     unsigned numVertices,unsigned numIndices);
         };
         static inline std::shared_ptr<Factory>& getFactory();
         static inline void setFactory(std::shared_ptr<Factory>& f);

      protected:
         static std::shared_ptr<Factory> _factory;
      };

   }
}



// inline and template methods
//
// note: they need their own includes that can not be placed on the beginning of this file
//       as there are circular header includes and the classes need to be defined before
//       inline methods to avoid incomplete type compiler error

namespace ge
{
   namespace sg
   {
      inline const BlockAllocation& AttribStorage::getVertexAllocationBlock(unsigned id) const  { return _vertexAllocationManager[id]; }
      inline const BlockAllocation& AttribStorage::getIndexAllocationBlock(unsigned id) const  { return _indexAllocationManager[id]; }
      inline BlockAllocation& AttribStorage::getVertexAllocationBlock(unsigned id)  { return _vertexAllocationManager[id]; }
      inline BlockAllocation& AttribStorage::getIndexAllocationBlock(unsigned id)  { return _indexAllocationManager[id]; }
      inline const AttribConfigRef& AttribStorage::getAttribConfig() const  { return _attribConfig; }
      inline RenderingContext* AttribStorage::getRenderingContext() const  { return _renderingContext; }
      inline bool AttribStorage::isPrivate() const  { return _privateFlag; }
      inline unsigned AttribStorage::getNumVerticesTotal() const  { return _vertexAllocationManager._numItemsTotal; }
      inline unsigned AttribStorage::getNumVerticesAvailable() const  { return _vertexAllocationManager._numItemsAvailable; }
      inline unsigned AttribStorage::getNumVerticesAvailableAtTheEnd() const  { return _vertexAllocationManager._numItemsAvailableAtTheEnd; }
      inline unsigned AttribStorage::getFirstVertexAvailableAtTheEnd() const  { return _vertexAllocationManager._firstItemAvailableAtTheEnd; }
      inline unsigned AttribStorage::getIdOfVertexBlockAtTheEnd() const  { return _vertexAllocationManager._idOfBlockAtTheEnd; }
      inline unsigned AttribStorage::getNumIndicesTotal() const  { return _indexAllocationManager._numItemsTotal; }
      inline unsigned AttribStorage::getNumIndicesAvailable() const  { return _indexAllocationManager._numItemsAvailable; }
      inline unsigned AttribStorage::getNumIndicesAvailableAtTheEnd() const  { return _indexAllocationManager._numItemsAvailableAtTheEnd; }
      inline unsigned AttribStorage::getFirstIndexAvailableAtTheEnd() const  { return _indexAllocationManager._firstItemAvailableAtTheEnd; }
      inline unsigned AttribStorage::getIdOfIndicesBlockAtTheEnd() const  { return _indexAllocationManager._idOfBlockAtTheEnd; }
      inline BlockAllocationManager& AttribStorage::getVertexAllocationManager()  { return _vertexAllocationManager; }
      inline BlockAllocationManager& AttribStorage::getIndexAllocationManager()  { return _indexAllocationManager; }
      inline const BlockAllocationManager& AttribStorage::getVertexAllocationManager() const  { return _vertexAllocationManager; }
      inline const BlockAllocationManager& AttribStorage::getIndexAllocationManager() const  { return _indexAllocationManager; }
      inline std::shared_ptr<AttribStorage::Factory>& AttribStorage::getFactory() { return _factory; }
      inline void AttribStorage::setFactory(std::shared_ptr<AttribStorage::Factory>& f) { _factory = f; }

   }
}

#endif // GE_SG_ATTRIB_STORAGE_H