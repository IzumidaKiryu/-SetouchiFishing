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
	SetCamera(GetPlayerPos() + Vector3{ 0.0f,100.0f,100.0f }, GetFishModelPos());
}

void WaitForFishState::ComingFish()
{
	if (m_sum_current_fish_range_and_max_range_rate > m_sum_current_float_range_max_range_rate) {
		m_sum_current_fish_range_and_max_range_rate -= 0.001;
		if (m_sum_current_fish_range_and_max_range_rate - m_sum_current_float_range_max_range_rate <= 0) {
			Success();
			return;
		}
	}

	if (m_sum_current_fish_range_and_max_range_rate < m_sum_current_float_range_max_range_rate) {
		m_sum_current_fish_range_and_max_range_rate += 0.001;
		if (m_sum_current_float_range_max_range_rate - m_sum_current_fish_range_and_max_range_rate <= 0) {
			Success();
			return;
		}
	}

	SumFishModelPosition(m_sum_current_fish_range_and_max_range_rate);
	SetFish();
}
