#pragma once
#include "sound/SoundSource.h"


class Player;
class GameCamera;
class BackGround;
class GetRotation;

//Gameシーンを管理するクラス。
class Game : public IGameObject
{
public:
	Game();
	~Game();
	//更新処理。
	void Update();
	void Render(RenderContext& rc);

	Vector3 rotationQuantity;
	Vector3 m_InsideScale{ 1.02f,1.0f,1.0f };

	SpriteRender hpBarInSide;
	Player* player;			//プレイヤー。
	GameCamera* gameCamera;			//ゲームカメラ。
	BackGround* backGround;
	SoundSource* gameBGM;		//ゲーム中のBGM。
	GetRotation* getRotation;//回転を取得。
	FontRender m_fontRender;
};

