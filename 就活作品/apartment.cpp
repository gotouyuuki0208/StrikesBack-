//==========================
// 
// アパート[apartment.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "apartment.h"
#include"model.h"
#include"manager.h"

//静的メンバ初期化
const int CApartment::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CApartment::CApartment(int nPriority) :
CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CApartment::~CApartment()
{

}

//==========================
//初期化処理
//==========================
HRESULT CApartment::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CApartment::Uninit()
{
	//終了処理
	CBuilding::Uninit();

}

//==========================
//更新処理
//==========================
void CApartment::Update()
{
	//更新処理
	CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CApartment::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CApartment* CApartment::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CApartment* pApartment = DBG_NEW CApartment;

	//位置の設定
	pApartment->SetPos(pos);

	//向きの設定
	pApartment->SetRot(rot);

	//スケールの設定
	pApartment->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pApartment->SetModelIdx(pModel->Regist("data\\MODEL\\apartment.x"));
	pApartment->BindModel(pModel->GetMeshAdress(pApartment->GetModelIdx()),
		pModel->GetBuffMatAdress(pApartment->GetModelIdx()),
		pModel->GetNumMatAdress(pApartment->GetModelIdx()),
		pModel->GetTexIdx(pApartment->GetModelIdx()));

	//初期化処理
	pApartment->Init();

	//タイプを設定
	pApartment->SetType(TYPE::BUILDING);
	pApartment->SetBuildingType(BUILDING_TYPE::APARTMENT);

	return pApartment;
}