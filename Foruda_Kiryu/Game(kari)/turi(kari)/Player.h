#pragma once
#include"Character.h";
//プレイヤークラス。
class Player : public Character
{
public:
	Player();
	~Player();
	//更新処理。
	/*void Update();*/
	//ムーブスピードを設定。
	void SetMoveSpeed() override;
	//移動処理。
	//void Move();
	////回転処理。
	//void Rotation();
	////ステート管理。
	//void ManageState();
	////アニメーションの再生。
	//void PlayAnimation();

	//メンバ変数。
	//enum EnAnimationClip {		//アニメーション。
	//	enAnimationClip_Idle,
	//	enAnimationClip_Walk,
	//	enAnimationClip_Jump,
	//	enAnimationClip_Num,
	//};
/*	AnimationClip animationClips[enAnimationClip_Num];*/		//アニメーションクリップ。
	//CharacterController characterController;  //キャラクターコントローラー。
	//Vector3 moveSpeed;		//移動速度。
	//Quaternion rotation;  //クォータニオン。
	//int playerState = 0;	//プレイヤーのステート(状態)を表す変数。
	//int starCount = 0;	//集めた☆の数をカウントする。
	void Render(RenderContext& rc);
};
