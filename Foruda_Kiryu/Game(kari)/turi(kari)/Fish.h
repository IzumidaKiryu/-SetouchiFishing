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
	//�̒l��ݒ�

	float IndividualValue;//�̒l
	float m_time = 0.0f;
	float m_timeUntilEscape;
	float m_individualValue;

};

