#include "stdafx.h"
#include "FishSlot.h"
#include"PositionSelection.h"
#include"InGameState.h"
#include"FishManager.h"
#include "Enemy.h"
#include"StealPositionBar.h"


FishSlot::FishSlot()
{
}

FishSlot::~FishSlot()
{
}

void FishSlot::Update()
{
	SetFishUI();

	//魚の逃げる時間を合わすUIのサイズ更新。
	UpdateFishTimeUntilEscapeUISize();
}

bool FishSlot::Start()
{
	FindGameObjects();
	return true;
}

void FishSlot::FindGameObjects()
{
	m_positionSelection = FindGO<PositionSelection>("positionSelection");
	m_inGameState = FindGO<InGameState>("inGameState");
	m_fishManager = FindGO<FishManager>("fishManager");
	m_enemy = FindGO<Enemy>("enemy");
	m_stealPositionBar = FindGO<StealPositionBar>("stealPositionBar");
}

void FishSlot::ThiscClassInit()
{
	SetFishUI();	
	InitUI();
}

void FishSlot::InitUI()
{

	SetFishDisplayPosition();

	for (int i = 0; i < 6; i++) {

		SetTexture(i);
		SetPivot(i);
		SetPosition(i);
		SetScale(i);
		UIUpdate(i);

	}


}

void FishSlot::SetTexture(int i)
{
	m_fishDisplayInside[i].Init("Assets/modelData/fish_display_ui_inside.DDS", 130, 130);
	m_fishDisplayOutside[i].Init("Assets/modelData/fish_display_ui_outside.DDS", 130, 130);
	m_selectedFrameUI[i].Init("Assets/modelData/fish_display_ui_outside_selection.DDS", 130, 130);
	m_enemySelectedFrameUI[i].Init("Assets/modelData/castGauge_Outside.DDS", 130, 130);
	m_fishTimeUntilEscapeUI[i].Init("Assets/modelData/fishTimeUntilEscapeUI.DDS", 130, 130);

}

void FishSlot::SetPivot(int i)
{
	m_fishDisplayInside[i].SetPivot(Vector2(0.5f, 0.5f));
	m_fishDisplayOutside[i].SetPivot(Vector2(0.5f, 0.5f));
	m_selectedFrameUI[i].SetPivot(Vector2(0.5f, 0.5f));
	m_enemySelectedFrameUI[i].SetPivot(Vector2(0.5f, 0.5f));
	m_fishTimeUntilEscapeUI[i].SetPivot(Vector2(0.5f, 1.0f));
	m_fishUI[i]->SetPivot(Vector2(0.5f, 0.5f));

}

void FishSlot::SetPosition(int i)
{
	m_fishDisplayInside[i].SetPosition(m_fishDisplayPosition[i]);
	m_fishDisplayOutside[i].SetPosition(m_fishDisplayPosition[i]);
	m_selectedFrameUI[i].SetPosition(m_fishDisplayPosition[i]);
	m_enemySelectedFrameUI[i].SetPosition(m_fishDisplayPosition[i]);
	m_fishTimeUntilEscapeUI[i].SetPosition(m_fishDisplayPosition[i] + Vector3{ 0.0,130 / 2.0f,0.0f });
	m_fishUI[i]->SetPosition(m_fishDisplayPosition[i]);
}

