#include "stdafx.h"
#include "GameCrear.h"
#include"Title.h"

GameClear::GameClear()
{
	//�Q�[���N���A�̉摜��ǂݍ��ށB
	spriteRender.Init("Assets//modeleData.dds", 1920.0f, 1080.0f);
}

GameClear::~GameClear()
{

}

//�X�V����
void GameClear::Update()
{
	//A�{�^���������ꂽ��B
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//�^�C�g���̃I�u�W�F�N�g�����B
		NewGO<Title>(0, "title");
			//���M���폜����B
			DeleteGO(this);
	}
}
//�`�揈���B
void GameClear::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}