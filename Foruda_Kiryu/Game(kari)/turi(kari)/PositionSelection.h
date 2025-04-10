#pragma once
#include "sound/SoundSource.h"
#include <string>

enum Position {
	POSITION_A,
	POSITION_B,
	POSITION_C,
	POSITION_D,
	POSITION_E,
	POSITION_F,
};

class Player;
class GameCamera;
class BackGround;
class SoundSource;
class FishManager;
class PlayFishing;
class TimeLimitUI;


class PositionSelection : public IGameObject
{
public:
	

	PositionSelection();
	~PositionSelection();
	void Update();
	void Render(RenderContext& rc);
	void SetUI();
	void SetFishUI();//魚のUIをセット。
	void SetFishDisplayPosition();//ディスプレイUIの場所を設定。
	void SetisDisplayingTrue();
	void SetisDisplayingFalse();
	void ChangeSceneToPlayFishing();
	bool GetisDisplaying();

	void SetDeactivate();//非アクティブにする。
	void SetActivate();
	void Timer();
	void SetFishUIPosition();
	void FishChange();//魚を変える。
	void SelectPosition();
	void SelectPositionA();
	void SelectPositionB();
	void SelectPositionC();
	void SelectPositionD();
	void SelectPositionE();
	void SelectPositionF();
	

	float setFish=0.0f;
	Vector3 m_fishDisplayPosition[6];
	float m_fishDisplayPositionXcriteria = -350;//魚を表示するディスプレイの場所の基準（X軸）
	float m_fishDisplayPositionXinterval = 350.0f;
	bool m_is_displaying;

	bool m_shouldPartiallyDeactivate=false;//部分的に非アクティブにするべきか。
	double m_double_time=0.0f;//時間
	int m_int_time=0;
	float m_timelimit = 240;//時間制限
	bool m_is_time_up;//タイムアップしているかどうか。
	std::string fishManagerObjectName[6] = {
		"positionA",
		"positionB",
		"positionC",
		"positionD",
		"positionE",
		"positionF"
	}
	;
	std::string select_by_with_position;
	char* objectName[6]; 


	Player* player;			//プレイヤー。
	GameCamera* gameCamera;			//ゲームカメラ。
	BackGround* backGround;
	SoundSource* gameBGM;		//ゲーム中のBGM。
	FontRender m_fontRender;
	SpriteRender m_fishDisplayInside[6];
	SpriteRender m_fishDisplayOutside[6];
	FishManager* m_fishManager[6];
	PlayFishing* m_playFishing;
	SpriteRender* m_fishUI[6];
	TimeLimitUI* m_timeLimitUI;

	Stopwatch m_stopwatch;
};

