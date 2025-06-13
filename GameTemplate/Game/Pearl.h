#pragma once
#include "Fish.h"

class Pearl:public Fish
{
public:
	Pearl();
	~Pearl();
	bool OnInit() override;
};

