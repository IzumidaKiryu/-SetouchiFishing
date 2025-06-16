#include "stdafx.h"
#include "GameResult.h"
#include"InGameState.h"
#include"Game.h"
#include"Enemy.h"
#include"Player.h"
#include"ScoreManager.h"
#include "sound/SoundSource.h"
//namespace {
//	const float EASINGSTATE_PLAYER_X = -350.0f;
//	const float EASINGSTATE_ENAMY_X = 0.0f;
//	const float EASINGSTATE_Y[6] = {220,130,40,-50,-140,-230};
//}
//FPSが変わるとイージングがぶれる。
GameResult::GameResult()
{
}

GameResult::~GameResult()
{

}

bool GameResult::Start()
{
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/gameResultBGM.wav");

	m_sound = NewGO<SoundSource>(2);

	m_sound->Init(2);

	m_sound->Play(false);

	for (int i = 0; i < num; i++)
	{
		m_vec[i] = Vector3(1050.0f,0.0f,0.0f);
		m_enemyVec[i] = Vector3(1050.0f, 0.0f, 0.0f);
		m_t[i] = 0.0f;
		m_enemyT[i] = 0.0f;
		m_fishUI[i].SetPosition(m_vec[i]);
		m_enemyFishUI[i].SetPosition(m_enemyVec[i]);
	}
	//泉田追加
	m_scoreManager = FindGO<ScoreManager>("scoreManager");
	//泉田追加ここまで
	return true;
}

bool GameResult::Init()
{
	m_fishUI[BURI].Init("Assets/modelData/score/hamachiPoint.DDS", 530, 80);
	m_fishUI[TATIUO].Init("Assets/modelData/score/tachiuoPoint.DDS", 530, 80);
	m_fishUI[TAI].Init("Assets/modelData/score/taiPoint.DDS", 530, 80);
	m_fishUI[HIRAME].Init("Assets/modelData/score/hiramePoint.DDS", 530, 80);
	m_fishUI[SINJU].Init("Assets/modelData/score/pearlPoint.DDS", 530, 80);
	m_fishUI[JAKOTENN].Init("Assets/modelData/score/jyakotenPoint.DDS", 530, 80);
	m_back.Init("Assets/modelData/score/fishResult.DDS", 1320, 780);
	//泉田追加
	m_enemyFishUI[BURI].Init("Assets/modelData/score/hamachiPoint.DDS", 530, 80);
	m_enemyFishUI[TATIUO].Init("Assets/modelData/score/tachiuoPoint.DDS", 530, 80);
	m_enemyFishUI[TAI].Init("Assets/modelData/score/taiPoint.DDS", 530, 80);
	m_enemyFishUI[HIRAME].Init("Assets/modelData/score/hiramePoint.DDS", 530, 80);
	m_enemyFishUI[SINJU].Init("Assets/modelData/score/pearlPoint.DDS", 530, 80);
	m_enemyFishUI[JAKOTENN].Init("Assets/modelData/score/jyakotenPoint.DDS", 530, 80);
	return true;
}

