//==========================
// 
// 信号機[shingoki.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "shingoki.h"
#include "model.h"
#include "manager.h"

//静的メンバ初期化
const int CShingoki::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CShingoki::CShingoki(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CShingoki::~CShingoki()
{

}

//==========================
//初期化処理
//==========================
HRESULT CShingoki::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CShingoki::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CShingoki::Update()
{
	//更新処理
	//CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CShingoki::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CShingoki* CShingoki::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CShingoki* pHouse = DBG_NEW CShingoki;

	//位置の設定
	pHouse->SetPos(pos);

	//向きの設定
	pHouse->SetRot(rot);

	//スケールの設定
	pHouse->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pHouse->SetModelIdx(pModel->Regist("data\\MODEL\\shingoki.x"));
	pHouse->BindModel(pModel->GetMeshAdress(pHouse->GetModelIdx()),
		pModel->GetBuffMatAdress(pHouse->GetModelIdx()),
		pModel->GetNumMatAdress(pHouse->GetModelIdx()),
		pModel->GetTexIdx(pHouse->GetModelIdx()));

	//初期化処理
	pHouse->Init();

	//タイプを設定
	pHouse->SetType(TYPE::BUILDING);
	pHouse->SetBuildingType(BUILDING_TYPE::HOUSE);

	return pHouse;
}