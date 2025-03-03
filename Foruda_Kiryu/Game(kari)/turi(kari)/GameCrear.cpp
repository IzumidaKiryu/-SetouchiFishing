#include "stdafx.h"
#include "GameCrear.h"
#include"Title.h"

GameClear::GameClear()
{
	//ゲームクリアの画像を読み込む。
	spriteRender.Init("Assets//modeleData.dds", 1920.0f, 1080.0f);
}

GameClear::~GameClear()
{

}

//更新処理
void GameClear::Update()
{
	//Aボタンが押されたら。
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//タイトルのオブジェクトを作る。
		NewGO<Title>(0, "title");
			//自信を削除する。
			DeleteGO(this);
	}
}
//描画処理。
void GameClear::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}