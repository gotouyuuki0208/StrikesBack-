//==========================
// 
// 電柱[pole.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "pole.h"
#include "model.h"
#include "manager.h"

//静的メンバ初期化
const int CPole::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CPole::CPole(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CPole::~CPole()
{

}

//==========================
//初期化処理
//==========================
HRESULT CPole::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CPole::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CPole::Update()
{
	//更新処理
	CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CPole::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CPole* CPole::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CPole* pHouse = DBG_NEW CPole;

	//位置の設定
	pHouse->SetPos(pos);

	//向きの設定
	pHouse->SetRot(rot);

	//スケールの設定
	pHouse->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pHouse->SetModelIdx(pModel->Regist("data\\MODEL\\pole.x"));
	pHouse->BindModel(pModel->GetMeshAdress(pHouse->GetModelIdx()),
		pModel->GetBuffMatAdress(pHouse->GetModelIdx()),
		pModel->GetNumMatAdress(pHouse->GetModelIdx()),
		pModel->GetTexIdx(pHouse->GetModelIdx()));

	//初期化処理s
	pHouse->Init();

	//タイプを設定
	pHouse->SetType(TYPE::BUILDING);
	pHouse->SetBuildingType(BUILDING_TYPE::POLE);

	return pHouse;
}