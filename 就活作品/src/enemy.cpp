//==========================
// 
// エネミー[enemy.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "enemy.h"
#include "manager.h"
#include "model.h"
#include "enemymovepoint.h"
#include "player.h"
#include "enemystate.h"
#include"collision.h"

//静的メンバ初期化
const int CEnemy::PRIORITY = 1;//描画順
const float CEnemy::DUSH_DISTANCE = 10.0f;//走る距離
const float CEnemy::DUSH_SPEED = 3.5f;//走る速さ
const float CEnemy::STOP_DISTANCE = 5.0f;//停止する距離
const float CEnemy::WALK_SPEED = 2.0f;//歩く速さ

//==========================
//コンストラクタ
//==========================
CEnemy::CEnemy(int nPriority) :
CCharacter(nPriority),//基底コンストラクタ
m_EnemyType(ENEMY_TYPE::NONE),//敵の種類
m_player(nullptr),//プレイヤーの情報
m_Movable(false),//行動可能か判定
m_Angle(0.0f),//向き
Attackable(true),//攻撃可能判定
m_PlayMotion(true),//モーション再生判定
m_DamageNum(0),//ダメージ回数をカウント
m_Attack(false),//攻撃判定
m_AttackCoolTime(0),
m_ActionWave(0)
{
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Mtx);
}

//==========================
//デストラクタ
//==========================
CEnemy::~CEnemy()
{

}

//==========================
//初期化処理
//==========================
HRESULT CEnemy::Init()
{

	//初期設定
	CCharacter::Init();

	//プレイヤーの情報を取得
	GetPlayerInfo();

	//現在の位置を保存
	SetPosOld(GetPos());

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CEnemy::Uninit()
{
	//終了処理
	CCharacter::Uninit();

	if (m_player != nullptr)
	{
		m_player = nullptr;
	}	
}

//==========================
//更新処理
//==========================
void CEnemy::Update()
{
	//更新処理
	CCharacter::Update();

	//地面との当たり判定
	CollisionFild();
}

//==========================
//描画処理
//==========================
void CEnemy::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&GetMtxWorld());

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxTrans);

	
	if (GetState() == STATE::GRAB)
	{
		D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &m_Mtx);
	}

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());

	//モデルパーツの描画
	PartsDraw();
}

//==========================
//オブジェクト生成
//==========================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CEnemy* pEnemy = DBG_NEW CEnemy;

	//位置の設定
	pEnemy->SetPos(pos);

	//初期化処理
	pEnemy->Init();

	//ファイルを読み込む
	pEnemy->LoadFile("data\\MOTION\\motion_enemy_hit.txt", scale);

	//タイプ設定
	pEnemy->SetType(TYPE::ENEMY);

	return pEnemy;
}

//==========================
//移動処理
//==========================
void CEnemy::Move()
{
	//前回の位置を保存
	SetPosOld(GetPos());

	//移動値の設定
	SetMove(D3DXVECTOR3(GetMove().x += (0 - GetMove().x) * 0.25f,
		GetMove().y,
		GetMove().z += (0 - GetMove().z) * 0.25f));

	//吹き飛びの移動処理
	SetDamegeBlow(D3DXVECTOR3(GetDamegeBlow().x + (0 - GetDamegeBlow().x) * 0.25f,
		GetDamegeBlow().y,
		GetDamegeBlow().z + (0 - GetDamegeBlow().z) * 0.25f));

	SetMove(D3DXVECTOR3(GetMove().x + GetDamegeBlow().x,
		GetMove().y + GetDamegeBlow().y,
		GetMove().z + GetDamegeBlow().z));

	//位置を変更
	SetPos(GetPos() + GetMove());
}

//==========================
//掴まれる処理
//==========================
void CEnemy::BeGrabbed(D3DXMATRIX mtx)
{
	SetState(STATE::GRAB);//掴まれてる状態に変更

	m_Mtx = mtx;//マトリックスの保存

	SetPos(D3DXVECTOR3(15.0f, 0.0f, 50.0f));
	SetRot(D3DXVECTOR3(0.0f, 1.57f, -1.57f));
}

//==========================
//掴まれていない状態に変更
//==========================
void CEnemy::ReleaseGrab(D3DXVECTOR3 rot)
{
	SetState(STATE::NEUTRAL);//通常状態に変更

	SetPos(D3DXVECTOR3(GetMtxWorld()._41, GetMtxWorld()._42, GetMtxWorld()._43));
	SetRot(rot);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Mtx);

}

