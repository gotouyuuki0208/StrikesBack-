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
#include "block.h"
#include "bigweapon.h"
#include "smallweapon.h"
#include "boss.h"
#include "jihanki.h"
#include "deliveryperson.h"
#include "effect.h"
#include "particle.h"

//静的メンバ初期化
const int CPlayer::PRIORITY = 1;//描画順
const int CPlayer::MAX_LIFE = 25;//寿命の最大値
const int CPlayer::INPUT_START_FLAME = 24;//入力受付開始フレーム数
const int CPlayer::INPUT_FINISH_FLAME = 60;//入力受付終了フレーム数
const int CPlayer::RESET_FLAME = 54;//コンボの情報リセットフレーム数数
const float CPlayer::MOVE_VALUE = 3.0f;//移動
const float CPlayer::DASH_VALUE = 7.0f;//ダッシュ
const float CPlayer::JUMP_VALUE = 10.0f;//ジャンプ
const float CPlayer::GRAVITY_VALUE = 0.7f;//重力
const float CPlayer::INERTIA_VALUE = 0.5f;//慣性
const float CPlayer::ROT_VALUE = 1.57f;//向き
const float CPlayer::CHARA_WIDTH = 10.0f;//キャラクターのXサイズ
const float CPlayer::CHARA_HEIGHT = 10.0f;//キャラクターのYサイズ

//==========================
//コンストラクタ
//==========================
CPlayer::CPlayer(int nPriority) :
CCharacter(nPriority),//基底クラスのコンストラクタ
m_grab(false),//掴み判定
m_weapon(nullptr), //所持してる武器
//m_GrabEnemy(nullptr),//掴んでる敵
m_boss(nullptr),//ボスの情報を取得
m_FlameCount(0),//フレーム数のカウント用
m_ComboStack{},//攻撃コンボのスタック
m_StackIdx(0),//スタックのTOPの位置
m_Attack(false),//攻撃判定
m_CountAttack(0),//コンボ中に攻撃を当てた回数
m_testdeth(false),
m_DamageCount(0),
m_RecoveryItemStock(0),//アイテムのストック数
m_WeaponType(false),//武器の種類
m_VisualCor(false),//当たり判定の色の設定
m_Avoidance(0),//回避フレーム
LeftStickAngle(0.0f)//左スティックの角度
{
	SetLife(MAX_LIFE);//寿命の設定
	SetComboList();//コンボリストの生成
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
	SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

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

	/*if (m_GrabEnemy != nullptr)
	{
		m_GrabEnemy = nullptr;
	}*/
	
	if (m_boss != nullptr)
	{
		m_boss = nullptr;
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
	{//ステージ遷移中
		return;
	}

	if (!CManager::GetInstance()->GetDebug()->GetBossTest())
	{
		//入力処理
		Input();
	}

	//回避処理
	Avoidance();

	//移動処理
	Move();

	if (GetState() == STATE::ATTACK)
	{
		//攻撃処理
		Attack();
	}

	//地面との当たり判定
	CollisionFild();

	//m_VisualCor = false;

	//敵との当たり判定
	CollisionEnemy();

	ColisionDelevery();

	//モーションの更新
	MotionUpdate();

	//更新処理
	CCharacter::Update();

	if (GetDamage())
	{
		m_DamageCount++;
		if (m_DamageCount >= 54)
		{
			m_DamageCount = 0;
			SetDamage(false);
		}
	}

	//if (m_GrabEnemy != nullptr)
	//{//敵を掴んでいるとき
	//	GrabAttack();
	//}

	//カメラ追従
	CManager::GetInstance()->GetCamera()->Move(D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z));

	//可視化した当たり判定の設定
	//m_Visual->SetPos(GetPos());
	//m_Visual->Update();

	if (!m_VisualCor)
	{
		//m_Visual->SetCorNomal();
	}
	else
	{
		//m_Visual->SetCorCollision();
	}
}

