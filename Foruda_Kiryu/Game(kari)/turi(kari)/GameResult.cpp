#include "stdafx.h"
#include "GameResult.h"

GameResult::GameResult()
{
	m_fishUI[Buri].Init("Assets/modelData/score/hamachiPoint.DDS", 550, 85);
	/*m_fishUI[Tachiuo].Init("Assets/modelData/tatiuoUI.DDS", 150, 150);
	m_fishUI[Tai].Init("Assets/modelData/taiUI.DDS", 150, 150);
	m_fishUI[Hirame].Init("Assets/modelData/hirameUI.DDS", 150, 150);
	m_fishUI[Sinzyu].Init("Assets/modelData/sinnjuUI.DDS", 150, 150);
	m_fishUI[Zyako].Init("Assets/modelData/jakotenUI.DDS", 150, 150);*/
	m_back.Init("Assets/resultSprite/yattabe2.DDS", 1920, 1080);
}

GameResult::~GameResult()
{
}

bool GameResult::start()
{
	
	return true;
}

void GameResult::Update()
{
	Eaging(Buri, fastPos, endPos);
	m_fishUI[Buri].Update();
	/*m_fishUI[Tachiuo].Update();
	m_fishUI[Tai].Update();
	m_fishUI[Hirame].Update();
	m_fishUI[Sinzyu].Update();
	m_fishUI[Zyako].Update();*/
	m_back.Update();
}

void GameResult::Render(RenderContext& rc)
{
	m_back.Draw(rc);
	m_fishUI[Buri].Draw(rc);
	/*m_fishUI[Tachiuo].Draw(rc);
	m_fishUI[Tai].Draw(rc);
	m_fishUI[Hirame].Draw(rc);
	m_fishUI[Sinzyu].Draw(rc);
	m_fishUI[Zyako].Draw(rc);*/

}

void GameResult::Eaging(fishName name,Vector3 fastPos,Vector3 endPos)
{
	m_t += g_gameTime->GetFrameDeltaTime() / 1.0f;
	if (m_t > 1.0f) {
		m_t = 1.0f;
	}
	m_vec.Lerp(log(m_t), fastPos, endPos);
	m_fishUI[name].SetPosition(m_vec);
}


