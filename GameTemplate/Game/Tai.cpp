#include "stdafx.h"
#include "Tai.h"



Tai::Tai()
{

}

Tai::~Tai()
{

}

bool Tai::OnInit()
{
	SetUI("Assets/modelData/taiUI.DDS",Vector3::One*m_fishData.individualFactor);
	SetFishType(FishType::TAI);
	SetParameter(10.0f, 5.0f, 10000.0f, 0.6, 50, 50);
	SetTimeUntilEscape(5.0f);
	SetInitPos(0.6f);
	SetScore();
	return true;
}
