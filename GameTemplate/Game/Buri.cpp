#include "stdafx.h"
#include "Buri.h"

Buri::Buri()
{

}

Buri::~Buri()
{

}

bool Buri::OnInit()
{
	SetFishType(FishType::BURI);
	SetParameter(10.0f, 5.0f, 100.0f, 0.6, 50, 50);
	SetUI("Assets/modelData/buriUI.DDS",Vector3::One * m_fishData.individualFactor);

	return true;
}