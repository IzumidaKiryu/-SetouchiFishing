#include "stdafx.h"
#include "ScoreDisplay.h"
#include"PlayFishing.h"
#include"PositionSelection.h"
#include"InGameState.h"
#include "Enemy.h"
#include"Player.h"
#include "StealPositionBar.h"

ScoreDisplay::ScoreDisplay()
{

	m_player = FindGO<Player>("player");
	m_playFishing = FindGO<PlayFishing>("playFishing");
	m_stealPositionBar = FindGO<StealPositionBar>("stealPositionBar");

	//追加
	m_enemy = FindGO<Enemy>("enemy");

	m_score = m_playFishing->GetFIshScore();

	//1スコアのそれぞれの桁を求める。
	SetOnesPlace();
	SetTensPlace();
	SetHundredsPlace();

	//それぞれの桁のUIを設定する。
	SetOnesPlaceUI();
	SetTensPlaceUI();
	SetHundredsPlaceUI();

	m_scoreDisplay.Init("Assets/modelData/score/fishStatus.DDS", 500, 500);
	m_scoreDisplay.SetPivot(Vector2(0.5f, 0.5f));
	m_scoreDisplay.SetPosition(Vector3{ 200.0f,0.0f,0.0f });
	m_scoreDisplay.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_scoreDisplay.Update();
}

ScoreDisplay::~ScoreDisplay()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_inGameState = FindGO<InGameState>("inGameState");
	//魚をチェンジ。
	m_inGameState->ChangeFish(static_cast<int>(m_positionSelection->GetCurrentArea()));

	//プレイヤーが釣りをしていないと伝える。
	m_player->SetIsFishingInArea(false);

	//魚のロックをoffにする。
	//敵からエリアを奪った場合、魚にロックがかかっていて、逃げないので、ロックをoffにする。
	//別の場所でロックがかかっていても、有効。
	//ロックがかかっていなくても問題はない。
	m_stealPositionBar->SetIsStealLockActive(false);

	//敵の釣りが終わった後の処理をする。
	m_enemy->EndFishing();

	//選択画面を表示している？をtrueにする。
	m_positionSelection->SetisDisplayingTrue();

	//ポジションセレクトクラスのオブジェクトをアクティブにする
	m_positionSelection->SetActivate();
}

void ScoreDisplay::Update()
{
	SetOnesPlace();
	if (g_pad[0]->IsTrigger(enButtonA)) {
		DeleteGO(this);
	}
}

void ScoreDisplay::SetScore()
{

}

void ScoreDisplay::SetOnesPlace()
{
	m_onesPlace = m_score % 10;
}

void ScoreDisplay::SetTensPlace()
{
	m_tensPlace = m_score / 10;
	m_tensPlace %= 10;

}

void ScoreDisplay::SetHundredsPlace()
{
	m_hundredsPlace = m_score / 100;
	m_hundredsPlace %= 10;
}

void ScoreDisplay::SetOnesPlaceUI()
{
	switch (m_onesPlace)
	{
	case 0:
		m_onesPlaceUI.Init("Assets/modelData/score/0.DDS", 100, 100);
		break;
	case 1:
		m_onesPlaceUI.Init("Assets/modelData/score/1.DDS", 100, 100);
		break;
	case 2:
		m_onesPlaceUI.Init("Assets/modelData/score/2.DDS", 100, 100);
		break;
	case 3:
		m_onesPlaceUI.Init("Assets/modelData/score/3.DDS", 100, 100);
		break;
	case 4:
		m_onesPlaceUI.Init("Assets/modelData/score/4.DDS", 100, 100);
		break;
	case 5:
		m_onesPlaceUI.Init("Assets/modelData/score/5.DDS", 100, 100);
		break;
	case 6:
		m_onesPlaceUI.Init("Assets/modelData/score/6.DDS", 100, 100);
		break;
	case 7:
		m_onesPlaceUI.Init("Assets/modelData/score/7.DDS", 100, 100);
		break;
	case 8:
		m_onesPlaceUI.Init("Assets/modelData/score/8.DDS", 100, 100);
		break;
	case 9:
		m_onesPlaceUI.Init("Assets/modelData/score/9.DDS", 100, 100);
		break;
	default:
		break;
	}
	m_onesPlaceUI.SetPivot(Vector2(0.5f, 0.5f));
	m_onesPlaceUI.SetPosition(m_onesPlaceUIPos);
	m_onesPlaceUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_onesPlaceUI.Update();
}

