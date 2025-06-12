//==========================
// 
// 廊下の出口[corridorExit.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "corridorExit.h"
#include"model.h"
#include"manager.h"

//静的メンバ初期化
const int CCorridorExit::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CCorridorExit::CCorridorExit(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CCorridorExit::~CCorridorExit()
{

}

//==========================
//初期化処理
//==========================
HRESULT CCorridorExit::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CCorridorExit::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CCorridorExit::Update()
{
	//更新処理
	CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CCorridorExit::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CCorridorExit* CCorridorExit::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CCorridorExit* pCorridorExit = DBG_NEW CCorridorExit;

	//位置の設定
	pCorridorExit->SetPos(pos);

	//向きの設定
	pCorridorExit->SetRot(rot);

	//スケールの設定
	pCorridorExit->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pCorridorExit->SetModelIdx(pModel->Regist("data\\MODEL\\corridorExit.x"));
	pCorridorExit->BindModel(pModel->GetMeshAdress(pCorridorExit->GetModelIdx()),
		pModel->GetBuffMatAdress(pCorridorExit->GetModelIdx()),
		pModel->GetNumMatAdress(pCorridorExit->GetModelIdx()),
		pModel->GetTexIdx(pCorridorExit->GetModelIdx()));

	//初期化処理
	pCorridorExit->Init();

	//タイプを設定
	pCorridorExit->SetType(TYPE::BUILDING);
	pCorridorExit->SetBuildingType(BUILDING_TYPE::CEXIT);

	return pCorridorExit;
}