#include "stdafx.h"
#include "WaitForFishState.h"

WaitForFishState::WaitForFishState()
{

}

WaitForFishState::~WaitForFishState()
{
}

void WaitForFishState::Update()
{
	ComingFish();
	SumRodFloatPosition(Floating());
	SetFloat();

}

void WaitForFishState::ComingFish()
{
	if (m_current_fish_range_and_max_range_rate > m_current_float_range_max_range_rate) {
		m_current_fish_range_and_max_range_rate -= 0.001;
		if (m_current_fish_range_and_max_range_rate - m_current_float_range_max_range_rate <= 0) {
			Success();
		}
	}

	if (m_current_fish_range_and_max_range_rate < m_current_float_range_max_range_rate) {
		m_current_fish_range_and_max_range_rate += 0.001;
		if (m_current_float_range_max_range_rate - m_current_fish_range_and_max_range_rate <= 0) {
			Success();
		}
	}

	SumFishModelPosition(m_current_fish_range_and_max_range_rate);
	SetFish();
}
