#pragma once

#include <geSG/Export.h>
#include <geSG/SkeletalTransform.h>

#include <memory>
#include <vector>


namespace ge {
   namespace sg
   {
      class Model;
      class Skeleton;
      class SkeletonInstance;
      class SkeletalAnimationMixer;

      class RigModel
      {
      public:
         std::shared_ptr<Model> model;
         std::shared_ptr<Skeleton> skeleton;
      };

      class GESG_EXPORT RigModelInstance
      {
      public:
         RigModelInstance();
         RigModelInstance(RigModelInstance* orig);

         std::shared_ptr<RigModel> rigModel;
         std::shared_ptr<SkeletonInstance> skeletonInstance;
         std::shared_ptr<SkeletalAnimationMixer> animationMixer;
         std::shared_ptr<MatrixTransformNode> node;

         std::shared_ptr<std::vector<std::shared_ptr<SkeletalTransform>>> skeletalTransforms;
      };

   }
}
