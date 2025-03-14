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

	//正規化する。
	m_SceneLight.direction.d_direction.Normalize();

	//ライトのカラーの設定。
	m_SceneLight.direction.d_color.x = 0.5f;
	m_SceneLight.direction.d_color.y = 0.5f;
	m_SceneLight.direction.d_color.z = 0.5f;

	//視点の位置を設定する。
	m_SceneLight.direction.eyePos = g_camera3D->GetPosition();

	//ポイントライトの初期座標の設定。
	m_SceneLight.pointLig.ptPosition.x = 0.0f;
	m_SceneLight.pointLig.ptPosition.y = 50.0f;
	m_SceneLight.pointLig.ptPosition.z = 50.0f;

	//ポイントライトの初期カラーを設定。
	m_SceneLight.pointLig.ptColor.x = 15.0f;
	m_SceneLight.pointLig.ptColor.y = 0.0f;
	m_SceneLight.pointLig.ptColor.z = 0.0f;

	//ポイントライトの影響範囲の設定。
	m_SceneLight.pointLig.ptInfuluenceRenge = 100.0f;

}

void nsK2EngineLow::Light::Update()
{
}
