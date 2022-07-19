#pragma once

#include "Animator.h"

class BodyAnimator : public Animator
{
public:
	glm::mat4 Animate(glm::mat4 model) override;
};

