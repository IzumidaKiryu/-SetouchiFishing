#pragma once
class PlayFishing;
class PositionSelection;
class ScoreDisplay : public IGameObject
{
public:

	ScoreDisplay();
	~ScoreDisplay();

	void Update();
	void SetScore();
	void SetOnesPlace();
	void SetTensPlace();
	void SetHundredsPlace();
	void SetOnesPlaceUI();
	void SetTensPlaceUI();
	void SetHundredsPlaceUI();
	void ScoreUI();
	void Render(RenderContext& rc);


	int m_onesPlace;
	int m_tensPlace;
	int m_hundredsPlace;
	int m_prevTime;
	int m_score;

	Vector3 m_hundredsPlaceUIPos = { 490.0f - 270.0f + 200.0f,100.0f,0.0f };
	Vector3 m_tensPlaceUIPos = { 410.0f - 270.0f + 200.0f,100.0f,0.0f };
	Vector3 m_onesPlaceUIPos = { 330.0f - 270.0f + 200.00f,100.0f,0.0f };

	PlayFishing* m_playFishing;
	SpriteRender m_onesPlaceUI;
	SpriteRender m_tensPlaceUI;
	SpriteRender m_hundredsPlaceUI;
	SpriteRender m_scoreDisplay;
	PositionSelection* m_positionSelection;

};

