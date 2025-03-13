#pragma once
#include "sound/SoundSource.h"

class Player;
class GameCamera;
class BackGround;
class SoundSource;

enum FishType {
	null,
	Tai,
	Buri,
	Tatiuo,
	Hirame,
	Jakotenn,
	Sinju,
};
struct fishingPosition {
	FishType fish;
	bool fishChangeFlag;//魚を変えるかどうかのフラグ。
};
//#include "physics/PhysicsGhostObject.h"
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
	//PhysicsGhostObject m_physicsGhostObject;
	fishingPosition PositionA;
	fishingPosition PositionB;
	fishingPosition PositionC;
	fishingPosition PositionD;
	fishingPosition PositionE;
	fishingPosition PositionF;

};

