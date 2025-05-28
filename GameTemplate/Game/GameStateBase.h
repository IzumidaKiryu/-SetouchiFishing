#pragma once
#include< memory >
class GameStateBase : public IGameObject
{
public:
	GameStateBase() = default;
	virtual ~GameStateBase() = default;
	bool Start()override;

	void Render(RenderContext& rc)override;
	virtual bool ShouldChangeState() = 0; // 状態を変更すべきかどうかを決定する純粋仮想関数
	virtual void Update() final;//派生クラスではいじれない
	virtual void OnUpdate()=0;//毎フレームの処理はここに書く。
	virtual void Enter() final;	//派生クラスからはいじれない
	virtual void OnEnter()=0; 
	virtual void Exit() final;
	virtual void OnExit()=0;
	virtual void SetNextState(std::unique_ptr<GameStateBase> nextState)final; // 次の状態を設定する純粋仮想関数
	virtual  std::unique_ptr<GameStateBase> NextState() final; // 次の状態に遷移するための純粋仮想関数


	void SetActive(bool flag);
	bool am_isActive = false; // 状態がアクティブかどうかを示すフラグ

	std::unique_ptr<GameStateBase> m_nextState = nullptr; // 次の状態を保持するポインタ
};

