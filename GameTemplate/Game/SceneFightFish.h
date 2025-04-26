#pragma once
enum FIshState
{
	setWhen_State_Announce_Should,//いつアナウンスするかを設定する。
	normal,//普通。
	setWhen_State_Angry_or_exhausted_Should,//いつステートをAngryかexhaustedに変えるか。
	announce,//状態の変化をアナウンスする。
	change_Angry_or_exhausted,
	angry,//怒っている。
	exhausted,//疲弊している。
};

class GetRotation;
class PlayFishing;
class FishingRodHP;
class RodFloatMove;
class TensionGauge;
class GameCamera;
class PositionSelection;
class SceneFightFish:public IGameObject
{
public:
	SceneFightFish();
	~SceneFightFish();

	void Update();
	void RightAndLeftManagement();
	void SetSigns_of_Fish_Position();
	void SetFishEscapePower();
	void SetFishDirection();//魚が向いている方向を変えるかどうか。
	void FishDirectionChange();//魚が向いている方向を変える。
	void failure();//失敗。
	void success();//成功。
	float GetRotationPower();

	void SetWhen_State_Announce_Should_State();
	void NormalState();//魚が普通の状態の時の処理。
	void When_State_Angry_or_exhausted_Shoul();
	void AnnounceState();
	void Change_Angry_or_Exhausted_State();
	void AngerState();//魚が怒っているときの処理。
	void ExhaustedState();//魚が疲弊しているときの処理。
	void FishStateAdminister();
	void SetRodFloatModel();
	void SetCamera();
	void FrameCount();
	void Set3DFishPosition();
	void SetRangeRate();

	float m_forcePullFish;//魚を引っ張る力。
	bool m_previous_is_fish_suited_for_upper_side = true;//前のフレームで魚が上を向いていたかどうか。
	bool is_fish_suited_for_upper_side = true;//魚が上側を向いているかどうか。
	float m_initRangeRate;
	float m_range_rate = 0.0f;//最大距離と今いる距離の割合。
	float m_barTop = 473.0f;//ゲージの上端。
	float m_barBottom = -473.0f;//ゲージの下端。
	float m_fishEscapePower = 0.0f;//魚が逃げようとする力。（矢印を左右に引っ張る力）。
	int m_fishChange_in_DirectionTimes = 0;//魚が方向転換した数。
	int m_when_state_announce_should = 0;//いつステートをアナウンスに変えるか。（この数字23なら方向転換回数が23回目の時にステートをアナウンスにする。）
	int m_when_State_Angry_or_exhausted_Should;//いつステートをAngryかexhaustedに変えるか。
	int state_changed_when_directiontimes;//一番新しくステートが変わった時に魚が今まで方向転換した数。
	int m_angerState_frame_count = 0;//アンガーステートの時にフレームをカウントする。
	bool m_reduce_Hp_when_angry = true;
	bool m_should_change_fish_to_anger_ui = true;
	int m_frameCount = 0;
	float m_this_frame_by_fish_advanced_distance;//このフレームで魚が進んだ距離（割合で表す）
	float m_total_by_fish_advanced_distance;//トータルで魚が進んだ距離。

	Vector3 fish3DPos;

	FIshState m_fishState;
	SpriteRender m_tensionGaugeInside;
	SpriteRender m_tensionGaugeOutside;
	SpriteRender m_signs_of_Fish;//魚影
	GetRotation* m_getRotation;
	PlayFishing* m_playFishing;
	FishingRodHP* m_fishingRodHP;
	RodFloatMove* m_rodFloatMove;
	TensionGauge* m_tensionGauge;
	GameCamera* m_gameCamera;
	PositionSelection* m_positionSelection;
};

