#pragma once
class PlayFishing;
class ScoreDisplay : public IGameObject
{
public:

	ScoreDisplay();
	~ScoreDisplay();

	void ScoreUI(float score);
	PlayFishing* m_playFishing;
};

