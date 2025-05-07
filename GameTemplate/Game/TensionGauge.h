#pragma once
//さかなが右を向いていたら魚は逃げようと抵抗している、左を向いていたら抵抗しない。

#include "SceneFightFish.h"


class GetRotation;
class PlayFishing;
class FishingRodHP;
class RodFloatMove;
class TensionGauge :public IGameObject
{
public:

	TensionGauge();
	~TensionGauge();
	void Update();
	void Set_signs_of_Fish_UI();
	void RightAndLeftManagement();
	void SetFishUI_Position(float current_fish_range_and_max_range_rate);
	void SetFloatUI_Position(float current_float_range_max_range_rate);
	void SetScale();
	//void AnnounceChangeFishState();


	float m_signs_of_Fish_UI_Position = 0.0f;//魚影のポジション（X軸）
	float m_barBottom = -335.0f;//ゲージ下端。
	float m_barTop = 317.0f;//ゲージの上端。
	float m_bar_length = std::abs(m_barTop) + std::abs(m_barBottom);//バーの長さ。(abs()は絶対値を求める関数。)
	bool m_should_change_fish_to_anger_ui = true;
	Vector3 fish3DPos;

	FIshState m_fishState;
	SpriteRender m_tensionGaugeInside;
	SpriteRender m_tensionGaugeOutside;
	SpriteRender m_signs_of_Fish;//魚影
	SpriteRender m_rodFloatUI;
	PlayFishing* m_playFishing;
	SceneFightFish* m_sceneFightFish;
	RodFloatMove* m_rodFloatMove;

	void Render(RenderContext& rc);
};