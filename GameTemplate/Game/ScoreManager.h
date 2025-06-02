#pragma once
#include"Fish.h"

enum class CharacterType {
	Player,
	enemy
};
class ScoreManager :public IGameObject
{
public:
	ScoreManager();
	~ScoreManager();

	void SetScore(float score,FishType fishType, CharacterType characterType);

	float GetFishTotalScore(FishType fishType, CharacterType characterType);
	float GetTotalScore();
private:
	std::map<CharacterType,std::map<FishType, int>> m_fishCount;//各魚の獲得数
	std::map<CharacterType, std::map<FishType, float>>  m_fishTotalScore;//各魚の合計スコア（その瞬間の）
	float m_totalScore = 0.0f;
};

