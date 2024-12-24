//==========================
// 
// 体育館壁[gym_Door.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "gymdoor.h"
#include "model.h"
#include "manager.h"

//静的メンバ初期化
const int CGymDoor::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CGymDoor::CGymDoor(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CGymDoor::~CGymDoor()
{

}

//==========================
//初期化処理
//==========================
HRESULT CGymDoor::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CGymDoor::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CGymDoor::Update()
{
	//更新処理
	CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CGymDoor::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CGymDoor* CGymDoor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CGymDoor* pGymDoor = DBG_NEW CGymDoor;

	//位置の設定
	pGymDoor->SetPos(pos);

	//向きの設定
	pGymDoor->SetRot(rot);

	//スケールの設定
	pGymDoor->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pGymDoor->SetModelIdx(pModel->Regist("data\\MODEL\\gymdoor.x"));
	pGymDoor->BindModel(pModel->GetMeshAdress(pGymDoor->GetModelIdx()),
		pModel->GetBuffMatAdress(pGymDoor->GetModelIdx()),
		pModel->GetNumMatAdress(pGymDoor->GetModelIdx()),
		pModel->GetTexIdx(pGymDoor->GetModelIdx()));

	//初期化処理
	pGymDoor->Init();

	//タイプを設定
	pGymDoor->SetType(TYPE::BUILDING);
	pGymDoor->SetBuildingType(BUILDING_TYPE::GYMDOOR);

	return pGymDoor;
}