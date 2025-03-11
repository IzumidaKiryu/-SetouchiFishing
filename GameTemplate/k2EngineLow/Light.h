#pragma once
namespace nsK2EngineLow {



	class Light :public IGameObject
	{
	public:
		struct DirectionLight {
			Vector3 d_direction;//ライトの方向。3要素のベクトルで表現。
			float pad;
			Vector3 d_color;//ライトのカラー。光の3原色で表現。
		};

		struct PointLight {
			float p_position[3];//ライトの位置。3要素のベクトルで表現。
			float p_color[3];//ライトのカラー。光の3原色で表現。
			float p_infuluenceRenge;//影響範囲。単位はメートル。
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
		};

		Light();
		~Light();

		void Init();
		void Update();

		SceneLight& GetLight()
		{
			return m_light;
		}
		SceneLight m_light;
	};
}

