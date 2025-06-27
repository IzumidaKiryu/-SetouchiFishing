#pragma once
#include "sound/SoundSource.h"
#include< memory >


class Player;
class GameCamera;
class BackGround;
class GetRotation;
class PositionSelection;
class PlayFishing;
class ScoreDisplay;
class FishSlot;
class GameStartCountdown;
class Enemy;
class Player;
class GameStateBase;
class Title;
class InGameState;
class GameResult;
class GameGuide;

enum class GameState
{
	GameStartCountdown, //ゲーム開始カウントダウン画面
	PositionSelection, //場所を選ぶ画面
	PlayFishing, //釣りをする画面
	GameResult, //ゲーム結果の画面
};
//Game�V�[����Ǘ�����N���X�B
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	bool Init();
	//�X�V�����B
	void Update();
	void Render(RenderContext& rc);
	void NewGOStateObjects();
	void DeactivateGameObjects();
	void ResetInGame();//リザルト画面が終わったら呼ばれる。


	GameStateBase* currentState=nullptr;


	Vector3 m_rotationQuantity=Vector3::Zero;
	Vector3 m_InsideScale{ 1.02f,1.0f,1.0f };

	SpriteRender hpBarInSide;
	GameCamera* gameCamera=nullptr;
	BackGround* backGround=nullptr;
	/*SoundSource* gameBGM;*/
	FontRender m_fontRender;
	PositionSelection* positionSelection=nullptr;//場所を選ぶ画面のクラス。
	PlayFishing* m_playFishing=nullptr;
	/*ScoreDisplay* m_scoreDisplay;*/
	SkyCube* m_skyCube = nullptr;
	BackGround* m_backGround=nullptr;
	FishSlot* m_fishSlot=nullptr;
	GameStartCountdown* m_gameStartCountdown=nullptr;
	Player* m_player=nullptr;
	Enemy* m_enemy=nullptr;
	PositionSelection* m_positionSelection=nullptr;
	GameState m_gameState = GameState::GameStartCountdown; //ゲームの状態を管理する変数

	Title* m_title=nullptr;
	InGameState* m_inGameState=nullptr;
	GameResult* m_gameResult=nullptr;
	GameGuide* m_gameGuide=nullptr;

	};