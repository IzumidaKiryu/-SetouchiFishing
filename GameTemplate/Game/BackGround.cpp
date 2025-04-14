#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
	DeleteGO(this);
}

bool BackGround::Start()
{
	m_modelRender.Init("Assets/material/stera.tkm");
	return true;
}

void BackGround::Update()
{
	m_modelRender.Update();
}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
