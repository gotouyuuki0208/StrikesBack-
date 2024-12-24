//==========================
// 
// バスケットゴール[basketgoal.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "basketgoal.h"
#include "model.h"
#include "manager.h"

//静的メンバ初期化
const int CBasketgoal::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CBasketgoal::CBasketgoal(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CBasketgoal::~CBasketgoal()
{

}

//==========================
//初期化処理
//==========================
HRESULT CBasketgoal::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CBasketgoal::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CBasketgoal::Update()
{
	//更新処理
	//CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CBasketgoal::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CBasketgoal* CBasketgoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CBasketgoal* pBasketgoal = DBG_NEW CBasketgoal;

	//位置の設定
	pBasketgoal->SetPos(pos);

	//向きの設定
	pBasketgoal->SetRot(rot);

	//スケールの設定
	pBasketgoal->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBasketgoal->SetModelIdx(pModel->Regist("data\\MODEL\\basketgoal.x"));
	pBasketgoal->BindModel(pModel->GetMeshAdress(pBasketgoal->GetModelIdx()),
		pModel->GetBuffMatAdress(pBasketgoal->GetModelIdx()),
		pModel->GetNumMatAdress(pBasketgoal->GetModelIdx()),
		pModel->GetTexIdx(pBasketgoal->GetModelIdx()));

	//初期化処理
	pBasketgoal->Init();

	//タイプを設定
	pBasketgoal->SetType(TYPE::BUILDING);
	pBasketgoal->SetBuildingType(BUILDING_TYPE::BASKETGOAL);

	return pBasketgoal;
}