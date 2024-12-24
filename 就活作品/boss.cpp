//==========================
// 
// ボス[boss.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "boss.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int CBoss::PRIORITY = 1;//描画順
const int CBoss::GUARD_PROBABILITY = 60;//プレイヤーが素手の時ガードする確率
const int CBoss::NEAR_ACTION_COUNT = 240;//プレイヤーが近いときにする行動の長さ
const int CBoss::HITATTACK_PROBABILITY = 80;//プレイヤーが近いときに殴る確率
const int CBoss::WEAPONATTACK_PROBABILITY = 70;//武器が近いときに武器攻撃する確率
const int CBoss::ATTACKFINISH_COOLTIME = 300;//攻撃終了後のクールタイム
const float CBoss::DUSH_DISTANCE = 10.0f;//走る距離
const float CBoss::WALK_DISTANCE = 5.0f;//歩く距離
const float CBoss::GUARD_DISTANCE = 3.0f;//守る距離
const float CBoss::DUSH_SPEED = 3.5f;//走る速さ
const float CBoss::WALK_SPEED = 2.0f;//歩く速さ
//==========================
//コンストラクタ
//==========================
CBoss::CBoss(int nPriority):
CEnemy(nPriority),//基底コンストラクタ
m_weapon(nullptr),//武器の情報
m_Attack(false),//攻撃判定
m_AttackCoolTime(0),//攻撃のクールタイム
m_FlameCount(0),//攻撃のフレーム数をカウント
m_AttackNum(0),//攻撃回数
Attackable(true),//攻撃可能か判定
m_ComboStack{},//攻撃コンボのスタック
m_StackIdx(0),//スタックのTOPの位置
m_Angle(0.0f),//向き
m_NearCount(0),//プレイヤーが近づいた時の行動のカウント
m_NearAction(false),//プレイヤーが近づいた時の行動をしているか判定
m_BossHPGauge(nullptr)
{
	SetComboList();//コンボリストの生成
}

//==========================
//デストラクタ
//==========================
CBoss::~CBoss()
{

}

//==========================
//初期化処理
//==========================
HRESULT CBoss::Init()
{
	//初期設定
	CEnemy::Init();

	//攻撃方法を設定
	SetAttackState(ATTACK_STATE::ATTACK);

	if (GetPlayer() != nullptr)
	{
		GetPlayer()->GetBoss(this);
	}

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CBoss::Uninit()
{
	

	if (!CManager::GetInstance()->GetDebug()->GetEdit())
	{
		//プレイヤーが持つボスの情報を削除
		GetPlayer()->GetBoss(nullptr);

		if (CManager::GetInstance()->GetGameManager()->GetGame() == CGameManager::GAME::NONE)
		{
			CManager::GetInstance()->GetGameManager()->SetGame(CGameManager::GAME::CLEAR);
		}
	}
	
	//終了処理
	CEnemy::Uninit();

	if (m_BossHPGauge != nullptr)
	{
		m_BossHPGauge = nullptr;
	}

	if (m_weapon != nullptr)
	{
		m_weapon = nullptr;
	}

}

//==========================
//更新処理
//==========================
void CBoss::Update()
{
	if (CManager::GetInstance()->GetDebug()->GetEdit())
	{
		return;
	}

	if (!CManager::GetInstance()->GetDebug()->GetPlayerTest())
	{
		Count();//カウントする

		if (!GetDamage())
		{//ダメージ状態じゃない時

			
			if(GetAttackState() == ATTACK_STATE::WEAPONATTACK)
			{
				WeaponMove();//武器攻撃時の行動を設定
			}
			else
			{
				MoveAction();//移動時の行動を設定
			}
			Move();//移動処理
			Attack();//攻撃処理
		}
			Guard();//ガード処理
	}
	
	if (CManager::GetInstance()->GetDebug()->GetPlayerTest())
	{
		ChangeDirection();
	}

	//更新処理
	CEnemy::Update();

	if (m_BossHPGauge != nullptr)
	{
		m_BossHPGauge->SetHP(GetLife());
	}
	
}

//==========================
//描画処理
//==========================
void CBoss::Draw()
{
	//描画処理
	CEnemy::Draw();
}

//==========================
//オブジェクト生成
//==========================
CBoss* CBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CBoss* pBoss = DBG_NEW CBoss;

	//位置の設定
	pBoss->SetPos(pos);

	//初期化処理
	pBoss->Init();

	//寿命の設定
	pBoss->SetLife(50);

	//HPゲージの生成
	pBoss->m_BossHPGauge = CBossHPGauge::Create(D3DXVECTOR3(1200.0f, 680.0f, 0.0f), 10, 200, pBoss->GetLife());

	//ファイルを読み込む
	pBoss->LoadFile("data\\MOTION\\boss.txt", scale);

	//半径の設定
	pBoss->SetRadius(15.0f);

	//種類の設定
	pBoss->SetType(TYPE::ENEMY);

	//敵の種類を設定
	pBoss->SetEnemyType(ENEMY_TYPE::BOSS);

	return pBoss;
}

