#pragma once
namespace nsK2EngineLow {



	class Light :public IGameObject
	{
	public:
		struct DirectionLight {
			Vector3 d_direction;//���C�g�̕����B3�v�f�̃x�N�g���ŕ\���B
			float pad;
			Vector3 d_color;//���C�g�̃J���[�B����3���F�ŕ\���B
		};

		struct PointLight {
			float p_position[3];//���C�g�̈ʒu�B3�v�f�̃x�N�g���ŕ\���B
			float p_color[3];//���C�g�̃J���[�B����3���F�ŕ\���B
			float p_infuluenceRenge;//�e���͈́B�P�ʂ̓��[�g���B
		};

		struct SpotLight {
			float s_position[3];//���C�g�̈ʒu�B3�v�f�̃x�N�g���ŕ\���B
			float s_color[3];//���C�g�̃J���[�B����3���F�ŕ\���B
			float s_direction[3];//���˕����B3�v�f�̃x�N�g���ŕ\���B
			float s_angle;//���ˊp�x�B
			float s_infuluenceRenge;//�e���͈́B�P�ʂ̓��[�g���B
		};

		struct SceneLight
		{
			DirectionLight direction;
		};

		Light();
		~Light();

		void Init();
		void Update();

		SceneLight& GetLight()
		{
			return m_light;
		}
		SceneLight m_light;
	};
}

