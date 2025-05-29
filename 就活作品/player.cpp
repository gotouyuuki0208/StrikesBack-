//==========================
// 
// プレイヤー処理[player.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "player.h"
#include "manager.h"
#include "fild.h"
#include "bigweapon.h"
#include "smallweapon.h"
#include "boss.h"
#include "jihanki.h"
#include "effect.h"
#include "particle.h"
#include "guardeffect.h"
#include "weapon.h"
#include "enemy.h"
#include "weakenemy.h"
#include"collision.h"
//静的メンバ初期化
const int CPlayer::PRIORITY = 1;//描画順
const int CPlayer::MAX_LIFE = 25;//寿命の最大値
const float CPlayer::MOVE_VALUE = 3.0f;//移動
const float CPlayer::DASH_VALUE = 7.0f;//ダッシュ
const float CPlayer::JUMP_VALUE = 10.0f;//ジャンプ
const float CPlayer::GRAVITY_VALUE = 0.7f;//重力
const float CPlayer::INERTIA_VALUE = 0.5f;//慣性
const float CPlayer::ROT_VALUE = 1.57f;//向き
const float CPlayer::CHARA_WIDTH = 10.0f;//キャラクターのXサイズ
const float CPlayer::CHARA_HEIGHT = 10.0f;//キャラクターのYサイズ
const float CPlayer::AVOIDANCE_VALUE = 10.0f;//回避の移動値
//==========================
//コンストラクタ
//==========================
CPlayer::CPlayer(int nPriority) :
CCharacter(nPriority),//基底クラスのコンストラクタ
m_grab(false),//掴み判定
m_weapon(nullptr), //所持してる武器
m_boss(nullptr),//ボスの情報を取得
m_RecoveryItemStock(0),//アイテムのストック数
m_WeaponType(false),//武器の種類
m_VisualCor(false),//当たり判定の色の設定
LeftStickAngle(0.0f),//左スティックの角度
m_StateMachine(nullptr),//状態管理
m_DamageNum(0),//ダメージ回数カウント
m_Attack(false),//攻撃がヒットしたか判定
m_breakweapon(false)//武器が壊れたか判定
{
	SetLife(MAX_LIFE);//寿命の設定
}

//==========================
//デストラクタ
//==========================
CPlayer::~CPlayer()
{

}

//==========================
//初期化処理
//==========================
HRESULT CPlayer::Init()
{
	//初期設定
	CCharacter::Init();
	
	//HPゲージの生成
	CManager::GetInstance()->GetHudManager()->CreatePlayerHPGauge();

	//向きの変更
	SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	//状態管理クラスの作成
	m_StateMachine = DBG_NEW CStateMachine;
	auto NewState = DBG_NEW CNeutralState;
	ChangeState(NewState);

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CPlayer::Uninit()
{
	if (m_weapon != nullptr)
	{
		m_weapon = nullptr;
	}
	
	if (m_boss != nullptr)
	{
		m_boss = nullptr;
	}

	if (m_StateMachine != nullptr)
	{
		delete m_StateMachine;
		m_StateMachine = nullptr;
	}

	
	//終了処理
	CCharacter::Uninit();
}

//==========================
//更新処理
//==========================
void CPlayer::Update()
{
	if (CManager::GetInstance()->GetStageManager()->GetChange())
	{//ゲームが遊べない状態
		return;
	}

	if (!CManager::GetInstance()->GetGameManager()->GetPlayGame())
	{//ゲームが遊べない状態
		return;
	}

	//ステートの更新
	m_StateMachine->Update();

	//地面との当たり判定
	CollisionFild();

	//敵との当たり判定
	CollisionEnemy();

	//モーションの更新
	MotionUpdate();

	//更新処理
	CCharacter::Update();

	//HPゲージの更新
	CManager::GetInstance()->GetHudManager()->ChangePlayerHP(GetLife());
}

//==========================
//描画処理
//==========================
void CPlayer::Draw()
{
	//描画処理
	CCharacter::Draw();
}

//==========================
//オブジェクト生成
//==========================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CPlayer* pPlayer = DBG_NEW CPlayer;

	//位置の設定
	pPlayer->SetPos(pos);

	//初期化処理
	pPlayer->Init();

	//ファイルを読み込む
	pPlayer->LoadFile("data\\MOTION\\motion_player_15.txt", scale);

	//半径の設定
	pPlayer->SetRadius(15.0f);

	//タイプ設定
	pPlayer->SetType(TYPE::PLAYER);
	
	return pPlayer;
}

