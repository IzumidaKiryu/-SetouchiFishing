#pragma once
class Fish : public IGameObject
{
public:

	Fish();
	~Fish();
	//�X�V�����B
	void Update();
	void SetIndividualValue(float individualValue);//�̒l��ݒ�B
	void SetTimeUntilEscape(float timeUntilEscape);//������܂ł̎��Ԃ�ݒ�B
	float m_individualValue;//�̒l�B
	float m_timeUntilEscape;//����������܂ł̎��ԁi0�ɂȂ�Ɠ�����j�B
};

