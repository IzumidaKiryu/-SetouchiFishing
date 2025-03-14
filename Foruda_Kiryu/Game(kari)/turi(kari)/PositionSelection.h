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

class PositionSelection : public IGameObject
{
public:
	

	PositionSelection();
	~PositionSelection();
	void Update();
	void Render(RenderContext& rc);
	void SettingFishType(fishingPosition Position);//魚のタイプを設定。
	void SelectChangeFish(fishingPosition Position);//魚を変えるかどうか選ぶ。
	float setFish=0.0f;
	Player* player;			//プレイヤー。
	GameCamera* gameCamera;			//ゲームカメラ。
	BackGround* backGround;
	SoundSource* gameBGM;		//ゲーム中のBGM。
	FontRender m_fontRender;
	fishingPosition PositionA;
	fishingPosition PositionB;
	fishingPosition PositionC;
	fishingPosition PositionD;
	fishingPosition PositionE;
	fishingPosition PositionF;

};

