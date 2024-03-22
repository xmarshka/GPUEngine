#include <geSG/MatrixTransform.h>
#include <geSG/SkeletalTransform.h>

#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
#include <memory>


ge::sg::SkeletalTransform::SkeletalTransform(std::shared_ptr<glm::mat4> origTransform, int parentId)
   : MatrixTransformBase(*origTransform), originalTransform(origTransform), parentIndex(parentId), patQueue(std::make_shared<std::queue<std::pair<unsigned, PositionAttitudeTransform>>>())
{
}

ge::sg::SkeletalTransform::SkeletalTransform(SkeletalTransform* skTransform)
   : SkeletalTransform(skTransform->originalTransform, skTransform->parentIndex)
{
}

ge::sg::SkeletalTransform::~SkeletalTransform()
{
}