//==========================
//描画処理
//==========================
void CPlayer::Draw()
{
	if (!m_testdeth)
	{
		//描画処理
		CCharacter::Draw();

		//m_Visual->Draw();
	}
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
	//pPlayer->LoadFile("data\\MOTION\\motion_enemy_hit.txt", scale);
	pPlayer->LoadFile("data\\MOTION\\motion_player_15.txt", scale);

	//半径の設定
	pPlayer->SetRadius(15.0f);

	//タイプ設定
	pPlayer->SetType(TYPE::PLAYER);

	//当たり判定可視化
	//pPlayer->m_Visual = CCollisionVisual::Create(pPlayer->GetPos(), pPlayer->GetRadius());
	
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
//入力処理
//==========================
void CPlayer::Input()
{
	if (GetDamage())
	{
		return;
	}

	//攻撃の入力処理
	InputAttack();

	if (GetState() == STATE::NEUTRAL
		|| GetState() == STATE::MOVE)
	{
		//移動の入力処理
		InputMove();
	}
}

//==========================
//攻撃関係の入力処理
//==========================
void CPlayer::InputAttack()
{
	if (GetState() != STATE::GUARD)
	{
		if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_J)
			|| CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_Y))
		{//攻撃
			SetState(STATE::ATTACK);
		}

		if (m_weapon == nullptr)
		{//武器を持っていないとき
			if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_O)
				|| CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_B))
			{//武器を拾う
				PickUpWeapon();
			}
		}
		else if (m_weapon != nullptr)
		{
			if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_P)
				|| CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_B))
			{//武器を手放す

				if (CManager::GetInstance()->GetJoypad()->Connection())
				{//パッドが接続されている
					if (CManager::GetInstance()->GetJoypad()->GetLeftStick())
					{//左スティックが入力されている
						ThrowWeapon();
						return;
					}
				}
				ReleaseWeapon();
			}
		}
	}
	
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_B)
		|| CManager::GetInstance()->GetJoypad()->GetPress(CInputJoypad::JOYKEY_X))
	{
		if ((GetMotion() == MOTION_TYPE::MOVE
			|| GetMotion() == MOTION_TYPE::NEUTRAL
			|| GetMotion() == MOTION_TYPE::SMALLWEAPONNEUTRAL)
			&& GetState() != STATE::ATTACK)
		{
			Guard();
		}
	}
	if (CManager::GetInstance()->GetKeyboard()->GetRelease(DIK_B)
		|| CManager::GetInstance()->GetJoypad()->GetRelease(CInputJoypad::JOYKEY_X))
	{
		SetState(STATE::NEUTRAL);
	}

	if (CManager::GetInstance()->GetJoypad()->GetRelease(CInputJoypad::JOYKEY_A))
	{
		SetState(STATE::AVOIDANCE);
	}
}

//==========================
//ガード処理
//==========================
void CPlayer::Guard()
{
	if (m_weapon != nullptr&&!m_WeaponType)
	{//両手武器を持っているとき
		return;
	}

	if (m_WeaponType)
	{//片手武器を持っているとき
		SetWeaponMotion(MOTION_TYPE::SMALLWEAPONGUARD);
	}
	else
	{//素手のとき
		SetMotion(MOTION_TYPE::GUARD);
	}

	SetState(STATE::GUARD);
}

