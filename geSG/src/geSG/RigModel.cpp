#include <geSG/RigModel.h>
#include <geSG/SkeletalAnimationMixer.h>
#include <geSG/SkeletalAnimationChannel.h>
#include <geSG/Skeleton.h>

#include <memory>
#include <map>

ge::sg::RigModelInstance::RigModelInstance()
{ }

ge::sg::RigModelInstance::RigModelInstance(RigModelInstance* orig)
{
   using TransformMap = std::map<ge::sg::SkeletalTransform*, std::shared_ptr<ge::sg::SkeletalTransform>>;
   using PatQueueTrMap = std::map<ge::sg::SkeletalAnimationPushChannel::idPatQueue*, ge::sg::SkeletalTransform*>;

   TransformMap transformMap;
   PatQueueTrMap patQueueTrMap;

   this->rigModel = orig->rigModel;
   this->skeletalTransforms = std::make_shared<std::vector<std::shared_ptr<ge::sg::SkeletalTransform>>>();

   for (auto transform : *orig->skeletalTransforms) {
      this->skeletalTransforms->push_back(std::make_shared<ge::sg::SkeletalTransform>(transform.get()));
      transformMap[transform.get()] = this->skeletalTransforms->back();
      patQueueTrMap[transform->patQueue.get()] = this->skeletalTransforms->back().get();
   }

   this->skeletonInstance = std::make_shared<ge::sg::SkeletonInstance>();
   this->skeletonInstance->skeleton = orig->skeletonInstance->skeleton;
   for (auto origBone : orig->skeletonInstance->bones) {
      ge::sg::BoneInstance newBone;
      newBone.bone = origBone.bone;
      newBone.transform = transformMap[origBone.transform.get()];
      this->skeletonInstance->bones.push_back((newBone));
   }

   this->animationMixer = std::make_shared<ge::sg::SkeletalAnimationMixer>();
   this->animationMixer->skeletalTransforms = this->skeletalTransforms;

   std::for_each(orig->animationMixer->animations.begin(), orig->animationMixer->animations.end(),
      [this, orig, &patQueueTrMap](std::shared_ptr<ge::sg::Animation> &anim) {
      this->animationMixer->animations.emplace_back(std::make_shared<ge::sg::Animation>());
      this->animationMixer->animations.back()->mode = ge::sg::Animation::Mode::LOOP;
      std::for_each(anim->channels.begin(), anim->channels.end(),
         [this, orig, &patQueueTrMap](std::shared_ptr<ge::sg::AnimationChannel> &chan) {
         std::shared_ptr<SkeletalAnimationPushChannel> ch = std::dynamic_pointer_cast<SkeletalAnimationPushChannel>(chan);
         std::shared_ptr<SkeletalAnimationPushChannel> newCh = std::make_shared<SkeletalAnimationPushChannel>();
         newCh->orientationKF = ch->orientationKF;
         newCh->positionKF = ch->positionKF;
         newCh->scaleKF = ch->scaleKF;
         newCh->setTarget(patQueueTrMap.at(ch->getTargetPointer().get())->patQueue);
         newCh->animationID = this->animationMixer->animations.size() - 1;
         this->animationMixer->animations.back()->channels.push_back(newCh);
      });
   });
}
