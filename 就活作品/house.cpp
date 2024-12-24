//==========================
// 
// 家[house.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "house.h"
#include "model.h"
#include "manager.h"

//静的メンバ初期化
const int CHouse::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CHouse::CHouse(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CHouse::~CHouse()
{

}

//==========================
//初期化処理
//==========================
HRESULT CHouse::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CHouse::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CHouse::Update()
{
	//更新処理
	CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CHouse::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CHouse* CHouse::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CHouse* pHouse = DBG_NEW CHouse;

	//位置の設定
	pHouse->SetPos(pos);

	//向きの設定
	pHouse->SetRot(rot);

	//スケールの設定
	pHouse->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pHouse->SetModelIdx(pModel->Regist("data\\MODEL\\House_001.x"));
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