void ScoreDisplay::SetTensPlaceUI()
{
	switch (m_tensPlace)
	{
	case 0:
		m_tensPlaceUI.Init("Assets/modelData/score/0.DDS", 100, 100);
		break;
	case 1:
		m_tensPlaceUI.Init("Assets/modelData/score/1.DDS", 100, 100);
		break;
	case 2:
		m_tensPlaceUI.Init("Assets/modelData/score/2.DDS", 100, 100);
		break;
	case 3:
		m_tensPlaceUI.Init("Assets/modelData/score/3.DDS", 100, 100);
		break;
	case 4:
		m_tensPlaceUI.Init("Assets/modelData/score/4.DDS", 100, 100);
		break;
	case 5:
		m_tensPlaceUI.Init("Assets/modelData/score/5.DDS", 100, 100);
		break;
	case 6:
		m_tensPlaceUI.Init("Assets/modelData/score/6.DDS", 100, 100);
		break;
	case 7:
		m_tensPlaceUI.Init("Assets/modelData/score/7.DDS", 100, 100);
		break;
	case 8:
		m_tensPlaceUI.Init("Assets/modelData/score/8.DDS", 100, 100);
		break;
	case 9:
		m_tensPlaceUI.Init("Assets/modelData/score/9.DDS", 100, 100);
		break;
	default:
		break;
	}
	m_tensPlaceUI.SetPivot(Vector2(0.5f, 0.5f));
	m_tensPlaceUI.SetPosition(m_tensPlaceUIPos);
	m_tensPlaceUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_tensPlaceUI.Update();
}

void ScoreDisplay::SetHundredsPlaceUI()
{
	switch (m_hundredsPlace)
	{
	case 0:
		m_hundredsPlaceUI.Init("Assets/modelData/score/0.DDS", 100, 100);
		break;
	case 1:
		m_hundredsPlaceUI.Init("Assets/modelData/score/1.DDS", 100, 100);
		break;
	case 2:
		m_hundredsPlaceUI.Init("Assets/modelData/score/2.DDS", 100, 100);
		break;
	case 3:
		m_hundredsPlaceUI.Init("Assets/modelData/score/3.DDS", 100, 100);
		break;
	case 4:
		m_hundredsPlaceUI.Init("Assets/modelData/score/4.DDS", 100, 100);
		break;
	case 5:
		m_hundredsPlaceUI.Init("Assets/modelData/score/5.DDS", 100, 100);
		break;
	case 6:
		m_hundredsPlaceUI.Init("Assets/modelData/score/6.DDS", 100, 100);
		break;
	case 7:
		m_hundredsPlaceUI.Init("Assets/modelData/score/7.DDS", 100, 100);
		break;
	case 8:
		m_hundredsPlaceUI.Init("Assets/modelData/score/8.DDS", 100, 100);
		break;
	case 9:
		m_hundredsPlaceUI.Init("Assets/modelData/score/9.DDS", 100, 100);
		break;
	default:
		break;
	}
	m_hundredsPlaceUI.SetPivot(Vector2(0.5f, 0.5f));
	m_hundredsPlaceUI.SetPosition(m_hundredsPlaceUIPos);
	m_hundredsPlaceUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_hundredsPlaceUI.Update();
}

void ScoreDisplay::ScoreUI()
{

}

void ScoreDisplay::Render(RenderContext& rc)
{
	m_scoreDisplay.Draw(rc);
	m_onesPlaceUI.Draw(rc);
	m_tensPlaceUI.Draw(rc);
	m_hundredsPlaceUI.Draw(rc);


}
