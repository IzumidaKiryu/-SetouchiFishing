#include "stdafx.h"
#include "Buri.h"

Buri::Buri()
{

	SetFishType(FishType::BURI);
	SetParameter(10.0f, 5.0f, 100.0f, 0.6,50,50);
}

Buri::~Buri()
{

}

bool Buri::Init()
{
	SetUI("Assets/modelData/buriUI.DDS");

	return true;
}