//==========================
// 
// 駐輪場[bicycleparking.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "bicycleparking.h"
#include"model.h"
#include"manager.h"

//静的メンバ初期化
const int CBParking::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CBParking::CBParking(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CBParking::~CBParking()
{

}

//==========================
//初期化処理
//==========================
HRESULT CBParking::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CBParking::Uninit()
{
	//終了処理
	CBuilding::Uninit();

}

//==========================
//更新処理
//==========================
void CBParking::Update()
{
	//更新処理
	CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CBParking::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CBParking* CBParking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CBParking* pApartment = DBG_NEW CBParking;

	//位置の設定
	pApartment->SetPos(pos);

	//向きの設定
	pApartment->SetRot(rot);

	//スケールの設定
	pApartment->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pApartment->SetModelIdx(pModel->Regist("data\\MODEL\\bicycleparking.x"));
	pApartment->BindModel(pModel->GetMeshAdress(pApartment->GetModelIdx()),
		pModel->GetBuffMatAdress(pApartment->GetModelIdx()),
		pModel->GetNumMatAdress(pApartment->GetModelIdx()),
		pModel->GetTexIdx(pApartment->GetModelIdx()));

	//初期化処理
	pApartment->Init();

	//タイプを設定
	pApartment->SetType(TYPE::BUILDING);
	pApartment->SetBuildingType(BUILDING_TYPE::BPARKING);

	return pApartment;
}