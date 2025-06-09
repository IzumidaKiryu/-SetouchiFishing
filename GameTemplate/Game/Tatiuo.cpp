#include "stdafx.h"
#include "Tatiuo.h"

Tatiuo::Tatiuo()
{

	SetFishType(FishType::TATIUO);
	SetParameter(
		12.0f,
		5.0f,
		120.0f,
		0.7,
		80,
		30,
		0.3f
	);
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