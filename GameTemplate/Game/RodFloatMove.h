#pragma once

//enum RodFloatState {
//	initState,//初期ステート
//	cast,//キャスト中。
//	buoyancy,
//	floating,//浮かんでいる。
//	fightFish,
//};

enum BuoyancyState {
	Down,
	Up,
};

class GameCamera;
class SceneFightFish;
class PlayFishing;
class TensionGauge;
class RodFloatMove :public IGameObject
{
public:
	RodFloatMove();
	~RodFloatMove();
	bool Start()override;
	bool Init();
	void Update();
	void ModelUpdate();
	/*void Buoyancy();
	void Cast();*/
	void Float();
	/*void RodFloatStateManagement();
	void SetCastState();
	void SetFightFishState();
	void SetScalar_multiply_in_first_velocity_vector(float scalar_multiply_in_first_velocity_vector);*/
	void SetPosition();
	void SetPosition(Vector3 position);
	float ChangePosition_Z(float currentFloatDistanceRate);
	float GetCurrentFloatDistanceRate(float position_z);
	void SetRotation(Quaternion rot);

	void SetSumPosition(Vector3 positon);//ポジションを足し算する。
	/*void FightFish();*/
	void Render(RenderContext& rc);
	//bool IsCastEnd();//キャストが終わっているか。
	Vector3 GetPosition();
	void DeleteThisClass();


	float m_scalar_multiply_in_first_velocity_vector;//初速度に掛けるスカラー
	float first_velocity_vector_z=2;//初速ベクトルｚの値（ｙとｚの比率）。
	Vector3 first_velocity_vector{ 0.0f,1.0f,first_velocity_vector_z };//初速ベクトル（ｙは必ず1にしておく）。
	float m_z_axis_value_drop_float;//ウキを落とすｚ軸の値。

	float t = 0;
	Vector3 g{ 0.0f,-30.0f,0.0f };
	Vector3 InitPos{ 0.0f,500.0f,10.0f };
	Vector3 m_position= InitPos;
	Vector3 m_sumPosition=Vector3::Zero;
	ModelRender m_rodFloatModel;
	//void SetRodFloatPositon();
	GameCamera* m_gameCamera = nullptr;
	//RodFloatState m_floatState;
	float m_float_t=0.0f;
	float water_surface_position_y=0.0f;
	Vector3 m_floating=Vector3::Zero;
	float m_cos=0.0f;
	Vector3 landing_position = Vector3::Zero;
	float m_current_range_and_max_range_rate=1;//今の距離と限界の距離の割合。

	
	bool m_cast_end=false;//キャストが終わっているか。

	float float_diameter=50.0f;
	float m_water_contains_rate=0.0f;//ウキが水につかっている割合（1なら100パーセント）
	float float_volume=0.0f;//ウキの体積。
	Vector3 m_range_with_fish={0.0f,0.0f,0.0f};
	float m_limit_range_with_ship=2010.1f;//船との限界距離。


	BuoyancyState m_buoyancyState;
	SceneFightFish* m_sceneFightFish = nullptr;
	PlayFishing* m_playFishing = nullptr;
	TensionGauge* m_tensionGauge = nullptr;

};

