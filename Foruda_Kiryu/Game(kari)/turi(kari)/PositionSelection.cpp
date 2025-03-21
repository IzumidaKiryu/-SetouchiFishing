#include "stdafx.h"
#include "PositionSelection.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "FishManager.h"
#include "PlayFishing.h"

PositionSelection::PositionSelection()
{
	srand(time(NULL));
	//ƒvƒŒƒCƒ„[‚ÌƒIƒuƒWƒFƒNƒg‚ğì‚éB
	player = NewGO<Player>(0, "player");

	//ƒQ[ƒ€ƒJƒƒ‰‚ÌƒIƒuƒWƒFƒNƒg‚ğì‚éB
	gameCamera = NewGO<GameCamera>(0, "gamecamera");

	//”wŒi‚ÌƒIƒuƒWƒFƒNƒg‚ğì‚éB
	backGround = NewGO<BackGround>(0);
	//ƒQ[ƒ€’†‚ÌBGM‚ğ“Ç‚İ‚ŞB
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/gamebgm.wav");
	//ƒQ[ƒ€’†‚ÌBGM‚ğÄ¶‚·‚éB
	gameBGM = NewGO<SoundSource>(0);
	/*gameBGM->Init(1);
	gameBGM->Play(true);*/
	gameCamera->m_toCameraPos.Set(0.0f, 1250.0f, -250.0f);

	//UI‚ÌêŠ‚ğŒˆ‚ß‚éB
	SetFishDisplayPosition();

	//UI‚ğİ’è‚·‚éB
	SetUI();

	for (int i = 0; i < 6; i++) {
		m_fishManager[i] = NewGO<FishManager>(0,"fishManager");
	}

}

PositionSelection::~PositionSelection()
{
	//ƒvƒŒƒCƒ„[‚ğíœ‚·‚éB
	DeleteGO(player);
	//ƒQ[ƒ€ƒJƒƒ‰‚ğíœ‚·‚éB
	DeleteGO(gameCamera);
	//ƒQ[ƒ€’†‚ÌBGM‚ğíœ‚·‚éB
	DeleteGO(gameCamera);
	//”wŒi‚ğíœ‚·‚éB
	DeleteGO(backGround);
}

void PositionSelection::Update()
{
	if (m_shouldPartiallyDeactivate == false) {//ï¿½Aï¿½Nï¿½eï¿½Bï¿½uï¿½ï¿½ï¿½Ç‚ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½fï¿½ï¿½ï¿½ï¿½B
		if (g_pad[0]->IsTrigger(enButtonA)) {//Aï¿½{ï¿½^ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ê‚½ï¿½ï¿½B
			ChangeSceneToPlayFishing();//ï¿½vï¿½ï¿½ï¿½Cï¿½tï¿½Bï¿½bï¿½Vï¿½ï¿½ï¿½Oï¿½Vï¿½[ï¿½ï¿½ï¿½É•Ï‚ï¿½ï¿½ï¿½B
		}
	}
}

void PositionSelection::Render(RenderContext& rc)
{
	if (m_shouldPartiallyDeactivate==false) {
		for (int i = 0; i < 6; i++) {
			m_fishDisplayInside[i].Draw(rc);
			m_fishDisplayOutside[i].Draw(rc);
		}
	}
}