void GameResult::OnUpdate()
{
	switch (nowFishName)
	{
	case GameResult::BURI:
		Easing(BURI, m_fastPos[BURI], m_endPos[BURI]);
		EasingEnemy(BURI, m_enemyUIFarstPos[BURI], m_enemyUIEndPos[BURI]);
		break;
	case GameResult::TATIUO:
		Easing(TATIUO, m_fastPos[TATIUO], m_endPos[TATIUO]);
		EasingEnemy(TATIUO, m_enemyUIFarstPos[TATIUO], m_enemyUIEndPos[TATIUO]);
		break;
	case GameResult::TAI:
		Easing(TAI, m_fastPos[TAI], m_endPos[TAI]);
		EasingEnemy(TAI, m_enemyUIFarstPos[TAI], m_enemyUIEndPos[TAI]);
		break;
	case GameResult::HIRAME:
		Easing(HIRAME, m_fastPos[HIRAME], m_endPos[HIRAME]);
		EasingEnemy(HIRAME, m_enemyUIFarstPos[HIRAME], m_enemyUIEndPos[HIRAME]);
		break;
	case GameResult::SINJU:
		Easing(SINJU, m_fastPos[SINJU], m_endPos[SINJU]);
		EasingEnemy(SINJU, m_enemyUIFarstPos[SINJU], m_enemyUIEndPos[SINJU]);
		break;
	case GameResult::JAKOTENN:
		Easing(JAKOTENN, m_fastPos[JAKOTENN], m_endPos[JAKOTENN]);
		EasingEnemy(JAKOTENN, m_enemyUIFarstPos[JAKOTENN], m_enemyUIEndPos[JAKOTENN]);
		break;
	case GameResult::num:
		break;
	default:
		break;
	}

	SetFishScore();

	//表示するテキストを設定。
	for (int i = 0; i < 6; i++) {
		m_fontRender[i].SetText(m_scoreText[i]);
		m_fontRender[i + 6].SetText(m_scoreText[i + 6]);
	}
	//フォントの位置を設定。
	m_fontRender[0].SetPosition(Vector3(-380.0f, 280.0f, 0.0f));
	m_fontRender[1].SetPosition(Vector3(-380.0f, 170.0f, 0.0f));
	m_fontRender[2].SetPosition(Vector3(-380.0f, 65.0f, 0.0f));
	m_fontRender[3].SetPosition(Vector3(-380.0f, -40.0f, 0.0f));
	m_fontRender[4].SetPosition(Vector3(-380.0f, -150.0f, 0.0f));
	m_fontRender[5].SetPosition(Vector3(-380.0f, -260.0f, 0.0f));
	m_fontRender[6].SetPosition(Vector3(500.0f, 280.0f, 0.0f));
	m_fontRender[7].SetPosition(Vector3(500.0f, 170.0f, 0.0f));
	m_fontRender[8].SetPosition(Vector3(500.0f, 65.0f, 0.0f));
	m_fontRender[9].SetPosition(Vector3(500.0f, -40.0f, 0.0f));
	m_fontRender[10].SetPosition(Vector3(500.0f, -150.0f, 0.0f));
	m_fontRender[11].SetPosition(Vector3(500.0f, -260.0f, 0.0f));
	//からーの設定
	for (int i = 0; i < 6; i++) {
		m_fontRender[i].SetColor(Vector4(0.0f, 0.0f, 0.0f, m_alpha[i]));
		m_fontRender[i + 6].SetColor(Vector4(0.0f, 0.0f, 0.0f, m_enemyAlpha[i]));
	}
	
	//UIの更新
	m_fishUI[BURI].Update();
	m_fishUI[TATIUO].Update();
	m_fishUI[TAI].Update();
	m_fishUI[HIRAME].Update();
	m_fishUI[SINJU].Update();
	m_fishUI[JAKOTENN].Update();
	m_enemyFishUI[BURI].Update();
	m_enemyFishUI[TATIUO].Update();
	m_enemyFishUI[TAI].Update();
	m_enemyFishUI[HIRAME].Update();
	m_enemyFishUI[SINJU].Update();
	m_enemyFishUI[JAKOTENN].Update();
	m_back.Update();
	SetVictory();
	wchar_t wcsbuf[256];

	swprintf_s(wcsbuf, 256, L"SCORE: %d", int(playerTotalScore));

	//表示するテキストを設定。
	m_allScorePlayer.SetText(wcsbuf);
	//フォントの位置を設定。
	m_allScorePlayer.SetPosition(Vector3(-500.0f, -340.0f, 0.0f));
	//フォントの大きさを設定。
	m_allScorePlayer.SetScale(1.0f);
	//フォントの色を設定。
	m_allScorePlayer.SetColor({ 1.0f,0.0f,0.0f,1.0f });


	wchar_t wcsbufk[256];
	swprintf_s(wcsbufk, 256, L"SCORE: %d", int(enemyTotalScore));
	//表示するテキストを設定。
	m_allScoreEnemy.SetText(wcsbufk);
	//フォントの位置を設定。
	m_allScoreEnemy.SetPosition(Vector3(300.0f, -340.0f, 0.0f));
	//フォントの大きさを設定。
	m_allScoreEnemy.SetScale(1.0f);
	//フォントの色を設定。
	m_allScoreEnemy.SetColor({ 1.0f,0.0f,0.0f,1.0f });
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
        DeleteGO(m_sound);
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
	m_fishUI[BURI].Draw(rc);
	m_fishUI[TATIUO].Draw(rc);
	m_fishUI[TAI].Draw(rc);
	m_fishUI[HIRAME].Draw(rc);
	m_fishUI[SINJU].Draw(rc);
	m_fishUI[JAKOTENN].Draw(rc);
	m_enemyFishUI[BURI].Draw(rc);
	m_enemyFishUI[TATIUO].Draw(rc);
	m_enemyFishUI[TAI].Draw(rc);
	m_enemyFishUI[HIRAME].Draw(rc);
	m_enemyFishUI[SINJU].Draw(rc);
	m_enemyFishUI[JAKOTENN].Draw(rc);
	for (int i = 0; i < 6; i++) {
		m_fontRender[i].Draw(rc);
		m_fontRender[i + 6].Draw(rc);
	}
	m_allScorePlayer.Draw(rc);
	m_allScoreEnemy.Draw(rc);
}

