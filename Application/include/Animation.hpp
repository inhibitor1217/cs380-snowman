#pragma once

#include <RenderObject.hpp>
#include "Snowman.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

class Animation
{
public:
	struct KeyFrame
	{
		float timeStamp;
		glm::quat torsoJoint;
		glm::quat headJoint;
		glm::quat leftShoulder;
		glm::quat rightShoulder;
	};

private:
	std::vector<KeyFrame> _keyframes;
	float _time;

public:
	Animation();
	void AddKeyFrame(float time, glm::mat4 torso, glm::mat4 head,
		glm::mat4 leftShoulder, glm::mat4 rightShoulder);
	void AddKeyFrame(float time, glm::quat torso, glm::quat head, 
		glm::quat leftShoulder, glm::quat rightShoulder);
	void AddKeyFrame(KeyFrame keyframe);
	std::vector<KeyFrame> GetKeyFrames() { return _keyframes; }
	void AnimateSnowman(Snowman *snowman);
	void InitTime();
	void AddTime(float deltaTime);

private:
	KeyFrame Interpolate(float time);
};