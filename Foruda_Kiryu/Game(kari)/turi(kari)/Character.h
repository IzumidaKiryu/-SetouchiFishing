#pragma once
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
		const char* animationClip_Walk
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

	//メンバ変数。
	ModelRender modelRender;	//モデルレンダ―。
	Vector3 position;			//座標。
	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		//enAnimationClip_Jump,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];		//アニメーションクリップ。
	CharacterController characterController;  //キャラクターコントローラー。
	Vector3 moveSpeed;		//移動速度。
	Quaternion rotation;  //クォータニオン。
	int playerState = 0;	//プレイヤーのステート(状態)を表す変数。

};

