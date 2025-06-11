#include "stdafx.h"
#include "BuffManager.h"

BuffManager::BuffManager()
{
    InitSetBuffEffect();
}

BuffManager::~BuffManager()
{

}

void BuffManager::ApplyBuffEffect(const std::map<BuffType, float>& buffEffect ,const BuffType buffType)
{
    //指定されたタイプのバフを探す。
    auto it = buffEffect.find(buffType);

    if (it != buffEffect.end()) {//登録されてなければ計算しない。
        switch (buffType)
        {
        case BuffType::StealBoostBuff:
            m_buffEffect[buffType] += it->second;
            break;
        case BuffType::PullStrengthBuff:
            m_buffEffect[buffType] += it->second;
            break;
        case BuffType::StaminaRegenBuff:
            m_buffEffect[buffType] += it->second;
            break;
        case BuffType::RandumBuff:
            break;
        case BuffType::NoBuff:
            break;
        default:
            break;
        }
    }
}

float  BuffManager::GetBuffEffect(BuffType buffType) const
{
    auto it = m_buffEffect.find(buffType);
    if (it != m_buffEffect.end()) {
        return it->second;
    }
    return 0.0f;  // デフォルト値を返す（見つからなければ）
}

float BuffManager::GetTotalStealBoostBuff()
{
    return m_buffEffect[BuffType::StealBoostBuff];
}

float BuffManager::GetTotalPullStrengthBuff()
{
    return m_buffEffect[BuffType::PullStrengthBuff];
}

float BuffManager::GetTotalStaminaRegenBuff()
{
    return m_buffEffect[BuffType::StaminaRegenBuff];
}

void BuffManager::InitSetBuffEffect()
{
    m_buffEffect[BuffType::PullStrengthBuff] = 0.0f;
    m_buffEffect[BuffType::StaminaRegenBuff] = 0.0f;
    m_buffEffect[BuffType::StaminaRegenBuff] = 0.0f;
    m_buffEffect[BuffType::RandumBuff] = 0.0f;
    m_buffEffect[BuffType::NoBuff] = 0.0f;
}
