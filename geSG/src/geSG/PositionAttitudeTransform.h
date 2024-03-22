#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <memory>

namespace ge
{
	namespace sg {

		class PositionAttitudeTransform
		{
		public:
			PositionAttitudeTransform(glm::vec3 p, glm::quat o, glm::vec3 s) : position{p}, orientation{o}, scale{s} {}

			glm::vec3 position;
			glm::quat orientation;
			glm::vec3 scale;
		};

	}
}