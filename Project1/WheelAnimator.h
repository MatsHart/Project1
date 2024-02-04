#pragma once
#include "Animator.h"
class WheelAnimator : public Animator
{
private: 	
	const int rotate = -2.0f;
	int count = 0;
public:
	//Animator function from Animator.h
	glm::mat4 Animate(glm::mat4 model) override;
};

