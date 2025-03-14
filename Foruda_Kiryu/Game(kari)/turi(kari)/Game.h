#pragma once
#include "sound/SoundSource.h"


class Player;
class GameCamera;
class BackGround;
class GetRotation;
class PositionSelection;
class PlayFishing;

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
	Player* player;			//�v���C���[�B
	GameCamera* gameCamera;			//�Q�[���J�����B
	BackGround* backGround;
	SoundSource* gameBGM;		//�Q�[������BGM�B
	GetRotation* getRotation;//��]��擾�B
	FontRender m_fontRender;
	PositionSelection* positionSelection;//�ꏊ�I���
	PlayFishing* m_playFishing;
};