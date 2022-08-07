#pragma once

#include "Animator.h"

class BodyAnimator : public Animator
{

private:
	int count = 0;
public:
	//Animate function from Animator.h
	glm::mat4 Animate(glm::mat4 model) override;
};

