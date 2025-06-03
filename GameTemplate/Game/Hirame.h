#pragma once
#include "Fish.h"

class Hirame : public Fish
{
public:
	Hirame();
	~Hirame();
	bool Init() override;


	void Effect()override;
};

