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
	Player* player;			//�v���C���[�B
	GameCamera* gameCamera;			//�Q�[���J�����B
	BackGround* backGround;
	SoundSource* gameBGM;		//�Q�[������BGM�B
	FontRender m_fontRender;

};

