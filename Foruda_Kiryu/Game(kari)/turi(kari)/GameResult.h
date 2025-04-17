#pragma once
class GameResult :public IGameObject
{
public:
	enum FishName {
		Hamachi,
		Tachiuo,
		Tai,
		Hirame,
		Pearl,
		Jakoten,
		num
	};
	GameResult();
	~GameResult();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Easing(FishName name, Vector3 fastPos, Vector3 endPos);

	//Vector3 m_fastPos = { -350.0f,200.0f,0.0f };//イージング前の座標。
	//Vector3 m_endPos={ -600.0f,200.0f,0.0f };//イージング後の座標。
	Vector3 m_fastPos = { -350.0f,220.0f,0.0f };//イージング前の座標。
	Vector3 m_endPos = { -600.0f,220.0f,0.0f };//イージング後の座標。

	Vector3 m_fastPos2 = { -350.0f,130.0f,0.0f };//イージング前の座標。
	Vector3 m_endPos2 = { -600.0f,130.0f,0.0f };//イージング後の座標。

	Vector3 m_fastPos3 = { -350.0f,40.0f,0.0f };//イージング前の座標。
	Vector3 m_endPos3 = { -600.0f,40.0f,0.0f };//イージング後の座標。

	Vector3 m_fastPos4 = { -350.0f,-50.0f,0.0f };//イージング前の座標。
	Vector3 m_endPos4 = { -600.0f,-50.0f,0.0f };//イージング後の座標。

	Vector3 m_fastPos5 = { -350.0f,-140.0f,0.0f };//イージング前の座標。
	Vector3 m_endPos5 = { -600.0f,-140.0f,0.0f };//イージング後の座標。

	Vector3 m_fastPos6 = { -350.0f,-230.0f,0.0f };//イージング前の座標。
	Vector3 m_endPos6 = { -600.0f,-230.0f,0.0f };//イージング後の座標。

	Vector3 m_vec[num];
	float m_t[num];			//補完率。

	

	SpriteRender m_fishUI[6];//収集した魚の表示用スプライトレンダー。
	SpriteRender m_back;
};