//==========================
//モーションの更新
//==========================
void CPlayer::MotionUpdate()
{
	//パーツの数値の計算
	CalParts();
	if (m_weapon != nullptr)
	{//武器を持ってる
		m_weapon->SetPos(CalMotionPos(15));
		m_weapon->SetRot(CalMotionRot(15));

	}

	//モーションカウンターを進める
	MotionCountUpdate();

	if (ExceedMaxFlame())
	{//モーションのカウンターが再生フレームを超えたとき

		if (m_weapon != nullptr)
		{//武器を持ってる
			KeepFirstPos(m_weapon->GetPos(), 15);
			KeepFirstRot(m_weapon->GetRot(), 15);
		}
	}

	//モーションの情報を更新
	UpdateMotionInfo();

}

//==========================
//状態を変更
//==========================
void CPlayer::ChangeState(CPlayerStateBase* NewState)
{
	NewState->SetOwner(this);
	m_StateMachine->ChangeState(NewState);
}

//==========================
//移動の入力処理
//==========================
void CPlayer::InputMove()
{
	float move = MOVE_VALUE;
	float CameraRot = CManager::GetInstance()->GetCamera()->GetRot().y;

	if (CManager::GetInstance()->GetJoypad()->GetTriggerPedal(CInputJoypad::JOYKEY_LEFT_TRIGGER))
	{//ダッシュ

		//現在の状態を取得
		auto State = m_StateMachine->GetState();

		if (typeid(*State) != typeid(CBigWeaponMoveState))
		{//両手武器を持ってない

			move = DASH_VALUE;
		}
	}

	if (CManager::GetInstance()->GetJoypad()->Connection())
	{//パッドが接続されているとき

		//左スティックの角度を取得
		LeftStickAngle = CManager::GetInstance()->GetJoypad()->GetLeftAngle();

		//移動値の設定
		SetMove(D3DXVECTOR3(GetMove().x + sinf(CameraRot * D3DX_PI + LeftStickAngle) * move,
			GetMove().y,
			GetMove().z + cosf(CameraRot * D3DX_PI + LeftStickAngle) * move));

		//向きの設定
		D3DXVECTOR3 rot = GetRot();

		SetRot(D3DXVECTOR3(GetRot().x, ((CameraRot * D3DX_PI) + (LeftStickAngle + D3DX_PI)), GetRot().z));
	}

}

//==========================
//攻撃時の移動処理
//==========================
void CPlayer::AttackMove()
{
	if (CManager::GetInstance()->GetJoypad()->Connection())
	{//パッドが接続されているとき

		//左スティックの角度を取得
		LeftStickAngle = CManager::GetInstance()->GetJoypad()->GetLeftAngle();

		//移動値の設定
		SetMove(D3DXVECTOR3(GetMove().x + sinf(GetRot().y + D3DX_PI) * MOVE_VALUE,
			GetMove().y,
			GetMove().z + cosf(GetRot().y + D3DX_PI) * MOVE_VALUE));
	}
}

