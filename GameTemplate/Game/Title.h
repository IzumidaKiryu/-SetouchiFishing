#pragma once
#include "sound/SoundSource.h"
#include "GameStateBase.h"

//タイトル。
class GameStartCountdown;
class Title :public GameStateBase
{
public:
	Title();
	~Title();
	void OnUpdate();
	bool ShouldChangeState(); // 状態を変更すべきかどうかを決定する純粋仮想関数
	void OnEnter();
	void OnExit();

	void Render(RenderContext& rc)override;

	SpriteRender spriteRender ;
	//SoundSource* titleBGM;			//タイトルのBGM。

	GameStartCountdown* m_gameStartCountdown; // ゲームスタートカウントダウンのポインタ
};

