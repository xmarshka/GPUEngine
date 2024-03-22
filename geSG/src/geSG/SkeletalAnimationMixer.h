#pragma once

#include <geSG/Animation.h>
#include <geSG/SkeletalTransform.h>

#include <chrono>
#include <memory>
#include <vector>
#include <list>


namespace ge {
   namespace sg
   {
      class GESG_EXPORT SkeletalAnimationMixer : public core::Updatable
      {
      public:
         virtual void update(const core::time_point& t) override;
         void playAnimation(unsigned num, const ge::core::time_point& startTime, Animation::Mode mode = Animation::Mode::LOOP);
         void stopAnimations();

         virtual ~SkeletalAnimationMixer(){}

         std::shared_ptr<std::vector<std::shared_ptr<SkeletalTransform>>> skeletalTransforms;
         std::vector<std::shared_ptr<Animation>> animations;
         std::list<std::shared_ptr<Animation>> playingAnimations;

      private:
         void removeFinishedAnimation();
      };
   }
}
