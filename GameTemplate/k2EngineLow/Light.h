#pragma once
namespace nsK2EngineLow {


	//���C�g�N���X�B�����̓V�F�[�_�[���Őݒ肵�Ă�(�e�����l0.3f)�B
	class Light :public IGameObject
	{
	public:
		struct DirectionLight {
			Vector3 m_direction;//���C�g�̕����B3�v�f�̃x�N�g���ŕ\���B
			float pad0;
			Vector3 m_color;//���C�g�̃J���[�B����3���F�ŕ\���B
			float pad1;
		};

		struct PointLight {
			Vector3 m_position;//���C�g�̈ʒu�B3�v�f�̃x�N�g���ŕ\���B
			float pad2;//�p�e�B���O�B
			Vector3 m_color;//���C�g�̃J���[�B����3���F�ŕ\���B
			float m_renge;//�e���͈́B�P�ʂ̓��[�g���B
		
		};

		struct SpotLight {
			Vector3 m_position;//���C�g�̈ʒu�B3�v�f�̃x�N�g���ŕ\���B
			float pad3;
			Vector3 m_color;//���C�g�̃J���[�B����3���F�ŕ\���B
			float m_range;//�e���͈́B�P�ʂ̓��[�g���B
			Vector3 m_direction;//���˕����B3�v�f�̃x�N�g���ŕ\���B
			float m_angle;//���ˊp�x�B
		};

		struct HemisphereLight {
			Vector3 m_groundColor;
			float pad6;
			Vector3 m_skyColor;
			float pad7;
			Vector3 m_groundNormal;
			float pad8;
		};

		struct SceneLight
		{
			DirectionLight directionLig;
			PointLight pointLig;
			SpotLight spotLig;
			Vector3 eyePos;
			float pad0;
			Vector3 ambientLight;
			float pad5;
			HemisphereLight m_hemiLig;
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