//==========================
//敵の種類を設定
//==========================
void CEnemy::SetEnemyType(ENEMY_TYPE EnemyType)
{
	m_EnemyType = EnemyType;
}

//==========================
//敵の種類を取得
//==========================
CEnemy::ENEMY_TYPE CEnemy::GetEnemyType()
{
	return m_EnemyType;
}

//==========================
//プレイヤーの情報を取得
//==========================
CPlayer* CEnemy::GetPlayer()
{
	return m_player;
}

//==========================
//地面との当たり判定
//==========================
void CEnemy::CollisionFild()
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

		//オブジェクトをFildクラスにキャスト
		CFild* pFild = (CFild*)pObj;

		if (GetPos().x < pFild->GetPos().x + pFild->GetSize().x
			&& GetPos().x > pFild->GetPos().x - pFild->GetSize().x
			&& GetPos().z < pFild->GetPos().z + pFild->GetSize().z
			&& GetPos().z > pFild->GetPos().z - pFild->GetSize().z)
		{//衝突している
			SetMove(D3DXVECTOR3(GetMove().x, 0.0f, GetMove().z));
			SetPos(D3DXVECTOR3(GetPos().x, pFild->GetPos().y, GetPos().z));
			break;
		}

		pObj = CObject::GetObj(pObj, CFild::PRIORITY);
	}
}

//==========================
//プレイヤーの情報を取得
//==========================
void CEnemy::GetPlayerInfo()
{
	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CPlayer::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CPlayer::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::PLAYER)
		{//オブジェクトがプレイヤーではない
			pObj = CObject::GetObj(pObj, CPlayer::PRIORITY);
			continue;
		}

		CPlayer* pPlayer = (CPlayer*)pObj;

		//プレイヤーの情報を取得
		m_player = pPlayer;

		break;
	}
}

//==========================
//移動可能か取得
//==========================
bool CEnemy::GetMovable()
{
	return m_Movable;
}

//==========================
//行動可能にする
//==========================
void CEnemy::SetMovable()
{
	m_Movable = true;
}

//==========================
//行動出来るか判定
//==========================
void CEnemy::JudgeMovable()
{
	if (m_player == nullptr
		|| m_Movable)
	{//プレイヤーの情報を持ってないかすでに行動可能なとき
		return;
	}

	//球の当たり判定
	bool Colision = Collision::Sphere(GetPos(), m_player->GetPos(), GetRadius() * 30, m_player->GetRadius());
	
	//範囲内に入っている
	if (Colision)
	{
		SetMovable();//行動可能にする
	}
}

//==========================
//攻撃時の移動
//==========================
void CEnemy::AttackMove()
{
	//向きの変更
	ChangeDirection();

	//移動値を設定
	SetMove(D3DXVECTOR3(sinf(m_Angle) * WALK_SPEED, 0.0f, cosf(m_Angle) * WALK_SPEED));
}

//==========================
//ダッシュ判定
//==========================
bool CEnemy::JudgeDush()
{
	
	if (!Collision::Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * DUSH_DISTANCE))
	{//プレイヤーの半径の10倍の距離より遠い
		return true;
	}

	return false;
}

//==========================
//ダッシュ移動処理
//==========================
void CEnemy::Dush()
{
	//向きの変更
	ChangeDirection();

	//移動値を設定
	SetMove(D3DXVECTOR3(sinf(m_Angle) * DUSH_SPEED, 0.0f, cosf(m_Angle) * DUSH_SPEED));
}

//==========================
//歩き判定
//==========================
bool CEnemy::JudgeWalk()
{
	if (Collision::Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * DUSH_DISTANCE)
		&& !JudgeStop())
	{//プレイヤーの半径の10倍の距離より近いかつ停止する距離より遠い
		return true;
	}

	return false;
}

//==========================
//歩き移動処理
//==========================
void CEnemy::Walk()
{
	//向きの変更
	ChangeDirection();

	//移動値を設定
	SetMove(D3DXVECTOR3(sinf(m_Angle) * WALK_SPEED, 0.0f, cosf(m_Angle) * WALK_SPEED));
}

