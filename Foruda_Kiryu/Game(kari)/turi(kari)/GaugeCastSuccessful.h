#pragma once
class GaugeCastSuccessful :public IGameObject
{
public:
		float m_position = 0.0f;//�L���X�g�����Q�[�W�̃|�W�V����
		float m_scale = 0.0f;//�L���X�g�����Q�[�W�̃X�P�[��
		float m_rangelower = 0.0f;//�����Q�[�W�̓����蔻��͈̔́i�����j�B
		float m_rangeMax = 0.0f;//�����Q�[�W�̓����蔻��͈̔́i����j�B
		float m_heightFirstGaugeCastSuccessful = 10.0f;//�����Q�[�W�̍ŏ��̉����B

		void Init(float position,float scale);
		void SetRange();
		bool hitTest(float arrowPosition);//�����蔻��
		SpriteRender m_gaugeCastSuccessfulSprite;//�L���X�g�����Q�[�W�B
};

