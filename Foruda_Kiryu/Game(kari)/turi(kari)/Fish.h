#pragma once
class Fish : public IGameObject
{
public:

	Fish();
	~Fish();
	//�X�V�����B
	void Update();
	void SetIndividualValue();//�̒l��ݒ�

	float IndividualValue;//�̒l

};

