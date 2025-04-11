#pragma once
//さかなが右を向いていたら魚は逃げようと抵抗している、左を向いていたら抵抗しない。
class GetRotation;
class PlayFishing;
class TensionGauge :public IGameObject
{
public:

	TensionGauge();
	~TensionGauge();
	void Update();
	void RightAndLeftManagement();
	void SetSigns_of_Fish_Position();
	void SetFishEscapePower();
	void SetFishDirection();//魚が向いている方向を変えるかどうか。
	void FishDirectionChange();//魚が向いている方向を変える。
	void failure();//失敗。
	void success();//成功。
	float GetRotationPower();
	void Set_signs_of_Fish_UI();

	float m_forcePullFish;//魚を引っ張る力。
	bool m_previous_isFishDirectionisLeft = true;//前のフレームで魚が左を向いていたかどうか。
	bool m_isFishDirectionisLeft = true;//魚が左を向いているかどうか。
	float m_signs_of_Fish_Position = 0.0f;//魚影のポジション（X軸）
	float m_gaugeRightmost = 473.0f;//ゲージの右端。
	float m_gaugeLeftmost = -473.0f;//ゲージの左端。
	float m_fishEscapePower = 0.0f;//魚が逃げようとする力。（矢印を左右に引っ張る力）。

	SpriteRender m_tensionGaugeInside;
	SpriteRender m_tensionGaugeOutside;
	SpriteRender m_signs_of_Fish;//魚影
	GetRotation* m_getRotation;
	PlayFishing* m_playFishing;
	void Render(RenderContext& rc);
};