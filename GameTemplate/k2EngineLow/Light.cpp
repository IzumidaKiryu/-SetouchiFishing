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
	//ディレクションライトの初期座標の設定。
	m_SceneLight.direction.d_direction.x = 1.0f;
	m_SceneLight.direction.d_direction.y = -1.0f;
	m_SceneLight.direction.d_direction.z = -1.0f;

	//正規化する。
	m_SceneLight.direction.d_direction.Normalize();

	//ライトのカラーの設定。
	m_SceneLight.direction.d_color.x = 0.0f;
	m_SceneLight.direction.d_color.y = 0.0f;
	m_SceneLight.direction.d_color.z = 0.0f;

	//視点の位置を設定する。
	m_SceneLight.eyePos = g_camera3D->GetPosition();

	//ポイントライトの初期座標の設定。
	m_SceneLight.pointLig.ptPosition.x = 0.0f;
	m_SceneLight.pointLig.ptPosition.y = 25.0f;
	m_SceneLight.pointLig.ptPosition.z = -50.0f;

	//ポイントライトの初期カラーを設定。
	m_SceneLight.pointLig.ptColor.x = 1.0f;
	m_SceneLight.pointLig.ptColor.y = 0.0f;
	m_SceneLight.pointLig.ptColor.z = 0.0f;

	//ポイントライトの影響範囲の設定。
	m_SceneLight.pointLig.ptInfuluenceRenge = 100.0f;

	
	//スポットライトノデータを初期化する。
	//座標。
	m_SceneLight.spotLig.s_position.x = 0.0f;
	m_SceneLight.spotLig.s_position.y = 50.0f;
	m_SceneLight.spotLig.s_position.z = 0.0f;

	//ライトのカラーを設定。
	m_SceneLight.spotLig.s_color.x = 10.0f;
	m_SceneLight.spotLig.s_color.y = 10.0f;
	m_SceneLight.spotLig.s_color.z = 10.0f;

	//初期方向は斜め下にする。
	m_SceneLight.spotLig.s_direction.x = 1.0f;
	m_SceneLight.spotLig.s_direction.y = -1.0f;
	m_SceneLight.spotLig.s_direction.z = 1.0f;

	//方向データなので大きさを1にするため正規化する。
	m_SceneLight.spotLig.s_direction.Normalize();

	//射出範囲は300。
	m_SceneLight.spotLig.s_Range = 300.0f;
	//射出角度は25度。
	m_SceneLight.spotLig.s_angle = Math::DegToRad(25.0f);

	m_SceneLight.ambientLight.x = 0.3f;
	m_SceneLight.ambientLight.y = 0.3f;
	m_SceneLight.ambientLight.z = 0.3f;


	
}

void nsK2EngineLow::Light::Update()
{
}
