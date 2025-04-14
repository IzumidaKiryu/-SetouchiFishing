#pragma once
class FishHP : public IGameObject
{
public:
	FishHP();
	~FishHP();
	void Update();
	void Render(RenderContext& rc);
	void FishHPManagement();

	float m_fishHP=100.0f;

	
	SpriteRender m_fishHPBarFrame;
	SpriteRender m_fishHPBar;
};