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
#include "player.h"
#include "fild.h"

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
m_Durability(0),//耐久値
m_RotKeep(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),//向き保存用
m_ScaleKeep(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),//向き保存用
m_ThrowAngle(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
m_Throw(false)
{
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_rot);
	D3DXMatrixIdentity(&m_scale);
	
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
	ColisionPlayer();

	Move();

	//更新処理
	CObjectX::Update();	
}

//==========================
//描画処理
//==========================
void CWeapon::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&GetMtxWorld());

	//スケール設定
	D3DXMatrixScaling(&mtxScale, GetScale().x, GetScale().y, GetScale().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxScale);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &m_scale);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxRot);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &m_rot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxTrans);

	if (m_Parent != nullptr)
	{//階層構造の設定

		D3DXMATRIX mtxParent;
		
		mtxParent = m_Parent->GetMtxWorld();
		D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxParent);
	}

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());

	DrawModel();//モデルの描画
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
	m_Garb = true;

	if (Parent != nullptr)
	{
		m_RotKeep = GetRot();//向きを保存
		m_ScaleKeep = GetScale();//向きを保存

		SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	}
	
}

//==========================
//情報を戻す
//==========================
void CWeapon::CorrectInfo()
{
	SetRot(m_RotKeep);
	SetScale(m_ScaleKeep);
	m_Garb = false;
}

//==========================
//移動処理
//==========================
void CWeapon::Move()
{
	if (!m_Throw)
	{
		return;
	}

	SetPosOld(GetPos());

	//慣性と重力
	SetMove(D3DXVECTOR3(GetMove().x += (0 - GetMove().x) * 0.01f,
		GetMove().y - 0.15f,
		GetMove().z += (0 - GetMove().z) * 0.01f));

	//位置の設定
	SetPos(GetPos() + GetMove());

	//敵との当たり判定
	HitEnemy();

	//地面との当たり判定
	CollisionFild();
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
			
			pPlayer->SetPosOld(pPlayer->GetPos());

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
//敵への攻撃時の判定
//==========================
void CWeapon::HitEnemy()
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
		{//オブジェクトが敵ではない
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

		bool Colision = ColisionSphere(D3DXVECTOR3(GetMtxWorld()._41, GetMtxWorld()._42, GetMtxWorld()._43),
			D3DXVECTOR3(pEnemy->GetPartsMtx(1)._41, pEnemy->GetPartsMtx(1)._42, pEnemy->GetPartsMtx(1)._43),
			30.0f,
			30.0f);

		if (Colision)
		{
			if (m_weapontype == WEAPONTYPE::SMALL)
			{
				pEnemy->Damage(2);
			}
			else
			{
				pEnemy->Damage(3);
			}

			//武器の耐久値を減らす
			SubDurability();
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

	if (m_Durability <= 0)
	{
		Uninit();
	}
}

//==========================
//地面との当たり判定
//==========================
void CWeapon::CollisionFild()
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
		{//オブジェクトが地面ではない
			pObj = CObject::GetObj(pObj, CFild::PRIORITY);
			continue;
		}

		CFild* pFild = dynamic_cast<CFild*>(pObj);

		if (GetPosOld().y >= pFild->GetPos().y
			&& GetPos().y < pFild->GetPos().y)
		{
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			SetPos(D3DXVECTOR3(GetPos().x, pFild->GetPos().y, GetPos().z));
			CManager::GetInstance()->GetStageManager()->DeleteObj(*this);
			Uninit();
			break;
		}

		pObj = CObject::GetObj(pObj, CFild::PRIORITY);
	}
}

//==========================
//投げられる時の角度を求める
//==========================
void CWeapon::ThrowAngle(CMotionModel* Charactar)
{
	if (m_Parent == nullptr)
	{
		return;
	}

	m_Throw = true;

	D3DXMATRIX mtxRot,mtxScale;//親モデルの向きを保存
	
	CModelParts* parent = m_Parent;

	SetScale(parent->GetScale());
	
	while (1)
	{
		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, parent->GetRot().y, parent->GetRot().x, parent->GetRot().z);
		D3DXMatrixMultiply(&m_rot, &m_rot, &mtxRot);

		//スケールを反映
		//D3DXMatrixScaling(&mtxScale, parent->GetScale().x, parent->GetScale().y, parent->GetScale().z);
		//D3DXMatrixMultiply(&m_scale, &m_scale, &mtxScale);

		parent = parent->GetParent();

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxRot);
		D3DXMatrixIdentity(&mtxScale);

		if (parent == nullptr)
		{
			break;
		}
	}

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Charactar->GetRot().y, Charactar->GetRot().x, Charactar->GetRot().z);
	D3DXMatrixMultiply(&m_rot, &m_rot, &mtxRot);

	//スケールを反映
	D3DXMatrixScaling(&mtxScale, Charactar->GetScale().x, Charactar->GetScale().y, Charactar->GetScale().z);
	D3DXMatrixMultiply(&m_scale, &m_scale, &mtxScale);

	//CreateMtx();//行列の生成

	//D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &m_a);

	//LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	//pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	//ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());

	//D3DXMATRIX a = GetMtxWorld();
	//D3DXVECTOR3 pos = D3DXVECTOR3(GetMtxWorld()._41, GetMtxWorld()._42, GetMtxWorld()._43);
	SetPos(D3DXVECTOR3(GetMtxWorld()._41, GetMtxWorld()._42, GetMtxWorld()._43));
	
}

//==========================
//武器を投げた時の当たり判定
//==========================
void CWeapon::CollisionThrow()
{

}