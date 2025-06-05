#include "stdafx.h"
#include "GameResult.h"
#include"InGameState.h"
#include"Game.h"
#include"Enemy.h"
#include"Player.h"
#include"ScoreManager.h"
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
	//g_renderingEngine->isResultFlag = true;//後回し。プレイヤーのモデルをスプライト」の上に描画。
	//泉田追加ここまで
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
	//泉田追加
	m_enemyFishUI[Hamachi].Init("Assets/modelData/score/hamachiPoint.DDS", 530, 80);
	m_enemyFishUI[Tachiuo].Init("Assets/modelData/score/tachiuoPoint.DDS", 530, 80);
	m_enemyFishUI[Tai].Init("Assets/modelData/score/taiPoint.DDS", 530, 80);
	m_enemyFishUI[Hirame].Init("Assets/modelData/score/hiramePoint.DDS", 530, 80);
	m_enemyFishUI[Pearl].Init("Assets/modelData/score/pearlPoint.DDS", 530, 80);
	m_enemyFishUI[Jakoten].Init("Assets/modelData/score/jyakotenPoint.DDS", 530, 80);


	m_animationClip[enAnimationClip_Idle].Load("Assets/animData/Player/Idle.tka");
	m_animationClip[enAnimationClip_Idle].SetLoopFlag(true);
	m_enemyAnimationClip[enAnimationClip_Idle].Load("Assets/animData/Enemy/EnamyIdle.tka");
	m_enemyAnimationClip[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_Win].Load("Assets/animData/Player/Walking.tka");
	m_animationClip[enAnimationClip_Win].SetLoopFlag(true);
	m_enemyAnimationClip[enAnimationClip_Win].Load("Assets/animData/Enemy/EnamyWalking.tka");
	m_enemyAnimationClip[enAnimationClip_Win].SetLoopFlag(true);
	//リザルト用のモデルの初期化。
	m_playerModel.Init("Assets/modelData/Player/Player.tkm",m_animationClip,enAnimationClip_Num,enModelUpAxisZ);
	m_enemyModel.Init("Assets/modelData/Enemy/Enemy.tkm",m_enemyAnimationClip,enAnimationClip_Idle,enModelUpAxisZ);
	
	//位置決め。
	m_playerModel.SetPosition(Vector3(-350.0f, 0.0f, 0.0f));
	m_enemyModel.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	//回転初期化。
	m_playerModel.SetRotation(Quaternion::Identity);
	m_enemyModel.SetRotation(Quaternion::Identity);
	//大きさ初期化。
	m_playerModel.SetScale(Vector3(0.5f, 0.5f, 0.5f));
	m_enemyModel.SetScale(Vector3(0.5f, 0.5f, 0.5f));

	m_playerModel.Update();
	m_enemyModel.Update();
	return true;
}

void GameResult::OnUpdate()
{
	switch (nowFishName)
	{
	case GameResult::Hamachi:
		Easing(Hamachi, m_fastPos[Hamachi], m_endPos[Hamachi]);
		EasingEnemy(Hamachi, m_enemyUIFarstPos[Hamachi], m_enemyUIEndPos[Hamachi]);
		break;
	case GameResult::Tachiuo:
		Easing(Tachiuo, m_fastPos[Tachiuo], m_endPos[Tachiuo]);
		EasingEnemy(Tachiuo, m_enemyUIFarstPos[Tachiuo], m_enemyUIEndPos[Tachiuo]);
		break;
	case GameResult::Tai:
		Easing(Tai, m_fastPos[Tai], m_endPos[Tai]);
		EasingEnemy(Tai, m_enemyUIFarstPos[Tai], m_enemyUIEndPos[Tai]);
		break;
	case GameResult::Hirame:
		Easing(Hirame, m_fastPos[Hirame], m_endPos[Hirame]);
		EasingEnemy(Hirame, m_enemyUIFarstPos[Hirame], m_enemyUIEndPos[Hirame]);
		break;
	case GameResult::Pearl:
		Easing(Pearl, m_fastPos[Pearl], m_endPos[Pearl]);
		EasingEnemy(Pearl, m_enemyUIFarstPos[Pearl], m_enemyUIEndPos[Pearl]);
		break;
	case GameResult::Jakoten:
		Easing(Jakoten, m_fastPos[Jakoten], m_endPos[Jakoten]);
		EasingEnemy(Jakoten, m_enemyUIFarstPos[Jakoten], m_enemyUIEndPos[Jakoten]);
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
	m_fishUI[Hamachi].Update();
	m_fishUI[Tachiuo].Update();
	m_fishUI[Tai].Update();
	m_fishUI[Hirame].Update();
	m_fishUI[Pearl].Update();
	m_fishUI[Jakoten].Update();
	m_enemyFishUI[Hamachi].Update();
	m_enemyFishUI[Tachiuo].Update();
	m_enemyFishUI[Tai].Update();
	m_enemyFishUI[Hirame].Update();
	m_enemyFishUI[Pearl].Update();
	m_enemyFishUI[Jakoten].Update();
	m_back.Update();
	SetVictory();
	PalyerModelPlayAnimation();
	EnemyModelPlayAnimation();
	//モデルの更新。
	m_playerModel.Update();
	m_enemyModel.Update();
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
	m_enemyFishUI[Hamachi].Draw(rc);
	m_enemyFishUI[Tachiuo].Draw(rc);
	m_enemyFishUI[Tai].Draw(rc);
	m_enemyFishUI[Hirame].Draw(rc);
	m_enemyFishUI[Pearl].Draw(rc);
	m_enemyFishUI[Jakoten].Draw(rc);
	for (int i = 0; i < 6; i++) {
		m_fontRender[i].Draw(rc);
		m_fontRender[i + 6].Draw(rc);
	}
	//モデルの描画。
	m_playerModel.Draw(rc);
	m_enemyModel.Draw(rc);
}

void GameResult::Easing(FishName name, Vector3 fastPos, Vector3 endPos)
{
	m_t[name] += g_gameTime->GetFrameDeltaTime() / 0.1f;
	m_vec[name].Lerp((m_t[name]), fastPos, endPos);
	m_fishUI[name].SetPosition(m_vec[name]);

	if (m_t[name] > 1.0f) {
		m_t[name] = 1.0f;
		if (WaitSeconds(0.8f) == true) {
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
	float playerTotalScore = 0.0f;
	float enemyTotalScore = 0.0f;
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

void GameResult::PalyerModelPlayAnimation()
{
	if (m_plVictoryFlag == true) {
		m_playerModel.PlayAnimation(enAnimationClip_Win);

	}
	else {
		m_playerModel.PlayAnimation(enAnimationClip_Idle);
	}
}

void GameResult::EnemyModelPlayAnimation()
{
	if (m_enVictoryFlag == true) {
		m_enemyModel.PlayAnimation(enAnimationClip_Win);
	}
	else {
		m_enemyModel.PlayAnimation(enAnimationClip_Idle);

	}
}



