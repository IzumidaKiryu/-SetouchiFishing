#include "stdafx.h"
#include "Character.h"
Character::Character()
{
	////アニメーションクリップをロードする。
	//animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	//animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	//animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	//animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	
	////ユニティちゃんのモデルを読み込む。
	//modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);

	//キャラコンを初期化する。
	characterController.Init(25.0f, 75.0f, position);
}

Character::~Character()
{

}

//更新処理。
void Character::Update()
{
	//移動処理。
	Move();

	//回転処理。
	Rotation();

	//ステート管理。
	ManageState();

	//アニメーションの再生。
	PlayAnimation();

	//絵描きさんの更新処理。
	modelRender.Update();
}

void Character::SetModel(const char* filePath, AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
{
	//ユニティちゃんのモデルを読み込む。
	modelRender.Init(filePath, animationClips, numAnimationClips, enModelUpAxis);
}

void Character::SetAnimationClipsLoad(const char* animationClip_Idle, const char* animationClip_Walk)
{
	animationClips[enAnimationClip_Idle].Load(animationClip_Idle);
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);

	animationClips[enAnimationClip_Walk].Load(animationClip_Walk);
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
}

void Character::SetMoveSpeed()
{
	//派生クラスで定義する。
}

void Character::Move()
{
	//xzの移動速度を0.0fにする。
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	
	SetMoveSpeed();
	



	//地面に付いていたら。
	if (characterController.IsOnGround())
	{
		//重力を無くす。
		moveSpeed.y = 0.0f;
	}
	//地面に付いていなかったら。
	else
	{
		//重力を発生させる。
		moveSpeed.y -= 2.5f;
	}

	//キャラクターコントローラーを使って座標を移動させる。
	position = characterController.Execute(moveSpeed, 1.0f / 60.0f);

	//絵描きさんに座標を教える。
	modelRender.SetPosition(position);
}

void Character::Rotation()
{
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える。
		rotation.SetRotationYFromDirectionXZ(moveSpeed);
		//絵描きさんに回転を教える。
		modelRender.SetRotation(rotation);
	}
}

//ステート管理。
void Character::ManageState()
{
	//地面に付いていなかったら。
	if (characterController.IsOnGround() == false)
	{
		//ここでManageStateの処理を終わらせる。
		return;
	}

	//地面に付いていたら。
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		//ステートを歩きにする。
		playerState = enAnimationClip_Walk;
	}
	//xとzの移動速度が無かったら(スティックの入力が無かったら)。
	else
	{
		//ステートを0(待機)にする。
		playerState = enAnimationClip_Idle;
	}
}




//アニメーションの再生。
void Character::PlayAnimation()
{
	//switch文。
	switch (playerState) {
		//プレイヤーステートが0(待機)だったら。
	case enAnimationClip_Idle:
		//ジャンプアニメーションを再生する。
		modelRender.PlayAnimation(enAnimationClip_Idle);
		break;

	case enAnimationClip_Walk:
		//プレイヤーステートが2(歩き)だったら。
		modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	}
}
	////描画処理。
	//void Character::Render(RenderContext & rc)
	//{
	//	//ユニティちゃんを描画する。
	//	modelRender.Draw(rc);
	//}

