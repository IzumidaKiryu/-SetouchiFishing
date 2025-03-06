#pragma once
class CastGauge:public IGameObject
{
public:

	CastGauge();
	~CastGauge();
	void Update();
	void Render(RenderContext& rc);
	SpriteRender m_castGaugeOutside;
};

