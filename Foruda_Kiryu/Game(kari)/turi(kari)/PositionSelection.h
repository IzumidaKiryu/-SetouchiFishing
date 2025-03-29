#pragma once
#include "sound/SoundSource.h"

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


class PositionSelection : public IGameObject
{
public:
	

	PositionSelection();
	~PositionSelection();
	void Update();
	void Render(RenderContext& rc);
	void SetUI();
	void SetFishUI();
	void SetFishDisplayPosition();
	void SetisDisplayingTrue();
	void SetisDisplayingFalse();
	void ChangeSceneToPlayFishing();
	bool GetisDisplaying();
	void SetDeactivate();//非アクティブにする。
	void SetActivate();
	void Timer();
	void SetFishUIPosition();
	
	float setFish=0.0f;
	Vector3 m_fishDisplayPosition[6];
	float m_fishDisplayPositionXcriteria = -350;//魚を表示するディスプレイの場所の基準（X軸）
	float m_fishDisplayPositionXinterval = 350.0f;
	bool m_is_displaying;
	bool m_shouldPartiallyDeactivate=false;//部分的に非アクティブにするべきか。
	float m_time=0.0f;//時間
	float m_timelimit = 2000;//時間制限
	bool m_is_time_up;//タイムアップしているかどうか。
	

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
};

