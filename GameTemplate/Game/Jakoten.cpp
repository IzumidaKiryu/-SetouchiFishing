#include "stdafx.h"
#include "Jakoten.h"

Jakoten::Jakoten()
{

	SetFishType(FishType::JAKOTENN);
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

Jakoten::~Jakoten()
{

}

bool Jakoten::OnInit()
{
	SetUI("Assets/modelData/jakotenUI.DDS", Vector3::One * m_fishData.individualFactor);
	return true;
}