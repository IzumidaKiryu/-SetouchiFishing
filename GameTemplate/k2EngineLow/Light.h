#pragma once
namespace nsK2EngineLow {


	//ライトクラス。環境光はシェーダー側で設定してる(各初期値0.3f)。
	class Light :public IGameObject
	{
	public:
		struct DirectionLight {
			Vector3 d_direction;//ライトの方向。3要素のベクトルで表現。
			float pad0;
			Vector3 d_color;//ライトのカラー。光の3原色で表現。
			float pad1;
		};

		struct PointLight {
			Vector3 ptPosition;//ライトの位置。3要素のベクトルで表現。
			float pad2;//パティング。
			Vector3 ptColor;//ライトのカラー。光の3原色で表現。
			float ptInfuluenceRenge;//影響範囲。単位はメートル。
		
		};

		struct SpotLight {
			float s_position[3];//ライトの位置。3要素のベクトルで表現。
			float s_color[3];//ライトのカラー。光の3原色で表現。
			float s_direction[3];//放射方向。3要素のベクトルで表現。
			float s_angle;//放射角度。
			float s_infuluenceRenge;//影響範囲。単位はメートル。
		};

		struct SceneLight
		{
			DirectionLight direction;
			PointLight pointLig;
			Vector3 eyePos;
			float pad0;
			Vector3 ambientLight;

		};

		Light();
		~Light();

		void Init();
		void Update();

		SceneLight& GetLight()
		{
			return m_SceneLight;
		}
		SceneLight m_SceneLight;
	};
}



