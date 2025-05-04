//==========================
// 
// 建物[building.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "building.h"
#include "manager.h"
#include "model.h"
#include "player.h"
#include "enemy.h"

//静的メンバ初期化
const int CBuilding::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CBuilding::CBuilding(int nPriority):
CObjectX(nPriority),
m_nModelIdx(0),
m_Building_Type(BUILDING_TYPE::NONE)
{

}

//==========================
//デストラクタ
//==========================
CBuilding::~CBuilding()
{

}

//==========================
//初期化処理
//==========================
HRESULT CBuilding::Init()
{
	//サイズ設定
	SetSize();

	//初期設定
	CObjectX::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CBuilding::Uninit()
{
	//終了処理
	CObjectX::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CBuilding::Update()
{
	//更新処理
	CObjectX::Update();

	int rot = static_cast<int>(GetRot().y);

	if (rot == 1 || rot == -1)
	{
		//プレイヤーとの当たり判定
		ColisionPlayerWide();
	}
	else
	{
		//プレイヤーとの当たり判定
		ColisionPlayer();
	}
	
	if (!CManager::GetInstance()->GetDebug()->GetEdit())
	{
		if (rot == 1 || rot == -1)
		{
			//敵との当たり判定
			ColisionEnemyWide();
		}
		else
		{
			//プレイヤーとの当たり判定
			ColisionEnemy();
		}
	}
}

//==========================
//描画処理
//==========================
void CBuilding::Draw()
{
	//描画処理
	CObjectX::Draw();
}

//==========================
//オブジェクト生成
//==========================
CBuilding* CBuilding::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CBuilding* pBuilding = DBG_NEW CBuilding;

	//位置の設定
	pBuilding->SetPos(pos);

	//スケールの設定
	pBuilding->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBuilding->m_nModelIdx = pModel->Regist("data\\MODEL\\test_building001.x");
	pBuilding->BindModel(pModel->GetMeshAdress(pBuilding->m_nModelIdx),
		pModel->GetBuffMatAdress(pBuilding->m_nModelIdx),
		pModel->GetNumMatAdress(pBuilding->m_nModelIdx),
		pModel->GetTexIdx(pBuilding->m_nModelIdx));

	//初期化処理
	pBuilding->Init();

	//タイプを設定
	pBuilding->SetType(TYPE::BUILDING);
	pBuilding->SetBuildingType(BUILDING_TYPE::BUILDING);

	return pBuilding;
}

//==========================
//建物の種類を取得
//==========================
CBuilding::BUILDING_TYPE CBuilding::GetBuildingType()
{
	return m_Building_Type;
}

//==========================
//建物の種類を設定
//==========================
void CBuilding::SetBuildingType(BUILDING_TYPE type)
{
	m_Building_Type = type;
}

//==========================
//モデルの番号を取得
//==========================
int CBuilding::GetModelIdx()
{
	return m_nModelIdx;
}

//==========================
//モデルの番号を設定
//==========================
void CBuilding::SetModelIdx(int Idx)
{
	m_nModelIdx = Idx;
}

//==========================
//プレイヤーとの当たり判定
//==========================
void CBuilding::ColisionPlayer()
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

		if (pPlayer->GetPosOld().z + 10.0f <= GetPos().z + GetVtxMin().z
			&& pPlayer->GetPos().z + 10.0f > GetPos().z + GetVtxMin().z
			&& pPlayer->GetPos().x - 10.0f < GetPos().x + GetVtxMax().x
			&& pPlayer->GetPos().x + 10.0f > GetPos().x + GetVtxMin().x)
		{//手前
			pPlayer->SetMove(D3DXVECTOR3(pPlayer->GetMove().x, pPlayer->GetMove().y, 0.0f));
			pPlayer->SetPos(D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y, GetPos().z + GetVtxMin().z - 10.0f));
		}
		else if (pPlayer->GetPosOld().z - 10.0f >= GetPos().z + GetVtxMax().z
			&& pPlayer->GetPos().z - 10.0f < GetPos().z + GetVtxMax().z
			&& pPlayer->GetPos().x - 10.0f < GetPos().x + GetVtxMax().x
			&& pPlayer->GetPos().x + 10.0f > GetPos().x + GetVtxMin().x)
		{//奥
			pPlayer->SetMove(D3DXVECTOR3(pPlayer->GetMove().x, pPlayer->GetMove().y, 0.0f));
			pPlayer->SetPos(D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y, GetPos().z + GetVtxMax().z + 10.0f));
		}
		else if (pPlayer->GetPosOld().x - 10.0f >= GetPos().x + GetVtxMax().x
			&& pPlayer->GetPos().x - 10.0f < GetPos().x + GetVtxMax().x
			&& pPlayer->GetPos().z - 10.0f < GetPos().z + GetVtxMax().z
			&& pPlayer->GetPos().z + 10.0f > GetPos().z + GetVtxMin().z)
		{//右
			pPlayer->SetMove(D3DXVECTOR3(0.0f, pPlayer->GetMove().y, pPlayer->GetMove().z));
			pPlayer->SetPos(D3DXVECTOR3(GetPos().x+ GetVtxMax().x+10.0f, pPlayer->GetPos().y, pPlayer->GetPos().z));
		}
		else if (pPlayer->GetPosOld().x + 10.0f <= GetPos().x + GetVtxMin().x
			&& pPlayer->GetPos().x + 10.0f > GetPos().x + GetVtxMin().x
			&& pPlayer->GetPos().z - 10.0f < GetPos().z + GetVtxMax().z
			&& pPlayer->GetPos().z + 10.0f > GetPos().z + GetVtxMin().z)
		{//左
			pPlayer->SetMove(D3DXVECTOR3(0.0f, pPlayer->GetMove().y, pPlayer->GetMove().z));
			pPlayer->SetPos(D3DXVECTOR3(GetPos().x + GetVtxMin().x - 10.0f, pPlayer->GetPos().y, pPlayer->GetPos().z));
		}
		break;
	}
}

