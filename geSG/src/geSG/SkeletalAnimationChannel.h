#pragma once

#include <geSG/Export.h>
#include <memory>
#include <vector>
#include <queue>
#include <utility>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <geSG/KeyframeInterpolator.h>
#include <geSG/AnimationKeyFrame.h>
#include <geSG/AnimationChannel.h>
#include <geSG/PositionAttitudeTransform.h>
#include <geSG/Node.h>
#include <geCore/Updatable.h>
#include <chrono>

namespace ge
{
	namespace sg {


		class GESG_EXPORT SkeletalAnimationChannelBase : public AnimationChannel
		{
		public:

			typedef AnimationKeyFrameTemplate<glm::vec3> Vec3KeyFrame;
			typedef AnimationKeyFrameTemplate<glm::quat> QuatKeyFrame;

			SkeletalAnimationChannelBase();

			virtual void update(const core::time_point& t) = 0;
			core::time_unit getDuration() const override;

			virtual ~SkeletalAnimationChannelBase();

			std::shared_ptr<std::vector<Vec3KeyFrame>> positionKF;
			std::shared_ptr<std::vector<QuatKeyFrame>> orientationKF;
			std::shared_ptr<std::vector<Vec3KeyFrame>> scaleKF;
			std::unique_ptr<KeyframeInterpolator<std::vector<Vec3KeyFrame>>> positionInterpolator;
			std::unique_ptr<KeyframeInterpolator<std::vector<QuatKeyFrame>>> orientationInterpolator;
			std::unique_ptr<KeyframeInterpolator<std::vector<Vec3KeyFrame>>> scaleInterpolator;

		protected:
		};

		class GESG_EXPORT SkeletalAnimationSetChannel : public SkeletalAnimationChannelBase
		{
		public:

			SkeletalAnimationSetChannel();

			virtual void update(const core::time_point& t);

			inline void setTarget(std::shared_ptr<glm::mat4>& target) { _target = target; }
			inline std::shared_ptr<glm::mat4>& getTarget() { return _target; }
            inline glm::mat4 getTargetMatrix() { return *_target; }
			inline std::shared_ptr<glm::mat4> getTargetPointer() { return _target; }

			virtual ~SkeletalAnimationSetChannel();

		protected:
			std::shared_ptr<glm::mat4> _target;
		};

		class GESG_EXPORT SkeletalAnimationPushChannel : public SkeletalAnimationChannelBase
		{
		public:

			using idPat = std::pair<unsigned, PositionAttitudeTransform>;
			using idPatQueue = std::queue<idPat>;

			SkeletalAnimationPushChannel();

			virtual void update(const core::time_point& t);

			inline void setTarget(std::shared_ptr<idPatQueue>& target) { _target = target; }
			inline std::shared_ptr<idPatQueue> getTargetPointer() { return _target; }

			virtual ~SkeletalAnimationPushChannel();

			unsigned animationID;

		protected:

			std::shared_ptr<idPatQueue> _target;
		};

	}
}
