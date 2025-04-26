#pragma once
//�����Ȃ��E�������Ă����狛�͓����悤�ƒ�R���Ă���A���������Ă������R���Ȃ��B

#include "SceneFightFish.h"


class GetRotation;
class PlayFishing;
class FishingRodHP;
class RodFloatMove;
class TensionGauge :public IGameObject
{
public:

	TensionGauge();
	~TensionGauge();
	void Update();
	void Set_signs_of_Fish_UI();
	void RightAndLeftManagement();
	void SetFishUI_Position(float position);
	//void AnnounceChangeFishState();


	float m_signs_of_Fish_UI_Position = 0.0f;//���e�̃|�W�V�����iX���j
	float m_barBottom = -473.0f;//�Q�[�W���[�B
	float m_barTop = 473.0f;//�Q�[�W�̏�[�B
	float m_bar_length = std::abs(m_barTop) + std::abs(m_barBottom);//�o�[�̒����B(abs()�͐�Βl�����߂�֐��B)
	bool m_should_change_fish_to_anger_ui = true;
	Vector3 fish3DPos;

	FIshState m_fishState;
	SpriteRender m_tensionGaugeInside;
	SpriteRender m_tensionGaugeOutside;
	SpriteRender m_signs_of_Fish;//���e
	PlayFishing* m_playFishing;
	SceneFightFish* m_sceneFightFish;

	void Render(RenderContext& rc);
};