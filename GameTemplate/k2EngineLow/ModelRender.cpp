#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"
#include "Light.h"

nsK2EngineLow::ModelRender::ModelRender()
{
	m_light = NewGO<Light>(0, "light");
	m_light->Init();
}

nsK2EngineLow::ModelRender::~ModelRender()
{
}

void nsK2EngineLow::ModelRender::Init(const char* filePath, AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
{
	// スケルトンを初期化。
	InitSkeleton(filePath);
	// アニメーションを初期化。
	InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
	InitModel(filePath, enModelUpAxis);

}

void nsK2EngineLow::ModelRender::InitSkeleton(const char* filePath)
{

	//スケルトンのデータを読み込み。
	std::string skeletonFilePath = filePath;
	int pos = (int)skeletonFilePath.find(".tkm");
	skeletonFilePath.replace(pos, 4, ".tks");
	m_skeleton.Init(skeletonFilePath.c_str());
}

void nsK2EngineLow::ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
{
	m_animationClips = animationClips;
	m_numAnimationClips = numAnimationClips;
	if (m_animationClips != nullptr) {
		m_animation.Init(m_skeleton,
			m_animationClips,
			numAnimationClips);
	}
}

void nsK2EngineLow::ModelRender::InitModel(const char* filePath, EnModelUpAxis enModelUpAxis)
{
	ModelInitData initData;
	//tkmファイルのファイルパスを指定する。
	initData.m_tkmFilePath = filePath;
	//シェーダーファイルのファイルパスを指定する。
	initData.m_fxFilePath = "Assets/shader/model.fx";

	initData.m_expandConstantBuffer = &m_light->GetLight();
	initData.m_expandConstantBufferSize = sizeof(m_light->GetLight());

	//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
	initData.m_vsEntryPointFunc = "VSMain";

	if (m_animationClips != nullptr) {
		//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";
		//スケルトンを指定する。
		initData.m_skeleton = &m_skeleton;
	}

	//モデルの上方向を指定する。
	initData.m_modelUpAxis = enModelUpAxis;

	//作成した初期化データをもとにモデルを初期化する、
	m_model.Init(initData);
}
void nsK2EngineLow::ModelRender::Update()
{
	//スケルトンを更新。
	m_skeleton.Update(m_model.GetWorldMatrix());

	//モデルの更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//アニメーションを進める。
	m_animation.Progress(g_gameTime->GetFrameDeltaTime());


	//////コントローラーでポイントライトを動かす。（確認用の実装のため、コメントアウト）。
	//m_light->m_SceneLight.pointLig.ptPosition.x -= g_pad[0]->GetLStickXF();
	//if (g_pad[0]->IsPress(enButtonB)) {
	//	m_light->m_SceneLight.pointLig.ptPosition.y += g_pad[0]->GetLStickYF();
	//}
	//else {
	//	m_light->m_SceneLight.pointLig.ptPosition.z -= g_pad[0]->GetLStickYF();
	//}
	

	////コントローラーでスポットライトライトを動かす。（確認用の実装のため、コメントアウト）。
	m_light->m_SceneLight.spotLig.s_position.x -= g_pad[0]->GetLStickXF();
	if (g_pad[0]->IsPress(enButtonB)) {
		m_light->m_SceneLight.spotLig.s_position.y += g_pad[0]->GetLStickYF();
	}
	else {
		m_light->m_SceneLight.spotLig.s_position.z -= g_pad[0]->GetLStickYF();
	}


	//コントローラー右スティックでスポットライトを回転させる。
	//Y軸周りのクオータニオンを計算する。
	Quaternion qRotY;
	qRotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.01f);

	//計算したクオータニオンでライトのほうこうをまわす。
	qRotY.Apply(m_light->m_SceneLight.spotLig.s_direction);

	//X軸周りのクオータニオンを計算する。
	Vector3 rotAxis;
	rotAxis.Cross(g_vec3AxisY, m_light->m_SceneLight.spotLig.s_direction);
	Quaternion qRotX;
	qRotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.01f);

	//計算したクオータニオンでライトの方向を回す。
	qRotX.Apply(m_light->m_SceneLight.spotLig.s_direction);

	
}

void nsK2EngineLow::ModelRender::Draw(RenderContext& rc)
{
	m_model.Draw(rc);
	//m_zprepassModel.Draw(rc);
	//if (m_isEnableInstancingDraw) {
	//	// インスタンシング描画はビューフラスタムカリングは行わない。
	//	g_renderingEngine->AddRenderObject(this);
	//	m_worldMatrixArraySB.Update(m_worldMatrixArray.get());
	//	m_numInstance = 0;
	//}
	//else {
	//	// 通常描画
	//	if (m_geometryDatas[0].IsInViewFrustum()) {
	//		// ビューフラスタムに含まれている。
	//		g_renderingEngine->AddRenderObject(this);
	//	}
	//}
}
void nsK2EngineLow::ModelRender::IniTranslucent(
	const char* filePath,
	AnimationClip* animationClips,
	int numAnimationClips,
	EnModelUpAxis enModelUpAxis) {

}

