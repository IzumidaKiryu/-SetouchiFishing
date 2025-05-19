#pragma once

namespace nsK2EngineLow {
	class Light;
	class ModelRender
	{
	public:
		ModelRender();
		~ModelRender();

		void Init(const char* filePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationCrips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ);

		void InitSkyCubeModel(ModelInitData& initData);

		void InitModel(const char* filePath, EnModelUpAxis enModelUpAxis);

		void Update();

		void Draw(RenderContext& rc);

		void OnDraw(RenderContext& rc)
		{
			m_model.Draw(rc, 1);
		}
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}

		/// <summary>
		/// アニメーションの再生中？
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
		/// 座標を設定。
		/// </summary>
		/// <param name="x">x座標</param>
		/// <param name="y">y座標</param>
		/// <param name="z">z座標</param>
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x, y, z });
		}
		/// <summary>
		/// 回転を設定。
		/// </summary>
		/// <remark>
		/// インスタンシング描画が有効の場合は、この設定は無視されます。
		/// </remark>
		/// <param name="rotation">回転。</param>
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		Quaternion GetRotation()
		{
			return m_rotation;
		}

		/// <summary>
		/// 拡大率を設定。
		/// </summary>
		/// <remark>
		/// インスタンシング描画が有効の場合は、この設定は無視されます。
		/// </remark>
		/// <param name="scale">拡大率。</param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		void SetScale(float x, float y, float z)
		{
			SetScale({ x, y, z });
		}

		/// <summary>
	/// モデルを取得。
	/// </summary>
	/// <returns>モデル</returns>
		Model& GetModel()
		{
			return m_model;
		}

		/// <summary>
		/// スケルトンの初期化。
		/// </summary>
		/// <param name="filePath">ファイルパス。</param>
		void InitSkeleton(const char* filePath);
		/// <summary>
		/// アニメーションの初期化。
		/// </summary>
		/// <param name="animationClips">アニメーションクリップ。</param>
		/// <param name="numAnimationClips">アニメーションクリップの数。</param>
		/// <param name="enModelUpAxis">モデルの上向き。</param>
		void InitAnimation(AnimationClip* animationClips,
			int numAnimationClips,
			EnModelUpAxis enModelUpAxis);

		void IniTranslucent(
			const char* filePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ);
		float GetAnimationRatio();


		//座標拡大回転全てを設定
		void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
		{
			SetPosition(pos);
			SetRotation(rotation);
			SetScale(scale);
		}


		AnimationClip* m_animationClips = nullptr;			// アニメーションクリップ。
		int							m_numAnimationClips = 0;			// アニメーションクリップの数。
		Vector3 					m_position = Vector3::Zero;			// 座標。
		Quaternion	 				m_rotation = Quaternion::Identity;	// 回転。
		Vector3						m_scale = Vector3::One;				// 拡大率。
		EnModelUpAxis				m_enFbxUpAxis = enModelUpAxisZ;		// FBXの上方向。
		Animation					m_animation;						// アニメーション。
		//ComputeAnimationVertexBuffer m_computeAnimationVertexBuffer;	// アニメーション済み頂点バッファの計算処理。
		Model* m_addRaytracingWorldModel = nullptr;// レイトレワールドに登録したモデル。				
		Model						m_zprepassModel;					// ZPrepassで描画されるモデル
		Model						m_forwardRenderModel;				// フォワードレンダリングの描画パスで描画されるモデル
		Model						m_translucentModel;					// 半透明モデル。
		Model						m_renderToGBufferModel;				// RenderToGBufferで描画されるモデル
		Model						m_model;
		//Model						m_shadowModels[MAX_DIRECTIONAL_LIGHT][NUM_SHADOW_MAP];	// シャドウマップに描画するモデル
		//ConstantBuffer				m_drawShadowMapCameraParamCB[MAX_DIRECTIONAL_LIGHT][NUM_SHADOW_MAP];		// シャドウマップ作成時に必要なカメラパラメータ用の定数バッファ。
		bool						m_isUpdateAnimation = true;			// アニメーションを更新する？
		Skeleton					m_skeleton;							// 骨。
		bool						m_isShadowCaster = true;			// シャドウキャスターフラグ
		float						m_animationSpeed = 1.0f;
		int							m_numInstance = 0;					// インスタンスの数。
		int							m_maxInstance = 1;					// 最大インスタンス数。
		bool						m_isEnableInstancingDraw = false;	// インスタンシング描画が有効？
		bool						m_isRaytracingWorld = true;			//レイトレワールドに登録する？
		std::unique_ptr<Matrix[]>	m_worldMatrixArray;					// ワールド行列の配列。
		StructuredBuffer			m_worldMatrixArraySB;				// ワールド行列の配列のストラクチャードバッファ。
		//std::vector< GemometryData > m_geometryDatas;					// ジオメトリ情報。
		std::unique_ptr<int[]>		m_instanceNoToWorldMatrixArrayIndexTable;	// インスタンス番号からワールド行列の配列のインデックスに変換するテーブル。
		Light* m_light;
	};
}

