#include "stdafx.h"
#include "Enemy.h"
#include "PositionSelection.h"
#include"BackGround.h"
#include"Fish.h"
#include"InGameState.h"
#include"ScoreManager.h"
#include"random"
#include "Fish.h"
#include"PlayFishing.h"

Enemy::Enemy()
{
	srand(time(NULL));

	//各レアリティーの釣り上げる確率を設定。
	SetInitRarityProbability();

	SetInitPosition(Vector3{ 0.0f,0.0f,-200.0f });

}

Enemy::~Enemy()
{

}

bool Enemy::Init()
{
	Character::Init();




	SetAnimationClipsLoad("Assets/animData/Enemy/EnamyIdle.tka",
		/*"Assets/animData/Enemy/EnamyWalking.tka",*/
		"Assets/animData/Enemy/enemyWalk.tka",
		"Assets/animData/Player/FishingCast.tka"
	);

	SetRodAnimationClipsLoad(
		"Assets/animData/Player/rod.tka"
	);

	//ユニティちゃんのモデルを読み込む。
	SetModel("Assets/modelData/Enemy/Enemy.tkm", animationClips, enAnimationClip_Num, enModelUpAxisZ, true, false);

	

	return true;
}

bool Enemy::Start()
{

	Character::Start();

	FindGameObjects();
	return true;
}

void Enemy::Update()
{

	Character:: Update();


	if (m_isCountdownFinished == true)		//カウントダウンが終われば。
	{

		if (IsFishingInactive() == true)//釣り中でなければ
		{
			//釣るエリアを決定。
			//SetTargetFishingArea(m_positionSelection->FindFishHighScore()/*スコアが一番高い魚を探す*/);

		}
	}

	


	
}


void Enemy::FindGameObjects()
{
	m_backGround = FindGO<BackGround>("backGround");
	m_inGameState = FindGO<InGameState>("inGameState");
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_scoreManager = FindGO<ScoreManager>("scoreManager");
}


void Enemy::SetMoveSpeed()
{



	if (m_isCountdownFinished == true)//カウントダウンが終わったら。
	{
		//釣り中でなければターゲットエリアに向かう。
		if (IsFishingInactive() == true)
		{

			moveSpeed = Vector3::Zero;
			Vector3 fishingAreaPositionXZ = Vector3(m_fishingAreaPosition[static_cast<int>(m_targetFishingArea)].x,0.0f, m_fishingAreaPosition[static_cast<int>(m_targetFishingArea)].z);
			Vector3 enemyPosXZ =Vector3(m_position.x,0.0f, m_position.z);
			Vector3 range_of_enemy_and_position = fishingAreaPositionXZ - enemyPosXZ;//敵ポジションと選んでいるポジションの距離。


			if (range_of_enemy_and_position.Length() >= 20.0f) //敵が狙ったエリアにまだついていなければ。
			{

				moveSpeed += range_of_enemy_and_position;
				moveSpeed.Normalize();
				moveSpeed *= 700.0f;
			}
			else {//狙った魚の場所についたら。

				//ターゲットの魚のFishDataをセットする。
				SetTargetFishData(m_targetFishingArea);

				//ターゲットエリアについたらそのエリアで釣り中にする。
				SetIsFishingInArea(true, m_targetFishingArea);


			}
		}
	}
}

//描画処理。
void Enemy::Render(RenderContext& rc)
{
	m_playFishing = FindGO<PlayFishing>("playFishing");
	if (m_playFishing == nullptr) {
		modelRender.Draw(rc);
	}
}

void Enemy::SetCountdownFinished(bool countdownFinished)
{
	m_isCountdownFinished = countdownFinished;
}


/// <summary>
/// 敵が釣るエリアを決める。
/// プレイヤーの釣りの回数と敵の回数が同じになるようにする。
/// プレイヤーが釣りに成功した瞬間と釣りに失敗した瞬間に呼び出す。
/// </summary>
void Enemy::SetTargetFishingArea(Area targetFishingArea)
{
	m_targetFishingArea = targetFishingArea;
}

Area Enemy::GetTargetFishinArea()
{
	return m_targetFishingArea;
}

/// <summary>
/// 釣りをしていないか？
/// </summary>
/// <returns>敵が釣りをしていなければtrueを返す。</returns>
bool Enemy::IsFishingInactive()const
{
	return std::all_of(
		m_isFishingInArea.begin(),
		m_isFishingInArea.end(),
		[](const auto& pair) { return pair.second == false; }
	);
}

void Enemy::SetTargetFishData(Area targetarea)
{
	m_targetFishData = m_inGameState->GetFishData(static_cast<int>(targetarea));
}
/// <summary>
/// 今のターゲットの魚を釣り上げたか。
/// </summary>




bool Enemy::GetIsFishingInArea(Area area)
{
	return m_isFishingInArea[area];
}

void Enemy::EndFishing()
{
	//釣り中？をfalseに。
	SetIsFishingInArea(false);

	if (DecideFishingResult(m_targetFishData.rarity)) {//成功ならスコアを加算する。
		m_scoreManager->SetScore(m_targetFishData.score, m_targetFishData.fishType, CharacterType::enemy);
	}

	//ターゲットエリアを変える前に魚を更新する
	m_inGameState->ChangeFish();

	//ターゲットを変える。
	SetTargetFishingArea(m_positionSelection->FindFishHighScore()/*スコアが一番高い魚を探す*/);

	


}

void Enemy::SetEnemyScore()
{
	m_targetFishData;
}

bool Enemy::DecideFishingResult(FishRarity raritu)
{
	std::random_device rd;
	int randum = rd() % 100;

	if (m_rarityProbability[raritu] >= randum) {
		return true;
	}
	return false;
}

void Enemy::SetInitRarityProbability()
{
	m_rarityProbability[FishRarity::Common] = 70;
	m_rarityProbability[FishRarity::Rare] = 60;
	m_rarityProbability[FishRarity::SuperRare] = 10;
}

