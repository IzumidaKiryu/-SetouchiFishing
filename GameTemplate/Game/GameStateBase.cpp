#include "stdafx.h"
#include "GameStateBase.h"
#include< memory >

void GameStateBase::Render(RenderContext& rc)
{
}

void GameStateBase::Update()
{
	if (am_isActive) {
		OnUpdate();
	}
}

void GameStateBase::OnUpdate()
{
	// 毎フレームの処理はここに書く。
// 具体的なゲーム状態に応じてオーバーライドされることを期待しています。


}

void GameStateBase::Enter()
{
	am_isActive = true;
	OnEnter();
}

void GameStateBase::Exit()
{
	am_isActive = false;
	OnExit();
}


void GameStateBase::SetNextState(std::unique_ptr<GameStateBase> nextState)
{
	m_nextState = std::move(nextState);
}

std::unique_ptr<GameStateBase> GameStateBase::NextState()
{

	if (!m_nextState) {
		return nullptr; // 次の状態が設定されていない場合はnullptrを返す
	}
	return move(m_nextState);
}

void GameStateBase::SetActive(bool flag)
{
	am_isActive = flag;
}
