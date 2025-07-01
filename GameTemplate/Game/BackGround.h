#pragma once
#include "sound/SoundSource.h"

/// <summary>
/// 海・船などの背景オブジェクトを管理するクラス
/// </summary>
class BackGround : public IGameObject
{
public:
    BackGround();
    ~BackGround();

    bool Init();
    void Update();
    void Render(RenderContext& rc);

    /// <summary>
    /// 船のワールド上の初期座標を取得する
    /// </summary>
    Vector3 GetShipPosition() const;

private:
    /// <summary>
    /// 船の浮き沈みアニメーションを更新
    /// </summary>
    void UpdateFloating();

    // 浮きアニメーション用
    float floatingTime = 0.0f;
    Vector3 m_floating = Vector3::Zero;

    // 初期位置（const）
    const Vector3 m_shipPosition{ 0.0f, -100.0f, -400.0f };
    const Vector3 m_israndPosition{ -500.0f, 0.0f, 4000.0f };

    // モデル
    ModelRender m_ship;
    ModelRender m_sea;
    ModelRender m_isrand;
    ModelRender m_hitBox;

    // 当たり判定
    PhysicsStaticObject physicsStaticObject;
};
