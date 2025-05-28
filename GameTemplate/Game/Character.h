#pragma once
class FishingAnimationState;
class Character : public IGameObject
{
public:
	Character();
	~Character();
	//更新処理。
	void Update();
	//モデルの設定。
	void SetModel(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis);
	void SetAnimationClipsLoad(
		const char* animationClip_Idle,
		const char* animationClip_Walk,
		const char* animationClip_Cast
	);
	//ムーブスピードを設定。
	void virtual SetMoveSpeed();
	//移動処理。
	void  Move();
	//回転処理。
	void Rotation();
	//ステート管理。
	void ManageState();
	//アニメーションの再生。
	void PlayAnimation();
	//void Render(RenderContext& rc);
	bool SetChastAnimation();
	void EndCastAnimation();
	//void SetIdleAnimation();
	bool m_is_cast = false;
	Vector3 GetPos();
	float GetAnimationRatio();
	void SetIdleAnimation();


	//メンバ変数。
	ModelRender modelRender;	//モデルレンダ―。
	Vector3 m_position = { 0.0f,100.0f,-100.0f };			//座標。
	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		//enAnimationClip_Jump,
		enAnimationClip_Cast,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];		//アニメーションクリップ。
	CharacterController characterController;  //キャラクターコントローラー。
	Vector3 moveSpeed;		//移動速度。
	Quaternion rotation;  //クォータニオン。
	EnAnimationClip playerState;	//プレイヤーのステート(状態)を表す変数。
	FishingAnimationState* m_castAnimationState;

};

