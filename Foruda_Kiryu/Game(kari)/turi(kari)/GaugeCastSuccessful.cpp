#include "stdafx.h"
#include "GaugeCastSuccessful.h"
GaugeCastSuccessful::GaugeCastSuccessful()
{
}
GaugeCastSuccessful::~GaugeCastSuccessful()
{
}
void GaugeCastSuccessful::Init(float position, float scale)
{
	m_position = position;
	m_scale = scale;
	SetRange();
	m_gaugeCastSuccessfulSprite.Init("Assets/modelData/cast_successful.DDS", 90, m_heightFirstGaugeCastSuccessful);
	m_gaugeCastSuccessfulSprite.SetPivot(Vector2(0.0f, 1.0f));
	m_gaugeCastSuccessfulSprite.SetPosition(Vector3(500.0f, m_position, 0.0f));//?????f?B
	m_gaugeCastSuccessfulSprite.SetScale(Vector3{ 1.0f,m_scale, 1.0f });//???????f?B
	m_gaugeCastSuccessfulSprite.Update();
}

void GaugeCastSuccessful::SetRange()
{
	float rangeHeight = m_scale * m_heightFirstGaugeCastSuccessful;//?????Q?[?W??c???i?|?????X?P?[???~????????c???j
	m_rangelower = m_position - rangeHeight;
	m_rangeMax = m_position;
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