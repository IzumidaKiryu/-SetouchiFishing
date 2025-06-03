#include "stdafx.h"
#include "GameResult.h"
#include"InGameState.h"
#include"Game.h"
//namespace {
//	const float EASINGSTATE_PLAYER_X = -350.0f;
//	const float EASINGSTATE_ENAMY_X = 0.0f;
//	const float EASINGSTATE_Y[6] = {220,130,40,-50,-140,-230};
//}

GameResult::GameResult()
{
}

GameResult::~GameResult()
{

}

bool GameResult::Start()
{
	for (int i = 0; i < num; i++)
	{
		m_vec[i] = Vector3(1050.0f,0.0f,0.0f);
		m_t[i] = 0.0f;
		m_fishUI[i].SetPosition(m_vec[i]);
	}

	return true;
}

bool GameResult::Init()
{
	m_fishUI[Hamachi].Init("Assets/modelData/score/hamachiPoint.DDS", 530, 80);
	m_fishUI[Tachiuo].Init("Assets/modelData/score/tachiuoPoint.DDS", 530, 80);
	m_fishUI[Tai].Init("Assets/modelData/score/taiPoint.DDS", 530, 80);
	m_fishUI[Hirame].Init("Assets/modelData/score/hiramePoint.DDS", 530, 80);
	m_fishUI[Pearl].Init("Assets/modelData/score/pearlPoint.DDS", 530, 80);
	m_fishUI[Jakoten].Init("Assets/modelData/score/jyakotenPoint.DDS", 530, 80);
	m_back.Init("Assets/modelData/score/fishResult.DDS", 1320, 780);

	return true;
}

void GameResult::OnUpdate()
{
	switch (nowFishName)
	{
	case GameResult::Hamachi:
		Easing(Hamachi, m_fastPos[Hamachi], m_endPos[Hamachi]);
		break;
	case GameResult::Tachiuo:
		Easing(Tachiuo, m_fastPos[Tachiuo], m_endPos[Tachiuo]);
		break;
	case GameResult::Tai:
		Easing(Tai, m_fastPos[Tai], m_endPos[Tai]);
		break;
	case GameResult::Hirame:
		Easing(Hirame, m_fastPos[Hirame], m_endPos[Hirame]);
		break;
	case GameResult::Pearl:
		Easing(Pearl, m_fastPos[Pearl], m_endPos[Pearl]);
		break;
	case GameResult::Jakoten:
		Easing(Jakoten, m_fastPos[Jakoten], m_endPos[Jakoten]);
		break;
	case GameResult::num:
		break;
	default:
		break;
	}
	
	
	m_fishUI[Hamachi].Update();
	m_fishUI[Tachiuo].Update();
	m_fishUI[Tai].Update();
	m_fishUI[Hirame].Update();
	m_fishUI[Pearl].Update();
	m_fishUI[Jakoten].Update();
	m_back.Update();
}

void GameResult::OnEnter()
{
}

void GameResult::OnExit()
{
	m_game = FindGO<Game>("game");
	m_game->ResetInGame();
}


bool GameResult::ShouldChangeState()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		SetNextName("title");
		return true;
	}
	return false;
}

void GameResult::SetFastPos()
{
	for (int i = 0; i < num; i++) {
		m_vec[i] = m_fastPos[i];
	}
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

void GameResult::Easing(FishName name, Vector3 fastPos, Vector3 endPos)
{
	m_t[name] += g_gameTime->GetFrameDeltaTime() / 1.0f;
	if (m_t[name] > 1.0f) {
		m_t[name] = 1.0f;
		nowFishName++;
	}
	m_vec[name].Lerp(log(m_t[name]), fastPos, endPos);
	m_fishUI[name].SetPosition(m_vec[name]);
}