//==========================
//移動の入力処理
//==========================
void CPlayer::InputMove()
{
	float move = MOVE_VALUE;
	float CameraRot = CManager::GetInstance()->GetCamera()->GetRot().y;

	if (m_weapon == nullptr
		|| (m_weapon != nullptr && m_WeaponType))
	{
		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_LSHIFT)
			|| CManager::GetInstance()->GetJoypad()->GetTriggerPedal(CInputJoypad::JOYKEY_LEFT_TRIGGER))
		{//ダッシュ

			move = DASH_VALUE;
		}
	}

	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
	{//奥に移動

		//移動値の設定
		SetMove(D3DXVECTOR3(GetMove().x + sinf(CameraRot * D3DX_PI)* move,
			GetMove().y,
			GetMove().z + cosf(CameraRot * D3DX_PI) * move));
		
		//向きの設定
		//SetRotMove(D3DXVECTOR3(GetRotMove().x, CameraRot * D3DX_PI-3.14f, GetRotMove().z));

		SetRot(D3DXVECTOR3(GetRot().x, CameraRot * D3DX_PI - 3.14f, GetRot().z));

		if (move == MOVE_VALUE)
		{
			if (!m_WeaponType
				&&m_weapon->GetGrab())
			{
				SetWeaponMotion(MOTION_TYPE::WEAPONMOVE);//移動モーション
			}
			else
			{
				SetMotion(MOTION_TYPE::MOVE);//移動モーション
			}
		}
		else if (move == DASH_VALUE)
		{
			SetMotion(MOTION_TYPE::DUSH);//移動モーション
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_A))
	{//左に移動

		//移動値の設定
		SetMove(D3DXVECTOR3(GetMove().x + sinf(CameraRot * D3DX_PI-(D3DX_PI/2)) * move,
			GetMove().y,
			GetMove().z + cosf(CameraRot * D3DX_PI - (D3DX_PI / 2)) * move));

		//向きの設定
		//SetRotMove(D3DXVECTOR3(GetRotMove().x, CameraRot * D3DX_PI + D3DX_PI / 2, GetRotMove().z));
		SetRot(D3DXVECTOR3(GetRot().x, CameraRot * D3DX_PI + D3DX_PI / 2, GetRot().z));
		
		if (move == MOVE_VALUE)
		{
			if (!m_WeaponType
				&& m_weapon->GetGrab())
			{
				SetWeaponMotion(MOTION_TYPE::WEAPONMOVE);//移動モーション
			}
			else
			{
				SetMotion(MOTION_TYPE::MOVE);//移動モーション
			}
		}
		else if (move == DASH_VALUE)
		{
			SetMotion(MOTION_TYPE::DUSH);//移動モーション
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
	{//手前に移動
		SetMove(D3DXVECTOR3(GetMove().x - sinf(CameraRot * D3DX_PI) * move,
			GetMove().y,
			GetMove().z - cosf(CameraRot * D3DX_PI) * move));

		//向きの設定
		//SetRotMove(D3DXVECTOR3(GetRotMove().x, CameraRot * 0.0f, GetRotMove().z));
		SetRot(D3DXVECTOR3(GetRot().x, CameraRot * D3DX_PI, GetRot().z));

		if (move == MOVE_VALUE)
		{
			if (!m_WeaponType
				&& m_weapon->GetGrab())
			{
				SetWeaponMotion(MOTION_TYPE::WEAPONMOVE);//移動モーション
			}
			else
			{
				SetMotion(MOTION_TYPE::MOVE);//移動モーション
			}
		}
		else if (move == DASH_VALUE)
		{
			SetMotion(MOTION_TYPE::DUSH);//移動モーション
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_D))
	{//右に移動
		SetMove(D3DXVECTOR3(GetMove().x - sinf(CameraRot * D3DX_PI - (D3DX_PI / 2)) * move,
			GetMove().y,
			GetMove().z - cosf(CameraRot * D3DX_PI - (D3DX_PI / 2)) * move));

		//向きの設定
		//SetRotMove(D3DXVECTOR3(GetRotMove().x, CameraRot * D3DX_PI - D3DX_PI / 2, GetRotMove().z));
		SetRot(D3DXVECTOR3(GetRot().x, CameraRot * D3DX_PI - D3DX_PI / 2, GetRot().z));

		if (move == MOVE_VALUE)
		{
			if (!m_WeaponType
				&& m_weapon->GetGrab())
			{
				SetWeaponMotion(MOTION_TYPE::WEAPONMOVE);//移動モーション
			}
			else
			{
				SetMotion(MOTION_TYPE::MOVE);//移動モーション
			}
		}
		else if (move == DASH_VALUE)
		{
			SetMotion(MOTION_TYPE::DUSH);//移動モーション
		}
	}
	else
	{//移動していない
		//if (GetMotion() == MOTION_TYPE::MOVE
		//	|| GetMotion() == MOTION_TYPE::DUSH)
		//{
		//	if (m_weapon!=nullptr)
		//	{
		//		if (m_WeaponType)
		//		{
		//			SetMotion(MOTION_TYPE::SMALLWEAPONNEUTRAL);//待機モーション
		//		}
		//		else
		//		{
		//			SetMotion(MOTION_TYPE::WEAPONNEUTRAL);//待機モーション
		//		}
		//	}
		//	else
		//	{
		//		SetMotion(MOTION_TYPE::NEUTRAL);//待機モーション
		//	}
		//}

		//SetState(STATE::NEUTRAL);
	}

	if (CManager::GetInstance()->GetJoypad()->Connection())
	{//パッドが接続されているとき

		if (!CManager::GetInstance()->GetJoypad()->GetLeftStick())
		{//左スティックを入力していない

			//停止時のモーションに設定
			if (m_weapon != nullptr)
			{
				if (m_WeaponType)
				{
					SetWeaponMotion(MOTION_TYPE::SMALLWEAPONNEUTRAL);//待機モーション
				}
				else
				{
					SetWeaponMotion(MOTION_TYPE::WEAPONNEUTRAL);//待機モーション
				}
			}
			else
			{
				SetMotion(MOTION_TYPE::NEUTRAL);//待機モーション
			}
			return;
		}

		//左スティックの角度を取得
		LeftStickAngle = CManager::GetInstance()->GetJoypad()->GetLeftAngle();
		
		//移動値の設定
		SetMove(D3DXVECTOR3(GetMove().x + sinf(CameraRot * D3DX_PI+ LeftStickAngle) * move,
			GetMove().y,
			GetMove().z + cosf(CameraRot * D3DX_PI + LeftStickAngle) * move));
		
		//向きの設定
		SetRot(D3DXVECTOR3(GetRot().x, ((CameraRot* D3DX_PI) + (LeftStickAngle + D3DX_PI)), GetRot().z));

		//モーションの設定
		if (move == MOVE_VALUE)
		{
			if (m_weapon!=nullptr)
			{
				if (!m_WeaponType
					&& m_weapon->GetGrab())
				{
					SetWeaponMotion(MOTION_TYPE::WEAPONMOVE);//移動モーション
				}
			}
			else
			{
				SetMotion(MOTION_TYPE::MOVE);//移動モーション
			}
		}
		else if (move == DASH_VALUE)
		{
			SetMotion(MOTION_TYPE::DUSH);//移動モーション
		}
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_N))
	{
		Recovery();
	}

	//今のモーションを保存
	SetOldMotion(GetMotion());
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

	
	SetDamegeBlow(D3DXVECTOR3(GetDamegeBlow().x += (0 - GetDamegeBlow().x) * 0.25f,
		GetDamegeBlow().y,
		GetDamegeBlow().z += (0 - GetDamegeBlow().z) * 0.25f));
	
	//吹き飛び時の移動
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
	if (GetState() != STATE::AVOIDANCE)
	{
		return;
	}

	m_Avoidance++;

	if (CManager::GetInstance()->GetJoypad()->Connection())
	{//パッドが接続されているとき

		//カメラの向きを取得
		float CameraRot = CManager::GetInstance()->GetCamera()->GetRot().y;

		//移動値の設定
		SetMove(D3DXVECTOR3(GetMove().x - sinf(CameraRot * D3DX_PI + LeftStickAngle) * 7.0f,
			GetMove().y,
			GetMove().z - cosf(CameraRot * D3DX_PI + LeftStickAngle) * 7.0f));

		//向きの設定
		SetRot(D3DXVECTOR3(GetRot().x, ((CameraRot * D3DX_PI) + (LeftStickAngle + D3DX_PI)), GetRot().z));
	}

	SetMotion(MOTION_TYPE::AVOIDANCE_BACK);

	if (m_Avoidance == 10)
	{
		m_Avoidance = 0;
		SetState(STATE::NEUTRAL);
	}
}

