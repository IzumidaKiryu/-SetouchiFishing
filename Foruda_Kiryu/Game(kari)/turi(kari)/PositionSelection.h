#pragma once
#include "sound/SoundSource.h"

class Player;
class GameCamera;
class BackGround;
class SoundSource;

class PositionSelection : public IGameObject
{
public:

	PositionSelection();
	~PositionSelection();
	void Update();
	void Render(RenderContext& rc);
	void fishingPositionA_SetFish();
	void fishingPositionB_SetFish();
	void fishingPositionC_SetFish();
	void fishingPositionD_SetFish();
	void fishingPositionE_SetFish();
	void fishingPositionF_SetFish();
	float setFish=0.0f;
	Player* player;			//プレイヤー。
	GameCamera* gameCamera;			//ゲームカメラ。
	BackGround* backGround;
	SoundSource* gameBGM;		//ゲーム中のBGM。
	FontRender m_fontRender;

};

