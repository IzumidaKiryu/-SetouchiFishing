#include "stdafx.h"
#include "GameResult.h"
//namespace {
//	const float EASINGSTATE_PLAYER_X = -350.0f;
//	const float EASINGSTATE_ENAMY_X = 0.0f;
//	const float EASINGSTATE_Y[6] = {220,130,40,-50,-140,-230};
//}

GameResult::GameResult()
{
	m_fishUI[Hamachi].Init("Assets/modelData/score/hamachiPoint.DDS", 530, 80);
	m_fishUI[Tachiuo].Init("Assets/modelData/score/tachiuoPoint.DDS", 530, 80);
	m_fishUI[Tai].Init("Assets/modelData/score/taiPoint.DDS", 530, 80);
	m_fishUI[Hirame].Init("Assets/modelData/score/hiramePoint.DDS", 530, 80);
	m_fishUI[Pearl].Init("Assets/modelData/score/pearlPoint.DDS", 530, 80);
	m_fishUI[Jakoten].Init("Assets/modelData/score/jyakotenPoint.DDS", 530, 80);
	m_back.Init("Assets/modelData/score/fishResult.DDS", 1320, 780);
}

GameResult::~GameResult()
{

}

bool GameResult::Start()
{
	for (int i = 0; i < num; i++)
	{
		m_vec[i] = Vector3::Zero;
		m_t[i] = 0.0f;
	}

	return true;
}

void GameResult::Update()
{
	Easing(Hamachi, m_fastPos, m_endPos);
	Easing(Tachiuo, m_fastPos2, m_endPos2);
	Easing(Tai, m_fastPos3, m_endPos3);
	Easing(Hirame, m_fastPos4, m_endPos4);
	Easing(Pearl, m_fastPos5, m_endPos5);
	Easing(Jakoten, m_fastPos6, m_endPos6);

	m_fishUI[Hamachi].Update();
	m_fishUI[Tachiuo].Update();
	m_fishUI[Tai].Update();
	m_fishUI[Hirame].Update();
	m_fishUI[Pearl].Update();
	m_fishUI[Jakoten].Update();
	m_back.Update();
}

void GameResult::Render(RenderContext& rc)
{
	m_back.Draw(rc);
	m_fishUI[Hamachi].Draw(rc);
	m_fishUI[Tachiuo].Draw(rc);
	m_fishUI[Tai].Draw(rc);
	m_fishUI[Hirame].Draw(rc);
	m_fishUI[Pearl].Draw(rc);
	m_fishUI[Jakoten].Draw(rc);
}

void GameResult::Easing(FishName name,Vector3 fastPos,Vector3 endPos)
{
	m_t[name] += g_gameTime->GetFrameDeltaTime() / 1.0f;
	if (m_t[name] > 1.0f) {
		m_t[name] = 1.0f;
	}
	m_vec[name].Lerp(log(m_t[name]), fastPos, endPos);
	m_fishUI[name].SetPosition(m_vec[name]);
}


