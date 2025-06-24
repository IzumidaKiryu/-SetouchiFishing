#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include"BackGround.h"
#include"InGameState.h"
#include"PlayFishing.h"


Player::Player()
{
	SetInitPosition(Vector3{ 0.0f,0.0f,0.0f });


}

Player::~Player()
{

}


bool Player::Init()
{
	Character::Init();

	//アニメーションをセット。
	SetAnimationClipsLoad(
		"Assets/animData/Player/Idle.tka",
		/*"Assets/animData/Player/Walking.tka",*/
		"Assets/animData/Player/playerWalk.tka",
		"Assets/animData/Player/FishingCast.tka"
	);

	SetRodAnimationClipsLoad(
		"Assets/animData/Player/rod.tka",
		"Assets/animData/Player/rod.tka"
	/*	"Assets/animData/Player/akoyagaiFinishMorph.tka"*/
	);

	SetModel("Assets/modelData/Player/Player.tkm", animationClips, enAnimationClip_Num, enModelUpAxisZ, true, false);
	//きりゅう修正。モデルの初期化の際にPlayerのアニメデータがセットされていたため修正。
	SetRodModel("Assets/modelData/Player/rod.tkm", m_rodAnimationClips, enAnimationClip_RodNum, enModelUpAxisZ, true, false);

	//SetRodModel("Assets/modelData/Player/rod.tkm", m_rodAnimationClips, enAnimationClip_RodNum, enModelUpAxisZ, true, false);
	m_rodModel.SetPosition(m_rodPosition); // ここで座標を反映

	return true;
}

bool Player::Start()
{
	m_backGround = FindGO<BackGround>("backGround");

	m_playFishing = FindGO<PlayFishing>("playFishing");

	return true;
}

void Player::SetMoveSpeed()
{
	m_position;
	if (m_is_moveActive) {
		Vector3 forward = Vector3{ 0.0f,0.0f,1.0f };
		Vector3 right = Vector3{ 1.0f,0.0f,0.0f };

		//左スティックの入力量を取得。
		Vector3 stickL;
		stickL.x = g_pad[0]->GetLStickXF();
		stickL.y = g_pad[0]->GetLStickYF();

		//左スティックの入力量と300.0fを乗算。
		right *= stickL.x * 500.0f;
		forward *= stickL.y * 500.0f;

		//移動速度にスティックの入力量を加算する。
		moveSpeed += right + forward;
	}

}

void Player::SetMoveDeActive()
{
	m_is_moveActive = false;
}

void Player::SetMoveActive()
{
	m_is_moveActive = true;
}

//
// Player.cpp に追加
void Player::SetRodPosition(const Vector3& pos) {
    m_rodPosition = pos;
}

//描画処理。
// Render内で座標を反映
void Player::Render(RenderContext& rc)
{
	//ユニティちゃんを描画する。
	modelRender.Draw(rc);
	if (m_playFishing != nullptr)
	{
		
		m_rodModel.Draw(rc);
	}
}