//==========================
//移動処理
//==========================
void CPlayer::Move()
{
	//前回の位置を保存
	SetPosOld(GetPos());
	
	//慣性と重力
	SetMove(D3DXVECTOR3(GetMove().x += (0 - GetMove().x) * INERTIA_VALUE,
		GetMove().y,
		GetMove().z += (0 - GetMove().z) * INERTIA_VALUE));

	
	//吹き飛び時の移動
	SetDamegeBlow(D3DXVECTOR3(GetDamegeBlow().x += (0 - GetDamegeBlow().x) * 0.25f,
		GetDamegeBlow().y,
		GetDamegeBlow().z += (0 - GetDamegeBlow().z) * 0.25f));
	
	SetMove(D3DXVECTOR3(GetMove().x + GetDamegeBlow().x,
		GetMove().y+ GetDamegeBlow().y,
		GetMove().z + GetDamegeBlow().z));

	//位置の設定
	SetPos(GetPos() + GetMove());
}

//==========================
//回避
//==========================
void CPlayer::Avoidance()
{
	if (!CManager::GetInstance()->GetJoypad()->Connection())
	{//パッドが接続されていないとき
		return;
	}

	//カメラの向きを取得
	float CameraRot = CManager::GetInstance()->GetCamera()->GetRot().y;

	//移動値の設定
	SetMove(D3DXVECTOR3(GetMove().x - sinf(CameraRot * D3DX_PI + LeftStickAngle) * AVOIDANCE_VALUE,
		GetMove().y,
		GetMove().z - cosf(CameraRot * D3DX_PI + LeftStickAngle) * AVOIDANCE_VALUE));

	//向きの設定
	SetRot(D3DXVECTOR3(GetRot().x, ((CameraRot * D3DX_PI) + (LeftStickAngle + D3DX_PI)), GetRot().z));

	//位置の設定
	SetPos(GetPos() + GetMove());
}

//==========================
//ボスを取得
//==========================
void CPlayer::GetBoss(CEnemy* boss)
{
	if (m_boss != nullptr
		&&boss!=nullptr)
	{
		return;
	}

	m_boss = boss;
}

//==========================
//武器所持判定
//==========================
bool CPlayer::GetHaveWeapon()
{
	if (m_weapon == nullptr)
	{
		return false;
	}

	return true;
}

//==========================
//武器を持っていない状態に変更
//==========================
void CPlayer::DeleteWeapon()
{
	m_weapon = nullptr;
}

//==========================
//ダメージ処理
//==========================
void CPlayer::Damage()
{
	SetDamage(true);

	if (GetLife() <= 0)
	{
		if (CManager::GetInstance()->GetGameManager()->GetGame() == CGameManager::GAME::NONE)
		{
			CManager::GetInstance()->GetGameManager()->SetGame(CGameManager::GAME::OVER);
		}
	}
}

//==========================
//アイテムの数を増やす
//==========================
void CPlayer::AddItem()
{
	m_RecoveryItemStock++;
}

//==========================
//地面との当たり判定
//==========================
void CPlayer::CollisionFild()
{
	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CFild::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CFild::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::FILD)
		{//オブジェクトがフィールドではない
			pObj = CObject::GetObj(pObj, CFild::PRIORITY);
			continue;
		}

		CFild* pFild = (CFild*)pObj;

		if (GetPosOld().y >= pFild->GetPos().y - pFild->GetSize().y
			&& GetPos().y < pFild->GetPos().y + pFild->GetSize().y
			&& GetPos().x <= pFild->GetPos().x + pFild->GetSize().x
			&& GetPos().x >= pFild->GetPos().x - pFild->GetSize().x
			&& GetPos().z <= pFild->GetPos().z + pFild->GetSize().z
			&& GetPos().z >= pFild->GetPos().z - pFild->GetSize().z)
		{//衝突している
			SetMove(D3DXVECTOR3(GetMove().x, 0.0f, GetMove().z));
			SetPos(D3DXVECTOR3(GetPos().x, pFild->GetPos().y+0.1f, GetPos().z));
		}

		pObj = CObject::GetObj(pObj, CFild::PRIORITY);
	}
}

