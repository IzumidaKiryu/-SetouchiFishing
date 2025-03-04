#pragma once

namespace nsK2EngineLow {

	class ModelRender
	{
	public:
		ModelRender();
		~ModelRender();
		
		void Init(const char* filePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationCrips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ);

		void InitModel(const char* filePath, EnModelUpAxis enModelUpAxis);

		void Update();

		void Draw(RenderContext& rc);
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}

		/// <summary>
		/// �A�j���[�V�����̍Đ����H
		/// </summary>
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}

		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		/// <param name="x">x���W</param>
		/// <param name="y">y���W</param>
		/// <param name="z">z���W</param>
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x, y, z });
		}
		/// <summary>
		/// ��]��ݒ�B
		/// </summary>
		/// <remark>
		/// �C���X�^���V���O�`�悪�L���̏ꍇ�́A���̐ݒ�͖�������܂��B
		/// </remark>
		/// <param name="rotation">��]�B</param>
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		/// <summary>
		/// �g�嗦��ݒ�B
		/// </summary>
		/// <remark>
		/// �C���X�^���V���O�`�悪�L���̏ꍇ�́A���̐ݒ�͖�������܂��B
		/// </remark>
		/// <param name="scale">�g�嗦�B</param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		void SetScale(float x, float y, float z)
		{
			SetScale({ x, y, z });
		}

		/// <summary>
		/// �X�P���g���̏������B
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X�B</param>
		void InitSkeleton(const char* filePath);
		/// <summary>
		/// �A�j���[�V�����̏������B
		/// </summary>
		/// <param name="animationClips">�A�j���[�V�����N���b�v�B</param>
		/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐��B</param>
		/// <param name="enModelUpAxis">���f���̏�����B</param>
		void InitAnimation(AnimationClip* animationClips,
			int numAnimationClips,
			EnModelUpAxis enModelUpAxis);

		void IniTranslucent(
			const char* filePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ);

		AnimationClip* m_animationClips = nullptr;			// �A�j���[�V�����N���b�v�B
		int							m_numAnimationClips = 0;			// �A�j���[�V�����N���b�v�̐��B
		Vector3 					m_position = Vector3::Zero;			// ���W�B
		Quaternion	 				m_rotation = Quaternion::Identity;	// ��]�B
		Vector3						m_scale = Vector3::One;				// �g�嗦�B
		EnModelUpAxis				m_enFbxUpAxis = enModelUpAxisZ;		// FBX�̏�����B
		Animation					m_animation;						// �A�j���[�V�����B
		//ComputeAnimationVertexBuffer m_computeAnimationVertexBuffer;	// �A�j���[�V�����ςݒ��_�o�b�t�@�̌v�Z�����B
		Model* m_addRaytracingWorldModel = nullptr;// ���C�g�����[���h�ɓo�^�������f���B				
		Model						m_zprepassModel;					// ZPrepass�ŕ`�悳��郂�f��
		Model						m_forwardRenderModel;				// �t�H���[�h�����_�����O�̕`��p�X�ŕ`�悳��郂�f��
		Model						m_translucentModel;					// ���������f���B
		Model						m_renderToGBufferModel;				// RenderToGBuffer�ŕ`�悳��郂�f��
		Model						m_model;
		//Model						m_shadowModels[MAX_DIRECTIONAL_LIGHT][NUM_SHADOW_MAP];	// �V���h�E�}�b�v�ɕ`�悷�郂�f��
		//ConstantBuffer				m_drawShadowMapCameraParamCB[MAX_DIRECTIONAL_LIGHT][NUM_SHADOW_MAP];		// �V���h�E�}�b�v�쐬���ɕK�v�ȃJ�����p�����[�^�p�̒萔�o�b�t�@�B
		bool						m_isUpdateAnimation = true;			// �A�j���[�V�������X�V����H
		Skeleton					m_skeleton;							// ���B
		bool						m_isShadowCaster = true;			// �V���h�E�L���X�^�[�t���O
		float						m_animationSpeed = 1.0f;
		int							m_numInstance = 0;					// �C���X�^���X�̐��B
		int							m_maxInstance = 1;					// �ő�C���X�^���X���B
		bool						m_isEnableInstancingDraw = false;	// �C���X�^���V���O�`�悪�L���H
		bool						m_isRaytracingWorld = true;			//���C�g�����[���h�ɓo�^����H
		std::unique_ptr<Matrix[]>	m_worldMatrixArray;					// ���[���h�s��̔z��B
		StructuredBuffer			m_worldMatrixArraySB;				// ���[���h�s��̔z��̃X�g���N�`���[�h�o�b�t�@�B
		//std::vector< GemometryData > m_geometryDatas;					// �W�I���g�����B
		std::unique_ptr<int[]>		m_instanceNoToWorldMatrixArrayIndexTable;	// �C���X�^���X�ԍ����烏�[���h�s��̔z��̃C���f�b�N�X�ɕϊ�����e�[�u���B
	};
}

