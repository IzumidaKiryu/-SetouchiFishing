#include "k2EngineLowPreCompile.h"
#include "FontRender.h"

void nsK2EngineLow::FontRender::OnDraw(RenderContext& rc)
{
	if (m_text == nullptr)
	{
		return;
	}
	m_font.Begin(rc);
	m_font.Draw(m_text, Vector2(m_position.x, m_position.y), m_color, m_rotation, m_scale, m_pivot);
	m_font.End(rc);
}

void nsK2EngineLow::FontRender::Draw(RenderContext& rc)
{
	g_renderingEngine->AddFontRenderObject(this);

}
