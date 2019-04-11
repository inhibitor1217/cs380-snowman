#pragma once

#include <RenderObject.hpp>
#include "Snowman.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <map>

class Animation
{
private:
	float _time;

public:
	std::map<float, glm::quat> keyframes_torso;
	std::map<float, glm::quat> keyframes_head;
	std::map<float, glm::quat> keyframes_leftShoulder;
	std::map<float, glm::quat> keyframes_rightShoulder;

public:
	Animation();
	void AnimateSnowman(Snowman *snowman);
	void InitTime();
	void AddTime(float deltaTime);
};