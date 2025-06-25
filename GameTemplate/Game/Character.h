#pragma once
#include"PositionSelection.h"

enum EnAnimationClip
{		//アニメーション。
	enAnimationClip_Idle,
	enAnimationClip_Walk,
	//enAnimationClip_Jump,
	enAnimationClip_Cast,
	enAnimationClip_Steal,
	enAnimationClip_Num
};

class FishingAnimationState;
class PlayFishing;
class Character : public IGameObject
{
public:
	Character();
	~Character();
	virtual bool Init();
	//更新処理。
	void Update();

	//モデルの設定。
	void SetModel(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		bool shadowCast,
		bool shadowDrop);
	void SetRodModel(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		bool shadowCast,
		bool shadowDrop);

	void SetAnimationClipsLoad(
		const char* animationClip_Idle,
		const char* animationClip_Walk,
		const char* animationClip_Cast,
		const char* animationClip_Steal
	);

	void SetRodAnimationClipsLoad(const char* animationClip_Rod,const char*anim);
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
	bool m_is_steal = false;
	void SetIsSteal(bool isState);
	Vector3 GetPos();
	float GetAnimationRatio();
	void SetIdleAnimation();
	virtual void SetInitPosition(Vector3 pos)final;
	void SetIsFishingInArea(bool isFishingInArea, Area fishingArea = Area::A);
	bool GetIsFishingInArea(Area area);
	void InitFishingInArea();


	Vector3 m_initpos = Vector3::Zero;

	
	//メンバ変数。
	std::map< Area, bool> m_isFishingInArea =//各エリアで釣っているかどうか？ 
	{
		{Area::A,false},
		{ Area::B,false },
	{ Area::C,false },
	{ Area::D,false },
	{ Area::E,false },
	{ Area::F,false },
	};
	ModelRender modelRender;	//モデルレンダ―。
	ModelRender m_rodModel;
	Vector3 m_position = { 0.0f,100.0f,-300.0f };			//座標。
	
	enum EnRodAnimationClip {
		enAnimationClip_RodIdle,
		enAnimationClip_Rod,
		enAnimationClip_RodNum
	};

	AnimationClip animationClips[enAnimationClip_Num];	//アニメーションクリップ。
	AnimationClip m_rodAnimationClips[enAnimationClip_RodNum];	//ロッドのアニメーションクリップ。
	CharacterController characterController;  //キャラクターコントローラー。
	Vector3 moveSpeed = Vector3::Zero;		//移動速度。
	Quaternion rotation;  //クォータニオン。
	EnAnimationClip playerState;	//プレイヤーのステート(状態)を表す変数。
	EnRodAnimationClip rodState;
	FishingAnimationState* m_castAnimationState;
	PlayFishing* m_playFishing;
	
};