void PositionSelection::SetUI()
{
	for (int i = 0; i < 6; i++) {

		//‹›‚ğ•\¦‚·‚éƒfƒBƒXƒvƒŒƒC‚Ì“à‘¤

		m_fishDisplayInside[i].Init("Assets/modelData/fish_display_ui_inside.DDS", 150, 150);
		m_fishDisplayInside[i].SetPivot(Vector2(0.5f, 0.5f));
		m_fishDisplayInside[i].SetPosition(m_fishDisplayPosition[i]);
		m_fishDisplayInside[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
		m_fishDisplayInside[i].Update();

		//‹›‚ğ•\¦‚·‚éƒfƒBƒXƒvƒŒƒC‚ÌŠO‘¤

		m_fishDisplayOutside[i].Init("Assets/modelData/fish_display_ui_outside.DDS", 150, 150);
		m_fishDisplayOutside[i].SetPivot(Vector2(0.5f, 0.5f));
		m_fishDisplayOutside[i].SetPosition(m_fishDisplayPosition[i]);
		m_fishDisplayOutside[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
		m_fishDisplayOutside[i].Update();

	}
}

void PositionSelection::SetFishDisplayPosition()
{
	for (int i = 0; i < 6; i++) {
		if (i < 3) {
			m_fishDisplayPosition[i] = { m_fishDisplayPositionXcriteria+m_fishDisplayPositionXinterval*(i), 200.0f, 0.0f };
		}
		if (2 < i) {
			m_fishDisplayPosition[i] = { m_fishDisplayPositionXcriteria + m_fishDisplayPositionXinterval * (i-3), -200.0f, 0.0f };
		}
	}
}

void PositionSelection::SetisDisplayingTrue()
{
	m_is_displaying=true;
}

void PositionSelection::SetisDisplayingFalse()
{
	m_is_displaying = false;
}

void PositionSelection::ChangeSceneToPlayFishing()
{
	SetisDisplayingFalse();
	m_playFishing = NewGO<PlayFishing>(0, "playFishing");

	//ƒvƒŒƒCƒ„[‚ğíœ‚·‚éB
	DeleteGO(player);
	//ƒQ[ƒ€ƒJƒƒ‰‚ğíœ‚·‚éB
	DeleteGO(gameCamera);
	//ƒQ[ƒ€’†‚ÌBGM‚ğíœ‚·‚éB
	DeleteGO(gameCamera);
	//”wŒi‚ğíœ‚·‚éB
	DeleteGO(backGround);
}

bool PositionSelection::GetisDisplaying()
{
	return m_is_displaying;
}

void PositionSelection::SetDeactivate()
{
	//ï¿½vï¿½ï¿½ï¿½Cï¿½ï¿½ï¿½[ï¿½ï¿½ï¿½Aï¿½Nï¿½eï¿½Bï¿½uï¿½É‚ï¿½ï¿½ï¿½B
	player->Deactivate();
	//ï¿½Qï¿½[ï¿½ï¿½ï¿½Jï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Aï¿½Nï¿½eï¿½Bï¿½uï¿½É‚ï¿½ï¿½ï¿½B
	gameCamera->Deactivate();
	//ï¿½wï¿½iï¿½ï¿½ï¿½Aï¿½Nï¿½eï¿½Bï¿½uï¿½É‚ï¿½ï¿½ï¿½B
	backGround->Deactivate();
	//Uiï¿½ï¿½\ï¿½ï¿½ï¿½ï¿½ï¿½È‚ï¿½ï¿½B
	m_shouldPartiallyDeactivate = true;
}

void PositionSelection::SetActivate()
{
	//ï¿½vï¿½ï¿½ï¿½Cï¿½ï¿½ï¿½[ï¿½ï¿½Aï¿½Nï¿½eï¿½Bï¿½uï¿½É‚ï¿½ï¿½ï¿½B
	player->Activate();
	//ï¿½Qï¿½[ï¿½ï¿½ï¿½Jï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Aï¿½Nï¿½eï¿½Bï¿½uï¿½É‚ï¿½ï¿½ï¿½B
	gameCamera->Activate();
	//ï¿½wï¿½iï¿½ï¿½Aï¿½Nï¿½eï¿½Bï¿½uï¿½É‚ï¿½ï¿½ï¿½B
	backGround->Activate();
	//UIï¿½ï¿½\ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½B
	m_shouldPartiallyDeactivate = false;
}


//void PositionSelection::fishingPositionA_SetFish()
//{
//
//}
