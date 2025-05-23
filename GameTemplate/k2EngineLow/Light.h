#pragma once
namespace nsK2EngineLow {
	struct DirectionLight {
		Vector3 m_direction;//ライトの方向。3要素のベクトルで表現。
		float pad0;
		Vector3 m_color;//ライトのカラー。光の3原色で表現。
		float pad1;
	};

	struct PointLight {
		Vector3 m_position;//ライトの位置。3要素のベクトルで表現。
		float pad2;//パティング。
		Vector3 m_color;//ライトのカラー。光の3原色で表現。
		float m_renge;//影響範囲。単位はメートル。

	};

	struct SpotLight {
		Vector3 m_position;//ライトの位置。3要素のベクトルで表現。
		float pad3;
		Vector3 m_color;//ライトのカラー。光の3原色で表現。
		float m_range;//影響範囲。単位はメートル。
		Vector3 m_direction;//放射方向。3要素のベクトルで表現。
		float m_angle;//放射角度。
	};

	struct HemisphereLight {
		Vector3 m_groundColor;
		float pad6;
		Vector3 m_skyColor;
		float pad7;
		Vector3 m_groundNormal;
		float pad8;
	};

	struct SceneLight
	{
		DirectionLight directionLig;
		PointLight pointLig;
		SpotLight spotLig;
		Vector3 eyePos;
		float pad0;
		Vector3 ambientLight;
		float pad5;
		HemisphereLight m_hemiLig;
	};


	//ライトクラス。環境光はシェーダー側で設定してる(各初期値0.3f)。
	class Light :public IGameObject
	{
	public:
		
		Light();
		~Light();

		void Init();
		void Update();

		SceneLight& GetLight()
		{
			return m_SceneLight;
		}
	private:
		SceneLight m_SceneLight;
	};
}



