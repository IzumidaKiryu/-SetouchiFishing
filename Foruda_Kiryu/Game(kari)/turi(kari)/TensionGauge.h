#pragma once
//さかなが右を向いていたら魚は逃げようと抵抗している、左を向いていたら抵抗しない。

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
	void SetWhen_State_Announce_Should_State();
	void NormalState();//魚が普通の状態の時の処理。
	void When_State_Angry_or_exhausted_Shoul();
	void AnnounceState();
	void Change_Angry_or_Exhausted_State();
	void AngerState();//魚が怒っているときの処理。
	void ExhaustedState();//魚が疲弊しているときの処理。
	void FishStateAdminister();
	//void AnnounceChangeFishState();

	float m_forcePullFish;//魚を引っ張る力。
	bool m_previous_isFishDirectionisLeft = true;//前のフレームで魚が左を向いていたかどうか。
	bool m_isFishDirectionisLeft = true;//魚が左を向いているかどうか。
	float m_signs_of_Fish_Position = 0.0f;//魚影のポジション（X軸）
	float m_gaugeRightmost = 473.0f;//ゲージの右端。
	float m_gaugeLeftmost = -473.0f;//ゲージの左端。
	float m_fishEscapePower = 0.0f;//魚が逃げようとする力。（矢印を左右に引っ張る力）。
	int m_fishChange_in_DirectionTimes=0;//魚が方向転換した数。
	int m_when_state_announce_should=0;//いつステートをアナウンスに変えるか。（この数字23なら方向転換回数が23回目の時にステートをアナウンスにする。）
	int m_when_State_Angry_or_exhausted_Should;//いつステートをAngryかexhaustedに変えるか。
	int state_changed_when_directiontimes;//一番新しくステートが変わった時に魚が今まで方向転換した数。
	int m_angerState_frame_count=0;//アンガーステートの時にフレームをカウントする。
	bool m_reduce_Hp_when_angry = true;
	bool m_should_change_fish_to_anger_ui = true;

	FIshState m_fishState;
	SpriteRender m_tensionGaugeInside;
	SpriteRender m_tensionGaugeOutside;
	SpriteRender m_signs_of_Fish;//魚影
	GetRotation* m_getRotation;
	PlayFishing* m_playFishing;
	FishingRodHP* m_fishingRodHP;

	void Render(RenderContext& rc);
};