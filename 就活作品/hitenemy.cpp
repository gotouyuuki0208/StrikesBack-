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

//静的メンバ初期化
const int CHitEnemy::PRIORITY = 1;//描画順
const int CHitEnemy::NEAR_ACTION_COUNT = 240;//プレイヤーが近いときにする行動の長さ
const int CHitEnemy::ATTACKFINISH_COOLTIME = 300;//攻撃終了後のクールタイム

//==========================
//コンストラクタ
//==========================
CHitEnemy::CHitEnemy(int nPriority):
CEnemy(nPriority),//基底コンストラクタ
m_HPGauge(nullptr),//HPゲージの情報
m_NearAction(false),//プレイヤーが近くにいるときの行動判定
m_NearCount(0),//プレイヤーが近くにいるときの行動カウント
m_AttackCoolTime(0),//攻撃のクールタイム
m_Attack(false),//攻撃判定
m_FlameCount(0)//攻撃のフレームカウント
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
	CEnemy::Init();

	//殴り攻撃に設定
	//SetAttackState(ATTACK_STATE::ATTACK);

	//HPゲージを生成
	m_HPGauge = CHPGauge3D::Create(D3DXVECTOR3(GetParts(2)->GetMtxWorld()._41, GetParts(2)->GetMtxWorld()._42, GetParts(2)->GetMtxWorld()._43), D3DXVECTOR3(20.0f, 3.0f, 0.0f), GetLife());

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CHitEnemy::Uninit()
{
	//終了処理
	CEnemy::Uninit();

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
	CEnemy::Update();
}

//==========================
//描画処理
//==========================
void CHitEnemy::Draw()
{
	//描画処理
	CEnemy::Draw();
}

//==========================
//オブジェクト生成
//==========================
CHitEnemy* CHitEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CHitEnemy* pHitEnemy = DBG_NEW CHitEnemy;

	//位置の設定
	pHitEnemy->SetPos(pos);

	//寿命の設定
	pHitEnemy->SetLife(5);

	//ファイルを読み込む
	pHitEnemy->LoadFile("data\\MOTION\\enemy.txt", scale);

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

//==========================
//プレイヤーへの移動
//==========================
void CHitEnemy::Move()
{
	if (GetState() != STATE::NEUTRAL)
	{//攻撃状態の時終了
		return;
	}

	//前回の位置を保存
	SetPosOld(GetPos());

	SetMove(D3DXVECTOR3(GetMove().x += (0 - GetMove().x) * 0.25f,
		GetMove().y,
		GetMove().z += (0 - GetMove().z) * 0.25f));

	//位置を変更
	SetPos(GetPos() + GetMove());

	//モーションを設定
	SetOldMotion(GetMotion());
}

//==========================
//カウントする
//==========================
void CHitEnemy::Count()
{
	if (m_NearAction)
	{//プレイヤーが近づいたときの行動をしている
		m_NearCount++;
		if (m_NearCount >= NEAR_ACTION_COUNT
			&& GetPlayer()->GetState() != CPlayer::STATE::ATTACK)
		{
			m_NearAction = false;
			m_NearCount = 0;
			SetState(STATE::NEUTRAL);
		}
	}

	//if (!Attackable)
	//{//攻撃できないとき

	//	m_AttackCoolTime--;

	//	if (m_AttackCoolTime <= 0)
	//	{
	//		Attackable = true;
	//		m_AttackCoolTime = 0;
	//	}
	//}
}

//==========================
//攻撃処理
//==========================
void CHitEnemy::Attack()
{
	//if (GetState() != STATE::ATTACK || !Attackable)
	//{//攻撃状態以外の時または攻撃不可状態の時終了
	//	return;
	//}

	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	if (GetOldMotion() == GetMotion())
	{//前回のモーションと今のモーションが同じ

		//今のモーションを保存
		SetOldMotion(GetMotion());
	}

	if (m_FlameCount >= 10)
	{
		ColisionHitAttack();
	}

	m_FlameCount++;

	bool Colision = pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), 17.0f);
	if (m_FlameCount >= 26 && Colision )
	{//フレーム数が24以上かつプレイヤーが近いかつコンボできる

		m_FlameCount = 0;//カウントしてたフレーム数をリセット
		m_Attack = false;//攻撃していない状態の戻す
		ChangeDirection();//向きを変える
	}
	else if (m_FlameCount >= 24 && !Colision)
	{//プレイヤーが遠いまたはコンボできない

		SetOldMotion(GetMotion());//今のモーションを保存
		SetState(STATE::NEUTRAL);//通常状態に変更
		//SetAttackState(ATTACK_STATE::ATTACK);
		if (GetPartsExistence(15))
		{
			SetMotion(MOTION_TYPE::WEAPONNEUTRAL);//武器持ち待機状態に変更
		}

		m_FlameCount = 0;//フレーム数をリセット
		m_Attack = false;//攻撃判定をリセット
		//Attackable = false;//攻撃不可状態
		m_AttackCoolTime = ATTACKFINISH_COOLTIME;
	}
}

//==========================
//攻撃の当たり判定
//==========================
void CHitEnemy::ColisionHitAttack()
{
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	bool Colision = pCollision->Sphere(D3DXVECTOR3(GetPartsMtx(5)._41, GetPartsMtx(5)._42, GetPartsMtx(5)._43),
		D3DXVECTOR3(GetPlayer()->GetPartsMtx(1)._41, GetPlayer()->GetPartsMtx(1)._42, GetPlayer()->GetPartsMtx(1)._43),
		GetRadius(),
		GetPlayer()->GetRadius());

	if (Colision && !m_Attack)
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

		GetPlayer()->hit(GetPos(),1);
		m_Attack = true;
	}
}

