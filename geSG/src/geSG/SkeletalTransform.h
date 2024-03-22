#pragma once

#include <geSG/Export.h>
#include <geSG/Transform.h>
#include <geSG/MatrixTransform.h>
#include <geSG/Node.h>
#include <geSG/PositionAttitudeTransform.h>
#include <glm/glm.hpp>
#include <memory>
#include <queue>
#include <utility>

namespace ge{
   namespace sg
   {
      class GESG_EXPORT SkeletalTransform : public MatrixTransformBase
      {
      public:
         SkeletalTransform(std::shared_ptr<glm::mat4> origTransform, int parentId);
         SkeletalTransform(SkeletalTransform* skTransform);

         virtual ~SkeletalTransform();

		  std::shared_ptr<glm::mat4> originalTransform;
          int parentIndex;
		  std::shared_ptr<std::queue<std::pair<unsigned, PositionAttitudeTransform>>> patQueue;
      };
   }
}