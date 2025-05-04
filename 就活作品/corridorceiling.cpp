//==========================
// 
// 廊下の天井[corridorceiling.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"corridorceiling.h"
#include"model.h"
#include"manager.h"

//静的メンバ初期化
const int CCorridorceiling::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CCorridorceiling::CCorridorceiling(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CCorridorceiling::~CCorridorceiling()
{

}

//==========================
//初期化処理
//==========================
HRESULT CCorridorceiling::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CCorridorceiling::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CCorridorceiling::Update()
{
	//更新処理
	//CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CCorridorceiling::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CCorridorceiling* CCorridorceiling::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CCorridorceiling* pConveni = DBG_NEW CCorridorceiling;

	//位置の設定
	pConveni->SetPos(pos);

	//向きの設定
	pConveni->SetRot(rot);

	//スケールの設定
	pConveni->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pConveni->SetModelIdx(pModel->Regist("data\\MODEL\\corridorceiling.x"));
	pConveni->BindModel(pModel->GetMeshAdress(pConveni->GetModelIdx()),
		pModel->GetBuffMatAdress(pConveni->GetModelIdx()),
		pModel->GetNumMatAdress(pConveni->GetModelIdx()),
		pModel->GetTexIdx(pConveni->GetModelIdx()));

	//初期化処理
	pConveni->Init();

	//タイプを設定
	pConveni->SetType(TYPE::BUILDING);
	pConveni->SetBuildingType(BUILDING_TYPE::CORRIDORCEILING);

	return pConveni;
}