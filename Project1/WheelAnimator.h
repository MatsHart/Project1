#pragma once
#include "Animator.h"
class WheelAnimator : public Animator
{
public:
	glm::mat4 Animate(glm::mat4 model) override;
};

