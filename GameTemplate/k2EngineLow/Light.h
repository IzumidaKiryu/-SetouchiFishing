#pragma once
namespace nsK2EngineLow {


	//���C�g�N���X�B�����̓V�F�[�_�[���Őݒ肵�Ă�(�e�����l0.3f)�B
	class Light :public IGameObject
	{
	public:
		struct DirectionLight {
			Vector3 d_direction;//���C�g�̕����B3�v�f�̃x�N�g���ŕ\���B
			float pad0;
			Vector3 d_color;//���C�g�̃J���[�B����3���F�ŕ\���B
			float pad1;
		};

		struct PointLight {
			Vector3 ptPosition;//���C�g�̈ʒu�B3�v�f�̃x�N�g���ŕ\���B
			float pad2;//�p�e�B���O�B
			Vector3 ptColor;//���C�g�̃J���[�B����3���F�ŕ\���B
			float ptInfuluenceRenge;//�e���͈́B�P�ʂ̓��[�g���B
		
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
			PointLight pointLig;
			Vector3 eyePos;
			float pad0;
			Vector3 ambientLight;

		};

		Light();
		~Light();

		void Init();
		void Update();

		SceneLight& GetLight()
		{
			return m_SceneLight;
		}
		SceneLight m_SceneLight;
	};
}



