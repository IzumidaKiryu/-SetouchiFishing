#include "k2EngineLowPreCompile.h"
#include "Light.h"

nsK2EngineLow::Light::Light()
{
	
}

nsK2EngineLow::Light::~Light()
{
}

void nsK2EngineLow::Light::Init()
{
	//�f�B���N�V�������C�g�̏������W�̐ݒ�B
	m_SceneLight.direction.d_direction.x = 1.0f;
	m_SceneLight.direction.d_direction.y = -1.0f;
	m_SceneLight.direction.d_direction.z = -1.0f;

	//���K������B
	m_SceneLight.direction.d_direction.Normalize();

	//���C�g�̃J���[�̐ݒ�B
	m_SceneLight.direction.d_color.x = 0.0f;
	m_SceneLight.direction.d_color.y = 0.0f;
	m_SceneLight.direction.d_color.z = 0.0f;

	//���_�̈ʒu��ݒ肷��B
	m_SceneLight.eyePos = g_camera3D->GetPosition();

	//�|�C���g���C�g�̏������W�̐ݒ�B
	m_SceneLight.pointLig.ptPosition.x = 0.0f;
	m_SceneLight.pointLig.ptPosition.y = 25.0f;
	m_SceneLight.pointLig.ptPosition.z = -50.0f;

	//�|�C���g���C�g�̏����J���[��ݒ�B
	m_SceneLight.pointLig.ptColor.x = 1.0f;
	m_SceneLight.pointLig.ptColor.y = 0.0f;
	m_SceneLight.pointLig.ptColor.z = 0.0f;

	//�|�C���g���C�g�̉e���͈͂̐ݒ�B
	m_SceneLight.pointLig.ptInfuluenceRenge = 100.0f;

	
	//�X�|�b�g���C�g�m�f�[�^������������B
	//���W�B
	m_SceneLight.spotLig.s_position.x = 0.0f;
	m_SceneLight.spotLig.s_position.y = 50.0f;
	m_SceneLight.spotLig.s_position.z = 0.0f;

	//���C�g�̃J���[��ݒ�B
	m_SceneLight.spotLig.s_color.x = 10.0f;
	m_SceneLight.spotLig.s_color.y = 10.0f;
	m_SceneLight.spotLig.s_color.z = 10.0f;

	//���������͎΂߉��ɂ���B
	m_SceneLight.spotLig.s_direction.x = 1.0f;
	m_SceneLight.spotLig.s_direction.y = -1.0f;
	m_SceneLight.spotLig.s_direction.z = 1.0f;

	//�����f�[�^�Ȃ̂ő傫����1�ɂ��邽�ߐ��K������B
	m_SceneLight.spotLig.s_direction.Normalize();

	//�ˏo�͈͂�300�B
	m_SceneLight.spotLig.s_Range = 300.0f;
	//�ˏo�p�x��25�x�B
	m_SceneLight.spotLig.s_angle = Math::DegToRad(25.0f);

	m_SceneLight.ambientLight.x = 0.3f;
	m_SceneLight.ambientLight.y = 0.3f;
	m_SceneLight.ambientLight.z = 0.3f;


	
}

void nsK2EngineLow::Light::Update()
{
}
