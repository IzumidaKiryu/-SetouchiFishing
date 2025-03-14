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
	//SpotLight  spotLig;
	m_SceneLight.direction.d_direction.x = 1.0f;
	m_SceneLight.direction.d_direction.y = -1.0f;
	m_SceneLight.direction.d_direction.z = -1.0f;

	//���K������B
	m_SceneLight.direction.d_direction.Normalize();

	//���C�g�̃J���[�̐ݒ�B
	m_SceneLight.direction.d_color.x = 0.5f;
	m_SceneLight.direction.d_color.y = 0.5f;
	m_SceneLight.direction.d_color.z = 0.5f;

	//���_�̈ʒu��ݒ肷��B
	m_SceneLight.direction.eyePos = g_camera3D->GetPosition();

	//�|�C���g���C�g�̏������W�̐ݒ�B
	m_SceneLight.pointLig.ptPosition.x = 0.0f;
	m_SceneLight.pointLig.ptPosition.y = 50.0f;
	m_SceneLight.pointLig.ptPosition.z = 50.0f;

	//�|�C���g���C�g�̏����J���[��ݒ�B
	m_SceneLight.pointLig.ptColor.x = 15.0f;
	m_SceneLight.pointLig.ptColor.y = 0.0f;
	m_SceneLight.pointLig.ptColor.z = 0.0f;

	//�|�C���g���C�g�̉e���͈͂̐ݒ�B
	m_SceneLight.pointLig.ptInfuluenceRenge = 100.0f;

}

void nsK2EngineLow::Light::Update()
{
}
