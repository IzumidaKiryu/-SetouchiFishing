#pragma once
class Fish : public IGameObject
{
public:

	Fish();
	~Fish();
	//更新処理。
	void Update();
	void SetIndividualValue();//個体値を設定

	float IndividualValue;//個体値

};

