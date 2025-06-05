#include "stdafx.h"
#include "Enemy.h"
#include "PositionSelection.h"
#include"BackGround.h"
#include"Fish.h"
#include"InGameState.h"


Enemy::Enemy()
{
	srand(time(NULL));

}

Enemy::~Enemy()
{

}

bool Enemy::Init()
{
	Character::Init();


	InitFishingBaseTimes();


	m_backGround = FindGO<BackGround>("backGround");


	SetAnimationClipsLoad("Assets/animData/Enemy/EnamyIdle.tka",
		"Assets/animData/Enemy/EnamyWalking.tka",
		"Assets/animData/Player/FishingCast.tka"
	);
	//ユニティちゃんのモデルを読み込む。
	SetModel("Assets/modelData/Enemy/Enemy.tkm", animationClips, enAnimationClip_Num, enModelUpAxisZ, true, false);

	return true;
}

bool Enemy::Start()
{

	Character::Start();

	m_inGameState = FindGO<InGameState>("inGameState");
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
			SetTargetFishingArea();

		}
		else {//釣り中なら。

			//今狙っている魚と戦っている時間を更新する。
			UpdateFishingElapsedTime();
		}


		


		if (IsFishCaught()) {//今狙っている魚を釣り上げたら。

			//釣り中？をfalseに。
			SetIsFishingInArea(m_targetFishingArea, false);
			ResetTimer();
		}
	}

	
	


	
}


void Enemy::FindGameObjects()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_backGround = FindGO<BackGround>("backGround");

}

void Enemy::InitFishingBaseTimes()
{
	m_fishingBaseTimes[FishType::TAI] = 50.0f;
	m_fishingBaseTimes[FishType::BURI] = 30.0f;
	m_fishingBaseTimes[FishType::HIRAME] = 30.0f;
	m_fishingBaseTimes[FishType::TATIUO] = 30.0f;
	m_fishingBaseTimes[FishType::SINJU] = 20.0f;
	m_fishingBaseTimes[FishType::JAKOTENN] = 20.0f;



}

void Enemy::SetMoveSpeed()
{



	if (m_isCountdownFinished == true)//カウントダウンが終わったら。
	{
		m_positionSelection = FindGO<PositionSelection>("positionSelection");


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

				//タイマーを開始。
				StartFishingTimer();

				//ターゲットの魚のFishDataをセットする。
				SetTargetFishData(m_targetFishingArea);

				//釣るのにかかる時間を決定する。
				CalculateFishingTime(m_TargetFishData.fishType);

				//ターゲットエリアについたらそのエリアで釣り中にする。
				SetIsFishingInArea(m_targetFishingArea, true);
			}
		}
	}
}

//描画処理。
void Enemy::Render(RenderContext& rc)
{
	//ユニティちゃんを描画する。
	modelRender.Draw(rc);
}

void Enemy::SetCountdownFinished(bool countdownFinished)
{
	m_isCountdownFinished = countdownFinished;
}
/// <summary>
/// 敵が釣るエリアを決める。
/// </summary>
void Enemy::SetTargetFishingArea()
{
	m_targetFishingArea=m_positionSelection->FindFishHighScore();
}

Area Enemy::GetTargetFishinArea()
{
	return m_targetFishingArea;
}

/// <summary>
/// 敵が釣り中かどうかを設定する。
/// </summary>
/// <param name="fishingArea"></param>
/// <param name="isfishing"></param>
void Enemy::SetIsFishingInArea(Area fishingArea, bool isfishing)
{


	for (int i = 0; i < 6; i++)
	{


		//他のところは自動的にfalse。
		if (i == static_cast<int>(fishingArea)) {
			m_isFishingInArea[fishingArea] = isfishing;
		}
		else {
			m_isFishingInArea[static_cast<Area>(i)] = false;
		}
	}



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
/// <summary>
/// 一回の釣りにかかる時間を決める。
/// </summary>
void Enemy::CalculateFishingTime(FishType targetFish)
{
	//ターゲットの魚を釣るのにかかる時間＝各魚の基準時間×個体差。
	targetFishingTime=m_fishingBaseTimes[targetFish]*m_TargetFishData.individualFactor;
}

void Enemy::SetTargetFishData(Area targetarea)
{
	m_TargetFishData = m_inGameState->GetFishData(static_cast<int>(targetarea));
}
/// <summary>
/// 今のターゲットの魚を釣り上げたか。
/// </summary>
bool Enemy::IsFishCaught()
{
	if (!IsFishingInactive()/*釣りをしていない？*/) //釣りをしていれば。
	{
		if (targetFishingTime <= fishingElapsedTime) {//経過時間が釣るまでの時間より大きくなったら。
			return true;
		}
		else {//まだつっている最中。
			return false;
		}
	}
	else //釣りをしていない。（移動中）
	{
		return false;
	}
}

/// <summary>
/// タイマーをスタートさせる。
/// </summary>
void Enemy::StartFishingTimer()
{
	m_stopwatch.Start();
}

void Enemy::ResetTimer()
{
	m_stopwatch.Stop();
}

/// <summary>
/// 今狙っている魚を釣るのにかかった経過時間を更新する。
/// </summary>
void Enemy::UpdateFishingElapsedTime()
{
	fishingElapsedTime=m_stopwatch.GetElapsed();
	m_stopwatch.Stop();
}


