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
	m_SceneLight.directionLig.m_direction.x = 0.0f;
	m_SceneLight.directionLig.m_direction.y = 0.0f;
	m_SceneLight.directionLig.m_direction.z = -1.0f;

	//���K������B
	m_SceneLight.directionLig.m_direction.Normalize();

	//���C�g�̃J���[�̐ݒ�B
	m_SceneLight.directionLig.m_color.x = 0.5f;
	m_SceneLight.directionLig.m_color.y = 0.5f;
	m_SceneLight.directionLig.m_color.z = 0.5f;

	//���_�̈ʒu��ݒ肷��B
	m_SceneLight.eyePos = g_camera3D->GetPosition();

	//�|�C���g���C�g�̏������W�̐ݒ�B
	m_SceneLight.pointLig.m_position.x = 0.0f;
	m_SceneLight.pointLig.m_position.y = 25.0f;
	m_SceneLight.pointLig.m_position.z = -50.0f;

	//�|�C���g���C�g�̏����J���[��ݒ�B
	m_SceneLight.pointLig.m_color.x = 1.0f;
	m_SceneLight.pointLig.m_color.y = 0.0f;
	m_SceneLight.pointLig.m_color.z = 0.0f;

	//�|�C���g���C�g�̉e���͈͂̐ݒ�B
	m_SceneLight.pointLig.m_renge = 100.0f;

	
	//�X�|�b�g���C�g�m�f�[�^������������B
	//���W�B
	m_SceneLight.spotLig.m_position.x = 0.0f;
	m_SceneLight.spotLig.m_position.y = 50.0f;
	m_SceneLight.spotLig.m_position.z = 0.0f;

	//���C�g�̃J���[��ݒ�B
	m_SceneLight.spotLig.m_color.x = 0.0f;
	m_SceneLight.spotLig.m_color.y = 0.0f;
	m_SceneLight.spotLig.m_color.z = 50.0f;

	//���������͎΂߉��ɂ���B
	m_SceneLight.spotLig.m_direction.x = 1.0f;
	m_SceneLight.spotLig.m_direction.y = -1.0f;
	m_SceneLight.spotLig.m_direction.z = 1.0f;

	//�����f�[�^�Ȃ̂ő傫����1�ɂ��邽�ߐ��K������B
	m_SceneLight.spotLig.m_direction.Normalize();

	//�ˏo�͈͂�300�B
	m_SceneLight.spotLig.m_range = 300.0f;
	//�ˏo�p�x��25�x�B
	m_SceneLight.spotLig.m_angle = Math::DegToRad(25.0f);

	m_SceneLight.ambientLight.x = 0.1f;
	m_SceneLight.ambientLight.y = 0.1f;
	m_SceneLight.ambientLight.z = 0.1f;


	//�n�ʐF�B�A�V���F�A�n�ʂ̖@����ǉ�����B
	m_SceneLight.m_hemiLig.m_groundColor.x = 0.5f;
	m_SceneLight.m_hemiLig.m_groundColor.y = 0.4f;
	m_SceneLight.m_hemiLig.m_groundColor.z = 0.3f;

	m_SceneLight.m_hemiLig.m_skyColor.x = 0.15f;
	m_SceneLight.m_hemiLig.m_skyColor.y = 0.5f;
	m_SceneLight.m_hemiLig.m_skyColor.z = 0.5f;

	m_SceneLight.m_hemiLig.m_groundNormal.x = 0.0f;
	m_SceneLight.m_hemiLig.m_groundNormal.y = 1.0f;
	m_SceneLight.m_hemiLig.m_groundNormal.z = 0.0f;
}

void nsK2EngineLow::Light::Update()
{
}
