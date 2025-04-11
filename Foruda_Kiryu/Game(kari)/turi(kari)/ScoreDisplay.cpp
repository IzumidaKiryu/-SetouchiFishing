#include "stdafx.h"
#include "ScoreDisplay.h"
#include"PlayFishing.h"

ScoreDisplay::ScoreDisplay()
{
	m_playFishing=FindGO<PlayFishing>("playFishing");
	ScoreUI(m_playFishing->GetFIshScore());
}

ScoreDisplay::~ScoreDisplay()
{
}

void ScoreDisplay::ScoreUI(float score)
{

}