//==========================
//攻撃の種類を選択
//==========================
void CBoss::ChoiceAttack()
{
	//近い武器を探す
	FindNearbyWeapons();

	if (m_weapon == nullptr)
	{//武器が存在していない

		//攻撃方法を設定
		SetAttackState(ATTACK_STATE::ATTACK);

		return;
	}
	
	//ランダムな数値を取得
	int Attack = RandomNum();

	//プレイヤーと武器のどちらが近いか判定
	bool Near = MeasureDistance();

	if (!Near)
	{//武器が近い

		if (Attack <= WEAPONATTACK_PROBABILITY
			||GetPartsExistence(15))
		{
			//攻撃方法を設定
			SetAttackState(ATTACK_STATE::WEAPONATTACK);
		}
		else
		{
			//攻撃方法を設定
			SetAttackState(ATTACK_STATE::ATTACK);
			ReleseWeapon();
		}
	}
	else
	{//プレイヤーが近い

		if (Attack <= HITATTACK_PROBABILITY
			&& !GetPartsExistence(15))
		{
			//攻撃方法を設定
			SetAttackState(ATTACK_STATE::ATTACK);
			ReleseWeapon();
		}
		else
		{
			//攻撃方法を設定
			SetAttackState(ATTACK_STATE::WEAPONATTACK);
		}
	}
}

//==========================
//移動処理
//==========================
void CBoss::Move()
{
	if (GetState() != STATE::USUALLY)
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
//移動時の行動
//==========================
void CBoss::MoveAction()
{
	if ((GetState() != STATE::USUALLY)
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

		if(m_NearAction)
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
	else
	{
		if (ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * GUARD_DISTANCE))
		{//プレイヤーの半径の3倍の距離にいる
			if (!m_NearAction)
			{
				PlayerNearAction();
			}
		}
		else
		{
			//移動値を設定
			SetMove(D3DXVECTOR3(sinf(m_Angle) * 1.0f, 0.0f, cosf(m_Angle) * 1.0f));

			//モーションを設定
			SetMotion(MOTION_TYPE::MOVE);
		}
	}

	//向きの設定
	ChangeDirection();
}

//==========================
//武器攻撃の移動処理
//==========================
void CBoss::WeaponMove()
{
	if ((GetState() != STATE::USUALLY)
		|| m_AttackCoolTime > (ATTACKFINISH_COOLTIME - 60))
	{//通常状態以外の時または攻撃終了してから1秒たっていない時終了
		return;
	}

	if (!GetPartsExistence(15)
		&& m_weapon!=nullptr)
	{
		//向きの設定
		float angle = atan2f(m_weapon->GetPos().x - GetPos().x, m_weapon->GetPos().z - GetPos().z);
		SetRot(D3DXVECTOR3(GetRot().x, angle + D3DX_PI, GetRot().z));

		//移動値を設定
		SetMove(D3DXVECTOR3(sinf(angle) * DUSH_SPEED, 0.0f, cosf(angle) * DUSH_SPEED));

		//モーションを設定
		SetMotion(MOTION_TYPE::DUSH);
		SetOldMotion(GetMotion());

		//武器との当たり判定
		ColisionWeapon();
	}
	else
	{
		MoveAction();//移動時の行動を設定
	}
}

//==========================
//向きの変更
//==========================
float CBoss::ChangeDirection()
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
//攻撃処理
//==========================
void CBoss::Attack()
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
		if (GetPartsExistence(15))
		{
			ColisionWeaponAttack();
		}
		else
		{
			ColisionHitAttack();
		}
	}

	m_FlameCount++;

	bool Colision = ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), 17.0f);
	if (m_FlameCount >= 26 && Colision&& m_StackIdx > 0)
	{//フレーム数が24以上かつプレイヤーが近いかつコンボできる

			SetMotion(Pop());//モーションを再生
			m_FlameCount = 0;//カウントしてたフレーム数をリセット
			m_Attack = false;//攻撃していない状態の戻す
			ChangeDirection();//向きを変える
	}
	else if (m_FlameCount >= 24 &&(!Colision||m_StackIdx <= 0))
	{//プレイヤーが遠いまたはコンボできない
		
		SetOldMotion(GetMotion());//今のモーションを保存
		SetState(STATE::USUALLY);//通常状態に変更
		SetAttackState(ATTACK_STATE::ATTACK);
		if (GetPartsExistence(15))
		{
			if (m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
			{
				SetMotion(MOTION_TYPE::WEAPONNEUTRAL);//武器持ち待機状態に変更
			}
			else
			{
				SetMotion(MOTION_TYPE::SMALLWEAPONNEUTRAL);//武器持ち待機状態に変更
			}
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
void CBoss::ColisionHitAttack()
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
			GetPlayer()->DamageBlow(GetPos());
		}
	}
}