//==========================
//攻撃処理
//==========================
void CPlayer::Attack()
{
	
	if (GetDamage())
	{//ダメージを受けている
		return;
	}

	if (GetOldMotion() == GetMotion())
	{//前回のモーションと今のモーションが同じ

		//今のモーションを保存
		SetOldMotion(GetMotion());

		if (m_weapon != nullptr)
		{
			SetWeaponMotion(Pop());
		}
		else
		{
			//攻撃モーションに変更
			SetMotion(Pop());
		}
	}

	if (m_FlameCount > 10 && m_FlameCount < 24)
	{
		//自販機への当たり判定
		CollisionJihankiAttack();

		//配達員への当たり判定
		ColisionDeleveryAttack();
		
		//敵への攻撃判定
		if (m_weapon==nullptr)
		{//武器を持っていない
			CollisionHitEnemy();
		}
		else
		{
			CollisionWeaponEnemy();
		}

		CorrectionAngle();
	}
	else
	{
		for (int i = 0; i < MAX_PARTS; i++)
		{
			if (GetPartsExistence(i))
			{
				//GetParts(i)->VisualDelete();
			}
		}
	}

	m_FlameCount++;

	if (m_FlameCount > INPUT_START_FLAME && m_FlameCount <= INPUT_FINISH_FLAME && m_StackIdx>0)
	{
		if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_J)
			|| CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_Y))
		{
			//モーションを再生
			if (m_weapon != nullptr)
			{
				SetWeaponMotion(Pop());
			}
			else
			{
				//攻撃モーションに変更
				SetMotion(Pop());
			}

			CorrectionAngle();

			m_FlameCount = 0;
			m_Attack = false;
			
		}
	}
	else if (m_FlameCount > INPUT_FINISH_FLAME || (m_FlameCount > RESET_FLAME && m_StackIdx <= 0))
	{
		//今のモーションを保存
		SetOldMotion(GetMotion());

		//通常状態に変更
		SetState(STATE::NEUTRAL);

		if (m_weapon!=nullptr)
		{//武器を持ってるとき

			if (m_WeaponType)
			{//片手武器のとき
				SetWeaponMotion(MOTION_TYPE::SMALLWEAPONNEUTRAL);//待機モーション
			}
			else
			{//両手武器のとき
				SetWeaponMotion(MOTION_TYPE::WEAPONNEUTRAL);//待機モーション
			}
		}

		//コンボのスタックをリセット
		ResetStak();

		m_FlameCount = 0;

		m_Attack = false;

		m_CountAttack = 0;

		for (int i = 0; i < MAX_PARTS; i++)
		{
			if (GetPartsExistence(i))
			{
				//GetParts(i)->VisualDelete();
			}
		}
		
	}
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
//武器所持判定
//==========================
void CPlayer::DeleteWeapon()
{
	m_weapon = nullptr;
	SetComboList();
}