//==========================
//敵との当たり判定
//==========================
void CPlayer::CollisionEnemy()
{
	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CBoss::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CBoss::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//オブジェクトが敵ではない
			pObj = CObject::GetObj(pObj, CBoss::PRIORITY);
			continue;
		}

		CBoss* pBoss = (CBoss*)pObj;

		bool Colision = Collision::Sphere(GetPos(),
			pBoss->GetPos(),
			GetRadius(),
			pBoss->GetRadius());

		if (Colision)
		{

			D3DXVECTOR3 Vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きベクトル
			D3DXVECTOR3 NormalizeVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//正規化したベクトル

			//向きベクトルを算出
			Vector.x = VectorCalculation(pBoss->GetPos().x, GetPos().x);
			Vector.z = VectorCalculation(pBoss->GetPos().z, GetPos().z);

			//ベクトルを正規化
			D3DXVec3Normalize(&NormalizeVec, &Vector);
			
			//位置を変更
			pBoss->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			pBoss->SetPos(D3DXVECTOR3(GetPos().x + NormalizeVec.x * floor((GetRadius() + pBoss->GetRadius())),
				GetPos().y,
				GetPos().z + NormalizeVec.z * floor((GetRadius() + pBoss->GetRadius()))));
		}

		pObj = CObject::GetObj(pObj, CBoss::PRIORITY);
	}
}

//==========================
//敵を殴るときの当たり判定
//==========================
void CPlayer::HitEnemy(int PartsNum)
{

	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CEnemy::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//オブジェクトがエネミーではない
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		//エネミークラスにキャスト
		CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

		//判定の中心位置を設定
		D3DXVECTOR3 mypos = { GetParts(PartsNum)->GetMtxWorld()._41,GetParts(PartsNum)->GetMtxWorld()._42,GetParts(PartsNum)->GetMtxWorld()._43 };
		D3DXVECTOR3 pos = { pEnemy->GetParts(1)->GetMtxWorld()._41,pEnemy->GetParts(1)->GetMtxWorld()._42,pEnemy->GetParts(1)->GetMtxWorld()._43 };

		bool Colision = Collision::Sphere(mypos, pos,10.0f, 10.0f);

		if (Colision)
		{//攻撃が当たっている

			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

			//ダメージ処理
			if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::BOSS)
			{//敵がボス

				CBoss* pBoss = dynamic_cast<CBoss*>(pObj);

				pBoss->hit(GetPos(), 1,GetMotion());
			}
			else
			{//雑魚敵

				CWeakEnemy* pWeakEnemy = dynamic_cast<CWeakEnemy*>(pObj);

				//ダメージ処理
				pWeakEnemy->Hit(GetPos(), 1, GetMotion());
			}
			
			//カメラ揺れ
			CManager::GetInstance()->GetCamera()->SetShape(5, 5);
		}

		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
	}
}

