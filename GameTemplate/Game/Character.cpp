#include "stdafx.h"
#include "Character.h"
#include"FishingAnimationState.h"

Character::Character()
{

}

Character::~Character()
{

}

bool Character::Init()
{
	
	InitFishingInArea();
	//キャラコンを初期化する。
	characterController.Init(25.0f, 75.0f, m_position);

	
	return true;
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
	
	//これ追加。

	//絵描きさんの更新処理。
	modelRender.Update();

	//.SetPosition(m_rodPosition);
	m_rodModel.Update();
}
/// <summary>
		/// 通常描画用の初期化
		/// </summary>
		/// <param name="filePath">ファイルパス</param>
		/// <param name="animationClips">アニメーションクリップ</param>
		/// <param name="numAnimationClips">アニメーションクリップの数</param>
		/// <param name="enModelUpAxis">モデルの上方向</param>
		/// <param name="shadowCast">trueなら影を描画する</param>
		/// <param name="ShadowDrop">trueなら影を受ける</param>
void Character::SetModel(const char* filePath, AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis, bool shadowCast = true, bool shadowDrop = false)
{
	//ユ
	// ニティちゃんのモデルを読み込む。
	modelRender.Init(filePath, animationClips, numAnimationClips, enModelUpAxis,shadowCast, shadowDrop);
	modelRender.SetScale(Vector3{ 2.0f,2.0f,2.0f });
}
void Character::SetRodModel(const char* filePath, AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis, bool shadowCast, bool shadowDrop)
{
	// 修正:竿モデルの初期かなのにmodelRenderに上書きしていた。// AnimationClip の引数を nullptr に設定して、型の不一致を解消  
	m_rodModel.Init(filePath, animationClips, numAnimationClips, enModelUpAxis, shadowCast, shadowDrop);
	m_rodModel.SetScale(Vector3{ 2.0f, 2.0f, 2.0f });
}
void Character::SetAnimationClipsLoad(const char* animationClip_Idle, const char* animationClip_Walk, const char* animationClip_Cast)
{
	animationClips[enAnimationClip_Idle].Load(animationClip_Idle);
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load(animationClip_Walk);
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	/*animationClips[enAnimationClip_Cast].Load(animationClip_Cast);
	animationClips[enAnimationClip_Cast].SetLoopFlag(false);*/
	animationClips[enAnimationClip_Cast].Load(animationClip_Cast);
	animationClips[enAnimationClip_Cast].SetLoopFlag(false);

}
void Character::SetRodAnimationClipsLoad(const char* animationClip_Rod)
{
	m_rodAnimationClips[enAnimationClip_Rod].Load(animationClip_Rod);
	m_rodAnimationClips[enAnimationClip_Rod].SetLoopFlag(false);
}
void Character::SetMoveSpeed()
{
	//派生クラスで定義する。
}
void Character::Move()
{
	moveSpeed = Vector3::Zero;


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
	m_position = m_initpos +characterController.Execute(moveSpeed, 1.0f / 60.0f);

	//絵描きさんに座標を教える。
	modelRender.SetPosition(m_position);
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
	m_castAnimationState = FindGO<FishingAnimationState>("fishingAnimationState");
	//キャストアニメーションクラスが実行されていたら。
	if (m_is_cast) {
		playerState = enAnimationClip_Cast;
		return;
	}
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
	case enAnimationClip_Cast:
		modelRender.PlayAnimation(enAnimationClip_Cast);
		//きりゅう修正。竿のアニメーションの再生だから竿のモデルのアニメーションの設定。
		m_rodModel.PlayAnimation(enAnimationClip_Rod);
		break;
	}

}
bool Character::SetChastAnimation()
{
	m_is_cast = true;
	return modelRender.IsPlayingAnimation();
}
void Character::EndCastAnimation()
{
	m_is_cast = false;
}
Vector3 Character::GetPos()
{
	return m_position;
}
float Character::GetAnimationRatio()
{
	return modelRender.GetAnimationRatio();
}
void Character::SetIdleAnimation()
{
	playerState = enAnimationClip_Idle;
	modelRender.PlayAnimation(enAnimationClip_Idle);
}
void Character::SetInitPosition(Vector3 pos)
{
	m_initpos = pos;
}


void Character::SetIsFishingInArea(bool isFishingInArea, Area fishingArea)
{
	for (int i = 0; i < 6; i++)
	{
		//他のところは自動的にfalse。
		if (i == static_cast<int>(fishingArea)) {
			m_isFishingInArea[fishingArea] = isFishingInArea;
		}
		else {
			m_isFishingInArea[static_cast<Area>(i)] = false;
		}
	}
}

bool Character::GetIsFishingInArea(Area area)
{
	return m_isFishingInArea[area];
}

void Character::InitFishingInArea()
{
	for (int i = 0; i < 6; ++i) {
		m_isFishingInArea[static_cast<Area>(i)] = false;
	}
}


////描画処理。
//void Character::Render(RenderContext & rc)
//{
//	//ユニティちゃんを描画する。
//	modelRender.Draw(rc);
//}
