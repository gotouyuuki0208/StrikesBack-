//==========================
// 
// 殴る敵[hitenemy.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "hitenemy.h"
#include "manager.h"
#include "model.h"
#include "hpgauge3D.h"

//静的メンバ初期化
const int CHitEnemy::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CHitEnemy::CHitEnemy(int nPriority):
CWeakEnemy(nPriority),//基底コンストラクタ
m_HPGauge(nullptr)//HPゲージの情報
{

}

//==========================
//デストラクタ
//==========================
CHitEnemy::~CHitEnemy()
{

}

//==========================
//初期化処理
//==========================
HRESULT CHitEnemy::Init()
{
	//初期設定
	CWeakEnemy::Init();

	//殴り攻撃に設定
	//SetAttackState(ATTACK_STATE::ATTACK);

	//HPゲージを生成
	m_HPGauge = CHPGauge3D::Create(D3DXVECTOR3(GetParts(2)->GetMtxWorld()._41, GetParts(2)->GetMtxWorld()._42, GetParts(2)->GetMtxWorld()._43),
		D3DXVECTOR3(20.0f, 3.0f, 0.0f),
		GetLife());
	
	return S_OK;
}

//==========================
//終了処理
//==========================
void  CHitEnemy::Uninit()
{
	//終了処理
	CWeakEnemy::Uninit();

	if (m_HPGauge != nullptr)
	{
		m_HPGauge->Uninit();
		m_HPGauge = nullptr;
	}
}

//==========================
//更新処理
//==========================
void CHitEnemy::Update()
{
	if (CManager::GetInstance()->GetDebug()->GetEdit())
	{
		return;
	}

	//更新処理
	CWeakEnemy::Update();

	if (m_HPGauge != nullptr)
	{
		m_HPGauge->SetHP(GetLife());
		m_HPGauge->SetPos({ GetParts(2)->GetMtxWorld()._41, GetParts(2)->GetMtxWorld()._42 + 20.0f, GetParts(2)->GetMtxWorld()._43 });
	}
}

//==========================
//描画処理
//==========================
void CHitEnemy::Draw()
{
	//描画処理
	CWeakEnemy::Draw();
}

//==========================
//オブジェクト生成
//==========================
CHitEnemy* CHitEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int wave)
{
	//インスタンス生成
	CHitEnemy* pHitEnemy = DBG_NEW CHitEnemy;

	//位置の設定
	pHitEnemy->SetPos(pos);

	//寿命の設定
	pHitEnemy->SetLife(5);

	//ファイルを読み込む
	pHitEnemy->LoadFile("data\\MOTION\\enemy.txt", scale);

	//行動するウェーブを設定
	pHitEnemy->SetActionWave(wave);

	//初期化処理
	pHitEnemy->Init();

	//pHitEnemy->SetDamageCor();

	//半径の設定
	pHitEnemy->SetRadius(15.0f);

	//種類の設定
	pHitEnemy->SetType(TYPE::ENEMY);

	//敵の種類を設定
	pHitEnemy->SetEnemyType(ENEMY_TYPE::HitEnemy);

	//当たり判定を可視化
	//pHitEnemy->SetVisual();

	return pHitEnemy;
}