#include "stdafx.h"
#include "GaugeCastSuccessful.h"

void GaugeCastSuccessful::Init(float position, float scale)
{
	m_position = position;
	m_scale = scale;
	SetRange();
	m_gaugeCastSuccessfulSprite.Init("Assets/modelData/cast_successful.DDS", 90, m_heightFirstGaugeCastSuccessful);
	m_gaugeCastSuccessfulSprite.SetPivot(Vector2(0.0f, 1.0f));
	m_gaugeCastSuccessfulSprite.SetPosition(Vector3(500.0f,m_position, 0.0f));//êŠ‚ğ”½‰fB
	m_gaugeCastSuccessfulSprite.SetScale(Vector3{ 1.0f,m_scale, 1.0f });//‘å‚«‚³‚ğ”½‰fB
	m_gaugeCastSuccessfulSprite.Update();
}

void GaugeCastSuccessful::SetRange()
{
	float rangeHeight = m_scale * m_heightFirstGaugeCastSuccessful;//¬Œ÷ƒQ[ƒW‚Ìc•iŠ|‚¯‚½ƒXƒP[ƒ‹~‰Šúİ’è‚Ìc•j
	m_rangelower =m_position - rangeHeight;
	m_rangeMax =m_position;
}

bool GaugeCastSuccessful::hitTest(float arrowPosition)
{
	if (m_rangelower <= arrowPosition && m_rangeMax >= arrowPosition) {

		DeleteGO(this);
		return true;
	}
	else {
		return false;
	}
}
