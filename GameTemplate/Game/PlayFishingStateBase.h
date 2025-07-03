#pragma once
#include"PlayFishing.h"

class GameCamera;
class FishModel;
class PlayFishing;
class RodFloatMove;
class TensionGauge;
class Player;

enum FishFacing {
	Upward,
	Downward,
};
class PlayFishingStateBase :public IGameObject
{
public:

	PlayFishingStateBase();
	~PlayFishingStateBase();
	bool Start()override final;
	virtual bool OnStart()=0;
	virtual bool Init()final;
	virtual bool OnInit()=0;
	void Update();
	void ChangeState();
	bool GetIsChengeState();
	void SetSuccess();
	void SetFailure();
	Successful_or_Failure GetSuccessful_or_Failure();
	void SetCamera(Vector3 position, Vector3 targete);
	void SumFishModelPosition(Vector3 position);
	void SumFishModelPosition(float current_fish_range_and_max_range_rate);
	void SumRodFloatPosition(Vector3 position);
	void SumRodFloatPosition(float current_float_range_max_range_rate);

	void SetFishData();
	void SetFish();//ポジションを反映させるためにこれを呼ぶ。
	/*void SetFloat(float current_float_range_max_range_rate);*/
	void ResetFishModelPosition();
	void ResetFloatModelPosition();
	void SetFloat();
	void SetFloatPosition();
	void SetFishModelPos();
	void SetFishUIPosition(float current_fish_range_and_max_range_rate);
	void SetFloatUIPosition(float current_float_range_max_range_rate);
	void SetCurrentFishRangeAndMaxRangeRate(float current_fish_range_and_max_range_rate);
	Vector3 GetRodPosition();
	Vector3 GetFishModelPosition();
	void Success();
	void Failure();
	void Pass_Current_Fish_Range_And_Max_Range_Rate();//プレイフィッシングに魚の距離の割合いを渡す。
	void Pass_Current_Float_Range_And_Max_Range_Rate();//プレイフィッシングにウキの距離の割合いを渡す。
	void Pass_FishModelPos();
	void Pass_FloatModelPos();
	void Pass_CameraPos();
	void Pass_CameraTarget();
	void Set_Init_Current_Fish_Range_And_Max_Range_Rate();
	void Set_Init_Current_Float_Range_And_Max_Range_Rate();
	void Set_Init_FishModelPos();
	void Set_Init_FloatModelPos();
	void Set_Init_CameraPos();
	void Set_Init_CameraTarget();
	void SetFishModelDownward();
	void SetFishModelUpward();
	void SetFishDownward();
	void SetFishUpward();
	virtual void CameraManagement();
	float GetCurrentFishRangeAndMaxRangeRate();
	float GetCurrent_Float_Range_Max_Range_Rate();
	Vector3 GetPlayerPos();
	Vector3 GetFishModelPos();
	Vector3 GetFloatModelPos();
	void SetFloatGameObject(RodFloatMove* rodfloatmove);

	enum FloatingPattern {
		CameraPattern,
		ModelPattern
	};

	Vector3 Floating(FloatingPattern floatingPattern=ModelPattern);//海の上で浮いている表現



	float m_floatingTime = 0.0f;
	Vector3 m_floating=Vector3::Zero;


	Vector3 m_initFishModelPos = Vector3::Zero;
	Vector3 m_initFloatModelPos = Vector3::Zero;

	Vector3 m_sumFishModelPos = Vector3::Zero;
	Vector3 m_sumFloatModelPos = Vector3::Zero;

	Vector3 m_cameraPos = Vector3::Zero;
	Vector3 m_cameraTarget = Vector3::Zero;

	float m_currentFishRangeAndMaxRangeRate;//今の魚の距離と最大の魚の距離の割合（それぞれのクラスで船と魚の最大距離とこの割合を掛けて場所を表現する。）
	float m_sumCurrentFloatRangeMaxRangeRate;//今のウキの距離と最大のウキの距離の割合。
	bool m_isChengeState = false;

	float m_cameraPosTime = 0;
	float m_cameraTargetTime = 0;
	float m_animationTime = 0;

	Vector3 m_initCameraPos = Vector3::Zero;
	Vector3 m_endCameraPos = Vector3::Zero;

	Vector3 m_initCameraTarget = Vector3::Zero;
	Vector3 m_endCameraTarget = Vector3::Zero;

	GameCamera* m_gameCamera = nullptr;
	FishModel* m_fishModel = nullptr;
	RodFloatMove* m_rodFloatMove=nullptr;
	PlayFishing* m_playFishing = nullptr;
	TensionGauge* m_tensionGauge = nullptr;

	FishData m_fishData;
	Successful_or_Failure m_successfulOrFailure = unfixed;
	Player* m_player = nullptr;
	FishFacing m_fishFacing;

//private:
	Vector3 m_fishModelPos=Vector3::Zero;
	Vector3 m_floatModelPos=Vector3::Zero;
};

