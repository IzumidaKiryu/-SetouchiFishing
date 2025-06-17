#include "stdafx.h"
#include "GameGuide.h"

GameGuide::GameGuide()
{
}

GameGuide::~GameGuide()
{
}

bool GameGuide::Start()
{
	return true;
}

bool GameGuide::Init()
{
	SetGuidSprite();
	return true;
}

void GameGuide::SetGuidSprite()
{
	m_GuideSprite[0].Init("Assets/sprite/setumei/setumei_2.DDS", 1650.0f, 900.0f);
	m_GuideSprite[1].Init("Assets/sprite/setumei/setumei_3.DDS", 1650.0f, 900.0f);
	m_GuideSprite[2].Init("Assets/sprite/setumei/setumei_4.DDS", 1650.0f, 900.0f);
	m_GuideSprite[3].Init("Assets/sprite/setumei/setumei_5.DDS", 1650.0f, 900.0f);
	m_GuideSprite[4].Init("Assets/sprite/setumei/setumei_6.DDS", 1650.0f, 900.0f);
	m_GuideSprite[5].Init("Assets/sprite/setumei/setumei_7.DDS", 1650.0f, 900.0f);
	m_GuideSprite[6].Init("Assets/sprite/setumei/setumei_8.DDS", 1650.0f, 900.0f);
	m_GuideSprite[7].Init("Assets/sprite/setumei/setumei_9.DDS", 1650.0f, 900.0f);
	m_GuideSprite[8].Init("Assets/sprite/setumei/setumei.DDS", 1650.0f, 900.0f);


}

void GameGuide::OnUpdate()
{

	if (g_pad[0]->IsTrigger(enButtonB))
	{
		m_pageIndex++;
	}
	if (m_pageIndex!=0) {
		if (g_pad[0]->IsTrigger(enButtonX))
		{
			m_pageIndex--;
		}
	}
}

bool GameGuide::ShouldChangeState()
{
	if (m_pageIndex >= 9) {
		SetNextName("inGameState");

		return true;
	}
	else {
		return false;
	}
}

void GameGuide::OnEnter()
{
}

void GameGuide::OnExit()
{
}

void GameGuide::Render(RenderContext& rc)
{
	if(0<=m_pageIndex&& m_pageIndex<=8)
	m_GuideSprite[m_pageIndex].Draw(rc);
}