void GameResult::Easing(FishName name, Vector3 fastPos, Vector3 endPos)
{
	m_t[name] += g_gameTime->GetFrameDeltaTime() / 0.1f;
	m_vec[name].Lerp((m_t[name]), fastPos, endPos);
	m_fishUI[name].SetPosition(m_vec[name]);

	if (m_t[name] > 1.0f) {
		m_t[name] = 1.0f;
		if (WaitSeconds(0.5f) == true) {
			nowFishName++;
		}
	}
	//追加。
	m_alpha[name] +=g_gameTime->GetFrameDeltaTime()/0.1f;

	if (m_alpha[name] > 1.0f) {
		m_alpha[name] = 1.0f;
	}
}

void GameResult::EasingEnemy(FishName name, Vector3 fastPos, Vector3 endPos)
{
	m_enemyT[name] += g_gameTime->GetFrameDeltaTime() / 0.1f;
	m_enemyVec[name].Lerp((m_enemyT[name]), fastPos, endPos);
	m_enemyFishUI[name].SetPosition(m_enemyVec[name]);

	if (m_enemyT[name] > 1.0f) {
		m_enemyT[name] = 1.0f;
	}
	m_enemyAlpha[name] += g_gameTime->GetFrameDeltaTime() / 0.1f;
	if (m_enemyAlpha[name] > 1.0f) {
		m_enemyAlpha[name] = 1.0f;
	}
}

void GameResult::SetFishScore()
{
	
	for (int i=0; i < 2; i++) {
		for (int j=0; j < 6; j++) {
			int index = i * 6 + j;
			//テクスチャの配列名変えてね。
			swprintf_s(m_scoreText[index], 256, L"%d", (int)m_scoreManager->GetFishTotalScore(static_cast<FishType>(j), static_cast<CharacterType>(i)));
		}
	}


}

void GameResult::SetVictory()
{
	
	playerTotalScore=m_scoreManager->GetTotalScore(CharacterType::Player);
	enemyTotalScore = m_scoreManager->GetTotalScore(CharacterType::enemy);

	if (playerTotalScore > enemyTotalScore) {//プレイヤーの勝ち。
		m_plVictoryFlag = true;
	}
	else if (playerTotalScore == enemyTotalScore) {//同点。
		m_plVictoryFlag = true;
		m_enVictoryFlag = true;
	}
	else {
		m_enVictoryFlag = true;//エネミーの勝ち。
	}
}

