#pragma once

#include "Animator.h"

class BodyAnimator : public Animator
{
public:
	//Animate function from Animator.h
	glm::mat4 Animate(glm::mat4 model) override;
};

