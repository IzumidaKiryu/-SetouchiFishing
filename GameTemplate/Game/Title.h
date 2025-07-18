#pragma once
#include "sound/SoundSource.h"
#include "GameStateBase.h"
#include"GameGuide.h"


//タイトル。
class InGameState;
class Title :public GameStateBase
{
public:
	Title();
	~Title();
	bool Start()override;
	bool Init();
	void OnUpdate();
	/// <summary>
	/// 状態を変更すべきかどうかを決定する純粋仮想関数
	/// </summary>
	/// <returns></returns>
	bool ShouldChangeState(); 
	void OnEnter();
	void OnExit();
	void Render(RenderContext& rc)override;

private:
	SpriteRender m_pressA;
	SpriteRender m_pressX;
	SpriteRender spriteRender ;
	InGameState* m_inGameState=nullptr;
	SoundSource* m_sound=nullptr;
};

