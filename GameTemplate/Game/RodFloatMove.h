#pragma once

enum RodFloatState {
	cast,//キャスト中
	buoyancy,
	floating,//浮かんでいる
};

enum BuoyancyState {
	Down,
	Up,
};

class GameCamera;
class RodFloatMove :public IGameObject
{
public:
	RodFloatMove();
	~RodFloatMove();
	void Update();
	void ModelUpdate();
	void Buoyancy();
	void Cast();
	void Float();
	void RodFloatStateManagement();

	void Render(RenderContext& rc);


	Vector3 first_velocity_vector{ 5.0f,0.5f,0.0f };
	float t = 0;
	Vector3 g{ 0.0f,-30.0f,0.0f };
	Vector3 InitPos{ 100.0f,500.0f,10.0f };
	Vector3 m_rodFloatPosition= InitPos;
	ModelRender m_rodFloatModel;
	//void SetRodFloatPositon();
	GameCamera* m_gameCamera;
	RodFloatState m_floatState;
	float m_float_t;
	float water_surface_position_y;
	Vector3 m_floating;
	float m_cos=0.0f;
	Vector3 landing_position;

	float float_diameter=50.0f;
	float m_water_contains_rate;//ウキが水につかっている割合（1なら100パーセント）
	float float_volume;//ウキの体積。

	BuoyancyState m_buoyancyState;

};

