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

	SpriteRender m_pressA;
	SpriteRender m_pressB;
	SpriteRender spriteRender ;
	SpriteRender m_bInfo; // Bボタン説明画像用
	bool m_isShowBInfo = false; // 表示フラグ
	InGameState* m_inGameState;
	SoundSource* m_sound;
	//SoundSource* titleBGM;			//タイトルのBGM。
 // ゲームスタートカウントダウンのポインタ
};

