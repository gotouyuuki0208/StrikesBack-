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

//静的メンバ初期化
const int CEnemy::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CEnemy::CEnemy(int nPriority) :
CCharacter(nPriority),//基底コンストラクタ
m_AttackState(ATTACK_STATE::USUALLY),//攻撃方法
m_EnemyType(ENEMY_TYPE::NONE),//敵の種類
m_player(nullptr),//プレイヤーの情報
m_Movable(false),//行動可能か判定
m_CurPoint(0)//現在の移動地点
{
	for (int i = 0; i < POINT;i++)
	{
		m_Point[i] = nullptr;//移動地点の情報
	}
	
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
	
	for (int i = 0; i < POINT; i++)
	{
		if (m_Point[i] != nullptr)
		{
			m_Point[i] = nullptr;
		}
	}
}

//==========================
//更新処理
//==========================
void CEnemy::Update()
{
	//移動処理
	Move();

	//モーションの更新
	//Motion();

	//更新処理
	CCharacter::Update();

	//地面との当たり判定
	CollisionFild();

	//敵同士の当たり判定
	ColisionEnemy();

	if (GetDamage())
	{
		if (m_player->GetInputFrame() >= 54)
		{

			SetDamage(false);
		}
	}

	
	if (GetLife() <= 0)
	{
		CManager::GetInstance()->GetStageManager()->DeleteObj(*this);
		Uninit();
	}

	//if (m_visual != nullptr)
	{
		//m_visual->SetPos(GetPos());
	}
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

	//if (m_visual != nullptr)
	{
		//m_visual->Draw();
	}
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
	/*if (m_state == STATE::GRAB)
	{
		return;
	}*/

	SetDamegeBlow(D3DXVECTOR3(GetDamegeBlow().x + (0 - GetDamegeBlow().x) * 0.25f,
		GetDamegeBlow().y - 1.0f,
		GetDamegeBlow().z + (0 - GetDamegeBlow().z) * 0.25f));

	SetMove(GetDamegeBlow());

	SetPos(GetPos() + GetDamegeBlow());
}

//==========================
//ダメージを受けたときの処理
//==========================
void CEnemy::Damage(int damage)
{
	if (!CManager::GetInstance()->GetDebug()->GetPlayerTest())
	{
		if (GetState() != STATE::GUARD)
		{//ガードしてないとき

			//寿命を減らす
			SetLife(GetLife() - damage);

			//ダメージ状態に変更
			SetDamage(true);

			//ダメージモーションに設定
			SetMotion(MOTION_TYPE::DAMAGE);
		}
		else
		{//ガードしてるとき

			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL::SOUND_LABEL_SE_GUARD);

			if (m_player->GetHaveWeapon())
			{//プレイヤーが武器をもっている

				//寿命を減らす
				int Damage = damage / 2;

				if (Damage < 1)
				{//ダメージが1より小さいとき
					Damage = 1;
				}
				SetLife(GetLife() - Damage);

				//ダメージ状態に変更
				SetDamage(true);
			}
		}
	}
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
//状態の設定
//==========================
void CEnemy::SetAttackState(ATTACK_STATE state)
{
	m_AttackState = state;
}

