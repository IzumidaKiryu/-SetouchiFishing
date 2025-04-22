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
	void SetFishUI_Position(float position);
	//void AnnounceChangeFishState();


	float m_signs_of_Fish_UI_Position = 0.0f;//魚影のポジション（X軸）
	float m_barBottom = -473.0f;//ゲージ下端。
	float m_barTop = 473.0f;//ゲージの上端。
	float m_bar_length = std::abs(m_barTop) + std::abs(m_barBottom);//バーの長さ。(abs()は絶対値を求める関数。)
	bool m_should_change_fish_to_anger_ui = true;
	Vector3 fish3DPos;

	FIshState m_fishState;
	SpriteRender m_tensionGaugeInside;
	SpriteRender m_tensionGaugeOutside;
	SpriteRender m_signs_of_Fish;//魚影
	PlayFishing* m_playFishing;
	SceneFightFish* m_sceneFightFish;

	void Render(RenderContext& rc);
};