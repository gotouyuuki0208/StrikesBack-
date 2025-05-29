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
#include "weapon.h"
#include "bosshpgauge.h"
#include "bossState.h"
#include "bat.h"
#include "collision.h"

//静的メンバ初期化
const int CBoss::PRIORITY = 1;//描画順
const int CBoss::GUARD_PROBABILITY = 60;//プレイヤーが素手の時ガードする確率
const int CBoss::NEAR_ACTION_COUNT = 240;//プレイヤーが近いときにする行動の長さ
const int CBoss::HITATTACK_PROBABILITY = 80;//プレイヤーが近いときに殴る確率
const int CBoss::WEAPONATTACK_PROBABILITY = 70;//武器が近いときに武器攻撃する確率
const int CBoss::ATTACKFINISH_COOLTIME = 300;//攻撃終了後のクールタイム
const float CBoss::GUARD_DISTANCE = 5.0f;//守る距離

//==========================
//コンストラクタ
//==========================
CBoss::CBoss(int nPriority):
CEnemy(nPriority),//基底コンストラクタ
m_weapon(nullptr),//武器の情報
m_HaveWeapon(nullptr),//持ってる武器
m_FlameCount(0),//攻撃のフレーム数をカウント
m_NearCount(0),//プレイヤーが近づいた時の行動のカウント
m_NearAction(false),//プレイヤーが近づいた時の行動をしているか判定
m_StateMachine(nullptr),//状態管理
m_NextAttack(true),//次の攻撃(false:素手 true:武器)
m_Guard(false),//ガード判定
m_weaponbreak(false)//武器破壊判定
{
	
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

	//HPゲージの生成
	CManager::GetInstance()->GetHudManager()->CreateBossHPGauge();

	//状態管理クラスの作成
	m_StateMachine = DBG_NEW CStateMachine;
	auto NewState = DBG_NEW CBossDirectionState;
	ChangeState(NewState);

	if (GetPlayer() != nullptr)
	{//プレイヤーにボスの情報を持たせる
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

	if (m_weapon != nullptr)
	{
		m_weapon = nullptr;
	}

	if (m_StateMachine != nullptr)
	{
		delete m_StateMachine;
		m_StateMachine = nullptr;
	}
}

//==========================
//更新処理
//==========================
void CBoss::Update()
{
	//モーションの更新
	MotionUpdate();

	//ステートの更新
	m_StateMachine->Update();

	//更新処理
	CEnemy::Update();

	if (!GetAttackable())
	{//攻撃できないとき

		//クールタイムを減らす
		SubCoolTime();

		if (GetCoolTime() <= 0)
		{//クールタイムがなくなった

			//次の攻撃を設定
			ChoiceAttack();

			//攻撃可能にする
			ChangeAttackable();
		}
	}

	//HPゲージの更新
	CManager::GetInstance()->GetHudManager()->ChangeBossHP(GetLife());

	if (GetLife() <= 0)
	{//ライフがない

		//終了処理
		Uninit();
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

	//ファイルを読み込む
	pBoss->LoadFile("data\\MOTION\\boss.txt", scale);

	//半径の設定
	pBoss->SetRadius(15.0f);

	//種類の設定
	pBoss->SetType(TYPE::ENEMY);

	//敵の種類を設定
	pBoss->SetEnemyType(ENEMY_TYPE::BOSS);

	//ボスに武器を持たせる
	pBoss->InitHaveWeapon();

	return pBoss;
}

//==========================
//モーションの更新
//==========================
void CBoss::MotionUpdate()
{
	//パーツの数値の計算
	CalParts();

	if (m_HaveWeapon != nullptr)
	{//武器を持ってる
		if (m_HaveWeapon->GetGrab())
		{
			m_HaveWeapon->SetRot(CalMotionRot(15));
			m_HaveWeapon->SetPos(CalMotionPos(15));
		}
	}

	//モーションカウンターを進める
	MotionCountUpdate();

	if (ExceedMaxFlame())
	{//モーションのカウンターが再生フレームを超えたとき

		if (m_HaveWeapon != nullptr)
		{//武器を持ってる
			if (m_HaveWeapon->GetGrab())
			{
				KeepFirstPos(m_HaveWeapon->GetPos(), 15);
				KeepFirstRot(m_HaveWeapon->GetRot(), 15);
			}
		}
	}

	//モーションの情報を更新
	UpdateMotionInfo();
}

//==========================
//状態を変更
//==========================
void CBoss::ChangeState(CBossStateBase* NewState)
{
	//stateの所有者を設定
	NewState->SetOwner(this);

	//stateを変更
	m_StateMachine->ChangeState(NewState);
}

//==========================
//攻撃の種類を選択
//==========================
void CBoss::ChoiceAttack()
{
	//近い武器を探す
	FindNearbyWeapons();

	if (m_weapon == nullptr
		&&m_HaveWeapon==nullptr)
	{//武器が存在していない

		//攻撃方法を素手攻撃に変更
		m_NextAttack = false;

		return;
	}
	
	//ランダムな数値を取得
	int Attack = RandomNum();

	//プレイヤーと武器のどちらが近いか判定
	bool Near = MeasureDistance();

	if (!Near)
	{//武器が近い

		if (Attack <= WEAPONATTACK_PROBABILITY)
		{//武器攻撃する

			//攻撃方法を武器攻撃に変更
			m_NextAttack = true;
		}
		else
		{
			//武器を持っていたら捨てる
			ReleseWeapon();

			//攻撃方法を素手攻撃に変更
			m_NextAttack = false;
		}
	}
	else
	{//プレイヤーが近い

		if (Attack <= HITATTACK_PROBABILITY)
		{//素手攻撃する

			//武器を持っていたら捨てる
			ReleseWeapon();

			//攻撃方法を素手攻撃に変更
			m_NextAttack = false;
		}
		else
		{
			//攻撃方法を武器攻撃に変更
			m_NextAttack = true;
		}
	}
}

//==========================
//次の攻撃方法を取得
//==========================
bool CBoss::GetNextAttack()
{
	return m_NextAttack;
}

//==========================
//武器攻撃の移動処理
//==========================
void CBoss::WeaponMove()
{
	if (!GetWeapon())
	{//武器が存在しているかつ掴まれていない

		//向きの設定
		float angle = atan2f(m_weapon->GetPos().x - GetPos().x, m_weapon->GetPos().z - GetPos().z);
		SetRot(D3DXVECTOR3(GetRot().x, angle + D3DX_PI, GetRot().z));

		//移動値を設定
		SetMove(D3DXVECTOR3(sinf(angle) * DUSH_SPEED, 0.0f, cosf(angle) * DUSH_SPEED));

		//武器との当たり判定
		ColisionWeapon();
	}
}

//==========================
//武器との当たり判定
//==========================
void CBoss::ColisionWeapon()
{

	//当たり判定
	bool Colision = Collision::Sphere(GetPos(),
		m_weapon->GetPos(),
		GetRadius(),
		m_weapon->GetRadius());

	if (Colision)
	{//衝突している
		
		//武器をパーツとして生成
		if (m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
		{//両手武器
			
			//武器の親モデルを設定
			m_weapon->SetParent(GetParts(5));

			//位置と向きを設定
			m_weapon->SetPos(D3DXVECTOR3(10.0f, -2.0f, -5.0f));
			m_weapon->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			//持ってる武器として保存
			m_HaveWeapon = m_weapon;
			m_weapon = nullptr;
		}
		else
		{
			//武器の親モデルを設定
			m_weapon->SetParent(GetParts(8));

			//位置と向きを設定
			m_weapon->SetPos(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
			m_weapon->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			//持ってる武器として保存
			m_HaveWeapon = m_weapon;
			m_weapon = nullptr;
		}

		m_HaveWeapon->GrabCharacter();//掴まれた状態にする
	}
}

//==========================
//近い武器を探す
//==========================
void CBoss::FindNearbyWeapons()
{
	if (m_HaveWeapon != nullptr)
	{//すでに武器を持っている
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
	if (m_weapon == nullptr)
	{//武器がない
		return true;
	}

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
//武器を離す
//==========================
void CBoss::ReleseWeapon()
{
	if (m_HaveWeapon != nullptr)
	{
		if (m_HaveWeapon->GetGrab())
		{//武器を持ってるとき

			//プレイヤーが持つ武器の位置を取得
			D3DXVECTOR3 pos = D3DXVECTOR3(m_HaveWeapon->GetMtxWorld()._41, 0.0f, m_HaveWeapon->GetMtxWorld()._43);
			m_HaveWeapon->SetParent(nullptr);
			m_HaveWeapon->ReleseCharacter(pos);//武器を放す
			m_HaveWeapon->CorrectInfo();
			m_HaveWeapon = nullptr;//武器の情報を削除

			auto NewState = DBG_NEW CBossNeutralState;
			ChangeState(NewState);
		}
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

//==========================
//武器を所持しているか判定
//==========================
bool CBoss::GetWeapon()
{
	if (m_HaveWeapon != nullptr)
	{
		return true;
	}

	return false;
}

//==========================
//武器のタイプを取得
//==========================
bool CBoss::GetWeaponType()
{
	if (m_HaveWeapon->GetWeaponType() == CWeapon::WEAPONTYPE::SMALL)
	{//武器が片手武器
		return false;
	}
	else if (m_HaveWeapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
	{//両手武器
		return true;
	}
}

//==========================
//攻撃被弾処理
//==========================
bool CBoss::hit(D3DXVECTOR3 pos, int damage,MOTION_TYPE hitmotion)
{
	
	if (GetDamageNum() >= 3 || GetHitMotion() == hitmotion)
	{//3回攻撃を受けてる

		return false;
	}

	//被弾回数を増やす
	AddDamegeNum();

	//モーションを保存
	SetHitMotion(hitmotion);

	//ダメージの数値を取得
	int DamageNum = damage;

	//現在の状態を取得
	auto State = m_StateMachine->GetState();

	if (typeid(*State) == typeid(CGuardState))
	{//ガード状態の時

		//ダメージを減らす
		DamageNum /= 2;
	}
	else if (typeid(*State) == typeid(CSmallWeaponGuardState))
	{//武器ガード状態の時

		//ダメージを減らす
		DamageNum /= 2;

		//武器の耐久を減らす
		WeaponDamage();
	}

	//ライフを減らす
	int Life = GetLife();
	SetLife(Life -= DamageNum);

	if (typeid(*State) != typeid(CGuardState))
	{//ガード状態ではない
		Damage();

		if (GetDamageNum() >= 3)
		{//3回被弾している
			DamegeBlow(pos);
		}
	}

	return true;
}

//==========================
//武器の耐久値を減らす
//==========================
void CBoss::WeaponDamage()
{
	//武器の耐久値を減らす
	m_HaveWeapon->SubDurability();

	if (m_HaveWeapon->GetDurability() <= 0)
	{//耐久値がなくなったとき
		DeleteParts(15);

		//武器を削除する
		CManager::GetInstance()->GetStageManager()->DeleteObj(*m_HaveWeapon);
		m_HaveWeapon->Uninit();
		m_HaveWeapon = nullptr;

		m_weaponbreak = true;
	}
}

//==========================
//ガードの情報をリセット
//==========================
void CBoss::GuardReset()
{
	//近くのときの行動をしていない
	m_NearAction = false;

	//ガードしない状態に変更
	m_Guard = false;
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

	//プレイヤーが近いときの行動をしている状態
	m_NearAction = true;

	//ランダムな数字を取得
	int Action = RandomNum();

	if (Action <= GUARD_PROBABILITY)
	{//数字がガードする確率の数字より小さい

		//ガードする
		m_Guard = true;
	}
	else
	{
		//ガードしない
		m_Guard = false;
	}
}

//==========================
//ガードするか取得
//==========================
bool CBoss::GetGuard()
{
	return m_Guard;
}

//==========================
//ガードする距離にいるか判定
//==========================
bool CBoss::JudgeGuard()
{
	if (Collision::Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius()* GUARD_DISTANCE))
	{//プレイヤーがガードする距離にいる

		return true;
	}

	return false;
}

//==========================
//最初に武器を持たせる
//==========================
void CBoss::InitHaveWeapon()
{
	//バットを持たせる
	m_HaveWeapon = CBat::Create({ 0.0f,0.0f,0.0f }, { 1.5f,1.5f,1.5f }, { 0.0f,0.0f,0.0f });

	//武器の親モデルを設定
	m_HaveWeapon->SetParent(GetParts(8));

	//位置と向きを設定
	m_HaveWeapon->SetPos(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
	m_HaveWeapon->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//掴まれた状態にする
	m_HaveWeapon->GrabCharacter();

}

//==========================
//ダメージ処理
//==========================
void CBoss::Damage()
{
	SetDamage(true);

	if (GetLife() <= 0)
	{
		if (CManager::GetInstance()->GetGameManager()->GetGame() == CGameManager::GAME::NONE)
		{
			CManager::GetInstance()->GetGameManager()->SetGame(CGameManager::GAME::CLEAR);
		}
	}
}

//==========================
//武器攻撃の当たり判定
//==========================
void CBoss::ColisionWeaponAttack()
{
	if (m_HaveWeapon == nullptr)
	{
		return;
	}

	bool Colision = Collision::Sphere(D3DXVECTOR3(m_HaveWeapon->GetMtxWorld()._41, m_HaveWeapon->GetMtxWorld()._42, m_HaveWeapon->GetMtxWorld()._43),
		D3DXVECTOR3(GetPlayer()->GetPartsMtx(1)._41, GetPlayer()->GetPartsMtx(1)._42, GetPlayer()->GetPartsMtx(1)._43),
		30.0f,
		30.0f);

	
	if (Colision && !GetAttack())
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_WEAOPNATTACK);
		SetAttack();

		GetPlayer()->hit(GetPos(),2);
		
		WeaponDamage();
	}
}

//==========================
//武器が壊れたか取得
//==========================
bool CBoss::GetWeaponBreak()
{
	return m_weaponbreak;
}

//==========================
//武器破壊判定をリセット
//==========================
void CBoss::BreakReset()
{
	m_weaponbreak = false;
}