//==========================
//敵を武器で殴るときの当たり判定
//==========================
void CPlayer::WeaponHitEnemy()
{
	if (m_weapon == nullptr)
	{//武器がないとき
		return;
	}

	//攻撃をヒット判定を初期化
	m_Attack = false;

	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CEnemy::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//オブジェクトがエネミーではない
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

		bool Colision = Collision::Sphere(D3DXVECTOR3(m_weapon->GetMtxWorld()._41, m_weapon->GetMtxWorld()._42, m_weapon->GetMtxWorld()._43),
			D3DXVECTOR3(pEnemy->GetPartsMtx(1)._41, pEnemy->GetPartsMtx(1)._42, pEnemy->GetPartsMtx(1)._43),
			30.0f,
			30.0f);

		if (!Colision)
		{//当たっていない
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		if (m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::SMALL)
		{//片手武器のとき

			//ダメージ処理
			if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::BOSS)
			{//敵がボス

				CBoss* pBoss = dynamic_cast<CBoss*>(pObj);

				//ダメージ処理
				m_Attack = pBoss->hit(GetPos(), 2, GetMotion());
			}
			else
			{//雑魚敵

				CWeakEnemy* pWeakEnemy = dynamic_cast<CWeakEnemy*>(pObj);

				//ダメージ処理
				pWeakEnemy->Hit(GetPos(), 1, GetMotion());
			}
		}
		else
		{//両手武器のとき

			//ダメージ処理
			if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::BOSS)
			{//敵がボス

				CBoss* pBoss = dynamic_cast<CBoss*>(pObj);

				//ダメージ処理
				m_Attack = pBoss->hit(GetPos(), 2, GetMotion());
			}
			else
			{//雑魚敵

				CWeakEnemy* pWeakEnemy = dynamic_cast<CWeakEnemy*>(pObj);

				//ダメージ処理
				m_Attack = pWeakEnemy->Hit(GetPos(), 2, GetMotion());
			}
		}

		if (m_Attack)
		{//敵にダメージが入った

			//SEを再生
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_WEAOPNATTACK);

			for (int i = 0; i < 20; i++)
			{//パーティクルの生成
				CParticle::Create(D3DXVECTOR3(m_weapon->GetMtxWorld()._41, m_weapon->GetMtxWorld()._42, m_weapon->GetMtxWorld()._43),
					D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
					10,
					1.0f,
					1.0f,
					10.0f);

			}

			for (int i = 0; i < 3; i++)
			{//エフェクトの表示
				CEffect::Create(D3DXVECTOR3(m_weapon->GetMtxWorld()._41, m_weapon->GetMtxWorld()._42, m_weapon->GetMtxWorld()._43), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 15.0f, 15.0f);
			}

			//武器の耐久を減らす
			WeaponDamage();

			if (m_breakweapon)
			{
				break;
			}

			m_Attack = false;
		}
		
		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
	}
}

//==========================
//自販機に攻撃時の当たり判定
//==========================
void CPlayer::CollisionJihankiAttack()
{
	

	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CJihanki::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CJihanki::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::JIHANKI)
		{//オブジェクトが自販機ではない
			pObj = CObject::GetObj(pObj, CJihanki::PRIORITY);
			continue;
		}

		CJihanki* pJihan = (CJihanki*)pObj;

		bool Colision = Collision::Sphere(D3DXVECTOR3(GetPartsMtx(5)._41, GetPartsMtx(5)._42, GetPartsMtx(5)._43),
			D3DXVECTOR3(pJihan->GetPos().x, pJihan->GetPos().y+20.0f, pJihan->GetPos().z),
			10.0f,
			30.0f);

		if (Colision )
		{
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

			//ダメージ処理
			pJihan->Damage(1);
			CManager::GetInstance()->GetCamera()->SetShape(5, 5);
		}

		pObj = CObject::GetObj(pObj, CJihanki::PRIORITY);
	}
}

//==========================
//武器を拾う
//==========================
void CPlayer::PickUpWeapon()
{
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

		CWeapon* pWeapon = (CWeapon*)pObj;

		if (pWeapon->GetGrab())
		{//武器が近まれている
			pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
			continue;
		}

		bool colision = Collision::Sphere(GetPos(), pWeapon->GetPos(), GetRadius(), pWeapon->GetRadius());

		if (colision)
		{
			

			if (pWeapon->GetWeaponType() == CWeapon::WEAPONTYPE::BIG)
			{
				pWeapon->SetParent(GetParts(5));
				pWeapon->SetPos(D3DXVECTOR3(10.0f, -2.0f, -5.0f));
				pWeapon->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				SetWeaponMotion(MOTION_TYPE::WEAPONNEUTRAL);//待機モーション(武器持ち)
				m_WeaponType = false;
			}
			else
			{
				pWeapon->SetParent(GetParts(8));
				pWeapon->SetPos(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
				pWeapon->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				SetWeaponMotion(MOTION_TYPE::SMALLWEAPONNEUTRAL);//待機モーション(武器持ち)
				m_WeaponType = true;
			}
			
			pWeapon->GrabCharacter();//掴まれた状態にする
			m_weapon = pWeapon;//掴んだ武器の情報を保存
			if (m_boss != nullptr)
			{//ボスがいるとき
				CBoss* pBoss = dynamic_cast<CBoss*>(m_boss);
				pBoss->GrabChangeWeapon(pWeapon);
			}

			m_breakweapon = false;

			break;
		}

		pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
	}
}

