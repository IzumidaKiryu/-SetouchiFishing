#pragma once
class Fish : public IGameObject
{
public:

	Fish();
	~Fish();
	//�X�V�����B
	void Update();
	void SetIndividualValue(float individualValue);
	void SetTimeUntilEscape(float timeUntilEscape);
	bool TimeCount();
	//void SetIndividualValue();//�̒l��ݒ�

	float m_individualValue;//�̒l
	float m_timeUntilEscape;
	float m_time = 0.0f;

};

