//==========================
// 
// 武器敵[weaponenemy.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "weaponenemy.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int CWeaponEnemy::PRIORITY = 1;//描画順
const int CWeaponEnemy::NEAR_ACTION_COUNT = 240;//プレイヤーが近いときにする行動の長さ
const int CWeaponEnemy::ATTACKFINISH_COOLTIME = 300;//攻撃終了後のクールタイム
const float CWeaponEnemy::DUSH_DISTANCE = 10.0f;//走る距離
const float CWeaponEnemy::WALK_DISTANCE = 5.0f;//歩く距離
const float CWeaponEnemy::DUSH_SPEED = 3.5f;//走る速さ
const float CWeaponEnemy::WALK_SPEED = 2.0f;//歩く速さ

//==========================
//コンストラクタ
//==========================
CWeaponEnemy::CWeaponEnemy(int nPriority):
CEnemy(nPriority),//基底コンストラクタ
m_HPGauge(nullptr),//HPゲージの情報
m_NearAction(false),//プレイヤーが近くにいるときの行動判定
m_NearCount(0),//プレイヤーが近くにいるときの行動カウント
Attackable(true),//攻撃可能判定
m_AttackCoolTime(0),//攻撃のクールタイム
m_StackIdx(0),//TOPの位置
m_Attack(false),//攻撃判定
m_Angle(0.0f),//向き
m_FlameCount(0)//攻撃のフレームカウント

{
	SetComboList();//コンボリストの生成
}

//==========================
//デストラクタ
//==========================
CWeaponEnemy::~CWeaponEnemy()
{

}

//==========================
//初期化処理
//==========================
HRESULT CWeaponEnemy::Init()
{
	//初期設定
	CEnemy::Init();

	//殴り攻撃に設定
	//SetAttackState(ATTACK_STATE::WEAPONATTACK);

	//HPゲージを生成
	//m_HPGauge = CHPGauge3D::Create(D3DXVECTOR3(GetParts(2)->GetMtxWorld()._41, GetParts(2)->GetMtxWorld()._42, GetParts(2)->GetMtxWorld()._43), D3DXVECTOR3(20.0f, 3.0f, 0.0f), GetLife());

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CWeaponEnemy::Uninit()
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
void CWeaponEnemy::Update()
{
	if (CManager::GetInstance()->GetDebug()->GetEdit())
	{
		return;
	}

	if (CManager::GetInstance()->GetGameManager()->GetPlayGame())
	{//遊べない状態
		return;
	}

	if (!CManager::GetInstance()->GetDebug()->GetPlayerTest())
	{
		Count();//カウントする

		if (!GetDamage())
		{//ダメージ状態じゃない時

			MoveAction();//移動時の行動を設定
			Move();//移動処理
			Attack();//攻撃処理
		}
	}

	//更新処理
	CEnemy::Update();

	//HPゲージの設定
	if (m_HPGauge != nullptr)
	{
		m_HPGauge->SetHP(GetLife());
		m_HPGauge->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + 70.0f, GetPos().z));
	}
}

//==========================
//描画処理
//==========================
void CWeaponEnemy::Draw()
{
	//描画処理
	CEnemy::Draw();
}

//==========================
//オブジェクト生成
//==========================
CWeaponEnemy* CWeaponEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CModel* pModel = CManager::GetInstance()->GetModel();
	int modelnum = pModel->Regist("data\\MODEL\\bigweapon.x");

	//インスタンス生成
	CWeaponEnemy* pWeaponEnemy = DBG_NEW CWeaponEnemy;

	//位置の設定
	pWeaponEnemy->SetPos(pos);

	//初期化処理
	pWeaponEnemy->Init();

	//寿命の設定
	pWeaponEnemy->SetLife(10);

	//ファイルを読み込む
	pWeaponEnemy->LoadFile("data\\MOTION\\motion_player_15.txt", scale);

	//武器をパーツとして生成
	pWeaponEnemy->SetParts(D3DXVECTOR3(10.0f, -2.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), pWeaponEnemy->GetParts(5), modelnum, D3DXVECTOR3(1.5f, 1.5f, 1.5f));

	//半径の設定
	pWeaponEnemy->SetRadius(15.0f);

	//種類の設定
	pWeaponEnemy->SetType(TYPE::ENEMY);

	//敵の種類を設定
	pWeaponEnemy->SetEnemyType(ENEMY_TYPE::WeaponEnemy);

	return pWeaponEnemy;
}

//==========================
//プレイヤーへの移動
//==========================
void CWeaponEnemy::Move()
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
void CWeaponEnemy::Count()
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

	if (!Attackable)
	{//攻撃できないとき

		m_AttackCoolTime--;

		if (m_AttackCoolTime <= 0)
		{
			Attackable = true;
			m_AttackCoolTime = 0;
		}
	}
}

