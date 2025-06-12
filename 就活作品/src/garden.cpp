//==========================
// 
// 庭[garden.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "garden.h"
#include "model.h"
#include "manager.h"

//静的メンバ初期化
const int CGarden::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CGarden::CGarden(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CGarden::~CGarden()
{

}

//==========================
//初期化処理
//==========================
HRESULT CGarden::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CGarden::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CGarden::Update()
{
	//更新処理
	CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CGarden::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CGarden* CGarden::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CGarden* pGarden = DBG_NEW CGarden;

	//位置の設定
	pGarden->SetPos(pos);

	//向きの設定
	pGarden->SetRot(rot);

	//スケールの設定
	pGarden->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pGarden->SetModelIdx(pModel->Regist("data\\MODEL\\Garden.x"));
	pGarden->BindModel(pModel->GetMeshAdress(pGarden->GetModelIdx()),
		pModel->GetBuffMatAdress(pGarden->GetModelIdx()),
		pModel->GetNumMatAdress(pGarden->GetModelIdx()),
		pModel->GetTexIdx(pGarden->GetModelIdx()));

	//初期化処理
	pGarden->Init();

	//タイプを設定
	pGarden->SetType(TYPE::BUILDING);
	pGarden->SetBuildingType(BUILDING_TYPE::GARDEN);

	return pGarden;
}