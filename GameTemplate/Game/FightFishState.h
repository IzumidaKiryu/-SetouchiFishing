#pragma once
#include "PlayFishingStateBase.h"

class GetRotation;
class PlayFishing;
class FishingRodHP;
class RodFloatMove;
class TensionGauge;
class GameCamera;
class PositionSelection;
class FightFishState :public PlayFishingStateBase
{
public:

	FightFishState();
	~FightFishState();

	bool OnInit();
	bool OnStart();

	void Update();

	void FishDirectionChange();//魚が向いている方向を変える。
	void SetInitFishDirection();

	void CalculateDistanceMultiplier();//距離による魚の力の倍率を計算する。
	void CalculateCalculateFishPullForce();//魚を引っ張る力を計算する。
	void CalculateFishEscapePower();//魚が逃げようとする力を計算する。
	void CalculateFishDisplacement();//魚の移動距離を計算する。

	
	void CheckFailure();//失敗。
	void CheckSuccess();//成功。

	float GetRotationPower();

	void ExhaustedState();//魚が疲弊しているときの処理。
	void CameraManagement()override;
	FishFacing GetFishFacing();


	float m_forcePullFish=0.0f;//魚を引っ張る力。
	//bool is_fish_suited_for_upper_side = true;//魚が上側を向いているかどうか。
	float m_initRangeRate=0.0f;
	float m_fishEscapePower = 0.0f;//魚が逃げようとする力。
	int m_fishChange_in_DirectionTimes = 0;//魚が方向転換した数。
	int m_when_state_announce_should = 0;//いつステートをアナウンスに変えるか。（この数字23なら方向転換回数が23回目の時にステートをアナウンスにする。）
	int m_when_State_Angry_or_exhausted_Should = 0;//いつステートをAngryかexhaustedに変えるか。
	int state_changed_when_directiontimes=0;//一番新しくステートが変わった時に魚が今まで方向転換した数。
	int m_angerState_frame_count = 0;//アンガーステートの時にフレームをカウントする。
	bool m_reduce_Hp_when_angry = true;
	bool m_should_change_fish_to_anger_ui = true;
	int m_frameCount = 0;
	float m_this_frame_by_fish_advanced_distance=0.0f;//このフレームで魚が進んだ距離（割合で表す）
	float m_total_by_fish_advanced_distance=0.0f;//トータルで魚が進んだ距離。
	float m_distanceMultiplier=0.0f;//距離によりる魚の力の倍率。
	float m_upwardBiasPullForce = 0.02f;//魚が上を向いているときの引っ張るベースの力。
	float m_downwardBiasPullForce = 0.02f;//魚が下を向いているときの引っ張るベースの力。
	bool m_isFightActive = true;//失敗したらfalseにする。//キリュウ追加。
	Vector3 fish3DPos=Vector3::Zero;

	SpriteRender m_tensionGaugeOutside;
	SpriteRender m_signs_of_Fish;//魚影
	GetRotation* m_getRotation=nullptr;
	FishingRodHP* m_fishingRodHP=nullptr;
	PositionSelection* m_positionSelection=nullptr;
	FishFacing m_previous_fishFacing = Upward;//前のフレームで魚が上を向いていたかどうか。
	BuffManager* m_buffManager=nullptr;

};

