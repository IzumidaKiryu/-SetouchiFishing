#include "stdafx.h"
#include "GameStateBase.h"
#include< memory >

bool GameStateBase::Start()
{
	Deactivate();
		return true;
}

void GameStateBase::Render(RenderContext& rc)
{
}

GameStateBase* GameStateBase::ChangeState()
{
	SetActive(false);
	GameStateBase* nextState = FindGO<GameStateBase>(m_nextStateName);
	if (nextState) {
		nextState->SetActive(true);
	}
	//K2_ASSERT(nextState != nullptr, "持つからない");
	return nextState;
}
void GameStateBase::SetNextName(const char* nextStateName)
{
	m_nextStateName = nextStateName;
}

void GameStateBase::Update()
{
		if (m_isActive) {
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
	 Activate();
	OnEnter();
}

void GameStateBase::Exit()
{
	Deactivate();
	OnExit();
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
	m_isActive = flag;
}
