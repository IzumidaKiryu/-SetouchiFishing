#include "stdafx.h"
#include "Hirame.h"

Hirame::Hirame()
{


}

Hirame::~Hirame()
{

}


bool Hirame::OnInit()
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
	SetUI("Assets/modelData/hirameUI.DDS",Vector3::One*m_fishData.individualFactor);
	SetBuff(BuffType::StealBoostBuff,100.0f);

	return true;
}