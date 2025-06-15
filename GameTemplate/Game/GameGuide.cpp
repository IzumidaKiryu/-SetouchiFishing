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
	return false;
}

bool GameGuide::Init()
{
	return true;
}

void GameGuide::SetGuidSprite()
{
	m_GuideSprite[0].Init("Assets/modelData/Guide_a.DDS", 1650.0f, 900.0f);
	m_GuideSprite[1].Init("Assets/modelData/Guide_b.DDS", 1650.0f, 900.0f);
	m_GuideSprite[2].Init("Assets/modelData/Guide_c.DDS", 1650.0f, 900.0f);
	m_GuideSprite[3].Init("Assets/modelData/Guide_d.DDS", 1650.0f, 900.0f);
	m_GuideSprite[4].Init("Assets/modelData/Guide_e.DDS", 1650.0f, 900.0f);
	m_GuideSprite[5].Init("Assets/modelData/Guide_f.DDS", 1650.0f, 900.0f);
	m_GuideSprite[6].Init("Assets/modelData/Guide_g.DDS", 1650.0f, 900.0f);
	m_GuideSprite[7].Init("Assets/modelData/Guide_h.DDS", 1650.0f, 900.0f);
	m_GuideSprite[8].Init("Assets/modelData/Guide_i.DDS", 1650.0f, 900.0f);


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
	if (m_pageIndex <= 9) {
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
