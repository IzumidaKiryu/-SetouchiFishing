#pragma once
class PositionSelection;
class StealPositionBar :public IGameObject
{
public:
	StealPositionBar();
	void DisplayUI(RenderContext& rc);
	void Update();
	void SetBarLength();
	void AddStealPoint(float addPoint);//ポイントを足す。

	SpriteRender m_stealPositionBarInsideUI;
	SpriteRender m_stealPositionBarOutsideUI;
	SpriteRender m_stealPositionGaugeUI;

	float m_stealPoint=0.0f;
	float m_bar_Length=0.0f;
	float m_point_increase_in_frame=0.01;
	int m_piling_up_bar_count;//たまっているバーの本数。
	float m_bar_rate;//バーの割合。
	const float m_bar_one_minutes_point=100;//バー一本分のポイント
	const float m_max_barLength=0.95;//バーの最大の長さ。


	PositionSelection* positionSelection;
};

