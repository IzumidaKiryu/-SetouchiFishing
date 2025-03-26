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
	// �X�P���g�����������B
	InitSkeleton(filePath);
	// �A�j���[�V�������������B
	InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
	InitModel(filePath, enModelUpAxis);

}

void nsK2EngineLow::ModelRender::InitSkeleton(const char* filePath)
{

	//�X�P���g���̃f�[�^��ǂݍ��݁B
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
	//tkm�t�@�C���̃t�@�C���p�X���w�肷��B
	initData.m_tkmFilePath = filePath;
	//�V�F�[�_�[�t�@�C���̃t�@�C���p�X���w�肷��B
	initData.m_fxFilePath = "Assets/shader/model.fx";

	initData.m_expandConstantBuffer = &m_light->GetLight();
	initData.m_expandConstantBufferSize = sizeof(m_light->GetLight());

	//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
	initData.m_vsEntryPointFunc = "VSMain";

	if (m_animationClips != nullptr) {
		//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";
		//�X�P���g�����w�肷��B
		initData.m_skeleton = &m_skeleton;
	}

	//���f���̏�������w�肷��B
	initData.m_modelUpAxis = enModelUpAxis;

	//�쐬�����������f�[�^�����ƂɃ��f��������������A
	m_model.Init(initData);
}
void nsK2EngineLow::ModelRender::Update()
{
	//�X�P���g�����X�V�B
	m_skeleton.Update(m_model.GetWorldMatrix());

	//���f���̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//�A�j���[�V������i�߂�B
	m_animation.Progress(g_gameTime->GetFrameDeltaTime());


	//////�R���g���[���[�Ń|�C���g���C�g�𓮂����B�i�m�F�p�̎����̂��߁A�R�����g�A�E�g�j�B
	//m_light->m_SceneLight.pointLig.ptPosition.x -= g_pad[0]->GetLStickXF();
	//if (g_pad[0]->IsPress(enButtonB)) {
	//	m_light->m_SceneLight.pointLig.ptPosition.y += g_pad[0]->GetLStickYF();
	//}
	//else {
	//	m_light->m_SceneLight.pointLig.ptPosition.z -= g_pad[0]->GetLStickYF();
	//}
	

	////�R���g���[���[�ŃX�|�b�g���C�g���C�g�𓮂����B�i�m�F�p�̎����̂��߁A�R�����g�A�E�g�j�B
	m_light->m_SceneLight.spotLig.s_position.x -= g_pad[0]->GetLStickXF();
	if (g_pad[0]->IsPress(enButtonB)) {
		m_light->m_SceneLight.spotLig.s_position.y += g_pad[0]->GetLStickYF();
	}
	else {
		m_light->m_SceneLight.spotLig.s_position.z -= g_pad[0]->GetLStickYF();
	}


	//�R���g���[���[�E�X�e�B�b�N�ŃX�|�b�g���C�g����]������B
	//Y������̃N�I�[�^�j�I�����v�Z����B
	Quaternion qRotY;
	qRotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.01f);

	//�v�Z�����N�I�[�^�j�I���Ń��C�g�̂ق��������܂킷�B
	qRotY.Apply(m_light->m_SceneLight.spotLig.s_direction);

	//X������̃N�I�[�^�j�I�����v�Z����B
	Vector3 rotAxis;
	rotAxis.Cross(g_vec3AxisY, m_light->m_SceneLight.spotLig.s_direction);
	Quaternion qRotX;
	qRotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.01f);

	//�v�Z�����N�I�[�^�j�I���Ń��C�g�̕������񂷁B
	qRotX.Apply(m_light->m_SceneLight.spotLig.s_direction);

	
}

void nsK2EngineLow::ModelRender::Draw(RenderContext& rc)
{
	m_model.Draw(rc);
	//m_zprepassModel.Draw(rc);
	//if (m_isEnableInstancingDraw) {
	//	// �C���X�^���V���O�`��̓r���[�t���X�^���J�����O�͍s��Ȃ��B
	//	g_renderingEngine->AddRenderObject(this);
	//	m_worldMatrixArraySB.Update(m_worldMatrixArray.get());
	//	m_numInstance = 0;
	//}
	//else {
	//	// �ʏ�`��
	//	if (m_geometryDatas[0].IsInViewFrustum()) {
	//		// �r���[�t���X�^���Ɋ܂܂�Ă���B
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

