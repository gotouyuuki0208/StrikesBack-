//==========================
// 
// 武器[weapon.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "weapon.h"
#include "manager.h"
#include "model.h"
#include "enemy.h"
#include"player.h"

//静的メンバ初期化
const int CWeapon::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CWeapon::CWeapon(int nPriority) :
CObjectX(nPriority),//基底コンストラクタ
//m_nModelIdx(0),//モデルの番号
m_Attack(false),//攻撃判定
m_weapontype(WEAPONTYPE::NONE),//武器の種類
m_Parent(nullptr),//親モデル
m_ModelIdx(0),//モデルの番号
m_WeaponPoint(nullptr),//武器の位置表示
m_Transparent(false),//透明度の上下判定
m_visual(nullptr),//当たり判定の可視化
m_Garb(false),//キャラクターが持ってるか判定
m_Durability(0)//耐久値
{
	
}

//==========================
//デストラクタ
//==========================
CWeapon::~CWeapon()
{

}

//==========================
//初期化処理
//==========================
HRESULT CWeapon::Init()
{
	//サイズ設定
	SetSize();

	//初期設定
	CObjectX::Init();
	
	//UIを生成
	m_WeaponPoint = CWeaponPoint::Create(D3DXVECTOR3(GetPos().x, GetPos().y + GetVtxMax().y + 15.0f, GetPos().z), D3DXVECTOR3(5.0f, 5.0f, 0.0f));
	
	return S_OK;
}

//==========================
//終了処理
//==========================
void  CWeapon::Uninit()
{
	//終了処理
	CObjectX::Uninit();

	if (m_WeaponPoint != nullptr)
	{
		m_WeaponPoint->Uninit();
		m_WeaponPoint = nullptr;
	}

	if (m_visual != nullptr)
	{
		m_visual->Uninit();
		m_visual = nullptr;
	}

	Release();
}

//==========================
//更新処理
//==========================
void CWeapon::Update()
{
	if (m_Garb)
	{//掴まれてるとき
		return;
	}

	ColisionPlayer();

	//更新処理
	CObjectX::Update();

	
}

//==========================
//描画処理
//==========================
void CWeapon::Draw()
{
	if (m_Garb)
	{//掴まれてるとき
		return;
	}

	//描画処理
	CObjectX::Draw();

	if (m_visual != nullptr)
	{
		//m_visual->Draw();
	}
}

//==========================
//オブジェクト生成
//==========================
CWeapon* CWeapon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CWeapon* pWeapon = DBG_NEW CWeapon;

	//位置の設定
	pWeapon->SetPos(pos);

	//向きの設定
	pWeapon->SetRot(D3DXVECTOR3(1.57f, 0.0f, 0.0f));

	//スケールの設定
	pWeapon->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pWeapon->m_ModelIdx = pModel->Regist("data\\MODEL\\bat.x");
	pWeapon->BindModel(pModel->GetMeshAdress(pWeapon->m_ModelIdx),
		pModel->GetBuffMatAdress(pWeapon->m_ModelIdx),
		pModel->GetNumMatAdress(pWeapon->m_ModelIdx),
		pModel->GetTexIdx(pWeapon->m_ModelIdx));

	//初期化処理
	pWeapon->Init();

	//タイプを設定
	pWeapon->SetType(TYPE::WEAPON);
	
	return pWeapon;
}

//==========================
//親の設定
//==========================
void CWeapon::SetParent(CModelParts* Parent)
{
	m_Parent = Parent;
}

//==========================
//敵との当たり判定
//==========================
void CWeapon::CollisionEnemy()
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

		CEnemy* pEnemy = (CEnemy*)pObj;

		bool Colision = ColisionSphere(D3DXVECTOR3(GetMtxWorld()._41, GetMtxWorld()._42 + 5.0f, GetMtxWorld()._43),
			D3DXVECTOR3(pEnemy->GetPartsMtx(0)._41, pEnemy->GetPartsMtx(0)._42, pEnemy->GetPartsMtx(0)._43),
			10.0f,
			30.0f);

		if (Colision
			&&!m_Attack)
		{
			//pEnemy->Damage(D3DXVECTOR3(GetMtxWorld()._41, GetMtxWorld()._42, GetMtxWorld()._43),1);
			m_Attack = true;
		}

		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
	}
}

