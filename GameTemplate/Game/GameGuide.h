#pragma once
#include "GameStateBase.h"
class GameGuide:public GameStateBase
{
public:
	GameGuide();
	~GameGuide();

	bool Start()override;
	bool Init();
	void SetGuidSprite();
	void OnUpdate();
	bool ShouldChangeState(); // 状態を変更すべきかどうかを決定する純粋仮想関数
	void OnEnter();
	void OnExit();
	void Render(RenderContext& rc)override;
	SpriteRender m_GuideSprite[9];
	int m_pageIndex=0;
};

