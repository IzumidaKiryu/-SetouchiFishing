#include "stdafx.h"
#include "Hirame.h"

Hirame::Hirame()
{

	SetFishType(FishType::HIRAME);
	SetBaseScore(180);
	SetParameter(
		15.0f,
		10.0f,
		120.0f,
		0.7,
		40,
		60);
}

Hirame::~Hirame()
{

}

bool Hirame::Init()
{
	SetUI("Assets/modelData/hirameUI.DDS");

	return true;
}

void Hirame::Effect()
{

}
