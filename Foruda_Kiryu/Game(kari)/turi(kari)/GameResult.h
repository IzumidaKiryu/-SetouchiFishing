#pragma once
class GameResult:public IGameObject
{
public:
	enum fishName {
		Buri,
		Tachiuo,
		Tai,
		Hirame,
		Sinzyu,
		Zyako,
	};
	GameResult();
	~GameResult();
	bool start();
	void Update();
	void Render(RenderContext&rc);
	void Eaging(fishName name,Vector3 fastPos,Vector3 endPos);
	
	Vector3 fastPos;//イージング前の座標。
	Vector3 endPos;//イージング後の座標。
	Vector3 m_vec = Vector3::Zero;
	int m_t = 0.0f;//補完率。

	SpriteRender m_fishUI[6];//収集した魚の表示用スプライトレンダー。
	SpriteRender m_back;
};

