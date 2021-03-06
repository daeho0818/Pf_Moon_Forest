#include "DXUT.h"
#include "RendererC.h"

RendererC::RendererC(Object* object) : Component(object)
{
}

RendererC::~RendererC()
{
}

void RendererC::Init()
{
}

void RendererC::Update()
{
}

void RendererC::Render()
{
	if (m_image && !is_ui)
	{
		RENDER->CenterRender(m_image, m_transform->m_position,
			m_transform->m_localScale, D3DXToRadian(m_transform->m_rotationZ),
			false, m_color);
	}
}

void RendererC::UIRender()
{
	if (m_image && is_ui)
	{
		RENDER->CenterRender(m_image, m_transform->m_position,
			m_transform->m_localScale, D3DXToRadian(m_transform->m_rotationZ),
			true, m_color);
	}
}

void RendererC::Release()
{
}

void RendererC::SetRenderer(Image* image, D3DXCOLOR color, bool is_ui)
{
	m_image = image;
	m_color = color;
	this->is_ui = is_ui;
}

void RendererC::SetImage(Image* image)
{
	m_image = image;
}

Image* RendererC::GetImage()
{
	return m_image;
}

void RendererC::SetColor(D3DXCOLOR color)
{
	m_color = color;
}

D3DXCOLOR RendererC::GetColor()
{
	return m_color;
}
