#pragma once
class PlayFishing;
class FishModel :public IGameObject
{
public:

	FishModel();
	~FishModel();
	bool Init();
	bool Start()override;
	void Update();
	ModelRender m_fishModel;

	void SetShadowAnimationClipsLoad(const char* animationClip_Shadow);
	
	void Render(RenderContext& rc);
	void SetPosition(Vector3 position);
	void SetInitPositon();
	void SetPosition();
	void SetSumPosition(Vector3 position);
	float ChangePosition_Z(float current_fish_range_and_max_range_rate);//魚の距離の割合いを、魚のｚポジションに変える。
	float GetCurrentFishRangeAndMaxRangeRate(float position_z);
	Vector3 GetPosistion();
	void SetAnimationClipsLoad();
	void TurnUpward();
	void TurnDownward();
	void SetISTurningUpwardTrue();
	void SetISTurningDownwardTrue();
	void SetScaleByIndividualFactor(float scale);

	enum EnShadowAnimationClip {
		enAnimationClip_Shadow,
		enAnimationClip_ShadowNum
	};

	Vector3 m_scale=Vector3::One*0.5;
	float m_limit_range_with_ship = 2010.1f;
	Vector3 m_position;
	AnimationClip m_animationClips;
	AnimationClip m_ShadowAnimationClips[enAnimationClip_ShadowNum];	//ロッドのアニメーションクリップ。
	float turn_t;
	bool m_is_TurningUpward = false;//向きが上向きになるように回っているかどうか。
	bool m_is_TurningDownward = false;//向きが下向きになるように回っているかどうか。

	PlayFishing* m_playFishing;
};

