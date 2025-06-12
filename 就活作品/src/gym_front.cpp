//==========================
// 
// 体育館正面[gym_front.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "gym_front.h"
#include "model.h"
#include "manager.h"

//静的メンバ初期化
const int CGymfront::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CGymfront::CGymfront(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CGymfront::~CGymfront()
{

}

//==========================
//初期化処理
//==========================
HRESULT CGymfront::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CGymfront::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CGymfront::Update()
{
	//更新処理
	CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CGymfront::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CGymfront* CGymfront::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CGymfront* pGymfront = DBG_NEW CGymfront;

	//位置の設定
	pGymfront->SetPos(pos);

	//向きの設定
	pGymfront->SetRot(rot);

	//スケールの設定
	pGymfront->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pGymfront->SetModelIdx(pModel->Regist("data\\MODEL\\gym_front.x"));
	pGymfront->BindModel(pModel->GetMeshAdress(pGymfront->GetModelIdx()),
		pModel->GetBuffMatAdress(pGymfront->GetModelIdx()),
		pModel->GetNumMatAdress(pGymfront->GetModelIdx()),
		pModel->GetTexIdx(pGymfront->GetModelIdx()));

	//初期化処理
	pGymfront->Init();

	//タイプを設定
	pGymfront->SetType(TYPE::BUILDING);
	pGymfront->SetBuildingType(BUILDING_TYPE::GYMFRONT);

	return pGymfront;
}