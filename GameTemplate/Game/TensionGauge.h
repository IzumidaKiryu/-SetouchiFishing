#pragma once
//さかなが右を向いていたら魚は逃げようと抵抗している、左を向いていたら抵抗しない。

#include "FightFishState.h"



class GetRotation;
class PlayFishing;
class FishingRodHP;
class RodFloatMove;
class FightFishState;
class FishDetectionRadius;
class TensionGauge :public IGameObject
{
public:
	enum class FlapFrameType {
		A,
		B,
		Count // フレーム数としても使える
	};
	TensionGauge();
	~TensionGauge();
	bool Init();
	bool Start()override;
	void Update();
	void FindGOGameObject();
	void SetUpwardFishUI();
	void SetDownwardFishUI();
	void RightAndLeftManagement();
	void SetFishUI_Position(float currentFishDistanceRate);
	void SetFloatUI_Position(float current_float_range_max_range_rate);
	void SetFloatScale();
	void SetFishUIScaleByIndividualFactor(float scale);
	void SwayShipUIByWaves();



	Vector3 GetFishUIPosition();

	//途中でNewGOされるクラスのオブジェクトがNewGOされた
	// 瞬間にこの関数を呼びFindGOする。
	void FindGOFishDetectionRadius();
	void FindGORodFloatMove();
	void FishUIFinFlap();
	void SetIsFinFlapping(bool isFinFlapping);


	//void AnnounceChangeFishState();

private:



	FlapFrameType m_flapFrameType = FlapFrameType::A;
	float m_flapElapsedTime = 0.0f;
	const float m_flapSwitchInterval = 10;

	/// <summary>
	/// 魚のUIを初期化
	/// </summary>
	void InitFishUI();
	float m_barBottom = -335.0f;//ゲージ下端。
	float m_barTop = 317.0f;//ゲージの上端。
	float m_bar_length = std::abs(m_barTop) + std::abs(m_barBottom);//バーの長さ。(abs()は絶対値を求める関数。)
	bool m_should_change_fish_to_anger_ui = true;
	Vector3 fish3DPos=Vector3::Zero;
	Vector3 m_fishUIPos = {0.0f,0.0f,0.0f};
	Vector3 m_shipUIPos = { 650.0f, -400.0f, 0.0f };
	Vector3 m_shipUIScale = Vector3::One * 2.5f;//船のUIの大きさ
	float m_shipFloating_t=0.0f;

	//円周率
	double pie = 3.141592653589793;

	bool m_isFinFlapping = false;
	Vector3 m_baseSigns_of_FishUiSize = Vector3::One;
	SpriteRender m_tensionGaugeInside;
	SpriteRender m_tensionGaugeOutside;
	SpriteRender m_signs_of_Fish;//魚影
	SpriteRender m_signs_of_Fish_FlappingFins[2];//魚影がひれをパタパタさせるUI
	SpriteRender m_rodFloatUI;
	SpriteRender m_shipUI;
	PlayFishing* m_playFishing = nullptr;
	FightFishState* m_fightFishState = nullptr;
	RodFloatMove* m_rodFloatMove=nullptr;
	Quaternion m_upward;
	Quaternion m_downward;
	FishDetectionRadius* m_fishDetectionRadius = nullptr;

	void Render(RenderContext& rc);

};