//==========================
//武器の種類を取得
//==========================
bool CPlayer::GetWeaponType()
{
	return m_WeaponType;
}

//==========================
//武器を手放す
//==========================
void CPlayer::ReleaseWeapon()
{
	if (m_weapon == nullptr)
	{//武器を持っていない
		return;
	}

	//プレイヤーが持つ武器の位置を取得
	D3DXVECTOR3 pos = D3DXVECTOR3(m_weapon->GetMtxWorld()._41, 0.0f, m_weapon->GetMtxWorld()._43);
	m_weapon->SetParent(nullptr);
	m_weapon->ReleseCharacter(pos);//武器を放す
	m_weapon->CorrectInfo();
	m_weapon = nullptr;//武器の情報を削除
	
}

//==========================
//角度の補正
//==========================
void CPlayer::CorrectionAngle()
{
	float distance = 0.0f;
	CEnemy* pNearEnemy = nullptr;

	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CEnemy::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//オブジェクトがエネミーではない
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

		float newdistance = (pEnemy->GetPos().x - GetPos().x) * (pEnemy->GetPos().x - GetPos().x) +
			(pEnemy->GetPos().z - GetPos().z) * (pEnemy->GetPos().z - GetPos().z);

		if (distance == 0.0f || newdistance <= distance)
		{
			distance = newdistance;//距離を保存
			pNearEnemy = pEnemy;//近い敵の情報を保存
		}

		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
	}

	if (pNearEnemy == nullptr)
	{
		if (CManager::GetInstance()->GetJoypad()->Connection())
		{//パッドが接続されているとき

			//カメラの向きを取得
			float CameraRot = CManager::GetInstance()->GetCamera()->GetRot().y;

			//移動値の設定
			SetMove(D3DXVECTOR3(GetMove().x + sinf(CameraRot * D3DX_PI + LeftStickAngle) * 3.0f,
				GetMove().y,
				GetMove().z + cosf(CameraRot * D3DX_PI + LeftStickAngle) * 3.0f));

			//向きの設定
			SetRot(D3DXVECTOR3(GetRot().x, ((CameraRot * D3DX_PI) + (LeftStickAngle + D3DX_PI)), GetRot().z));
		}

		return;
	}

	bool colision = Collision::Sphere(GetPos(), pNearEnemy->GetPos(), GetRadius() * 3, pNearEnemy->GetRadius());

	if (colision)
	{
		//進む角度を計算
		float Angle = atan2f(pNearEnemy->GetPos().x - GetPos().x, pNearEnemy->GetPos().z - GetPos().z);

		//向きを設定
		SetRot(D3DXVECTOR3(GetRot().x, Angle + D3DX_PI, GetRot().z));
	}
	else
	{
		if (CManager::GetInstance()->GetJoypad()->Connection())
		{//パッドが接続されているとき

			//カメラの向きを取得
			float CameraRot = CManager::GetInstance()->GetCamera()->GetRot().y;

			//移動値の設定
			SetMove(D3DXVECTOR3(GetMove().x + sinf(CameraRot * D3DX_PI + LeftStickAngle) * 3.0f,
				GetMove().y,
				GetMove().z + cosf(CameraRot * D3DX_PI + LeftStickAngle) * 3.0f));

			//向きの設定
			SetRot(D3DXVECTOR3(GetRot().x, ((CameraRot * D3DX_PI) + (LeftStickAngle + D3DX_PI)), GetRot().z));
		}
	}
}

//==========================
//武器所持時のモーションを設定
//==========================
void CPlayer::SetWeaponMotion(CMotionModel::MOTION_TYPE motion)
{
	if (GetMotion() == motion)
	{
		return;
	}

	SetMotion(motion);

	if (m_weapon != nullptr)
	{
		KeepFirstPos(m_weapon->GetPos(),15);
		KeepFirstRot(m_weapon->GetRot(),15);
	}
}