//==========================
//攻撃判定を戻す
//==========================
void CWeapon::SetAttackReset()
{
	m_Attack = false;
}

//==========================
//武器の種類を取得
//==========================
CWeapon::WEAPONTYPE CWeapon::GetWeaponType()
{
	return m_weapontype;
}

//==========================
//武器の種類を設定
//==========================
void CWeapon::SetWeaponType(WEAPONTYPE weapontype)
{
	m_weapontype = weapontype;
}

//==========================
//モデルの番号を取得
//==========================
int CWeapon::GetModelIdx()
{
	return m_ModelIdx;
}

//==========================
//モデルの番号を設定
//==========================
void CWeapon::SetModelIdx(int num)
{
	m_ModelIdx = num;
}

//==========================
//武器を所持出来るときの反応
//==========================
void CWeapon::Reaction()
{
	if (m_Transparent)
	{
		SetTransparent(GetTransparent() + 0.03f);//透明度をあげる
	}
	else
	{
		SetTransparent(GetTransparent() - 0.03f);//透明度をさげる
	}

	if (GetTransparent() > 1.0f)
	{
		m_Transparent = false;
	}
	else if (GetTransparent() < 0.8f)
	{
		m_Transparent = true;
	}
}

//==========================
//スケールをリセット
//==========================
void CWeapon::Reset()
{
	m_Transparent = false;
	SetTransparent(1.0f);
}

//==========================
//プレイヤーとの当たり判定
//==========================
void CWeapon::ColisionPlayer()
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

		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		bool Colision = ColisionSphere(GetPos(),
			pPlayer->GetPos(),
			GetRadius() - 1.0f,
			pPlayer->GetRadius() - 1.0f);

		if (Colision)
		{

			D3DXVECTOR3 Vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きベクトル
			D3DXVECTOR3 NormalizeVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//正規化したベクトル

			//向きベクトルを算出
			Vector.x = VectorCalculation(pPlayer->GetPos().x, GetPos().x);
			Vector.z = VectorCalculation(pPlayer->GetPos().z, GetPos().z);

			//ベクトルを正規化
			D3DXVec3Normalize(&NormalizeVec, &Vector);

			//位置を変更
			pPlayer->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			pPlayer->SetPos(D3DXVECTOR3(GetPos().x + NormalizeVec.x * floor((GetRadius() - 1.0f + pPlayer->GetRadius())),
				GetPos().y,
				GetPos().z + NormalizeVec.z * floor((GetRadius()-1.0f + pPlayer->GetRadius()))));
		}

		Colision = ColisionSphere(GetPos(),
			pPlayer->GetPos(),
			GetRadius(),
			pPlayer->GetRadius());

		if (Colision)
		{
			Reaction();//透明度を変更
		}
		else
		{
			Reset();//透明度をリセット
		}
		break;
	}
}

//==========================
//当たり判定を可視化する
//==========================
void CWeapon::CreateVisual()
{
	if (m_visual == nullptr)
	{
		//m_visual = CCollisionVisual::Create(GetPos(), GetRadius());
	}
}

//==========================
//キャラクターに掴まれた
//==========================
void CWeapon::GrabCharacter()
{
	m_Garb = true;

	m_WeaponPoint->Uninit();
	m_WeaponPoint = nullptr;
}

//==========================
//キャラクターが放した
//==========================
void CWeapon::ReleseCharacter(D3DXVECTOR3 pos)
{
	//位置を変更
	SetPos(pos);
	//m_visual->SetPos(GetPos());

	//UIを生成
	m_WeaponPoint = CWeaponPoint::Create(D3DXVECTOR3(GetPos().x, GetPos().y + GetVtxMax().y + 15.0f, GetPos().z), D3DXVECTOR3(5.0f, 5.0f, 0.0f));

	//放されてる状態にする
	m_Garb = false;
}

//==========================
//掴まれてるか取得
//==========================
bool CWeapon::GetGrab()
{
	return m_Garb;
}

//==========================
//耐久値の設定
//==========================
void CWeapon::SetDurability(int Num)
{
	m_Durability = Num;
}

//==========================
//耐久値の取得
//==========================
int CWeapon::GetDurability()
{
	return m_Durability;
}

//==========================
//耐久値を減らす
//==========================
void CWeapon::SubDurability()
{
	m_Durability--;
}