//==========================
//モデルが横向きの時の当たり判定
//==========================
void CBuilding::ColisionPlayerWide()
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

		if (pPlayer->GetPosOld().z + 10.0f <= GetPos().z + GetVtxMin().x
			&& pPlayer->GetPos().z + 10.0f > GetPos().z + GetVtxMin().x
			&& pPlayer->GetPos().x - 10.0f < GetPos().x + GetVtxMax().z
			&& pPlayer->GetPos().x + 10.0f > GetPos().x + GetVtxMin().z)
		{//手前
			pPlayer->SetMove(D3DXVECTOR3(pPlayer->GetMove().x, pPlayer->GetMove().y, 0.0f));
			pPlayer->SetPos(D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y, GetPos().z + GetVtxMin().x - 10.0f));
		}
		else if (pPlayer->GetPosOld().z - 10.0f >= GetPos().z + GetVtxMax().x
			&& pPlayer->GetPos().z - 10.0f < GetPos().z + GetVtxMax().x
			&& pPlayer->GetPos().x - 10.0f < GetPos().x + GetVtxMax().z
			&& pPlayer->GetPos().x + 10.0f > GetPos().x + GetVtxMin().z)
		{//奥
			pPlayer->SetMove(D3DXVECTOR3(pPlayer->GetMove().x, pPlayer->GetMove().y, 0.0f));
			pPlayer->SetPos(D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y, GetPos().z + GetVtxMax().x + 10.0f));
		}
		else if (pPlayer->GetPosOld().x - 10.0f >= GetPos().x + GetVtxMax().z
			&& pPlayer->GetPos().x - 10.0f < GetPos().x + GetVtxMax().z
			&& pPlayer->GetPos().z - 10.0f < GetPos().z + GetVtxMax().x
			&& pPlayer->GetPos().z + 10.0f > GetPos().z + GetVtxMin().x)
		{//右
			pPlayer->SetMove(D3DXVECTOR3(0.0f, pPlayer->GetMove().y, pPlayer->GetMove().z));
			pPlayer->SetPos(D3DXVECTOR3(GetPos().x + GetVtxMax().z + 10.0f, pPlayer->GetPos().y, pPlayer->GetPos().z));
		}
		else if (pPlayer->GetPosOld().x + 10.0f <= GetPos().x + GetVtxMin().z
			&& pPlayer->GetPos().x + 10.0f > GetPos().x + GetVtxMin().z
			&& pPlayer->GetPos().z - 10.0f < GetPos().z + GetVtxMax().x
			&& pPlayer->GetPos().z + 10.0f > GetPos().z + GetVtxMin().x)
		{//左
			pPlayer->SetMove(D3DXVECTOR3(0.0f, pPlayer->GetMove().y, pPlayer->GetMove().z));
			pPlayer->SetPos(D3DXVECTOR3(GetPos().x + GetVtxMin().z - 10.0f, pPlayer->GetPos().y, pPlayer->GetPos().z));
		}
		break;
	}
}

