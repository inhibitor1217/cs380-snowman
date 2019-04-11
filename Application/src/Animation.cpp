#include <Animation.hpp>
#include <algorithm>

Animation::Animation()
{
	keyframes_torso = std::map<float, glm::quat>();
	keyframes_head = std::map<float, glm::quat>();
	keyframes_leftShoulder = std::map<float, glm::quat>();
	keyframes_rightShoulder = std::map<float, glm::quat>();
	_time = 0.0f;
}

void Animation::InitTime()
{
	_time = 0.0f;
}

void Animation::AddTime(float deltaTime)
{
	_time += deltaTime;
}

float Animation::GetTime()
{
	return _time;
}

void Animation::AnimateSnowman(Snowman *snowman)
{
	if (keyframes_torso.size() == 0
		|| keyframes_head.size() == 0
		|| keyframes_leftShoulder.size() == 0
		|| keyframes_rightShoulder.size() == 0)
		throw std::exception();

	if (keyframes_torso.size() == 1)
		snowman->b_torsoJoint->SetOrientation(glm::mat4_cast(keyframes_torso.begin()->second));
	else
	{
		for (auto it = keyframes_torso.begin(); ; )
		{
			float t0 = it->first;
			glm::quat q0 = it->second;

			if (it == keyframes_torso.begin() && _time < t0)
			{
				snowman->b_torsoJoint->SetOrientation(glm::mat4_cast(q0));
				break;
			}

			it++;
			if (it == keyframes_torso.end())
			{
				snowman->b_torsoJoint->SetOrientation(glm::mat4_cast(q0));
				break;
			}

			float t1 = it->first;
			glm::quat q1 = it->second;

			if (t0 <= _time && _time < t1)
			{
				snowman->b_torsoJoint->SetOrientation(
					glm::mat4_cast(glm::slerp(q0, q1, (_time - t0) / (t1 - t0)))
				);
				break;
			}
		}
	}

	if (keyframes_head.size() == 1)
		snowman->b_headJoint->SetOrientation(glm::mat4_cast(keyframes_head.begin()->second));
	else
	{
		for (auto it = keyframes_head.begin(); ; )
		{
			float t0 = it->first;
			glm::quat q0 = it->second;

			if (it == keyframes_head.begin() && _time < t0)
			{
				snowman->b_headJoint->SetOrientation(glm::mat4_cast(q0));
				break;
			}

			it++;
			if (it == keyframes_head.end())
			{
				snowman->b_headJoint->SetOrientation(glm::mat4_cast(q0));
				break;
			}

			float t1 = it->first;
			glm::quat q1 = it->second;

			if (t0 <= _time && _time < t1)
			{
				snowman->b_headJoint->SetOrientation(
					glm::mat4_cast(glm::slerp(q0, q1, (_time - t0) / (t1 - t0)))
				);
				break;
			}
		}
	}

	if (keyframes_leftShoulder.size() == 1)
		snowman->b_leftShoulder->SetOrientation(glm::mat4_cast(keyframes_leftShoulder.begin()->second));
	else
	{
		for (auto it = keyframes_leftShoulder.begin(); ; )
		{
			float t0 = it->first;
			glm::quat q0 = it->second;

			if (it == keyframes_leftShoulder.begin() && _time < t0)
			{
				snowman->b_leftShoulder->SetOrientation(glm::mat4_cast(q0));
				break;
			}

			it++;
			if (it == keyframes_leftShoulder.end())
			{
				snowman->b_leftShoulder->SetOrientation(glm::mat4_cast(q0));
				break;
			}

			float t1 = it->first;
			glm::quat q1 = it->second;

			if (t0 <= _time && _time < t1)
			{
				snowman->b_leftShoulder->SetOrientation(
					glm::mat4_cast(glm::slerp(q0, q1, (_time - t0) / (t1 - t0)))
				);
				break;
			}
		}
	}

	if (keyframes_rightShoulder.size() == 1)
		snowman->b_rightShoulder->SetOrientation(glm::mat4_cast(keyframes_rightShoulder.begin()->second));
	else
	{
		for (auto it = keyframes_rightShoulder.begin(); ; )
		{
			float t0 = it->first;
			glm::quat q0 = it->second;

			if (it == keyframes_rightShoulder.begin() && _time < t0)
			{
				snowman->b_rightShoulder->SetOrientation(glm::mat4_cast(q0));
				break;
			}

			it++;
			if (it == keyframes_rightShoulder.end())
			{
				snowman->b_rightShoulder->SetOrientation(glm::mat4_cast(q0));
				break;
			}

			float t1 = it->first;
			glm::quat q1 = it->second;

			if (t0 <= _time && _time < t1)
			{
				snowman->b_rightShoulder->SetOrientation(
					glm::mat4_cast(glm::slerp(q0, q1, (_time - t0) / (t1 - t0)))
				);
				break;
			}
		}
	}
}