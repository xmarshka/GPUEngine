#pragma once

#include <glm/glm.hpp>
#include <geSG/Animation.h>
#include <geSG/Node.h>
#include <geSG/SkeletalTransform.h>
#include <vector>
#include <memory>

namespace ge
{
	namespace sg {

		class Bone
		{
		public:

			std::string name;
			glm::mat4 meshToBone;
			std::shared_ptr<MatrixTransformNode> node;

		protected:
		};

		class BoneInstance
		{
		public:

			std::shared_ptr<Bone> bone;
			std::shared_ptr<SkeletalTransform> transform;

		protected:
		};
	}
}