//==========================
//コンボリストの生成
//==========================
void CPlayer::SetComboList()
{
	if (m_weapon == nullptr)
	{//武器を持っていない
		m_ComboList[0] = MOTION_TYPE::ATTACK;
		m_ComboList[1] = MOTION_TYPE::ATTACK2;
		m_ComboList[2] = MOTION_TYPE::ATTACK3;
	}
	else
	{//武器を持っている
		if (m_WeaponType)
		{//片手武器
			m_ComboList[0] = MOTION_TYPE::SMALLWEAPONATTACK;
			m_ComboList[1] = MOTION_TYPE::SMALLWEAPONATTACK2;
			m_ComboList[2] = MOTION_TYPE::SMALLWEAPONATTACK3;

		}
		else
		{//両手武器
			m_ComboList[0] = MOTION_TYPE::WEAPONATTACK;
			m_ComboList[1] = MOTION_TYPE::WEAPONATTACK2;
			m_ComboList[2] = MOTION_TYPE::WEAPONATTACK3;
		}
	}

	ResetStak();//スタックのリセット
}

//==========================
//ダメージ処理
//==========================
void CPlayer::Damage(int damage)
{
	if (GetState() != STATE::GUARD)
	{
		SetLife(GetLife()- damage);
		SetMotion(MOTION_TYPE::DAMAGE);
		m_DamageCount = 0;
		SetDamage(true);
		
		//コンボのスタックをリセット
		ResetStak();
		m_FlameCount = 0;
		m_Attack = false;
		m_CountAttack = 0;
	}
	
	if (GetState() == STATE::GUARD)
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_GUARD);

	}

	if (GetLife() <= 0)
	{
		m_testdeth = true;
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
//入力受付時間を取得
//==========================
int CPlayer::GetInputFrame()
{
	return m_FlameCount;
}

//==========================
//掴み攻撃の処理
//==========================
void CPlayer::GrabAttack()
{
	/*m_FlameCount++;

	if (m_FlameCount > 3 && m_FlameCount <=31)
	{
		m_GrabEnemy->BeGrabbed(GetParts(5)->GetMtxWorld());
	}
	else if(m_FlameCount>31)
	{
		ReleaseEnemy();
		m_FlameCount = 0;
	}*/
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

		bool Colision = ColisionSphere(GetPos(),
			pBoss->GetPos(),
			GetRadius(),
			pBoss->GetRadius());

		if (Colision)
		{
			//m_VisualCor = true;

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
void CPlayer::CollisionHitEnemy()
{
	if (m_StackIdx != 1)
	{
		//GetParts(8)->CreateVisual(D3DXVECTOR3(GetPartsMtx(8)._41, GetPartsMtx(8)._42, GetPartsMtx(8)._43), 20.0f);
	}
	else
	{
		//GetParts(5)->CreateVisual(D3DXVECTOR3(GetPartsMtx(5)._41, GetPartsMtx(5)._42, GetPartsMtx(5)._43), 15.0f);
	}

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

		CEnemy* pEnemy = (CEnemy*)pObj;

		bool Colision;

		if (m_StackIdx != 1)
		{
			Colision = ColisionSphere(D3DXVECTOR3(GetPartsMtx(8)._41 + 5.0f, GetPartsMtx(8)._42, GetPartsMtx(8)._43),
				D3DXVECTOR3(pEnemy->GetPartsMtx(1)._41, pEnemy->GetPartsMtx(1)._42, pEnemy->GetPartsMtx(1)._43),
				20.0f,
				15.0f);
		}
		else
		{
			Colision = ColisionSphere(D3DXVECTOR3(GetPartsMtx(5)._41 + 5.0f, GetPartsMtx(5)._42, GetPartsMtx(5)._43),
				D3DXVECTOR3(pEnemy->GetPartsMtx(1)._41, pEnemy->GetPartsMtx(1)._42, pEnemy->GetPartsMtx(1)._43),
				15.0f,
				15.0f);
		}

		//pEnemy->DamageVisual(1, 15.0f);

		if (Colision && !m_Attack)
		{
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

			if (m_StackIdx != 1)
			{
				//GetParts(8)->GetVisual()->SetCorCollision();

				for (int i = 0; i < 3; i++)
				{
					CEffect::Create(D3DXVECTOR3(GetPartsMtx(8)._41, GetPartsMtx(8)._42, GetPartsMtx(8)._43), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f),15.0f,15.0f);
				}
			}
			else
			{
				//GetParts(5)->GetVisual()->SetCorCollision();

				for (int i = 0; i < 3; i++)
				{
					CEffect::Create(D3DXVECTOR3(GetPartsMtx(5)._41, GetPartsMtx(5)._42, GetPartsMtx(5)._43), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 15.0f, 15.0f);
				}
			}
			

			//ダメージ処理
			pEnemy->Damage(1);
			m_Attack = true;
			CManager::GetInstance()->GetCamera()->SetShape(5, 5);
			m_CountAttack++;
			if (m_StackIdx <= 0 && m_CountAttack >= 3)
			{
				if (!CManager::GetInstance()->GetDebug()->GetPlayerTest())
				{
					//吹き飛び
					pEnemy->DamegeBlow(GetPos());

				}
			}
		}

		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
	}
}

//==========================
//敵を武器で殴るときの当たり判定
//==========================
void CPlayer::CollisionWeaponEnemy()
{
	//GetParts(15)->CreateVisual(D3DXVECTOR3(GetPartsMtx(8)._41, GetPartsMtx(8)._42, GetPartsMtx(8)._43), 30.0f);

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

		CEnemy* pEnemy = (CEnemy*)pObj;

		bool Colision = ColisionSphere(D3DXVECTOR3(m_weapon->GetMtxWorld()._41, m_weapon->GetMtxWorld()._42, m_weapon->GetMtxWorld()._43),
			D3DXVECTOR3(pEnemy->GetPartsMtx(1)._41, pEnemy->GetPartsMtx(1)._42, pEnemy->GetPartsMtx(1)._43),
			30.0f,
			30.0f);

		//pEnemy->DamageVisual(1, 30.0f);

		if (Colision && !m_Attack)
		{
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_WEAOPNATTACK);

			for (int i = 0; i < 20; i++)
			{
				CParticle::Create(D3DXVECTOR3(m_weapon->GetMtxWorld()._41, m_weapon->GetMtxWorld()._42, m_weapon->GetMtxWorld()._43),
					D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
					10,
					1.0f,
					1.0f,
					10.0f);

			}

			for (int i = 0; i < 3; i++)
			{
				CEffect::Create(D3DXVECTOR3(m_weapon->GetMtxWorld()._41, m_weapon->GetMtxWorld()._42, m_weapon->GetMtxWorld()._43), D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 15.0f, 15.0f);
			}

			//GetParts(15)->GetVisual()->SetCorCollision();
			if (m_weapon->GetWeaponType() == CWeapon::WEAPONTYPE::SMALL)
			{
				pEnemy->Damage(2);
			}
			else
			{
				pEnemy->Damage(3);
			}
			m_Attack = true;
			m_weapon->SubDurability();//武器の耐久値を減らす
			if (m_StackIdx <= 0)
			{
				if (!CManager::GetInstance()->GetDebug()->GetPlayerTest())
				{
					//吹き飛び
					pEnemy->DamegeBlow(GetPos());
				}
			}

			if (m_weapon->GetDurability() <= 0)
			{//耐久値がなくなったとき
				DeleteParts(15);
				SetMotion(MOTION_TYPE::NEUTRAL);//待機モーション

				//武器を削除する
				CManager::GetInstance()->GetStageManager()->DeleteObj(*m_weapon);
				m_weapon->Uninit();
				m_weapon = nullptr;
				m_WeaponType = false;

				SetComboList();//コンボリストの生成
				break;
			}
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

		bool Colision = ColisionSphere(D3DXVECTOR3(GetPartsMtx(5)._41, GetPartsMtx(5)._42, GetPartsMtx(5)._43),
			D3DXVECTOR3(pJihan->GetPos().x, pJihan->GetPos().y+20.0f, pJihan->GetPos().z),
			10.0f,
			30.0f);

		//pJihan->DamageVisual(D3DXVECTOR3(pJihan->GetPos().x, pJihan->GetPos().y + 30.0f, pJihan->GetPos().z),
			//30.0f);

		if (Colision && !m_Attack)
		{
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

			//ダメージ処理
			pJihan->Damage(1);
			m_Attack = true;
			CManager::GetInstance()->GetCamera()->SetShape(5, 5);
			m_CountAttack++;
		}

		pObj = CObject::GetObj(pObj, CJihanki::PRIORITY);
	}
}

