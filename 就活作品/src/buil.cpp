//==========================
// 
// ビル[buil.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"buil.h"
#include"model.h"
#include"manager.h"

//静的メンバ初期化
const int CBuil::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CBuil::CBuil(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CBuil::~CBuil()
{

}

//==========================
//初期化処理
//==========================
HRESULT CBuil::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CBuil::Uninit()
{
	//終了処理
	CBuilding::Uninit();

}

//==========================
//更新処理
//==========================
void CBuil::Update()
{
	//更新処理
	CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CBuil::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CBuil* CBuil::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CBuil* pBuil = DBG_NEW CBuil;

	//位置の設定
	pBuil->SetPos(pos);

	//向きの設定
	pBuil->SetRot(rot);

	//スケールの設定
	pBuil->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBuil->SetModelIdx(pModel->Regist("data\\MODEL\\buil.x"));
	pBuil->BindModel(pModel->GetMeshAdress(pBuil->GetModelIdx()),
		pModel->GetBuffMatAdress(pBuil->GetModelIdx()),
		pModel->GetNumMatAdress(pBuil->GetModelIdx()),
		pModel->GetTexIdx(pBuil->GetModelIdx()));

	//初期化処理
	pBuil->Init();

	//タイプを設定
	pBuil->SetType(TYPE::BUILDING);
	pBuil->SetBuildingType(BUILDING_TYPE::BUILDING);

	return pBuil;
}