//==========================
//敵との当たり判定
//==========================
void  CBuilding::ColisionEnemy()
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
		{//オブジェクトがプレイヤーではない
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

		
		if (pEnemy->GetPosOld().z + 10.0f <= GetPos().z + GetVtxMin().z
			&& pEnemy->GetPos().z + 10.0f > GetPos().z + GetVtxMin().z
			&& pEnemy->GetPos().x - 10.0f < GetPos().x + GetVtxMax().x
			&& pEnemy->GetPos().x + 10.0f > GetPos().x + GetVtxMin().x)
		{//手前
			pEnemy->SetMove(D3DXVECTOR3(pEnemy->GetMove().x, pEnemy->GetMove().y, 0.0f));
			pEnemy->SetPos(D3DXVECTOR3(pEnemy->GetPos().x, pEnemy->GetPos().y, GetPos().z + GetVtxMin().z - 10.0f));
		}
		if (pEnemy->GetPosOld().z - 10.0f >= GetPos().z + GetVtxMax().z
			&& pEnemy->GetPos().z - 10.0f < GetPos().z + GetVtxMax().z
			&& pEnemy->GetPos().x - 10.0f < GetPos().x + GetVtxMax().x
			&& pEnemy->GetPos().x + 10.0f > GetPos().x + GetVtxMin().x)
		{//奥
			pEnemy->SetMove(D3DXVECTOR3(pEnemy->GetMove().x, pEnemy->GetMove().y, 0.0f));
			pEnemy->SetPos(D3DXVECTOR3(pEnemy->GetPos().x, pEnemy->GetPos().y, GetPos().z + GetVtxMax().z + 10.0f));
		}
		else if (pEnemy->GetPosOld().x - 10.0f >= GetPos().x + GetVtxMax().x
			&& pEnemy->GetPos().x - 10.0f < GetPos().x + GetVtxMax().x
			&& pEnemy->GetPos().z - 10.0f < GetPos().z + GetVtxMax().z
			&& pEnemy->GetPos().z + 10.0f > GetPos().z + GetVtxMin().z)
		{//右
			pEnemy->SetMove(D3DXVECTOR3(0.0f, pEnemy->GetMove().y, pEnemy->GetMove().z));
			pEnemy->SetPos(D3DXVECTOR3(GetPos().x + GetVtxMax().x + 10.0f, pEnemy->GetPos().y, pEnemy->GetPos().z));
		}
		else if (pEnemy->GetPosOld().x + 10.0f <= GetPos().x + GetVtxMin().x
			&& pEnemy->GetPos().x + 10.0f > GetPos().x + GetVtxMin().x
			&& pEnemy->GetPos().z - 10.0f < GetPos().z + GetVtxMax().z
			&& pEnemy->GetPos().z + 10.0f > GetPos().z + GetVtxMin().z)
		{//左
			pEnemy->SetMove(D3DXVECTOR3(0.0f, pEnemy->GetMove().y, pEnemy->GetMove().z));
			pEnemy->SetPos(D3DXVECTOR3(GetPos().x + GetVtxMin().x - 10.0f, pEnemy->GetPos().y, pEnemy->GetPos().z));
		}
		
		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);

	}
}

