#pragma once
#include< memory >
#include "sound/SoundSource.h"
#include"InGameState.h"

class InGameState;
class Game;
//泉田追加
class Player;
class Enemy;
class ScoreManager;
//ここまで
class GameResult :public GameStateBase
{
public:
	enum FishName {
		TAI,
		BURI,
		TATIUO,
		HIRAME,
		JAKOTENN,
		SINJU,
		num
	};
	GameResult();
	~GameResult();
	bool Start();
	bool Init();
	void OnUpdate();
	void OnEnter();
	void OnExit();
	void Reset();



	virtual bool ShouldChangeState(); // 状態を変更すべきかどうかを決定する純粋仮想関数
	void SetFastPos();//各配列の初期化
	void Render(RenderContext& rc);
	void Easing(FishName name, Vector3 fastPos, Vector3 endPos);

	void EasingEnemy(FishName name, Vector3 fastPos, Vector3 endPos);


	//魚のスコアをセットする関数。
	void SetFishScore();

	Vector3 m_fastPos[num] = {//イージング前の座標プレイヤー側。
		{ 0.0f,220.0f,0.0f } ,
		{ 0.0f,130.0f,0.0f },
		{ 0.0f,40.0f,0.0f },
		{ 0.0f,-50.0f,0.0f },
		{ 0.0f,-140.0f,0.0f },
		{ 0.0f,-230.0f,0.0f }
	};

	Vector3 m_endPos[num]{//イージング後の座標Playerがわ。
		{ -320.0f,220.0f,0.0f },
		{ -320.0f,130.0f,0.0f },
		{ -320.0f,40.0f,0.0f },
		{ -320.0f,-50.0f,0.0f },
		{ -320.0f,-140.0f,0.0f },
		{ -320.0f,-230.0f,0.0f }
	};

	Vector3 m_enemyUIFarstPos[num]{
		{ 700.0f,220.0f,0.0f } ,
		{ 700.0f,130.0f,0.0f },
		{ 700.0f,40.0f,0.0f },
		{ 700.0f,-50.0f,0.0f },
		{ 700.0f,-140.0f,0.0f },
		{ 700.0f,-230.0f,0.0f }
	};

	Vector3 m_enemyUIEndPos[num]{
	{ 400.0f,220.0f,0.0f } ,
	{ 400.0f,130.0f,0.0f },
	{ 400.0f,40.0f,0.0f },
	{ 400.0f,-50.0f,0.0f },
	{ 400.0f,-140.0f,0.0f },
	{ 400.0f,-230.0f,0.0f }
	};

	Vector3 m_vec[num];//各UIのポジション。
	float m_t[num];			//補完率。

	Vector3 m_enemyVec[num];//敵のUIのポジション。
	float m_enemyT[num];	//敵のUIの補完率。


	SpriteRender m_fishUI[6];//収集した魚の表示用スプライトレンダー。
	SpriteRender m_back;//リザルト画面の背景用スプライトレンダー。

	int nowFishName = FishName::TAI;//イージングさせる魚のUI(初期設定はtai)。
	InGameState* m_inGameState=nullptr;
	Game* m_game=nullptr;
	//泉田追加
	ScoreManager* m_scoreManager = nullptr; // スコアマネージャーのポインタ
	FontRender m_fontRender[12] = {}; // フォントレンダラー
	wchar_t m_scoreText[12][256]; // スコア表示用のテキスト配列
	float m_alpha[num] = {}; // アルファ値
	float m_enemyAlpha[num] = {}; // 敵のUIのアルファ値
	SpriteRender m_enemyFishUI[6]; // 敵の魚のUI用スプライトレンダー
	
	float m_waitTimer = 0.0f;
	bool m_waiting = false;

	//指定時間待つ関数。
	bool WaitSeconds(float seconds)
	{
		if (!m_waiting) {
			m_waitTimer = 0.0f;
			m_waiting = true;
		}

		m_waitTimer += g_gameTime->GetFrameDeltaTime();
		if (m_waitTimer >= seconds) {
			m_waiting = false;
			
			return true; // 待ち完了
		}

		return false; // まだ待機中
	}

	RenderingEngine* m_renderingEngine = nullptr; // レンダリングエンジンのポインタ
	
	bool m_plVictoryFlag = false;//trueの時Playerの勝ち。
	bool m_enVictoryFlag = false;
	void SetVictory();//勝者の設定。

	SoundSource* m_sound;
	FontRender m_allScoreEnemy; // リザルト画面のフォントレンダラー
	FontRender m_allScorePlayer; // リザルト画面のフォントレンダラー2
	float playerTotalScore = 0.0f;
	float enemyTotalScore = 0.0f;
	
	//ここまで
};