//==========================
//配達員の攻撃当たり判定
//==========================
void CPlayer::ColisionDeleveryAttack()
{
	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CDeliveryPerson::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CDeliveryPerson::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::DELIVERY)
		{//オブジェクトが配達員ではない
			pObj = CObject::GetObj(pObj, CDeliveryPerson::PRIORITY);
			continue;
		}

		CDeliveryPerson* pDelivery = (CDeliveryPerson*)pObj;

		bool Colision = ColisionSphere(D3DXVECTOR3(GetPartsMtx(5)._41, GetPartsMtx(5)._42, GetPartsMtx(5)._43),
			D3DXVECTOR3(pDelivery->GetPartsMtx(1)._41, pDelivery->GetPartsMtx(1)._42, pDelivery->GetPartsMtx(1)._43),
			10.0f,
			30.0f);

		if (Colision && !m_Attack)
		{
			//ダメージ処理
			pDelivery->Damage(1);
			m_Attack = true;
			CManager::GetInstance()->GetCamera()->SetShape(5, 5);
			m_CountAttack++;
		}

		pObj = CObject::GetObj(pObj, CDeliveryPerson::PRIORITY);
	}
}

//==========================
//配達員の当たり判定
//==========================
void CPlayer::ColisionDelevery()
{
	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CDeliveryPerson::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CDeliveryPerson::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::DELIVERY)
		{//オブジェクトが配達員ではない
			pObj = CObject::GetObj(pObj, CDeliveryPerson::PRIORITY);
			continue;
		}

		CDeliveryPerson* pDelivery = (CDeliveryPerson*)pObj;

		bool Colision = ColisionSphere(GetPos(),
			pDelivery->GetPos(),
			GetRadius(),
			pDelivery->GetRadius());

		pDelivery->Movable();//移動可能にする

		if (Colision)
		{
			//m_VisualCor = true;

			pDelivery->Immovable();//移動不可能にする
		}

		pObj = CObject::GetObj(pObj, CDeliveryPerson::PRIORITY);
	}
}

