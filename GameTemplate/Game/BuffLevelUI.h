#pragma once
#include"BuffManager.h"
class BuffManager;
class BuffLevelUI: public IGameObject
{
public:
	BuffLevelUI();
	~BuffLevelUI();
	bool Init();
	bool Start();
	void Update();
	void SetUI();
	void DisplayUI(RenderContext& rc);

private:

	const float m_fontScale = 2.0f;// フォントのスケール
	const Vector3 m_buffLevelUIPos = { -750.0f,0.0f,0.0f };// バフレベルUIの位置
	SpriteRender m_buffLevelUI;
	BuffManager* m_buffManager=nullptr;
	std::map<BuffType, FontRender> m_buffLevelFont;// バフレベルのフォント
	std::map<BuffType, Vector3> m_fontPos;// バフレベルのフォントの位置

private:

	/// <summary>
	/// バフレベルに応じてフォントを更新する。
	/// </summary>
	/// <param name="type">バフの種類</param>
	void UpdateFont(BuffType type);

	/// <summary>
	/// フォントの初期位置を設定する。
	/// </summary>
	void SetInitFontPos();

};

