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

	TensionGauge();
	~TensionGauge();
	void Update();
	void Set_signs_of_Fish_UI();
	void SetUpwardFishUI();
	void SetDownwardFishUI();
	void RightAndLeftManagement();
	void SetFishUI_Position(float current_fish_range_and_max_range_rate);
	void SetFloatUI_Position(float current_float_range_max_range_rate);
	void SetScale();

	Vector3 GetFishUIPosition();
	//void AnnounceChangeFishState();


	float m_barBottom = -335.0f;//ゲージ下端。
	float m_barTop = 317.0f;//ゲージの上端。
	float m_bar_length = std::abs(m_barTop) + std::abs(m_barBottom);//バーの長さ。(abs()は絶対値を求める関数。)
	bool m_should_change_fish_to_anger_ui = true;
	Vector3 fish3DPos;
	Vector3 m_fishUIPos = {0.0f,0.0f,0.0f};

	//円周率
	double pie = 3.141592653589793;
	FIshState m_fishState;
	SpriteRender m_tensionGaugeInside;
	SpriteRender m_tensionGaugeOutside;
	SpriteRender m_signs_of_Fish;//魚影
	SpriteRender m_rodFloatUI;
	PlayFishing* m_playFishing;
	FightFishState* m_fightFishState;
	RodFloatMove* m_rodFloatMove;
	Quaternion m_upward;
	Quaternion m_downward;
	FishDetectionRadius* m_fishDetectionRadius;

	void Render(RenderContext& rc);
};