//==========================
//敵を掴む処理
//==========================
void CPlayer::GrabEnemy()
{
	/*if (m_GrabEnemy != nullptr)
	{
		return;
	}*/

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

		CEnemy* pEnemy = (CEnemy*)pObj;

		bool colision = ColisionSphere(GetPos(), pEnemy->GetPos(), 10.0f, 30.0f);

		if (colision)
		{
			//SetMotion(MOTION_TYPE::GRABATTACK);
			//pEnemy->SetMotion(MOTION_TYPE::GRAB);
			//pEnemy->SetMotion(MOTION_TYPE::GRAB);
			//pEnemy->BeGrabbed(GetParts(5)->GetMtxWorld());
			//m_GrabEnemy = pEnemy;
		}

		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
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

		bool colision = ColisionSphere(GetPos(), pWeapon->GetPos(), GetRadius(), pWeapon->GetRadius());

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
			
			SetComboList();//コンボリストの生成
			break;
		}

		pObj = CObject::GetObj(pObj, CWeapon::PRIORITY);
	}
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

	SetMotion(MOTION_TYPE::NEUTRAL);//待機モーション
	SetComboList();//コンボリストの生成
}

//==========================
//敵を放す
//==========================
void CPlayer::ReleaseEnemy()
{
	/*if (m_GrabEnemy != nullptr)
	{
		m_GrabEnemy->ReleaseGrab(D3DXVECTOR3(GetParts(5)->GetRot().x, GetRot().y+D3DX_PI, 0.0f));
		m_GrabEnemy->Damage(10);
		m_GrabEnemy = nullptr;
	}*/
}

