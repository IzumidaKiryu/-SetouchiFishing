#include "stdafx.h"
#include "PositionSelection.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "FishManager.h"
#include "PlayFishing.h"
#include "TimeLimitUI.h"
#include <Time.h>
#include <string>

PositionSelection::PositionSelection()
{
	srand(time(NULL));

	m_stopwatch.Start();

	for (int i = 0; i < 6; i++)
	{
		objectName[i] = new char[fishManagerObjectName[i].size() + 1];
	}
	//§ŒÀŠÔ‚ÌUI‚ğì‚éB
	m_timeLimitUI= NewGO<TimeLimitUI>(0, "timelimitUI");

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
	gameCamera->m_toCameraPos.Set(0.0f, 750.0f, -250.0f);

	//UI‚ÌêŠ‚ğŒˆ‚ß‚éB
	SetFishDisplayPosition();

	//UI‚ğİ’è‚·‚éB
	SetUI();

	for (int i = 0; i < 6; i++) {

		//ƒtƒBƒbƒVƒ…ƒ}ƒl[ƒWƒƒ[‚É‚Â‚¯‚éƒIƒuƒWƒFƒNƒgƒl[ƒ€‚Ìİ’èB
			std::char_traits<char>::copy(objectName[i], fishManagerObjectName[i].c_str(), fishManagerObjectName[i].size() + 1);
		
			//ƒtƒBƒbƒVƒ…ƒ}ƒl[ƒWƒƒ[‚Ì¶¬B
		m_fishManager[i] = NewGO<FishManager>(0, objectName[i]);
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
	//ŠÔ‚ğ‚Í‚©‚éB
	Timer();
	m_timeLimitUI->DisplayTimeLimitUI(m_int_time);//ƒ^ƒCƒ€ƒŠƒ~ƒbƒg‚ğ•\¦‚·‚éB

	if (m_shouldPartiallyDeactivate == false) {//ƒAƒNƒeƒBƒu‚©‚Ç‚¤‚©”»’f‚·‚éB
		SetFishUI();
		if (g_pad[0]->IsTrigger(enButtonA)) {//Aƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚½‚çB
			ChangeSceneToPlayFishing();//ƒvƒŒƒCƒtƒBƒbƒVƒ“ƒOƒV[ƒ“‚É•Ï‚¦‚éB
		}
	}
	/*for (int i = 0; i < 6; i++) {
		m_timelimit=m_fishManager[i]->m_randum;
	}*/
}

void PositionSelection::Render(RenderContext& rc)
{
	m_timeLimitUI->GetClockUI().Draw(rc);
	m_timeLimitUI->GetOnesPlacUI().Draw(rc);
	m_timeLimitUI->GetTensPlacUI().Draw(rc);
	m_timeLimitUI->GetHundredsPlacUI().Draw(rc);
	if (m_shouldPartiallyDeactivate==false) {
		for (int i = 0; i < 6; i++) {
			m_fishDisplayInside[i].Draw(rc);
			m_fishDisplayOutside[i].Draw(rc);
			m_fishUI[i]->Draw(rc);
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

		//‹›‚ğ•\¦‚·‚éƒfƒBƒXƒvƒŒƒC‚ÌŠO‘¤

		m_fishDisplayOutside[i].Init("Assets/modelData/fish_display_ui_outside.DDS", 150, 150);
		m_fishDisplayOutside[i].SetPivot(Vector2(0.5f, 0.5f));
		m_fishDisplayOutside[i].SetPosition(m_fishDisplayPosition[i]);
		m_fishDisplayOutside[i].SetScale(Vector3{ 1.0f, 1.0f, 1.0f });

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

/// <summary>
/// ƒV[ƒ“‚ğƒvƒŒƒCƒtƒBƒbƒVƒ“ƒO‚É•Ï‚¦‚éB
/// </summary>
void PositionSelection::ChangeSceneToPlayFishing()
{
	SetisDisplayingFalse();
	
	// ï¿½Cï¿½ï¿½ï¿½Xï¿½^ï¿½ï¿½ï¿½Xï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½|ï¿½Wï¿½Vï¿½ï¿½ï¿½ï¿½ï¿½İ’è¨ï¿½ï¿½ï¿½ï¿½ï¿½İ’ï¿½(ï¿½ï¿½ï¿½ï¿½Åƒ|ï¿½Wï¿½Vï¿½ï¿½ï¿½ï¿½ï¿½İ’ï¿½Ìï¿½ï¿½ï¿½gï¿½ï¿½ï¿½Ä‚ï¿½ï¿½ï¿½)
	m_playFishing = NewGO<PlayFishing>(0, "playFishing");
	SelectPositionA();
	m_playFishing->Init();

	SetDeactivate();
}

bool PositionSelection::GetisDisplaying()
{
	return m_is_displaying;
}

void PositionSelection::SetDeactivate()
{
	//ƒvƒŒƒCƒ„[‚ğ”ñƒAƒNƒeƒBƒu‚É‚·‚éB
	player->Deactivate();
	//ƒQ[ƒ€ƒJƒƒ‰‚ğ”ñƒAƒNƒeƒBƒu‚É‚·‚éB
	gameCamera->Deactivate();
	//”wŒi‚ğ”ñƒAƒNƒeƒBƒu‚É‚·‚éB
	backGround->Deactivate();
	//Ui‚ğ•\¦‚µ‚È‚¢B
	m_shouldPartiallyDeactivate = true;
}

void PositionSelection::SetActivate()
{
	//ƒvƒŒƒCƒ„[‚ğƒAƒNƒeƒBƒu‚É‚·‚éB
	player->Activate();
	//ƒQ[ƒ€ƒJƒƒ‰‚ğƒAƒNƒeƒBƒu‚É‚·‚éB
	gameCamera->Activate();
	//”wŒi‚ğƒAƒNƒeƒBƒu‚É‚·‚éB
	backGround->Activate();
	//UI‚ğ•\¦‚·‚éB
	m_shouldPartiallyDeactivate = false;
}

/// <summary>
/// §ŒÀŠÔ‚ğ‚Í‚©‚éB
/// </summary>
void PositionSelection::Timer()
{
	m_double_time= m_timelimit-m_stopwatch.GetElapsed();
	m_stopwatch.Stop();
	m_int_time = m_double_time;
	if (m_double_time<=0)
	{
		m_is_time_up = true;
		m_stopwatch.Stop();

	}
}

void PositionSelection::SetFishUI()
{
	for (int i = 0; i < 6; i++) {
		m_fishUI[i] = m_fishManager[i]->m_ui;
	}
	SetFishUIPosition();

}


void PositionSelection::SetFishUIPosition()
{
	for (int i = 0; i < 6; i++) {
		m_fishUI[i]->SetPivot(Vector2(0.5f, 0.5f));
		m_fishUI[i]->SetPosition(m_fishDisplayPosition[i]);
		m_fishUI[i]->SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
		m_fishUI[i]->Update();
		//ƒtƒBƒbƒVƒ…ƒfƒBƒXƒvƒŒƒC‚ÌUI‚ÍƒtƒBƒbƒVƒ…ƒfƒBƒXƒvƒŒƒC‚Ì‰º‚É•\¦‚µ‚½‚¢‚Ì‚Å‚±‚±‚ÅƒAƒbƒvƒf[ƒg‚·‚éB
		m_fishDisplayOutside[i].Update();
		m_fishDisplayInside[i].Update();
	}
}

void PositionSelection::FishChange()
{
	for (int i = 0; i < 6; i++) {
		if (m_fishManager[i]->GetShouldFishChange()) {
			DeleteGO(m_fishManager[i]);

			//ƒtƒBƒbƒVƒ…ƒ}ƒl[ƒWƒƒ[‚Ì¶¬B
			m_fishManager[i] = NewGO<FishManager>(0, objectName[i]);
		}

	}
}

void PositionSelection::SelectPosition()
{
	if (true)
	{

	}
}

void PositionSelection::SelectPositionA()
{
	m_playFishing->SetFishManagerObjectName("positionA");
}

void PositionSelection::SelectPositionB()
{
	m_playFishing->SetFishManagerObjectName("positionB");
}

void PositionSelection::SelectPositionC()
{
	m_playFishing->SetFishManagerObjectName("positionC");
}

void PositionSelection::SelectPositionD()
{
	m_playFishing->SetFishManagerObjectName("positionD");
}

void PositionSelection::SelectPositionE()
{
	m_playFishing->SetFishManagerObjectName("positionE");
}

void PositionSelection::SelectPositionF()
{
	m_playFishing->SetFishManagerObjectName("positionF");
}

void PositionSelection::SetTotalValue(float individualValue)
{
	m_totalValue += individualValue;
}



//void PositionSelection::fishingPositionA_SetFish()
//{
//
//}
