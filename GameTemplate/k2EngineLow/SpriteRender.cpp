#include "k2EngineLowPreCompile.h"
#include "SpriteRender.h"
using namespace nsK2EngineLow;

void nsK2EngineLow::SpriteRender::Init(const char* filePath, const float w, const float h)
{
	SpriteInitData initData;
	//DDS�t�@�C���p�X���i�[����ϐ��̐ݒ�B
	initData.m_ddsFilePath[0] = filePath;
	//Sprite�Ŏg�p����V�F�[�_�[�p�X��ݒ�B
	initData.m_fxFilePath = "Assets/shader/sprite.fx";
	//�X�v���C�g�̏c������ݒ�B
	initData.m_width = w;
	initData.m_height = h;
	//SpriteRender�m�����f�[�^���g�p����Spritereader���������B
	m_sprite.Init(initData);
}
