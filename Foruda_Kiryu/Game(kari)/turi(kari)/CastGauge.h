#pragma once
class GaugeCastSuccessful;
class TensionGauge;
class FishingGauge;
class PositionSelection;
class PlayFishing;

class CastGauge :public IGameObject
{
public:
	CastGauge();
	~CastGauge();
	void Update();
	void SetArrowPosition();
	void UpAndDownManagement();//キャストゲージの上下動作の管理。
	void UpwardOperation();
	void DownwardOperation();
	void SetGaugeSpead();
	void HitTest();
	void Failure();//失敗。
	void Success();//成功。


	float m_arrowPosition = -237.0f;//矢印のポジション（初期設定は-237）
	bool upState = true;//上がっているかのステート
	void Render(RenderContext& rc);
	float m_gaugeUpperLimit = 237.0f;//ゲージの上限
	float m_gaugeLowerLimit = -237.0f;//ゲージの下限
	float m_gaugeSpead;

	float m_heightFirstGaugeCastSuccessful = 10.0f;//成功ゲージの最初の横幅。
	bool is_ended=false;

	SpriteRender m_castGaugeOutside;
	SpriteRender m_castGaugeInside;
	SpriteRender m_castGaugeArrow;
	GaugeCastSuccessful* m_gaugeCastSuccessful=nullptr;
	FishingGauge* m_fishingGauge;
	TensionGauge* tensionGauge=nullptr;
	PositionSelection* m_positionSelection;
	PlayFishing* m_playFishing;
	ModelRender m_rodFloatModel;

};

