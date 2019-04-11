#include <Animation.hpp>
#include <algorithm>

Animation::Animation()
{
	_keyframes = std::vector<KeyFrame>();
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

bool compareKeyFrames(Animation::KeyFrame k1, Animation::KeyFrame k2)
{
	return k1.timeStamp < k2.timeStamp;
}

void Animation::AddKeyFrame(float time, glm::mat4 torso, glm::mat4 head, glm::mat4 leftShoulder, glm::mat4 rightShoulder)
{
	AddKeyFrame(time,
		glm::quat_cast(torso),
		glm::quat_cast(head),
		glm::quat_cast(leftShoulder),
		glm::quat_cast(rightShoulder)
	);
}

void Animation::AddKeyFrame(float time, glm::quat torso, glm::quat head, glm::quat leftShoulder, glm::quat rightShoulder)
{
	KeyFrame keyframe;
	keyframe.timeStamp = time;
	keyframe.torsoJoint = torso;
	keyframe.headJoint = head;
	keyframe.leftShoulder = leftShoulder;
	keyframe.rightShoulder = rightShoulder;

	_keyframes.push_back(keyframe);
	std::sort(_keyframes.begin(), _keyframes.end(), compareKeyFrames);
}

void Animation::AddKeyFrame(KeyFrame keyframe)
{
	_keyframes.push_back(keyframe);
	std::sort(_keyframes.begin(), _keyframes.end(), compareKeyFrames);
}

glm::quat Lerp(glm::quat q1, glm::quat q2, float t)
{
	return q1 * (1.0f - t) + q2 * t;
}

Animation::KeyFrame Animation::Interpolate(float time)
{
	if (_keyframes.size() == 0)
		throw std::exception();

	if (_keyframes.size() == 1)
		return _keyframes[0];

	if (time < _keyframes[0].timeStamp)
		return _keyframes[0];

	for (int i = 0; i < _keyframes.size() - 1; i++)
	{
		if (_keyframes[i].timeStamp <= time && time < _keyframes[i + 1].timeStamp)
		{
			float t = (time - _keyframes[i].timeStamp) / (_keyframes[i + 1].timeStamp - _keyframes[i].timeStamp);

			KeyFrame ret;
			ret.timeStamp = time;
			ret.torsoJoint = Lerp(_keyframes[i].torsoJoint, _keyframes[i + 1].torsoJoint, t);
			ret.headJoint = Lerp(_keyframes[i].headJoint, _keyframes[i + 1].headJoint, t);
			ret.leftShoulder = Lerp(_keyframes[i].leftShoulder, _keyframes[i + 1].leftShoulder, t);
			ret.rightShoulder = Lerp(_keyframes[i].rightShoulder, _keyframes[i + 1].rightShoulder, t);

			return ret;
		}
	}

	return _keyframes[_keyframes.size() - 1];
}

void Animation::AnimateSnowman(Snowman *snowman)
{
	KeyFrame keyframe = Interpolate(_time);

	snowman->b_torsoJoint->SetOrientation(glm::toMat4(keyframe.torsoJoint));
	snowman->b_headJoint->SetOrientation(glm::toMat4(keyframe.headJoint));
	snowman->b_leftShoulder->SetOrientation(glm::toMat4(keyframe.leftShoulder));
	snowman->b_rightShoulder->SetOrientation(glm::toMat4(keyframe.rightShoulder));
}