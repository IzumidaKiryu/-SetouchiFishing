#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround() = default;
BackGround::~BackGround() = default;

bool BackGround::Init()
{
    //船モデルの初期化
    m_ship.SetPosition(m_shipPosition);
    m_ship.SetScale(Vector3{ 1.5f, 1.5f, 1.5f });
    m_ship.Init("Assets/modelData/2DShip/2DNewShip.tkm", nullptr, 0, enModelUpAxisZ, false, true);

    //衝突判定用ヒットボックス
    m_hitBox.SetPosition(m_shipPosition);
    m_hitBox.SetScale(Vector3{ 1.5f, 1.5f, 1.5f });
    m_hitBox.Init("Assets/modelData/2DShipFloor.tkm", nullptr, 0, enModelUpAxisZ, false, true);
    m_hitBox.Update();
    physicsStaticObject.CreateFromModel(m_hitBox.GetModel(), m_hitBox.GetModel().GetWorldMatrix());

    //海のモデル
    m_sea.SetPosition(Vector3{ 1.0f, 1.0f, 1.0f }); // 必要なら定数化
    m_sea.SetScale(Vector3{ 10.0f, 10.0f, 10.0f });
    m_sea.Init("Assets/modelData/sea_Kari.tkm", nullptr, 0, enModelUpAxisZ, false, true);
    m_sea.Update();

    //島モデル
    m_isrand.Init("Assets/modelData/stage/shima.tkm", nullptr, 0, enModelUpAxisZ, true, false);
    m_isrand.SetPosition(m_israndPosition);
    m_isrand.SetScale(Vector3(10.0f, 10.0f, 10.0f));
    m_isrand.Update();

    return true;
}

void BackGround::Update()
{
    UpdateFloating();
    m_ship.SetPosition(m_floating + m_shipPosition);
    m_ship.Update();
}

void BackGround::UpdateFloating()
{
    // 浮きの動きの調整用定数（すべてコンパイル時に決定）
    constexpr float FLOATING_SPEED = 0.05f;        // 時間の進み方（更新スピード）
    constexpr float FLOATING_HEIGHT = 5.0f;        // 上下方向の振れ幅
    constexpr float FLOATING_WIDTH = 10.0f;        // 左右方向の振れ幅
    constexpr float HORIZONTAL_PHASE = 0.7f;       // 左右揺れの周期ずれ（自然さを出す）

    // 経過時間を加算
    floatingTime += FLOATING_SPEED;

    // 上下方向の揺れ（y軸）
    m_floating.y = std::cos(floatingTime) * FLOATING_HEIGHT;
    // 左右方向の揺れ（x軸）
    m_floating.x = std::cos(floatingTime * HORIZONTAL_PHASE) * FLOATING_WIDTH;
}

Vector3 BackGround::GetShipPosition() const
{
    return m_shipPosition;
}

void BackGround::Render(RenderContext& rc)
{
    m_sea.Draw(rc);
    m_ship.Draw(rc);
    m_isrand.Draw(rc);
}
