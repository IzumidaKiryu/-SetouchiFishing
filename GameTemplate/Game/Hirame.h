#pragma once
#include "Fish.h"

class Hirame : public Fish
{
public:
	Hirame();
	~Hirame();
	bool OnInit() override;


	void Effect()override;
};

