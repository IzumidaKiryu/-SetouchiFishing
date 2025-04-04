#include "stdafx.h"
#include "PlayFishing.h"
#include"PlayFishingBackGround.h"
#include "GameCamera.h"
#include "CastGauge.h"
#include "PositionSelection.h"
#include "FishManager.h"


PlayFishing::PlayFishing()
{
	m_objectName= new char[6];// �t�B�b�V���}�l�[�W���[�̃I�u�W�F�N�g�l�[���̃������m��

	m_playFishingBackGround = NewGO< PlayFishingBackGround>(0, "playFishingBackGround");
	//�Q�[���J�����̃I�u�W�F�N�g�����B
	gameCamera = NewGO<GameCamera>(0, "gamecamera");
	CallCastGauge();
}

PlayFishing::~PlayFishing()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_positionSelection->SetisDisplayingTrue();

	DeleteGO(m_playFishingBackGround);
	DeleteGO(m_castGauge);
	DeleteGO(gameCamera);

	//�|�W�V�����Z���N�g�N���X�̃I�u�W�F�N�g���A�N�e�B�u�ɂ���
	m_positionSelection->SetActivate();
}

void PlayFishing::Update()
{
}

void PlayFishing::CallCastGauge()
{
	m_castGauge = NewGO< CastGauge>(0, "CastGauge");
}

void PlayFishing::DeleteThisClass()
{
	DeleteGO(this); 
}

void PlayFishing::SetFishManagerObjectName(std::string string_objectName)
{
	//�t�B�b�V���}�l�[�W���[�ɂ���I�u�W�F�N�g�l�[���̐ݒ�B
	std::char_traits<char>::copy(m_objectName, string_objectName.c_str(), string_objectName.size() + 1);
}

void PlayFishing::FindeFishManager()
{
	m_fishManager = FindGO<FishManager>(m_objectName);
}
