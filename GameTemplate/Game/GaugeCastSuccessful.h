#pragma once
class GaugeCastSuccessful :public IGameObject
{
public:
	GaugeCastSuccessful();
	~GaugeCastSuccessful();
	void Init(float position, float scale);
	void SetRange();
	bool hitTest(float arrowPosition);

	float m_position;
	float m_scale;
	float m_heightFirstGaugeCastSuccessful = 10.0f;
	float m_rangelower;
	float m_rangeMax;

	SpriteRender m_gaugeCastSuccessfulSprite;
};

