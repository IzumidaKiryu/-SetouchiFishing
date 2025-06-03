#include "stdafx.h"
#include "Tatiuo.h"

Tatiuo::Tatiuo()
{

	SetFishType(FishType::TATIUO);
	SetBaseScore(120.0f);
	SetScore();
	SetTimeUntilEscape(10.0f);
	SetInitPos(0.7f);
}

Tatiuo::~Tatiuo()
{
	SetUI("Assets/modelData/tatiuo.DDS");
}

bool Tatiuo::Init()
{
	SetUI("Assets/modelData/tatiuo.DDS");
	return true;
}