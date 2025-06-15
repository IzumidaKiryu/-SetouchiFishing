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


	GameStateBase* currentState;


	Vector3 m_rotationQuantity;
	Vector3 m_InsideScale{ 1.02f,1.0f,1.0f };

	SpriteRender hpBarInSide;
	GameCamera* gameCamera;
	BackGround* backGround;
	/*SoundSource* gameBGM;*/
	FontRender m_fontRender;
	PositionSelection* positionSelection;//場所を選ぶ画面のクラス。
	PlayFishing* m_playFishing;
	/*ScoreDisplay* m_scoreDisplay;*/
	SkyCube* m_skyCube = nullptr;
	BackGround* m_backGround;
	FishSlot* m_fishSlot;
	GameStartCountdown* m_gameStartCountdown;
	Player* m_player;
	Enemy* m_enemy;
	PositionSelection* m_positionSelection;
	GameState m_gameState = GameState::GameStartCountdown; //ゲームの状態を管理する変数

	Title* m_title;
	InGameState* m_inGameState;
	GameResult* m_gameResult;
	GameGuide* m_gameGuide;

	};