//==========================
// 
// 雑魚敵[weakenemy.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "weakenemy.h"
#include "manager.h"
#include "model.h"
#include "enemymovepoint.h"
#include "player.h"
#include "enemystate.h"

//静的メンバ初期化
const int CWeakEnemy::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CWeakEnemy::CWeakEnemy(int nPriority) :
	CEnemy(nPriority),//基底コンストラクタ
	m_CurPoint(0),//現在の移動地点
	m_StateMachine(nullptr),//状態管理
	m_Color(1.0f)
{
	for (int i = 0; i < POINT; i++)
	{
		m_Point[i] = nullptr;//移動地点の情報
	}

	
}

//==========================
//デストラクタ
//==========================
CWeakEnemy::~CWeakEnemy()
{

}

//==========================
//初期化処理
//==========================
HRESULT CWeakEnemy::Init()
{

	//初期設定
	CEnemy::Init();

	//状態管理クラスの作成
	m_StateMachine = DBG_NEW CStateMachine;
	auto NewState = DBG_NEW CEnemyMovabeState;
	ChangeState(NewState);

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CWeakEnemy::Uninit()
{
	//終了処理
	CEnemy::Uninit();

	if (m_StateMachine != nullptr)
	{//状態管理クラスの解放

		delete m_StateMachine;
		m_StateMachine = nullptr;
	}
}

//==========================
//更新処理
//==========================
void CWeakEnemy::Update()
{
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

			//攻撃可能にする
			ChangeAttackable();
		}
	}

	if (GetPlayMotion())
	{//モーションを再生する

		//モーションの更新
		Motion();
	}

	//敵同士の当たり判定
	ColisionEnemy();

	//透明度0で削除
	if (m_Color <= 0.0f)
	{
		Uninit();
	}
}

//==========================
//描画処理
//==========================
void CWeakEnemy::Draw()
{
	CEnemy::Draw();
}

//==========================
//オブジェクト生成
//==========================
CWeakEnemy* CWeakEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CWeakEnemy* pEnemy = DBG_NEW CWeakEnemy;

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
//状態を変更
//==========================
void CWeakEnemy::ChangeState(CEnemyStateBase* NewState)
{
	NewState->SetOwner(this);
	m_StateMachine->ChangeState(NewState);
}

//==========================
//敵同士の当たり判定
//==========================
void CWeakEnemy::ColisionEnemy()
{
	CCollision* pCollision = CManager::GetInstance()->GetCollision();

	//オブジェクトを取得
	CObject* pObj = CObject::GetObj(nullptr, CWeakEnemy::PRIORITY);

	while (pObj != nullptr)
	{
		if (pObj == nullptr)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CWeakEnemy::PRIORITY);
			continue;
		}

		if (pObj == this)
		{//オブジェクトがない
			pObj = CObject::GetObj(pObj, CWeakEnemy::PRIORITY);
			continue;
		}

		//種類の取得
		CObject::TYPE type = pObj->GetType();

		if (type != CObject::TYPE::ENEMY)
		{//オブジェクトがフィールドではない
			pObj = CObject::GetObj(pObj, CWeakEnemy::PRIORITY);
			continue;
		}

		CWeakEnemy* pEnemy = (CWeakEnemy*)pObj;

		bool Colision = pCollision->Sphere(GetPos(),
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

		pObj = CObject::GetObj(pObj, CWeakEnemy::PRIORITY);
	}
}

//==========================
//移動地点を取得
//==========================
void CWeakEnemy::GetMovePoint()
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
void CWeakEnemy::Patrol()
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

//==========================
//攻撃被弾処理
//==========================
void CWeakEnemy::Hit(D3DXVECTOR3 pos, int damage, MOTION_TYPE HitMotion)
{
	
	if (GetDamageNum() >= 3 || GetHitMotion() == HitMotion)
	{//ダメージ回数が3回以上か前回と同じ攻撃
		return;
	}

	//被弾回数を増やす
	AddDamegeNum();

	//攻撃を受けたモーションを保存
	SetHitMotion(HitMotion);

	//ダメージの数値を取得
	int DamageNum = damage;

	//ライフを減らす
	int Life = GetLife();
	SetLife(Life -= DamageNum);

	//ダメージを受けた状態に設定
	SetDamage(true);

	if (GetDamageNum() >= 3)
	{//3回被弾している
		DamegeBlow(pos);
	}

}

//==========================
//パーツの透明度を減らす
//==========================
void CWeakEnemy::SubPartsCol()
{
	//透明度を減らす
	m_Color -= 0.01f;

	//透明度を設定
	SubTransparency(m_Color);
}