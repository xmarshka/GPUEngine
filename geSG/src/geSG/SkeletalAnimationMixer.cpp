#include <geSG/SkeletalAnimationMixer.h>
#include <geSG/SkeletalTransform.h>

#include <algorithm>
#include <chrono>
#include <vector>

using namespace ge::sg;
using namespace ge::core;


/**
 * Updates each animation to time point t. 
 */
void SkeletalAnimationMixer::update(const time_point& t)
{
   std::for_each(playingAnimations.begin(), playingAnimations.end(), [t](std::shared_ptr<Animation> animation){animation->update(t); });
   std::for_each(skeletalTransforms->begin(), skeletalTransforms->end(), 
      [this](std::shared_ptr<ge::sg::SkeletalTransform> &transform)
   {
      if (transform->patQueue->empty())
         (*transform->getRefMatrix()) = *transform->originalTransform;
      else
      {
         PositionAttitudeTransform pat = transform->patQueue->back().second;

         glm::mat4 mat = glm::mat4_cast(pat.orientation);
         mat = glm::scale(mat, pat.scale);
         mat[3] = glm::vec4(pat.position, 1.f);

         *transform->getRefMatrix() = mat;

         while (!transform->patQueue->empty())
            transform->patQueue->pop();

         // interpolace transformaci ve fronte
         // ve fronte je par ID animace a pat
      }
      if (transform->parentIndex != -1)
         *transform->getRefMatrix() = (*this->skeletalTransforms)[transform->parentIndex]->getMatrix() * transform->getMatrix();
   }
   );
   removeFinishedAnimation();
}

void SkeletalAnimationMixer::playAnimation(unsigned num, const time_point& startTime, Animation::Mode mode)
{
   if (num < this->animations.size()) {
      std::shared_ptr<ge::sg::Animation> animation = this->animations.at(num);
         auto it = std::find(playingAnimations.begin(), playingAnimations.end(), animation);
      if (it == playingAnimations.end())
      {
         playingAnimations.push_back(animation);
      }
      animation->start(startTime);
   }
}

void SkeletalAnimationMixer::stopAnimations()
{
   this->playingAnimations.clear();
}

void SkeletalAnimationMixer::removeFinishedAnimation()
{
   auto it = playingAnimations.begin();
   for(; it != playingAnimations.end(); )
   {
      if((*it)->getCurrentTime() >= time_point((*it)->duration) && (*it)->mode == Animation::Mode::ONCE)
      {
         auto rm = it;
         ++it;
         playingAnimations.erase(rm);
      }
      else
      {
         ++it;
      }
   }
}
