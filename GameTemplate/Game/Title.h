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
	bool ShouldChangeState(); // 状態を変更すべきかどうかを決定する純粋仮想関数
	void OnEnter();
	void OnExit();

	void Render(RenderContext& rc)override;

	SpriteRender m_pressA;
	SpriteRender m_pressX;
	SpriteRender spriteRender ;
	InGameState* m_inGameState;
	SoundSource* m_sound;
	//SoundSource* titleBGM;			//タイトルのBGM。
 // ゲームスタートカウントダウンのポインタ
};

