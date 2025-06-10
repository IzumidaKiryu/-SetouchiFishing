#pragma once
#include "PlayFishingStateBase.h"

class FishCatchEffectState :public PlayFishingStateBase
{
public:
	FishCatchEffectState();
	~FishCatchEffectState();
	bool OnStart() override;
	bool OnInit() override;
	
	//bool Start() override;
	bool isPlay = false;
	void Update()override;
	void Render(RenderContext& rc);
	void SetModel(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		bool shadowCast,
		bool shadowDrop);
	

	void SetAnim(const char* activeAnim);
	void PlayAnim();

	enum GetFishType {
		Hamachi,
		Tachiuo,
		Tai,
		Hirame,
		Pearl,
		Jakoten,
		num
	};
	enum EnAnimationClip
	{		//アニメーション。
		enAnimationClip_active,
		enAnimationClip_Num,
	};

	AnimationClip m_animClip[enAnimationClip_Num];
	EnAnimationClip animeClip = enAnimationClip_active;
	ModelRender m_modelRender;
	GetFishType fishType = num;

	Vector3 m_pos = { 0.0f,0.0f,15.0f };

	Vector3 m_initCameraPos;

};

