#pragma once
#include< memory >
#include"InGameState.h"

class InGameState;
class Game;
class GameResult :public GameStateBase
{
public:
	enum FishName {
		Hamachi,
		Tachiuo,
		Tai,
		Hirame,
		Pearl,
		Jakoten,
		num
	};
	GameResult();
	~GameResult();
	bool Start();
	bool Init();
	void OnUpdate();
	void OnEnter();
	void OnExit();




	virtual bool ShouldChangeState(); // 状態を変更すべきかどうかを決定する純粋仮想関数
	void SetFastPos();//各配列の初期化
	void Render(RenderContext& rc);
	void Easing(FishName name, Vector3 fastPos, Vector3 endPos);

	Vector3 m_fastPos[num] = {//イージング前の座標。
		{ -350.0f,220.0f,0.0f } ,
		{ -350.0f,130.0f,0.0f },
		{ -350.0f,40.0f,0.0f },
		{ -350.0f,-50.0f,0.0f },
		{ -350.0f,-140.0f,0.0f },
		{ -350.0f,-230.0f,0.0f }
	};

	Vector3 m_endPos[num]{//イージング後の座標。
		{ -600.0f,220.0f,0.0f },
		{ -600.0f,130.0f,0.0f },
		{ -600.0f,40.0f,0.0f },
		{ -600.0f,-50.0f,0.0f },
		{ -600.0f,-140.0f,0.0f },
		{ -600.0f,-230.0f,0.0f }
	};

	Vector3 m_vec[num];//各UIのポジション。
	float m_t[num];			//補完率。

	SpriteRender m_fishUI[6];//収集した魚の表示用スプライトレンダー。
	SpriteRender m_back;//リザルト画面の背景用スプライトレンダー。

	int nowFishName = FishName::Hamachi;//イージングさせる魚のUI(初期設定はハマチ)。
	InGameState* m_inGameState;
	Game* m_game;
};
