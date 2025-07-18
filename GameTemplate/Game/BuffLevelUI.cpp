#include "stdafx.h"
#include "BuffLevelUI.h"
#include"BuffManager.h"

BuffLevelUI::BuffLevelUI()
{
}

BuffLevelUI::~BuffLevelUI()
{
}

bool BuffLevelUI::Init()
{
	SetUI();
	SetInitFontPos();
	return true;
}

void BuffLevelUI::SetInitFontPos()
{
	m_fontPos[BuffType::StealBoostBuff] = Vector3{ -650.0f,120.0f,0.0f };
	m_fontPos[BuffType::PullStrengthBuff] = Vector3{-650.0f,-30.0f,0.0f};
	m_fontPos[BuffType::StaminaRegenBuff] = Vector3{ -650.0f,-180.0f,0.0f};
}

bool BuffLevelUI::Start()
{
	m_buffManager = FindGO<BuffManager>("buffManager");
	return true;
}

void BuffLevelUI::Update()
{
	UpdateFont(BuffType::PullStrengthBuff);
	UpdateFont(BuffType::StaminaRegenBuff);
	UpdateFont(BuffType::StealBoostBuff);
}

void BuffLevelUI::SetUI()
{
	m_buffLevelUI.Init("Assets/modelData/BuffLevel.DDS", 300, 500);
	m_buffLevelUI.SetPivot(Vector2(0.0f, 0.5f));
	m_buffLevelUI.SetPosition(m_buffLevelUIPos);
	m_buffLevelUI.SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
	m_buffLevelUI.Update();
}

void BuffLevelUI::DisplayUI(RenderContext& rc)
{
	m_buffLevelUI.Draw(rc);
	m_buffLevelFont[BuffType::PullStrengthBuff].Draw(rc);
	m_buffLevelFont[BuffType::StaminaRegenBuff].Draw(rc);
	m_buffLevelFont[BuffType::StealBoostBuff].Draw(rc);
}

void BuffLevelUI::UpdateFont(BuffType type)
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%d", int(1+m_buffManager->GetBuffCount(type)));

	//表示するテキストを設定。
	m_buffLevelFont[type].SetText(wcsbuf);
	//フォントの位置を設定。
	m_buffLevelFont[type].SetPosition(m_fontPos[type]);
	//フォントの大きさを設定。
	m_buffLevelFont[type].SetScale(m_fontScale);
	//フォントの色を設定。
	m_buffLevelFont[type].SetColor({ 1.0f,1.0f,1.0f,1.0f });

}
