#pragma once
class PositionSelection;
class InGameState;
class FishManager;
class Enemy;
class StealPositionBar;
class FishSlot : public IGameObject
{
public:
	FishSlot();
	~FishSlot();
	void Update();
	bool Start();
	void FindGameObjects();
	void ThiscClassInit();
	void InitUI();
	void SetTexture(int i);
	void SetPivot(int i);
	void SetPosition(int i);
	void SetScale(int i);
	void UIUpdate(int i);

	void SetFishUI();
	void SetFishUIPosition(int i, Vector3 pos);
	//void Render(RenderContext& rc);

	void SetFishDisplayPosition();

	void ShowUI(RenderContext& rc);
	
	void SetActiveFishDisplayOutside(int index, bool isActive);
	void SetActiveSelectedFrameUI(int index, bool isActive);
	void SetActiveEnemySelectedFrameUI(int index, bool isActive);

	/*void ShowOnlySelectedFrameUI(int index);*/
	void UpdateSlotFrameVisibility(int playerPos, int enemyPos);
	void ShowOnlyFishDisplayOutsideUI(int index);
	void ShowOnlyEnemySelectedFrameUI(int index);
	void DisableAllFrameUI();

	void UpdateFishTimeUntilEscapeUISize();




	Vector3 m_fishDisplayPosition[6];
	SpriteRender m_fishCommonDisplayInside[6];
	SpriteRender m_fishRareDisplayInside[6];
	SpriteRender m_fishSuperRareDisplayInside[6];
	SpriteRender m_fishDisplayOutside[6];

	SpriteRender m_selectedFrameUI[6];
	SpriteRender m_enemySelectedFrameUI[6];
	SpriteRender* m_fishUI[6];
	SpriteRender m_fishTimeUntilEscapeUI[6];
	SpriteRender m_staminabuffUI[6];
	SpriteRender m_takeOverBuffUI[6];
	SpriteRender m_pullPowerBuffUI[6];
	PositionSelection* m_positionSelection=nullptr;
	InGameState* m_inGameState=nullptr;
	FishManager* m_fishManager[6];
	Enemy* m_enemy=nullptr;
	StealPositionBar* m_stealPositionBar=nullptr;
};