//==========================
//モデルが横向きの時の敵との当たり判定
//==========================
void CBuilding::ColisionEnemyWide()
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
		{//オブジェクトがプレイヤーではない
			pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
			continue;
		}

		CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

		if (pEnemy->GetPosOld().z + 10.0f <= GetPos().z + GetVtxMin().x
			&& pEnemy->GetPos().z + 10.0f > GetPos().z + GetVtxMin().x
			&& pEnemy->GetPos().x - 10.0f < GetPos().x + GetVtxMax().z
			&& pEnemy->GetPos().x + 10.0f > GetPos().x + GetVtxMin().z)
		{//手前
			pEnemy->SetMove(D3DXVECTOR3(pEnemy->GetMove().x, pEnemy->GetMove().y, 0.0f));
			pEnemy->SetPos(D3DXVECTOR3(pEnemy->GetPos().x, pEnemy->GetPos().y, GetPos().z + GetVtxMin().x - 10.0f));
		}
		else if (pEnemy->GetPosOld().z - 10.0f >= GetPos().z + GetVtxMax().x
			&& pEnemy->GetPos().z - 10.0f < GetPos().z + GetVtxMax().x
			&& pEnemy->GetPos().x - 10.0f < GetPos().x + GetVtxMax().z
			&& pEnemy->GetPos().x + 10.0f > GetPos().x + GetVtxMin().z)
		{//奥
			pEnemy->SetMove(D3DXVECTOR3(pEnemy->GetMove().x, pEnemy->GetMove().y, 0.0f));
			pEnemy->SetPos(D3DXVECTOR3(pEnemy->GetPos().x, pEnemy->GetPos().y, GetPos().z + GetVtxMax().x + 10.0f));
		}
		else if (pEnemy->GetPosOld().x - 10.0f >= GetPos().x + GetVtxMax().z
			&& pEnemy->GetPos().x - 10.0f < GetPos().x + GetVtxMax().z
			&& pEnemy->GetPos().z - 10.0f < GetPos().z + GetVtxMax().x
			&& pEnemy->GetPos().z + 10.0f > GetPos().z + GetVtxMin().x)
		{//右
			pEnemy->SetMove(D3DXVECTOR3(0.0f, pEnemy->GetMove().y, pEnemy->GetMove().z));
			pEnemy->SetPos(D3DXVECTOR3(GetPos().x + GetVtxMax().z + 10.0f, pEnemy->GetPos().y, pEnemy->GetPos().z));
		}
		else if (pEnemy->GetPosOld().x + 10.0f <= GetPos().x + GetVtxMin().z
			&& pEnemy->GetPos().x + 10.0f > GetPos().x + GetVtxMin().z
			&& pEnemy->GetPos().z - 10.0f < GetPos().z + GetVtxMax().x
			&& pEnemy->GetPos().z + 10.0f > GetPos().z + GetVtxMin().x)
		{//左
			pEnemy->SetMove(D3DXVECTOR3(0.0f, pEnemy->GetMove().y, pEnemy->GetMove().z));
			pEnemy->SetPos(D3DXVECTOR3(GetPos().x + GetVtxMin().z - 10.0f, pEnemy->GetPos().y, pEnemy->GetPos().z));
		}

		pObj = CObject::GetObj(pObj, CEnemy::PRIORITY);
	}
}