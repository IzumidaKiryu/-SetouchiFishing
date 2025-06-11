#include "stdafx.h"
#include "FishCatchEffectState.h"

FishCatchEffectState::FishCatchEffectState()
{
}

FishCatchEffectState::~FishCatchEffectState()
{
}

bool FishCatchEffectState::OnStart() {
	return true;
}

bool FishCatchEffectState::OnInit() {
	//アニメーションの初期化。ここにアニメーションのファイルパスを入れてね。
	SetAnim("Assets/animData/Fish/fishShadow.tka");
	//モデルの設定。モデルの初期化をするよ！ファイルパスを直してね！
	SetModel("Assets/modelData/Fish/fishShadow.tkm", m_animClip, enAnimationClip_Num, enModelUpAxisZ, true, false);

	return true;
}

void FishCatchEffectState::Update() {
	m_modelRender.SetPosition(m_pos);
	PlayAnim();
	
	m_modelRender.Update();
}
void FishCatchEffectState::Render(RenderContext& rc) {
	
		m_modelRender.Draw(rc);

	
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
void FishCatchEffectState::SetModel(const char* filePath, AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis, bool shadowCast = true, bool shadowDrop = false)
{
	//
	m_modelRender.Init(filePath, animationClips, numAnimationClips, enModelUpAxis, shadowCast, shadowDrop);
	m_modelRender.SetScale(Vector3{ 2.0f,2.0f,2.0f });
}

void FishCatchEffectState::SetAnim(const char* activeAnim)
{

	m_animClip[enAnimationClip_active].Load(activeAnim);
	m_animClip[enAnimationClip_active].SetLoopFlag(false);
}

void FishCatchEffectState::PlayAnim()
{
	switch (animeClip) {
	case enAnimationClip_active:
		//再生スタート
		m_modelRender.PlayAnimation(enAnimationClip_active);
		if (m_modelRender.IsPlayingAnimation() == false) {
			//アニメーションが終わったら終了
			Success();

		}
		break;
	default:
		break;
	}
}
