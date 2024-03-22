#include <geSG/Skeleton.h>

#include <glm/gtc/type_ptr.hpp>

float *ge::sg::SkeletonInstance::getBoneTransforms()
{
   this->finalTransforms.resize(this->bones.size() * 16);

   for (int i = 0; i < this->bones.size(); ++i) {
      glm::mat4 transform = this->skeleton->inverseTransform * this->bones[i].transform->getMatrix() * this->bones[i].bone->meshToBone;
      memcpy(this->finalTransforms.data() + 16 * i, glm::value_ptr(transform), sizeof(float) * 16);
   }

   return this->finalTransforms.data();
}
