#include "stdafx.h"
#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
}

ScoreManager::~ScoreManager()
{
}
/// <summary>
/// 指定されたキャラクターと魚の種類に対するスコアをセットする。
/// </summary>
/// <param name="score">スコア</param>
/// <param name="fishType">魚の種類</param>
/// <param name="characterType">キャラクターの種類</param>
void ScoreManager::SetScore(float score, FishType fishType, CharacterType characterType)
{
	//各魚の匹数に+1。
	m_fishCount[characterType][fishType]++;

	//各魚の合計スコアに加算。
	m_fishTotalScore[characterType][fishType] += score;

	//合計スコアに加算。
	m_totalScore += score;
}
/// <summary>
/// 指定されたキャラクターと魚の種類に対する合計スコアを返す。
/// </summary>
/// <param name="fishType">魚の種類</param>
/// <param name="characterType">キャラクターの種類</param>
/// <returns>魚のスコアの合計</returns>
float ScoreManager::GetFishTotalScore(FishType fishType, CharacterType characterType)
{
	return m_fishCount[characterType][fishType];
}

/// <summary>
/// 全種類の魚の合計スコアを渡す。
/// </summary>
/// <returns>全種の魚の合計スコア</returns>
float ScoreManager::GetTotalScore()
{
	return m_totalScore;
}
