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
#include"Player.h"
#include"StealPositionBar.h"

Enemy::Enemy()
{
	srand(time(NULL));

	//各レアリティーの釣り上げる確率を設定。
	SetInitRarityProbability();

	//各魚の釣り上げる時間を設定。
	InitFishingBaseTimes();

	//初期ポジションを設定。
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
		"Assets/animData/Player/FishingCast.tka",
		"Assets/animData/Player/yokodoriAnimation.tka"
	);

	//SetRodAnimationClipsLoad(
	//	"Assets/animData/Player/rod.tka"
	//);

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

	Character::Update();


	if (m_isCountdownFinished == true)		//カウントダウンが終われば。
	{

		//プレイヤーにエリアを取られた後じゃなければ。
		if (!m_stealPositionBar->IsAnyStealLockActive()) {

			//プレイヤーが一番スコアが高い魚のいるエリアで釣りをしているなら。
			if (m_player->GetIsFishingInArea(m_positionSelection->FindFishHighScore())) {

				//プレイヤーがいる場所以外で、今釣っている魚よりハイスコアな魚が居れば。
				if (m_positionSelection->FindSecondFishHighScore() != m_targetFishingArea) {

					//今の釣りを中断して、スコアが二番目に高い魚のいるエリアに移動する。
					InterruptAndRelocateFishing(m_positionSelection->FindSecondFishHighScore()/*スコアが二番目に高い魚を探す*/);

				}

			}

			//プレイヤーが一番スコアが高い魚のいるエリアで釣りをしていないなら。
			else {

				//今釣っている魚よりハイスコアな魚が居れば。
				if (m_positionSelection->FindFishHighScore() != m_targetFishingArea) {

					//今の釣りを中断して、スコアが一番高い魚のいるエリアに移動する。
					InterruptAndRelocateFishing(m_positionSelection->FindFishHighScore()/*スコアが一番高い魚を探す*/);

				}

			}

		}



		//釣り中のエリアで釣りをしているなら。
		if (GetIsFishingInArea(m_targetFishingArea) == true) {
			m_targetFishData;
			//釣りをしている時間が終わったかどうか？
			if (m_inGameState->GetTime() - m_carryOverFishingTime <= m_fishingEndTime) {
				//釣りを終える。
				EndFishing();
			}
		}





	}
}


void Enemy::FindGameObjects()
{
	m_backGround = FindGO<BackGround>("backGround");
	m_inGameState = FindGO<InGameState>("inGameState");
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_scoreManager = FindGO<ScoreManager>("scoreManager");
	m_player = FindGO<Player>("player");
}

void Enemy::FindStealPositionBarObjects()
{
	m_stealPositionBar = FindGO<StealPositionBar>("stealPositionBar");
}

void Enemy::InitFishingBaseTimes()
{
	//釣りのベース時間をセット。
	m_fishingBaseTimes[FishRarity::Common] = 10.0f;
	m_fishingBaseTimes[FishRarity::Rare] = 20.0f;
	m_fishingBaseTimes[FishRarity::SuperRare] = 40.0f;


}


void Enemy::SetMoveSpeed()
{



	if (m_isCountdownFinished == true)//カウントダウンが終わったら。
	{
		//釣り中でなければターゲットエリアに向かう。
		if (IsFishingInactive() == true)
		{

			moveSpeed = Vector3::Zero;
			Vector3 fishingAreaPositionXZ = Vector3(m_fishingAreaPosition[static_cast<int>(m_targetFishingArea)].x, 0.0f, m_fishingAreaPosition[static_cast<int>(m_targetFishingArea)].z);
			Vector3 enemyPosXZ = Vector3(m_position.x, 0.0f, m_position.z);
			Vector3 range_of_enemy_and_position = fishingAreaPositionXZ - enemyPosXZ;//敵ポジションと選んでいるポジションの距離。


			if (range_of_enemy_and_position.Length() >= 20.0f) //敵が狙ったエリアにまだついていなければ。
			{

				moveSpeed += range_of_enemy_and_position;
				moveSpeed.Normalize();
				moveSpeed *= 700.0f;
			}
			else {//狙った魚の場所についたら。

				//釣りを開始する。
				StartFishing(m_inGameState->GetTime());

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


void Enemy::SetTargetFishingArea(Area targetFishingArea)
{
	m_targetFishingArea = targetFishingArea;
}

void Enemy::InterruptAndRelocateFishing(Area targetFishingArea)
{
	//途中で釣りをやめたので、途中までつっていた経過時間を次に引き継ぐための。
	//変数をセットする。
	m_carryOverFishingTime = m_fishingStartTime - m_inGameState->GetTime();

	//釣りをしていない？がfalseなら。
	//（釣りをしているなら）。
	if (IsFishingInactive() == false)
	{
		//釣り中？をfalseに。
		SetIsFishingInArea(false);
	}

	//ターゲットエリアを変える。
	SetTargetFishingArea(targetFishingArea);
}

void Enemy::StartFishing(float currentTime)
{
	//ターゲットの魚のFishDataをセットする。
	SetTargetFishData(m_targetFishingArea);

	//釣り中のエリアをセットする。
	SetIsFishingInArea(true, m_targetFishingArea);

	//釣りが終わる時間をセットする。
	SetFishingEndTime(currentTime);

	//釣りを開始した時間をセット。
	m_fishingStartTime = currentTime;
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
void Enemy::SetFishingEndTime(float currentTime)
{
	//釣りが終わる時間をセットする。
	m_fishingEndTime = currentTime - m_fishingBaseTimes[m_targetFishData.rarity];
}

bool Enemy::IsEndCurrentFishing() const
{
	return false;
}





bool Enemy::GetIsFishingInArea(Area area)
{
	return m_isFishingInArea[area];
}

void Enemy::EndFishing()
{
	m_carryOverFishingTime = 0.0f; //釣りを終えたので、経過時間をリセット。

	//釣り中？をfalseに。
	SetIsFishingInArea(false);

	if (DecideFishingResult(m_targetFishData.rarity)) {//成功なら。
		//釣り上げた魚のスコアをセット。
		m_scoreManager->SetScore(m_targetFishData.score, m_targetFishData.fishType, CharacterType::enemy);
	}

	//ターゲットエリアを変える前に魚を更新する
	m_inGameState->ChangeFish();
	if (m_stealPositionBar->IsAnyStealLockActive()) {//もしプレイヤーが敵からエリアを奪った後なら。
		m_stealPositionBar->SetIsStealLockActive(false); //魚のロックをoffにする。
	}
	////ターゲットを変える。
	//SetTargetFishingArea(m_positionSelection->FindFishHighScore()/*スコアが一番高い魚を探す*/);




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
	m_rarityProbability[FishRarity::Common] = 80;
	m_rarityProbability[FishRarity::Rare] = 70;
	m_rarityProbability[FishRarity::SuperRare] = 20;
}