void FishSlot::SetScale(int i)
{
	m_fishDisplayInside[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_fishDisplayOutside[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_selectedFrameUI[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_enemySelectedFrameUI[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_fishTimeUntilEscapeUI[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_fishUI[i]->SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
}

void FishSlot::UIUpdate(int i)
{
	m_fishDisplayInside[i].Update();
	m_fishDisplayOutside[i].Update();
	m_selectedFrameUI[i].Update();
	m_enemySelectedFrameUI[i].Update();
	m_fishTimeUntilEscapeUI[i].Update();
	m_fishUI[i]->Update();

}

void FishSlot::SetFishUI()
{
	m_inGameState = FindGO<InGameState>("inGameState");

	for (int i = 0; i < 6; i++) {
		m_fishUI[i] = &m_inGameState->GetFishUI(i);
		SetFishUIPosition(i, m_fishDisplayPosition[i]);
	}
}

void FishSlot::SetFishUIPosition(int i, Vector3 pos)
{
	m_fishUI[i]->SetPosition(pos);
	m_fishUI[i]->Update();

}



void FishSlot::SetFishDisplayPosition()
{

	const float m_startX= -350;
	const float m_intervalX = 350;
	const float topRowY = 230.0f;
	const float bottomRowY = -300.0f;
	const int columns = 3;


	for (int i = 0; i < 6; i++) {

		int columnIndex = i % columns;

		if (i < columns) {
			m_fishDisplayPosition[i] = { m_startX + m_intervalX * (columnIndex), 230.0f, 0.0f };
		}
		if (2 < i) {
			m_fishDisplayPosition[i] = { m_startX + m_intervalX * (i - 3), -300.0f, 0.0f };
		}
	}
}

void FishSlot::ShowUI(RenderContext& rc)
{

	for (int i = 0; i < 6; i++) {

		m_fishDisplayInside[i].Draw(rc);

		if (static_cast<int>(m_enemy->GetTargetFishinArea()) != i) //敵のターゲットエリア以外のところに表示。
		{
			if (!m_stealPositionBar->GetIsStealLockActive(static_cast<Area>(i))) {//敵から奪ったエリアの場合は表示しない。
				m_fishTimeUntilEscapeUI[i].Draw(rc);
			}
		}

		if (m_selectedFrameUI[i].GetActive() == true)
		{
			m_selectedFrameUI[i].Draw(rc);
		}
		if (m_fishDisplayOutside[i].GetActive()==true) 
		{
		m_fishDisplayOutside[i].Draw(rc);
		}
		
		if (m_enemySelectedFrameUI[i].GetActive() == true)
		{
			m_enemySelectedFrameUI[i].Draw(rc);
		}
		m_fishUI[i]->Draw(rc);
	}
}

void FishSlot::SetActiveFishDisplayOutside(int index,bool isActive)
{
	if (index != static_cast<int>(Area::INITIALSTATE)) {
		m_fishDisplayOutside[index].SetActive(isActive);
	}
}

void FishSlot::SetActiveSelectedFrameUI(int index, bool isActive)
{
	if (index != static_cast<int>(Area::INITIALSTATE)) {
		m_selectedFrameUI[index].SetActive(isActive);
	}
}

void FishSlot::SetActiveEnemySelectedFrameUI(int index, bool isActive)
{
	if (index != static_cast<int>(Area::INITIALSTATE)) {
		m_enemySelectedFrameUI[index].SetActive(isActive);
	}
}

//void FishSlot::ShowOnlySelectedFrameUI(int index)
//{
//	SetActiveFishDisplayOutside(index, false);
//	SetActiveEnemySelectedFrameUI(index, false);
//	SetActiveSelectedFrameUI(index, true);
//
//
//}
void FishSlot::UpdateSlotFrameVisibility(int playerPos, int enemyPos)
{
	for (int index = 0; index < 6; index++) 
	{
		if (playerPos == enemyPos) {
			if (index == enemyPos) {
				SetActiveFishDisplayOutside(index, false);
				SetActiveEnemySelectedFrameUI(index, true);
				SetActiveSelectedFrameUI(index, false);
			}
	
		}
		if (playerPos != enemyPos) {
			if (index == playerPos) {
				SetActiveFishDisplayOutside(index, false);
				SetActiveEnemySelectedFrameUI(index, false);
				SetActiveSelectedFrameUI(index, true);
			}
			if (index == enemyPos) {
				SetActiveFishDisplayOutside(index, false);
				SetActiveEnemySelectedFrameUI(index, true);
				SetActiveSelectedFrameUI(index, false);
			}
		}
		if (index != playerPos && index != enemyPos)
		{
			SetActiveFishDisplayOutside(index, true);
			SetActiveEnemySelectedFrameUI(index, false);
			SetActiveSelectedFrameUI(index, false);
		}
	}
	
}

void FishSlot::ShowOnlyFishDisplayOutsideUI(int index)
{
	SetActiveFishDisplayOutside(index, true);
	SetActiveEnemySelectedFrameUI(index, false);
	SetActiveSelectedFrameUI(index, false);
}
void FishSlot::ShowOnlyEnemySelectedFrameUI(int index)
{
	SetActiveFishDisplayOutside(index, false);
	SetActiveEnemySelectedFrameUI(index, true);
	SetActiveSelectedFrameUI(index, false);

}

void FishSlot::DisableAllFrameUI()
{
	for (int index = 0; index < 6; index++) {
		SetActiveFishDisplayOutside(index, false);
		SetActiveEnemySelectedFrameUI(index, false);
		SetActiveSelectedFrameUI(index, false);

	}

}

void FishSlot::UpdateFishTimeUntilEscapeUISize()
{
	for (int i = 0; i < 6; i++) {
		//float scale = m_positionSelection->GerFishTimeRatio(i);
		float scale = m_inGameState->GerFishTimeRatio(i);
			m_fishTimeUntilEscapeUI[i].SetScale(Vector3{ 1.0,scale, 1.0f });
			m_fishTimeUntilEscapeUI[i].Update();
	}

}