//==========================
//移動時の行動
//==========================
void CWeaponEnemy::MoveAction()
{
	if ((GetState() != STATE::NEUTRAL)
		|| m_AttackCoolTime > (ATTACKFINISH_COOLTIME - 60))
	{//通常状態以外の時または攻撃終了してから1秒たっていない時終了
		return;
	}

	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	if (!pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * DUSH_DISTANCE))
	{//プレイヤーの半径の10倍の距離より遠い

		//移動値を設定
		SetMove(D3DXVECTOR3(sinf(m_Angle) * DUSH_SPEED, 0.0f, cosf(m_Angle) * DUSH_SPEED));

		//モーションを設定
		SetMotion(MOTION_TYPE::DUSH);

		if (m_NearAction)
		{
			m_NearAction = false;
			m_NearCount = 0;
		}
	}
	else if (!pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * WALK_DISTANCE))
	{//プレイヤーの半径の5倍の距離より遠い

		//移動値を設定
		SetMove(D3DXVECTOR3(sinf(m_Angle) * WALK_SPEED, 0.0f, cosf(m_Angle) * WALK_SPEED));

		//モーションを設定
		SetMotion(MOTION_TYPE::MOVE);
		if (m_NearAction)
		{
			m_NearAction = false;
			m_NearCount = 0;
		}
	}
	else if (Attackable
		&& !pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() + 2.0f))
	{//攻撃可能かつプレイヤーより遠い

		//移動値を設定
		SetMove(D3DXVECTOR3(sinf(m_Angle) * WALK_SPEED, 0.0f, cosf(m_Angle) * WALK_SPEED));

		//モーションを設定
		SetMotion(MOTION_TYPE::MOVE);
	}
	else if (Attackable
		&& pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() + 2.0f))
	{
		SetState(STATE::ATTACK);
	}

	//向きの設定
	ChangeDirection();
}

//==========================
//攻撃処理
//==========================
void CWeaponEnemy::Attack()
{
	if (GetState() != STATE::ATTACK || !Attackable)
	{//攻撃状態以外の時または攻撃不可状態の時終了
		return;
	}

	if (GetOldMotion() == GetMotion())
	{//前回のモーションと今のモーションが同じ

		//今のモーションを保存
		SetOldMotion(GetMotion());

		//攻撃モーションに変更
		SetMotion(Pop());
	}

	if (m_FlameCount >= 10)
	{
		ColisionWeaponAttack();
	}

	m_FlameCount++;

	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	bool Colision = pCollision->Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), 17.0f);
	if (m_FlameCount >= 26 && Colision && m_StackIdx > 0)
	{//フレーム数が24以上かつプレイヤーが近いかつコンボできる

		SetMotion(Pop());//モーションを再生
		m_FlameCount = 0;//カウントしてたフレーム数をリセット
		m_Attack = false;//攻撃していない状態の戻す
		ChangeDirection();//向きを変える
	}
	else if (m_FlameCount >= 24 && (!Colision || m_StackIdx <= 0))
	{//プレイヤーが遠いまたはコンボできない

		SetOldMotion(GetMotion());//今のモーションを保存
		SetState(STATE::NEUTRAL);//通常状態に変更
		//SetAttackState(ATTACK_STATE::ATTACK);
		if (GetPartsExistence(15))
		{
			SetMotion(MOTION_TYPE::WEAPONNEUTRAL);//武器持ち待機状態に変更
		}

		ResetStak();//コンボのスタックをリセット
		m_FlameCount = 0;//フレーム数をリセット
		m_Attack = false;//攻撃判定をリセット
		Attackable = false;//攻撃不可状態
		m_AttackCoolTime = ATTACKFINISH_COOLTIME;
	}
}

//==========================
//攻撃の当たり判定
//==========================
void CWeaponEnemy::ColisionWeaponAttack()
{
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	bool Colision = pCollision->Sphere(D3DXVECTOR3(GetPartsMtx(15)._41, GetPartsMtx(15)._42, GetPartsMtx(15)._43),
		D3DXVECTOR3(GetPlayer()->GetPartsMtx(1)._41, GetPlayer()->GetPartsMtx(1)._42, GetPlayer()->GetPartsMtx(1)._43),
		30.0f,
		30.0f);

	if (Colision && !m_Attack)
	{
		//GetPlayer()->Damage();
		m_Attack = true;

		if (m_StackIdx <= 0)
		{
			GetPlayer()->DamegeBlow(GetPos());
		}
	}
}

//==========================
//向きの変更
//==========================
float CWeaponEnemy::ChangeDirection()
{
	if (GetMotion() != MOTION_TYPE::GUARD)
	{
		//進む角度を計算
		m_Angle = atan2f(GetPlayer()->GetPos().x - GetPos().x, GetPlayer()->GetPos().z - GetPos().z);

		//向きを設定
		SetRot(D3DXVECTOR3(GetRot().x, m_Angle + D3DX_PI, GetRot().z));
	}

	return m_Angle;
}

//==========================
//スタックの情報を戻す
//==========================
void CWeaponEnemy::ResetStak()
{
	m_StackIdx = 0;
	for (int i = 2; i >= 0; i--)
	{
		Push(m_ComboList[i]);
	}
}

//==========================
//コンボリストの生成
//==========================
void CWeaponEnemy::SetComboList()
{
	m_ComboList[0] = MOTION_TYPE::WEAPONATTACK;
	m_ComboList[1] = MOTION_TYPE::WEAPONATTACK2;
	m_ComboList[2] = MOTION_TYPE::WEAPONATTACK3;

	ResetStak();//スタックのリセット
}

//==========================
//データの追加
//==========================
void CWeaponEnemy::Push(MOTION_TYPE motion)
{
	if (m_StackIdx < 3)
	{
		m_ComboStack[m_StackIdx++] = motion;
	}
}

//==========================
//データの取り出し
//==========================
CWeaponEnemy::MOTION_TYPE CWeaponEnemy::Pop()
{
	if (m_StackIdx <= 0)
	{
		if (GetPartsExistence(15))
		{
			return MOTION_TYPE::WEAPONNEUTRAL;
		}
		else
		{
			return MOTION_TYPE::NEUTRAL;
		}
	}

	return m_ComboStack[--m_StackIdx];

}
