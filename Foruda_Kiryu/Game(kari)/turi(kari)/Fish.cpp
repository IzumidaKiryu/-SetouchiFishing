#include "stdafx.h"
#include "Fish.h"

Fish::Fish()
{

}

Fish::~Fish()
{
}

void Fish::Update()
{
}

void Fish::SetIndividualValue(float individualValue)//�̒l��ݒ肷��B
{
	m_individualValue = individualValue;
}

void Fish::SetTimeUntilEscape(float timeUntilEscape)//������܂ł̎��Ԃ�ݒ肷��B
{
	m_timeUntilEscape = timeUntilEscape;
}
