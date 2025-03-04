#pragma once

class Game:public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	ModelRender m_modelRender;
	enum EnAnimationClip {		//�A�j���[�V�����B
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};
	AnimationClip m_animationClips[enAnimationClip_Num];
};

