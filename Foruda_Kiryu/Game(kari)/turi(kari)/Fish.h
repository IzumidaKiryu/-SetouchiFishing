#pragma once

struct FishData
{
	float arrowSpeed=0.0f;
	float score=0.0f;//�̒l
};
class PositionSelection;
class Fish : public IGameObject
{
public:
	Fish();
	~Fish();
	//�X�V�����B
	void Update();
	void SetScore();//�t�B�b�V���f�[�^��individualValue��ݒ肷��B
	void SetTimeUntilEscape(float timeUntilEscape);//�����ł̎��Ԃ̐ݒ�B
	bool TimeCount();
	//void SetIndividualValue();//�̒l��ݒ�
	void ShouldFishChange();//����ς��邩�ǂ����B
	void ShouldFishChangeTrue();
	void ShouldFishChangeFalse();
	void SetisSelectedTrue();
	void SetisSelectedFalse();
	bool GetShouldFishChange();
	void SetBaseScore(float baseScore);//��ɂȂ�X�R�A�B
	FishData& GetFishData();

	SpriteRender& GetUI();
	bool m_shouldFishChange = false;//����ς���ׂ����H
	bool m_isSelected=false;//�I�΂�Ă��邩�ǂ����B�i���Ă���Œ����ǂ����j
	float m_baseScore ;//��ɂȂ�X�R�A�B
	float m_timeUntilEscape;
	float m_time = 0.0f;
	SpriteRender m_ui;
	PositionSelection* m_positionSelection;
	FishData m_fishData;

};

