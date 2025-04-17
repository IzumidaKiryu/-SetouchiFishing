#pragma once
#include "sound/SoundSource.h"


class Player;
class GameCamera;
class BackGround;
class GetRotation;
class PositionSelection;
class PlayFishing;
class ScoreDisplay;

class GameResult;

//Game�V�[����Ǘ�����N���X�B
class Game : public IGameObject
{
public:
	Game();
	~Game();
	//�X�V�����B
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_rotationQuantity;
	Vector3 m_InsideScale{ 1.02f,1.0f,1.0f };

	SpriteRender hpBarInSide;
	Player* player;
	GameCamera* gameCamera;
	BackGround* backGround;
	/*SoundSource* gameBGM;*/
	FontRender m_fontRender;
	PositionSelection* positionSelection;//場所を選ぶ画面のクラス。
	PlayFishing* m_playFishing;
	GameResult* m_rul;
	/*ScoreDisplay* m_scoreDisplay;*/
};