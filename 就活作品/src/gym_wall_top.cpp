//==========================
// 
// 体育館壁上部[gym_wall_top.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "gym_wall_top.h"
#include "model.h"
#include "manager.h"

//静的メンバ初期化
const int CGymwalltop::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CGymwalltop::CGymwalltop(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CGymwalltop::~CGymwalltop()
{

}

//==========================
//初期化処理
//==========================
HRESULT CGymwalltop::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CGymwalltop::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CGymwalltop::Update()
{
	//更新処理
	CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CGymwalltop::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CGymwalltop* CGymwalltop::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CGymwalltop* pGymwalltop = DBG_NEW CGymwalltop;

	//位置の設定
	pGymwalltop->SetPos(pos);

	//向きの設定
	pGymwalltop->SetRot(rot);

	//スケールの設定
	pGymwalltop->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pGymwalltop->SetModelIdx(pModel->Regist("data\\MODEL\\gym_wall_top.x"));
	pGymwalltop->BindModel(pModel->GetMeshAdress(pGymwalltop->GetModelIdx()),
		pModel->GetBuffMatAdress(pGymwalltop->GetModelIdx()),
		pModel->GetNumMatAdress(pGymwalltop->GetModelIdx()),
		pModel->GetTexIdx(pGymwalltop->GetModelIdx()));

	//初期化処理
	pGymwalltop->Init();

	//タイプを設定
	pGymwalltop->SetType(TYPE::BUILDING);
	pGymwalltop->SetBuildingType(BUILDING_TYPE::GYMWALLTOP);

	return pGymwalltop;
}