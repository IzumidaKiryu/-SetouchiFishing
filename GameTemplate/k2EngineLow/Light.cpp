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
	m_SceneLight.directionLig.m_direction.x = 0.0f;
	m_SceneLight.directionLig.m_direction.y = 0.0f;
	m_SceneLight.directionLig.m_direction.z = -1.0f;

	//正規化する。
	m_SceneLight.directionLig.m_direction.Normalize();

	//ライトのカラーの設定。
	m_SceneLight.directionLig.m_color.x = 0.5f;
	m_SceneLight.directionLig.m_color.y = 0.5f;
	m_SceneLight.directionLig.m_color.z = 0.5f;

	//視点の位置を設定する。
	m_SceneLight.eyePos = g_camera3D->GetPosition();

	//ポイントライトの初期座標の設定。
	m_SceneLight.pointLig.m_position.x = 0.0f;
	m_SceneLight.pointLig.m_position.y = 25.0f;
	m_SceneLight.pointLig.m_position.z = -50.0f;

	//ポイントライトの初期カラーを設定。
	m_SceneLight.pointLig.m_color.x = 1.0f;
	m_SceneLight.pointLig.m_color.y = 0.0f;
	m_SceneLight.pointLig.m_color.z = 0.0f;

	//ポイントライトの影響範囲の設定。
	m_SceneLight.pointLig.m_renge = 100.0f;

	
	//スポットライトノデータを初期化する。
	//座標。
	m_SceneLight.spotLig.m_position.x = 0.0f;
	m_SceneLight.spotLig.m_position.y = 50.0f;
	m_SceneLight.spotLig.m_position.z = 0.0f;

	//ライトのカラーを設定。
	m_SceneLight.spotLig.m_color.x = 0.0f;
	m_SceneLight.spotLig.m_color.y = 0.0f;
	m_SceneLight.spotLig.m_color.z = 50.0f;

	//初期方向は斜め下にする。
	m_SceneLight.spotLig.m_direction.x = 1.0f;
	m_SceneLight.spotLig.m_direction.y = -1.0f;
	m_SceneLight.spotLig.m_direction.z = 1.0f;

	//方向データなので大きさを1にするため正規化する。
	m_SceneLight.spotLig.m_direction.Normalize();

	//射出範囲は300。
	m_SceneLight.spotLig.m_range = 300.0f;
	//射出角度は25度。
	m_SceneLight.spotLig.m_angle = Math::DegToRad(25.0f);

	m_SceneLight.ambientLight.x = 0.1f;
	m_SceneLight.ambientLight.y = 0.1f;
	m_SceneLight.ambientLight.z = 0.1f;


	//地面色。、天球色、地面の法線を追加する。
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
