#pragma once
class GaugeCastSuccessful :public IGameObject
{
public:
	GaugeCastSuccessful();
	~GaugeCastSuccessful();
	void Init(float position, float scale);
	void SetRange();
	bool hitTest(float arrowPosition);

	float m_position=0.0f;
	float m_scale=1.0f;
	float m_heightFirstGaugeCastSuccessful = 10.0f;
	float m_rangelower=0.0f;
	float m_rangeMax=0.0f;

	SpriteRender m_gaugeCastSuccessfulSprite;
};

