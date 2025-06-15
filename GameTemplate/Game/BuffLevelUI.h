#pragma once
#include"BuffManager.h"
class BuffManager;
class BuffLevelUI: public IGameObject
{
public:
	BuffLevelUI();
	~BuffLevelUI();
	bool Init();
	bool Start();
	void Update();
	void SetUI();
	void Render(RenderContext& rc);

private:
	const float m_fontScale = 2.0f;
	const Vector3 m_buffLevelUIPos = { -750.0f,0.0f,0.0f };
	SpriteRender m_buffLevelUI;
	BuffManager* m_buffManager;
	std::map<BuffType, FontRender> m_buffLevelFont;
	std::map<BuffType, Vector3> m_fontPos;
	void UpdateFont(BuffType type);
	void SetInitFont();
	void SetInitBuffPos();

};