//==========================
//データの追加
//==========================
void CPlayer::Push(MOTION_TYPE motion)
{
	if (m_StackIdx < 3)
	{
		m_ComboStack[m_StackIdx++] = motion;
	}
}

//==========================
//データの取り出し
//==========================
CMotionModel::MOTION_TYPE CPlayer::Pop()
{
	if (m_StackIdx <= 0)
	{
		if (m_weapon != nullptr)
		{//武器を持ってるとき
			if (m_WeaponType)
			{//片手武器
				return MOTION_TYPE::SMALLWEAPONNEUTRAL;//待機モーション
			}
			else
			{
				return MOTION_TYPE::WEAPONNEUTRAL;//待機モーション
			}
		}
		else
		{//武器を持っていない
			return MOTION_TYPE::NEUTRAL;
		}
	}

	return m_ComboStack[--m_StackIdx];

}

//==========================
//スタックの情報を戻す
//==========================
void CPlayer::ResetStak()
{
	m_StackIdx = 0;
	for (int i = 2; i >= 0; i--)
	{
		Push(m_ComboList[i]);
	}
}

//==========================
//回復アイテムを使用
//==========================
void CPlayer::Recovery()
{
	if (m_RecoveryItemStock <= 0)
	{
		return;
	}

	m_RecoveryItemStock--;//アイテム数を減らす

	SetLife(GetLife() + 2);//回復
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

	bool colision = ColisionSphere(GetPos(), pNearEnemy->GetPos(), GetRadius() * 3, pNearEnemy->GetRadius());

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

	SetMotion(MOTION_TYPE::NEUTRAL);//待機モーション
	SetComboList();//コンボリストの生成
}