//==========================
//武器を投げる
//==========================
void CPlayer::ThrowWeapon()
{
	if (m_weapon == nullptr)
	{//武器を持っていない
		return;
	}
	
	m_weapon->ThrowAngle(this);
	m_weapon->SetParent(nullptr);
	//m_weapon->CorrectInfo();
	m_weapon->SetPos(D3DXVECTOR3(m_weapon->GetMtxWorld()._41, m_weapon->GetMtxWorld()._42, m_weapon->GetMtxWorld()._43));
	float CameraRot = CManager::GetInstance()->GetCamera()->GetRot().y;

	//左スティックの角度を取得
	LeftStickAngle = CManager::GetInstance()->GetJoypad()->GetLeftAngle();

	//移動値の設定
	m_weapon->SetMove(D3DXVECTOR3(m_weapon->GetMove().x + sinf(CameraRot * D3DX_PI + LeftStickAngle) * 30.0f,
		m_weapon->GetMove().y,
		m_weapon->GetMove().z + cosf(CameraRot * D3DX_PI + LeftStickAngle) * 30.0f));

	m_weapon = nullptr;//武器の情報を削除
}

//==========================
//被弾回数初期化
//==========================
void CPlayer::ResetDamageNum()
{
	m_DamageNum = 0;
}

//==========================
//被弾回数取得
//==========================
int CPlayer::GetDamageNum()
{
	return m_DamageNum;
}

//==========================
//素手攻撃被弾処理
//==========================
void CPlayer::hit(D3DXVECTOR3 pos, int damage)
{
	if (m_DamageNum >= 3)
	{
		return;
	}

	//被弾回数を増やす
	m_DamageNum++;

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

		if (m_breakweapon)
		{//武器が壊れた

			//待機状態に変更
			auto NewState = DBG_NEW CNeutralState;
			ChangeState(NewState);
		}
	}

	//武器が壊れてないか判定
	State = m_StateMachine->GetState();

	//ライフを減らす
	int Life = GetLife();
	SetLife(Life -= DamageNum);

	if (typeid(*State) != typeid(CGuardState)
		&& typeid(*State) != typeid(CSmallWeaponGuardState))
	{//ガード状態ではない
		Damage();

		if (m_DamageNum >= 3)
		{//3回被弾している
			DamegeBlow(pos);
		}
	}
	else
	{
		//エフェクトを表示する位置
		D3DXVECTOR3 Effectpos = { GetParts(5)->GetMtxWorld()._41,GetParts(5)->GetMtxWorld()._42,GetParts(5)->GetMtxWorld()._43 };

		//ガードエフェクト
		CGuardEffect::Create(Effectpos, GetRot());
	}
}

//==========================
//武器の耐久を減らす
//==========================
void CPlayer::WeaponDamage()
{
	//武器の耐久値を減らす
	m_weapon->SubDurability();

	if (m_weapon->GetDurability() <= 0)
	{//耐久値がなくなったとき
		DeleteParts(15);

		//武器を削除する
		CManager::GetInstance()->GetStageManager()->DeleteObj(*m_weapon);
		m_weapon->Uninit();
		m_weapon = nullptr;
		m_WeaponType = false;

		//武器が壊れた判定に変更
		m_breakweapon = true;
	}
}

//==========================
//ライフの回復
//==========================
void CPlayer::RecoveryLife()
{
	//ライフを回復
	SetLife(GetLife() + 5);

	if (GetLife() >= MAX_LIFE)
	{
		SetLife(MAX_LIFE);
	}
}

//==========================
//武器が壊れたか取得
//==========================
bool CPlayer::GetWeaponBreak()
{
	return m_breakweapon;
}

//==========================
//武器破壊判定をリセット
//==========================
void CPlayer::BreakReset()
{
	m_breakweapon = false;
}

//==========================
//ステージ変更時のステートの変更
//==========================
void CPlayer::StageChangeState()
{
	auto NewState = DBG_NEW CNeutralState;
	ChangeState(NewState);
}