//==========================
//武器攻撃の当たり判定
//==========================
void CBoss::ColisionWeaponAttack()
{
	bool Colision = ColisionSphere(D3DXVECTOR3(GetPartsMtx(15)._41, GetPartsMtx(15)._42, GetPartsMtx(15)._43),
		D3DXVECTOR3(GetPlayer()->GetPartsMtx(1)._41, GetPlayer()->GetPartsMtx(1)._42, GetPlayer()->GetPartsMtx(1)._43),
		30.0f,
		30.0f);

	if (Colision && !m_Attack)
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_WEAOPNATTACK);
		GetPlayer()->Damage(1);
		m_Attack = true;

		if (m_StackIdx <= 0)
		{
			GetPlayer()->DamageBlow(GetPos());
		}

		if (m_weapon == nullptr)
		{
			return;
		}

		m_weapon->SubDurability();

		if (m_weapon->GetDurability() <= 0)
		{
			//武器パーツを削除
			DeleteParts(15);
			SetMotion(MOTION_TYPE::NEUTRAL);//待機モーション
			SetComboList();

			//武器を削除
			m_weapon->Uninit();
			m_weapon = nullptr;
		}
	}
}

//==========================
//攻撃可能か判定
//==========================
bool CBoss::JudgeAttackable()
{
	if (m_AttackCoolTime < 240)
	{
		m_AttackCoolTime++;
		return false;
	}

	m_AttackCoolTime = 0;
	return true;
}

