#pragma once
#include "sound/SoundSource.h"
#include "GameStateBase.h"

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

	SpriteRender spriteRender ;
	InGameState* m_inGameState;
	//SoundSource* titleBGM;			//タイトルのBGM。
 // ゲームスタートカウントダウンのポインタ
};

