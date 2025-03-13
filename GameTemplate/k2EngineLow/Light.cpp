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
	m_light.direction.d_direction.x = 1.0f;
	m_light.direction.d_direction.y = -1.0f;
	m_light.direction.d_direction.z = -1.0f;

	//正規化する。
	m_light.direction.d_direction.Normalize();

	//ライトのカラーの設定。
	m_light.direction.d_color.x = 0.5f;
	m_light.direction.d_color.y = 0.5f;
	m_light.direction.d_color.z = 0.5f;

	//視点の位置を設定する。
	m_light.direction.eyePos = g_camera3D->GetPosition();
}

void nsK2EngineLow::Light::Update()
{
}
