#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"
#include "Light.h"

nsK2EngineLow::ModelRender::ModelRender()
{
	/*m_light = NewGO<Light>(0, "light");
	m_light->Init();*/
}

nsK2EngineLow::ModelRender::~ModelRender()
{
}

void nsK2EngineLow::ModelRender::Init(const char* filePath,bool m_shadowDrop, AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
{
	// スケルトンを初期化。
	InitSkeleton(filePath);
	// アニメーションを初期化。
	InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
	ModelInitDataFR modelInitData;
	//影を落とすか落とされるかでシェーダーを変える。
	if (m_shadowDrop == true) {
		modelInitData.m_tkmFilePath = filePath;
		modelInitData.m_fxFilePath = "Assets/shader/model.fx";
		modelInitData.m_expandConstantBuffer = &g_renderingEngine->GetLightCB();
		modelInitData.m_expandConstantBufferSize = sizeof(g_renderingEngine->GetLightCB());
		modelInitData.m_modelUpAxis = enModelUpAxis;

		//輪郭線の処理。
		modelInitData.m_expandShaderResoruceView[0] = &g_renderingEngine->GetZPrepassDepthTexture();
		//ZPrepassの初期化。
		InitCommon(filePath, animationClips);

		//シャドウマップに描画するモデルを初期化。
		ModelInitData shadowModelInitData;
		shadowModelInitData.m_tkmFilePath = filePath;
		shadowModelInitData.m_fxFilePath = "Assets/shader/model.fx";
		shadowModelInitData.m_psEntryPointFunc = "PSShadowMain";
		shadowModelInitData.m_modelUpAxis = enModelUpAxis;
		// カラーバッファーのフォーマットに変更が入ったので、こちらも変更する
		shadowModelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

		//アニメーション有無でエントリーポイントを変える
		if (animationClips != nullptr) {
			shadowModelInitData.m_skeleton = &m_skeleton;
			shadowModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}
		else {
			shadowModelInitData.m_vsEntryPointFunc = "VSMain";
		}

		m_shadowModel.Init(shadowModelInitData);
	}
	else {
		// 影を受ける背景モデルを初期化
		modelInitData.m_tkmFilePath = filePath;
		// シャドウレシーバー(影が落とされるモデル)用のシェーダーを指定する
		modelInitData.m_fxFilePath = "Assets/shader/shadowReciever.fx";
		// シャドウマップを拡張SRVに設定する
		modelInitData.m_expandShaderResoruceView[1] = &g_renderingEngine->GetShadowTarget().GetRenderTargetTexture();
		// ライトビュープロジェクション行列を拡張定数バッファーに設定する
		modelInitData.m_expandConstantBuffer = &g_renderingEngine->GetLightCB();
		modelInitData.m_expandConstantBufferSize = sizeof(g_renderingEngine->GetLightCB());
		modelInitData.m_modelUpAxis = enModelUpAxis;
	}

	//アニメーション有無でエントリーポイントを変える
	if (animationClips != nullptr) {
		modelInitData.m_skeleton = &m_skeleton;
		modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
	}
	else {
		modelInitData.m_vsEntryPointFunc = "VSMain";
	}

	m_model.Init(modelInitData);
	
	//InitModel(filePath, enModelUpAxis);

}

void nsK2EngineLow::ModelRender::InitCommon(const char* tkmFilePath, AnimationClip* animationClips)
{
	// ZPrepass描画用のモデルを初期化
	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = tkmFilePath;
	modelInitData.m_fxFilePath = "Assets/shader/ZPrepass.fx";
	modelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32_FLOAT;

	//アニメーション有無でエントリーポイントを変える
	if (animationClips != nullptr) {
		modelInitData.m_skeleton = &m_skeleton;
		modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
	}
	else {
		modelInitData.m_vsEntryPointFunc = "VSMain";
	}

	m_zprepassModel.Init(modelInitData);
}

void nsK2EngineLow::ModelRender::InitSkyCubeModel(ModelInitData& initData)
{
	m_model.Init(initData);
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
	if (m_skeleton.IsInited())
	{
		m_skeleton.Update(m_model.GetWorldMatrix());
	}

	//モデルの更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//影のモデルに移動回転拡大を渡す
	m_shadowModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//輪郭線に移動回転拡大を渡す
	m_zprepassModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
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
	

	//////コントローラーでスポットライトライトを動かす。（確認用の実装のため、コメントアウト）。
	//m_light->m_SceneLight.spotLig.m_position.x -= g_pad[0]->GetLStickXF();
	//if (g_pad[0]->IsPress(enButtonB)) {
	//	m_light->m_SceneLight.spotLig.m_position.y += g_pad[0]->GetLStickYF();
	//}
	//else {
	//	m_light->m_SceneLight.spotLig.m_position.z -= g_pad[0]->GetLStickYF();
	//}


	//コントローラー右スティックでスポットライトを回転させる。
	////Y軸周りのクオータニオンを計算する。
	//Quaternion qRotY;
	//qRotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.01f);

	////計算したクオータニオンでライトのほうこうをまわす。
	//qRotY.Apply(m_light->m_SceneLight.spotLig.m_direction);

	////X軸周りのクオータニオンを計算する。
	//Vector3 rotAxis;
	//rotAxis.Cross(g_vec3AxisY, m_light->m_SceneLight.spotLig.m_direction);
	//Quaternion qRotX;
	//qRotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.01f);

	////計算したクオータニオンでライトの方向を回す。
	//qRotX.Apply(m_light->m_SceneLight.spotLig.m_direction);

	
}

void nsK2EngineLow::ModelRender::Draw(RenderContext& rc)
{
	g_renderingEngine->AddModelRenderObject(this);
	if (m_zprepassModel.IsInited())
	{
		g_renderingEngine->Add3DModelToZPrepass(m_zprepassModel);
	}

}
void nsK2EngineLow::ModelRender::IniTranslucent(
	const char* filePath,
	AnimationClip* animationClips,
	int numAnimationClips,
	EnModelUpAxis enModelUpAxis) {

}

float nsK2EngineLow::ModelRender::GetAnimationRatio()
{
	return m_animation.GetAnimationRatio();
}