//==========================
//武器との当たり判定
//==========================
void CBoss::ColisionWeapon()
{
	bool Colision = ColisionSphere(GetPos(),
		m_weapon->GetPos(),
		GetRadius(),
		m_weapon->GetRadius());

	if (Colision)
	{
		//武器をパーツとして生成
		
		if (m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
		{
			SetParts(D3DXVECTOR3(10.0f, -2.0f, -5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetParts(5), m_weapon->GetModelIdx(), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			m_weapon->GrabCharacter();
			SetMotion(MOTION_TYPE::WEAPONNEUTRAL);//待機モーション(武器持ち)
		}
		else
		{
			SetParts(D3DXVECTOR3(-10.0f, .0f, .0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetParts(8), m_weapon->GetModelIdx(), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
			m_weapon->GrabCharacter();
			SetMotion(MOTION_TYPE::SMALLWEAPONNEUTRAL);//待機モーション(武器持ち)
		}

		SetComboList();
	}
}

//==========================
//近い武器を探す
//==========================
void CBoss::FindNearbyWeapons()
{
	if (m_weapon != nullptr)
	{
		return;
	}
	float distance = 0.0f;//距離

	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CWeapon::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::WEAPON)
		{//オブジェクトが武器ではない
			pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
			continue;
		}

		CWeapon* pWeapon = dynamic_cast<CWeapon*>(pObj);

		if (pWeapon->GetGrab())
		{//武器が掴まれている
			pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
			continue;
		}

		float newdistance = (pWeapon->GetPos().x - GetPos().x)* (pWeapon->GetPos().x - GetPos().x) +
			(pWeapon->GetPos().z - GetPos().z)* (pWeapon->GetPos().z - GetPos().z);
		
		if (distance == 0.0f|| newdistance <= distance)
		{
			distance = newdistance;//距離を保存
			m_weapon = pWeapon;//武器の情報を保存
		}

		pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
	}
}

//==========================
//距離を測る
//==========================
bool CBoss::MeasureDistance()
{
	//一番近い武器との距離を測定
	float WeaponDistance = (m_weapon->GetPos().x - GetPos().x) * (m_weapon->GetPos().x - GetPos().x) +
		(m_weapon->GetPos().z - GetPos().z) * (m_weapon->GetPos().z - GetPos().z);

	//プレイヤーとの距離を測定
	float PlayerDistance = (GetPlayer()->GetPos().x - GetPos().x) * (GetPlayer()->GetPos().x - GetPos().x) +
		(GetPlayer()->GetPos().z - GetPos().z) * (GetPlayer()->GetPos().z - GetPos().z);

	if (WeaponDistance <= PlayerDistance)
	{//武器がプレイヤーより近い
		return false;
	}

	return true;

}

//==========================
//コンボリストの生成
//==========================
void CBoss::SetComboList()
{
	
	if (!GetPartsExistence(15))
	{
		m_ComboList[0] = MOTION_TYPE::ATTACK;
		m_ComboList[1] = MOTION_TYPE::ATTACK2;
		m_ComboList[2] = MOTION_TYPE::ATTACK3;
	}
	else
	{
		if (m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
		{
			m_ComboList[0] = MOTION_TYPE::WEAPONATTACK;
			m_ComboList[1] = MOTION_TYPE::WEAPONATTACK2;
			m_ComboList[2] = MOTION_TYPE::WEAPONATTACK3;
		}
		else
		{
			m_ComboList[0] = MOTION_TYPE::SMALLWEAPONATTACK;
			m_ComboList[1] = MOTION_TYPE::SMALLWEAPONATTACK2;
			m_ComboList[2] = MOTION_TYPE::SMALLWEAPONATTACK3;
		}
	}

	ResetStak();//スタックのリセット
}

//==========================
//スタックの情報を戻す
//==========================
void CBoss::ResetStak()
{
	m_StackIdx = 0;
	for (int i = 2; i >= 0; i--)
	{
		Push(m_ComboList[i]);
	}
}

//==========================
//データの追加
//==========================
void CBoss::Push(MOTION_TYPE motion)
{
	if (m_StackIdx < 3)
	{
		m_ComboStack[m_StackIdx++] = motion;
	}
}

//==========================
//データの取り出し
//==========================
CMotionModel::MOTION_TYPE CBoss::Pop()
{
	if (m_StackIdx <= 0)
	{
		if (GetPartsExistence(15))
		{
			if (m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
			{
			return MOTION_TYPE::WEAPONNEUTRAL;
			}
			else
			{
				return MOTION_TYPE::SMALLWEAPONNEUTRAL;
			}
		}
		else
		{
			return MOTION_TYPE::NEUTRAL;
		}
	}

	return m_ComboStack[--m_StackIdx];

}

//==========================
//ランダムな数値を取得
//==========================
int CBoss::RandomNum()
{
	//0から100の範囲でランダムな数値を取得
	random_device rd;
	uniform_int_distribution<int> dist(1, 100);
	int random_number = dist(rd);

	return random_number;
}

//==========================
//ガード処理
//==========================
void CBoss::Guard()
{
	if (GetState() != STATE::GUARD)
	{
		return;
	}
	
	if (m_weapon != nullptr
		&& m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
	{
		return;
	}

	if (GetPartsExistence(15)) 
	{
		SetMotion(MOTION_TYPE::SMALLWEAPONGUARD);
	}
	else
	{
		SetMotion(MOTION_TYPE::GUARD);

	}

	if (!ColisionSphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * GUARD_DISTANCE))
	{
		m_NearAction = false;
		m_NearCount = 0;
		SetState(STATE::USUALLY);
	}
}

//==========================
//プレイヤーが近いときの行動
//==========================
void CBoss::PlayerNearAction()
{
	if (m_NearAction)
	{
		return;
	}

	m_NearAction = true;

	int Action = RandomNum();
	if (Action <= GUARD_PROBABILITY)
	{
		Guard();
		SetState(STATE::GUARD);
	}
	else
	{
		SetMotion(MOTION_TYPE::NEUTRAL);
	}
}

//==========================
//カウントする
//==========================
void CBoss::Count()
{
	if (m_NearAction)
	{//プレイヤーが近づいたときの行動をしている
		m_NearCount++;
		if (m_NearCount >= NEAR_ACTION_COUNT
			&& GetPlayer()->GetState() != CPlayer::STATE::ATTACK)
		{
			m_NearAction = false;
			m_NearCount = 0;
			SetState(STATE::USUALLY);
		}
	}

	if (!Attackable)
	{//攻撃できないとき

		m_AttackCoolTime--;

		if (m_AttackCoolTime <= 0)
		{
			Attackable = true;
			m_AttackCoolTime = 0;
			ChoiceAttack();//次の攻撃を決める
		}
	}	
}

//==========================
//武器を離す
//==========================
void CBoss::ReleseWeapon()
{
	if (GetPartsExistence(15))
	{//武器を持ってるとき

		//武器パーツを削除
		DeleteParts(15);

		m_weapon->ReleseCharacter(D3DXVECTOR3(GetParts(14)->GetMtxWorld()._41,0.0f, GetParts(14)->GetMtxWorld()._43));
		m_weapon = nullptr;

		SetComboList();
	}
}

//==========================
//掴む武器を変える
//==========================
void CBoss::GrabChangeWeapon(CWeapon* weapon)
{
	if (m_weapon == nullptr
		|| m_weapon != weapon)
	{//掴む武器がないか掴まれた武器が掴む武器と違う武器のとき
		return;
	}

	//別の武器を探す
	m_weapon = nullptr;
	FindNearbyWeapons();
}