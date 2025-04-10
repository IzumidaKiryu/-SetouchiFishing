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
			Vector3 s_position;//ライトの位置。3要素のベクトルで表現。
			float pad3;
			Vector3 s_color;//ライトのカラー。光の3原色で表現。
			float s_Range;//影響範囲。単位はメートル。
			Vector3 s_direction;//放射方向。3要素のベクトルで表現。
			float s_angle;//放射角度。
			
		};

		struct SceneLight
		{
			DirectionLight direction;
			PointLight pointLig;
			SpotLight spotLig;
			Vector3 eyePos;
			float pad4;
			Vector3 ambientLight;
			float pad5;
			Vector3 groundColor;
			float pad6;
			Vector3 skyColor;
			float pad7;
			Vector3 groundNormal;
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



