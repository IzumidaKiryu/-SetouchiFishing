#pragma once
class GaugeCastSuccessful;
class TensionGauge;
class FishingGauge;
class PositionSelection;
class PlayFishing;
class GameCamera;
class RodFloatMove;

enum ChasutState {
	playing,
	character_animation,
	RodFloatMoveNewGO,
	chast,
};
class Player;
class CastGauge :public IGameObject
{
public:
	CastGauge();
	~CastGauge();
	void Update();

	//UIの処理。
	void SetArrowPosition();//矢印の場所を決める
	void UpAndDownManagement();//キャストゲージの上下動作の管理。
	void UpwardOperation();
	void DownwardOperation();
	void SetGaugeSpead();
	void HitTest();
	void Failure();//失敗。
	void Success();//成功。


	void Chast();
	void ChastStaeManager();
	void SetCameraPlayingSgtate();
	void SetCameraChast();
	void SetCamera();
	void WaveMotion();//波の動きを疑似的に表現


	//void SetRodFloatPositon();//


	float m_arrowPosition = -237.0f;//矢印のポジション（初期設定は-237）
	bool upState = true;//上がっているかのステート
	void Render(RenderContext& rc);
	float m_gaugeUpperLimit = 237.0f;//ゲージの上限
	float m_gaugeLowerLimit = -237.0f;//ゲージの下限
	float m_gaugeSpead;

	float m_heightFirstGaugeCastSuccessful = 10.0f;//成功ゲージの最初の横幅。
	bool is_ended = false;
	float t = 0.0f;
	Vector3 m_gameCameraTarget;
	Vector3 m_gameCameraPos;

	SpriteRender m_castGaugeOutside;
	SpriteRender m_castGaugeInside;
	SpriteRender m_castGaugeArrow;
	GaugeCastSuccessful* m_gaugeCastSuccessful = nullptr;
	FishingGauge* m_fishingGauge;
	TensionGauge* tensionGauge = nullptr;
	PositionSelection* m_positionSelection;
	PlayFishing* m_playFishing;
	ModelRender m_rodFloatModel;

	Vector3 first_velocity_vector{ 1.0f,0.0f,0.0f };
	Vector3 m_waveMotion;//波の動き
	Vector3 g{ 0.0f,-30.0f,0.0f };
	Vector3 m_rodFloatPosition{ 0.0f,500.0f,0.0f };
	Vector3 InitPos{0.0f,500.0f,0.0f};

	GameCamera* m_gameCamera;
	RodFloatMove* m_rodFloatMove;
	ChasutState m_chastState= playing;

	Player* m_player;
};

