#pragma once
#include "Animator.h"
class RotateCupAnimator : public Animator
{
public:
	//Animator function from Animator.h
	glm::mat4 Animate(glm::mat4 model) override;
};
