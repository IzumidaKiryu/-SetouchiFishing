#pragma once
#include "PlayFishing.h"

class GameCamera;
class FishModel;
class RodFloatMove;
class TensionGauge;
class Player;

/// <summary>
/// 魚の向きを示す列挙型
/// </summary>
enum FishFacing {
	Upward,
	Downward,
};

/// <summary>
/// プレイフィッシングの共通処理を提供するベースステートクラス
/// </summary>
class PlayFishingStateBase : public IGameObject
{
public:
	PlayFishingStateBase();
	~PlayFishingStateBase();

	/// <summary>開始処理</summary>
	bool Start() override final;
	/// <summary>開始時にステート固有の処理を実行する</summary>
	virtual bool OnStart() = 0;

	/// <summary>初期化処理</summary>
	virtual bool Init() final;
	/// <summary>初期化時にステート固有の処理を実行する</summary>
	virtual bool OnInit() = 0;

	/// <summary>毎フレーム更新処理</summary>
	void Update();

	/// <summary>成功・失敗の設定</summary>
	void SetSuccess();
	void SetFailure();
	Successful_or_Failure GetSuccessful_or_Failure();

	/// <summary>カメラ位置と注視点を設定</summary>
	void SetCamera(Vector3 position, Vector3 target);

	/// <summary>魚のモデル座標を加算</summary>
	void SumFishModelPosition(Vector3 position);
	void SumFishModelPosition(float currentFishDistanceRate);

	/// <summary>ウキのモデル座標を加算</summary>
	void SumRodFloatPosition(Vector3 position);
	void SumRodFloatPosition(float currentFloatDistanceRate);

	/// <summary>魚データをPlayFishingから取得</summary>
	void SetFishData();
	/// <summary>魚とUIの座標設定</summary>
	void SetFish();
	/// <summary>魚モデル移動量のリセット</summary>
	void ResetFishModelPosition();
	/// <summary>ウキモデル移動量のリセット</summary>
	void ResetFloatModelPosition();

	/// <summary>ウキとUIの座標設定</summary>
	void SetFloat();
	void SetFloatPosition();
	void SetFishModelPos();
	void SetFishUIPosition(float currentFishDistanceRate);
	void SetFloatUIPosition(float currentFloatDistanceRate);
	void SetCurrentFishDistanceRate(float currentFishDistanceRate);

	/// <summary>現在の魚・ウキの位置割合取得</summary>
	float GetCurrentFishRangeAndMaxRangeRate();
	float GetCurrent_Float_Range_Max_Range_Rate();

	/// <summary>座標取得系</summary>
	Vector3 GetRodPosition();
	Vector3 GetPlayerPos();
	Vector3 GetFishModelPos();
	Vector3 GetFishModelPosition();
	Vector3 GetFloatModelPos();

	/// <summary>成功・失敗処理呼び出し</summary>
	void Success();
	void Failure();

	/// <summary>魚モデル／UIの向き設定</summary>
	void SetFishModelDownward();
	void SetFishModelUpward();
	void SetFishDownward();
	void SetFishUpward();

	/// <summary>カメラ処理（ステートごとにオーバーライド可）</summary>
	virtual void CameraManagement();

	/// <summary>ウキの浮き動作（カメラ用/モデル用）</summary>
	enum FloatingPattern {
		CameraPattern,
		ModelPattern
	};
	Vector3 Floating(FloatingPattern floatingPattern = ModelPattern);

	/// <summary>外部からウキを渡す</summary>
	void SetFloatGameObject(RodFloatMove* rodfloatmove);

	/// <summary>
/// 現在のステートの情報（魚の位置、ウキの位置、カメラ位置など）を
/// PlayFishing クラスに同期させる。
/// ステートの終了時や遷移時に、進行状況を保持するために使用。
/// </summary>
	void SyncStateToPlayFishing();

	/// <summary>
	/// PlayFishing から初期状態（位置・割合など）を読み取り、
	/// 本ステートに初期値として保存する。
	/// </summary>
	void LoadInitialStateFromPlayFishing();
	
	FishFacing GetFishFacing() const;

protected:


protected:

	float m_floating_t = 0.0f;
	Vector3 m_floating = Vector3::Zero;

	Vector3 m_initFishModelPos = Vector3::Zero;
	Vector3 m_initFloatModelPos = Vector3::Zero;
	Vector3 m_sumFishModelPos = Vector3::Zero;
	Vector3 m_sumFloatModelPos = Vector3::Zero;

	Vector3 m_cameraPos = Vector3::Zero;
	Vector3 m_cameraTarget = Vector3::Zero;
	Vector3 m_initCameraPos = Vector3::Zero;
	Vector3 m_endCameraPos = Vector3::Zero;
	Vector3 m_initCameraTarget = Vector3::Zero;
	Vector3 m_endCameraTarget = Vector3::Zero;

	float m_cameraPos_t = 0;
	float m_cameraTarget_t = 0;
	float m_animation_t = 0;

	float m_fishDistanceRate = 0.0f;
	float m_floatDistanceRate = 0.0f;

	GameCamera* m_gameCamera = nullptr;
	FishModel* m_fishModel = nullptr;
	RodFloatMove* m_rodFloatMove = nullptr;
	PlayFishing* m_playFishing = nullptr;
	TensionGauge* m_tensionGauge = nullptr;
	Player* m_player = nullptr;

	FishData m_fishData;
	Successful_or_Failure m_successful_or_Failure = unfixed;
	FishFacing m_fishFacing = Downward;

	Vector3 m_fishModelPos = Vector3::Zero;
	Vector3 m_floatModelPos = Vector3::Zero;
};