//==========================
//停止判定
//==========================
bool CEnemy::JudgeStop()
{
	if (Collision::Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius(), GetPlayer()->GetRadius() * STOP_DISTANCE))
	{//距離が近い
		return true;
	}

	return false;
}

//==========================
//向きの変更
//==========================
float CEnemy::ChangeDirection()
{
	//進む角度を計算
	m_Angle = atan2f(GetPlayer()->GetPos().x - GetPos().x, GetPlayer()->GetPos().z - GetPos().z);

	//向きを設定
	SetRot(D3DXVECTOR3(GetRot().x, m_Angle + D3DX_PI, GetRot().z));

	return m_Angle;
}

//==========================
//攻撃可能か判定
//==========================
bool CEnemy::GetAttackable()
{
	return Attackable;
}

//==========================
//攻撃可能判定を変更
//==========================
void CEnemy::ChangeAttackable()
{
	Attackable = !Attackable;
}

//==========================
//攻撃範囲にプレイヤーがいるか判定
//==========================
bool CEnemy::JudgeAttackRange()
{
	if (!Collision::Sphere(GetPos(), GetPlayer()->GetPos(), GetRadius()+2.0f, GetPlayer()->GetRadius()+2.0f))
	{//プレイヤーが攻撃範囲にいない

		return true;
	}

	return false;
}

//==========================
//モーションの再生判定を変更
//==========================
void CEnemy::ChangePlayMotion(bool play)
{
	m_PlayMotion = play;
}

//==========================
//モーションの再生判定を取得
//==========================
bool CEnemy::GetPlayMotion()
{
	return m_PlayMotion;
}

//==========================
//被弾回数初期化
//==========================
void CEnemy::ResetDamageNum()
{
	m_DamageNum = 0;
}

//==========================
//被弾回数取得
//==========================
int CEnemy::GetDamageNum()
{
	return m_DamageNum;
}

//==========================
//ダメージ回数を増やす
//==========================
void CEnemy::AddDamegeNum()
{
	m_DamageNum++;
}

//==========================
//プレイヤーへの殴り攻撃の当たり判定
//==========================
void CEnemy::HitPlayer(int PartsNum)
{
	//判定
	bool Colision = Collision::Sphere(D3DXVECTOR3(GetPartsMtx(PartsNum)._41, GetPartsMtx(PartsNum)._42, GetPartsMtx(PartsNum)._43),
		D3DXVECTOR3(GetPlayer()->GetPartsMtx(1)._41, GetPlayer()->GetPartsMtx(1)._42, GetPlayer()->GetPartsMtx(1)._43),
		GetRadius(),
		GetPlayer()->GetRadius());

	//攻撃が当たっている
	if (Colision && !m_Attack)
	{
		//サウンドを再生
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_ATTACK);

		//プレイヤーのダメージ処理
		GetPlayer()->hit(GetPos(), 1);
		m_Attack = true;
	}
}

//==========================
//攻撃判定をリセット
//==========================
void CEnemy::ResetAttack()
{
	m_Attack = false;
}

//==========================
//攻撃のクールタイムを設定
//==========================
void CEnemy::SetCoolTime(int time)
{
	m_AttackCoolTime = time;
}

//==========================
//攻撃のクールタイムを取得
//==========================
int CEnemy::GetCoolTime()
{
	return m_AttackCoolTime;
}

//==========================
//クールタイムを減らす
//==========================
void CEnemy::SubCoolTime()
{
	m_AttackCoolTime--;
}

//==========================
//攻撃を受けたモーションを保存
//==========================
void CEnemy::SetHitMotion(MOTION_TYPE motion)
{
	m_HitMotion = motion;
}

//==========================
//攻撃を受けたモーションを取得
//==========================
CMotionModel::MOTION_TYPE CEnemy::GetHitMotion()
{
	return m_HitMotion;
}

//==========================
//攻撃判定を取得
//==========================
bool CEnemy::GetAttack()
{
	return m_Attack;
}

//==========================
//攻撃判定を設定
//==========================
void CEnemy::SetAttack()
{
	m_Attack = true;
}

//==========================
//行動するウェーブを設定
//==========================
void CEnemy::SetActionWave(int wave)
{
	m_ActionWave = wave;
}

//==========================
//行動するウェーブを取得
//==========================
int CEnemy::GetActionWave()
{
	return m_ActionWave;
}