//==========================
//状態の取得
//==========================
CEnemy::ATTACK_STATE CEnemy::GetAttackState()
{
	return m_AttackState;
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
//敵同士の当たり判定
//==========================
void CEnemy::ColisionEnemy()
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

		if (pObj == this)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//オブジェクトがフィールドではない
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = (CEnemy*)pObj;

		bool Colision = ColisionSphere(GetPos(),
			pEnemy->GetPos(),
			GetRadius(),
			pEnemy->GetRadius());

		if (Colision)
		{
			D3DXVECTOR3 Vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きベクトル
			D3DXVECTOR3 NormalizeVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//正規化したベクトル

			//向きベクトルを算出
			Vector.x = VectorCalculation(pEnemy->GetPos().x, GetPos().x);
			Vector.z = VectorCalculation(pEnemy->GetPos().z, GetPos().z);

			//ベクトルを正規化
			D3DXVec3Normalize(&NormalizeVec, &Vector);

			//位置を変更
			pEnemy->SetPos(D3DXVECTOR3(GetPos().x + NormalizeVec.x * (GetRadius() + pEnemy->GetRadius()),
				GetPos().y,
				GetPos().z + NormalizeVec.z * (GetRadius() + pEnemy->GetRadius())));
		}

		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
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
void CEnemy::judgeMovable()
{
	if (m_player == nullptr
		|| m_Movable)
	{//プレイヤーの情報を持ってないかすでに行動可能なとき
		return;
	}

	bool Colision = ColisionSphere(GetPos(), m_player->GetPos(), GetRadius() * 30, m_player->GetRadius());
	
	if (Colision)
	{
		SetMovable();//行動可能にする
	}
}

//==========================
//移動地点を取得
//==========================
void CEnemy::GetMovePoint()
{
	if (m_Point[0] != nullptr)
	{
		return;
	}

	int Point = 0;

	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CEnemyMovePoint::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CEnemyMovePoint::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::FILD)
		{//オブジェクトがプレイヤーではない
			pObj = CObject::GetObj(pObj, CEnemyMovePoint::PRIORITY);
			continue;
		}
		
		CFild* pFild = dynamic_cast<CFild*>(pObj);

		if (pFild->GetFildType() != CFild::FILDTYPE::ENEMYMOVEPOINT)
		{//移動地点ではない
			pObj = CObject::GetObj(pObj, CEnemyMovePoint::PRIORITY);
			continue;
		}

		CEnemyMovePoint* pPoint = dynamic_cast<CEnemyMovePoint*>(pObj);

		m_Point[Point] = pPoint;
		Point++;

		pObj = CObject::GetObj(pObj, CEnemyMovePoint::PRIORITY);
	}

	CEnemyMovePoint* pPoint = nullptr;
	float distance = 0.0f;

	//一番近いポイントを取得
	for (int i = 0; i < POINT; i++)
	{
		if (m_Point[i] == nullptr)
		{
			break;
		}

		float newdistance = (m_Point[i]->GetPos().x - GetPos().x) * (m_Point[i]->GetPos().x - GetPos().x) +
			(m_Point[i]->GetPos().z - GetPos().z) * (m_Point[i]->GetPos().z - GetPos().z);

		if (distance == 0.0f || newdistance <= distance)
		{
			distance = newdistance;//距離を保存
			pPoint = m_Point[i];//移動地点の情報を保存
		}
	}

	for (int i = 0; i < POINT; i++)
	{
		if (m_Point[i] == pPoint)
		{
			break;
		}

		m_CurPoint++;
	}
}

//==========================
//移動地点を巡回
//==========================
void CEnemy::Patrol()
{
	//移動地点を取得
	GetMovePoint();

	if (m_Point[m_CurPoint] == nullptr)
	{
		return;
	}

	//進む角度を計算
	float Angle = atan2f(m_Point[m_CurPoint]->GetPos().x - GetPos().x, m_Point[m_CurPoint]->GetPos().z - GetPos().z);

	//向きを設定
	SetRot(D3DXVECTOR3(GetRot().x, Angle + D3DX_PI, GetRot().z));

	//移動値を設定
	SetMove(D3DXVECTOR3(sinf(Angle) * 2.0f, 0.0f, cosf(Angle) * 2.0f));

	//モーションを設定
	SetMotion(MOTION_TYPE::MOVE);

	if (GetPos().x <= m_Point[m_CurPoint]->GetPos().x + 10.0f
		&& GetPos().x >= m_Point[m_CurPoint]->GetPos().x - 10.0f
		&& GetPos().z <= m_Point[m_CurPoint]->GetPos().z + 10.0f
		&& GetPos().z >= m_Point[m_CurPoint]->GetPos().z - 10.0f)
	{//移動地点についた
		m_CurPoint++;

		if (m_Point[m_CurPoint] == nullptr)
		{//次の移動地点がない
			m_CurPoint = 0;
			SetPos(D3DXVECTOR3(m_Point[m_CurPoint]->GetPos().x, 0.0f, m_Point[m_CurPoint]->GetPos().z));
		}

	}

}