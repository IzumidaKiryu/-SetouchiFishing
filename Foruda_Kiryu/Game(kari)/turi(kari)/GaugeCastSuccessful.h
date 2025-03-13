#pragma once
class GaugeCastSuccessful :public IGameObject
{
public:
		float m_position = 0.0f;//キャスト成功ゲージのポジション
		float m_scale = 0.0f;//キャスト成功ゲージのスケール
		float m_rangelower = 0.0f;//成功ゲージの当たり判定の範囲（下限）。
		float m_rangeMax = 0.0f;//成功ゲージの当たり判定の範囲（上限）。
		float m_heightFirstGaugeCastSuccessful = 10.0f;//成功ゲージの最初の横幅。

		void Init(float position,float scale);
		void SetRange();
		bool hitTest(float arrowPosition);//当たり判定
		SpriteRender m_gaugeCastSuccessfulSprite;//キャスト成功ゲージ。
};

