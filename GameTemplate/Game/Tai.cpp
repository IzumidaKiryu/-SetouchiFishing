#include "stdafx.h"
#include "Tai.h"



Tai::Tai()
{
	SetFishType(FishType::TAI);
	SetParameter(10.0f, 5.0f, 10000.0f, 0.6, 50, 50);
	SetTimeUntilEscape(5.0f);
	SetInitPos(0.6f);
	SetScore();
}

Tai::~Tai()
{

}

bool Tai::Init()
{
	SetUI("Assets/modelData/taiUI.DDS");
	return true;
}
