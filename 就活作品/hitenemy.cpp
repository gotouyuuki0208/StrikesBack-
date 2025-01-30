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
const float CHitEnemy::DUSH_DISTANCE = 10.0f;//走る距離
const float CHitEnemy::WALK_DISTANCE = 5.0f;//歩く距離
const float CHitEnemy::DUSH_SPEED = 3.5f;//走る速さ
const float CHitEnemy::WALK_SPEED = 2.0f;//歩く速さ
//==========================
//コンストラクタ
//==========================
CHitEnemy::CHitEnemy(int nPriority):
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
	SetComboList();//コンボリストの設定
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
	SetAttackState(ATTACK_STATE::ATTACK);

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

	if (CManager::GetInstance()->GetTutorial()->GetTutorial())
	{//操作説明表示中
		return;
	}

	//行動可能か判定
	judgeMovable();

	if (GetMovable())
	{//行動可能なとき
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

		//HPゲージの設定
		if (m_HPGauge != nullptr)
		{
			m_HPGauge->SetHP(GetLife());
			m_HPGauge->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + 70.0f, GetPos().z));
			m_HPGauge->DrawGauge();
		}
	}
	else
	{//行動できないとき

		Patrol();//移動地点を巡回

		if (!GetDamage())
		{//ダメージ状態じゃない時
			Move();//移動処理
		}

		//HPゲージの設定
		if (m_HPGauge != nullptr)
		{
			m_HPGauge->EraseGauge();
		}
	}

	//更新処理
	CEnemy::Update();
	Motion();
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
void CHitEnemy::MoveAction()
{
	if ((GetState() != STATE::NEUTRAL)
		|| m_AttackCoolTime > (ATTACKFINISH_COOLTIME - 60))
	{//通常状態以外の時または攻撃終了してから1秒たっていない時終了
		return;
	}

	if (!ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * DUSH_DISTANCE))
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
	else if (!ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * WALK_DISTANCE))
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
	else if (!Attackable
		&& ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * WALK_DISTANCE))
	{
		//モーションを設定
		SetMotion(MOTION_TYPE::NEUTRAL);
	}
	else if (Attackable
		&& !ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() + 2.0f))
	{//攻撃可能かつプレイヤーより遠い

		//移動値を設定
		SetMove(D3DXVECTOR3(sinf(m_Angle) * WALK_SPEED, 0.0f, cosf(m_Angle) * WALK_SPEED));

		//モーションを設定
		SetMotion(MOTION_TYPE::MOVE);
	}
	else if (Attackable
		&& ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() + 2.0f))
	{
		SetState(STATE::ATTACK);
	}
	//向きの設定
	ChangeDirection();
}

//==========================
//攻撃処理
//==========================
void CHitEnemy::Attack()
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
		ColisionHitAttack();
	}

	m_FlameCount++;

	bool Colision = ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), 17.0f);
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
		SetAttackState(ATTACK_STATE::ATTACK);
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
void CHitEnemy::ColisionHitAttack()
{
	bool Colision = ColisionSphere(D3DXVECTOR3(GetPartsMtx(5)._41, GetPartsMtx(5)._42, GetPartsMtx(5)._43),
		D3DXVECTOR3(GetPlayer()->GetPartsMtx(1)._41, GetPlayer()->GetPartsMtx(1)._42, GetPlayer()->GetPartsMtx(1)._43),
		GetRadius(),
		GetPlayer()->GetRadius());

	if (Colision && !m_Attack)
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

		GetPlayer()->Damage(1);
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
float CHitEnemy::ChangeDirection()
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
void CHitEnemy::ResetStak()
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
void CHitEnemy::SetComboList()
{
	m_ComboList[0] = MOTION_TYPE::ATTACK;
	m_ComboList[1] = MOTION_TYPE::ATTACK2;
	m_ComboList[2] = MOTION_TYPE::ATTACK3;

	ResetStak();//スタックのリセット
}

//==========================
//データの追加
//==========================
void CHitEnemy::Push(MOTION_TYPE motion)
{
	if (m_StackIdx < 3)
	{
		m_ComboStack[m_StackIdx++] = motion;
	}
}

//==========================
//データの取り出し
//==========================
CHitEnemy::MOTION_TYPE CHitEnemy::Pop()
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
