//==========================
// 
// 体育館壁[gym_wall.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "gym_wall.h"
#include "model.h"
#include "manager.h"

//静的メンバ初期化
const int CGymwall::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CGymwall::CGymwall(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CGymwall::~CGymwall()
{

}

//==========================
//初期化処理
//==========================
HRESULT CGymwall::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CGymwall::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CGymwall::Update()
{
	//更新処理
	CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CGymwall::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CGymwall* CGymwall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CGymwall* pGymwall = DBG_NEW CGymwall;

	//位置の設定
	pGymwall->SetPos(pos);

	//向きの設定
	pGymwall->SetRot(rot);

	//スケールの設定
	pGymwall->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pGymwall->SetModelIdx(pModel->Regist("data\\MODEL\\gym_wall.x"));
	pGymwall->BindModel(pModel->GetMeshAdress(pGymwall->GetModelIdx()),
		pModel->GetBuffMatAdress(pGymwall->GetModelIdx()),
		pModel->GetNumMatAdress(pGymwall->GetModelIdx()),
		pModel->GetTexIdx(pGymwall->GetModelIdx()));

	//初期化処理
	pGymwall->Init();

	//タイプを設定
	pGymwall->SetType(TYPE::BUILDING);
	pGymwall->SetBuildingType(BUILDING_TYPE::GYMWALL);

	return pGymwall;
}