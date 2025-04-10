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
			Vector3 s_position;//���C�g�̈ʒu�B3�v�f�̃x�N�g���ŕ\���B
			float pad3;
			Vector3 s_color;//���C�g�̃J���[�B����3���F�ŕ\���B
			float s_Range;//�e���͈́B�P�ʂ̓��[�g���B
			Vector3 s_direction;//���˕����B3�v�f�̃x�N�g���ŕ\���B
			float s_angle;//���ˊp�x�B
			
		};

		struct SceneLight
		{
			DirectionLight direction;
			PointLight pointLig;
			SpotLight spotLig;
			Vector3 eyePos;
			float pad4;
			Vector3 ambientLight;
			float pad5;
			Vector3 groundColor;
			float pad6;
			Vector3 skyColor;
			float pad7;
			Vector3 groundNormal;
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



