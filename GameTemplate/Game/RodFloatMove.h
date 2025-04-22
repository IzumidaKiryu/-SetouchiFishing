#pragma once

//enum RodFloatState {
//	initState,//�����X�e�[�g
//	cast,//�L���X�g���B
//	buoyancy,
//	floating,//������ł���B
//	fightFish,
//};

enum BuoyancyState {
	Down,
	Up,
};

class GameCamera;
class SceneFightFish;
class PlayFishing;
class RodFloatMove :public IGameObject
{
public:
	RodFloatMove();
	~RodFloatMove();
	void Update();
	void ModelUpdate();
	/*void Buoyancy();
	void Cast();*/
	void Float();
	/*void RodFloatStateManagement();
	void SetCastState();
	void SetFightFishState();
	void SetScalar_multiply_in_first_velocity_vector(float scalar_multiply_in_first_velocity_vector);*/
	void SetPosition(Vector3 position);

	void SetSumPosition(Vector3 positon);//�|�W�V�����𑫂��Z����B
	/*void FightFish();*/
	void SetCurrent_range_and_max_range_rate(float current_range_and_max_range_rate);

	void Render(RenderContext& rc);
	//bool IsCastEnd();//�L���X�g���I����Ă��邩�B


	float m_scalar_multiply_in_first_velocity_vector;//�����x�Ɋ|����X�J���[
	float first_velocity_vector_z=2;//�����x�N�g�����̒l�i���Ƃ��̔䗦�j�B
	Vector3 first_velocity_vector{ 0.0f,1.0f,first_velocity_vector_z };//�����x�N�g���i���͕K��1�ɂ��Ă����j�B
	float m_z_axis_value_drop_float;//�E�L�𗎂Ƃ������̒l�B

	float t = 0;
	Vector3 g{ 0.0f,-30.0f,0.0f };
	Vector3 InitPos{ 0.0f,500.0f,10.0f };
	Vector3 m_rodFloatPosition= InitPos;
	ModelRender m_rodFloatModel;
	//void SetRodFloatPositon();
	GameCamera* m_gameCamera;
	//RodFloatState m_floatState;
	float m_float_t;
	float water_surface_position_y;
	Vector3 m_floating;
	float m_cos=0.0f;
	Vector3 landing_position;
	float m_current_range_and_max_range_rate=1;//���̋����ƌ��E�̋����̊����B


	bool m_cast_end=false;//�L���X�g���I����Ă��邩�B

	float float_diameter=50.0f;
	float m_water_contains_rate;//�E�L�����ɂ����Ă��銄���i1�Ȃ�100�p�[�Z���g�j
	float float_volume;//�E�L�̑̐ρB
	Vector3 m_range_with_fish={0.0f,0.0f,0.0f};
	float m_limit_range_with_ship=2010.1f;//�D�Ƃ̌��E�����B

	BuoyancyState m_buoyancyState;
	SceneFightFish* m_sceneFightFish;
	PlayFishing* m_playFishing;

};

