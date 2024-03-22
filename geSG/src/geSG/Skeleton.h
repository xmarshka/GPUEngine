#pragma once

#include <glm/glm.hpp>
#include <geSG/Bone.h>
#include <vector>
#include <memory>

namespace ge
{
   namespace sg {
      class Animation;

      class Skeleton
      {
      public:

         std::vector<std::shared_ptr<Bone>> bones;
         std::vector<std::shared_ptr<Animation>> animations; ///holds animations
         glm::mat4 inverseTransform;
      protected:
      };

      class GESG_EXPORT SkeletonInstance
      {
      public:

         std::shared_ptr<Skeleton> skeleton;
         std::vector<BoneInstance> bones;
         std::vector<float> finalTransforms;

         float *getBoneTransforms();
      };
   }
}