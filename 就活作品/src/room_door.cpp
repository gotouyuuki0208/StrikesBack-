//==========================
// 
// 教室のドア[room_door.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"room_door.h"
#include"model.h"
#include"manager.h"

//静的メンバ初期化
const int CRoomDoor::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CRoomDoor::CRoomDoor(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CRoomDoor::~CRoomDoor()
{

}

//==========================
//初期化処理
//==========================
HRESULT CRoomDoor::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CRoomDoor::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CRoomDoor::Update()
{
	//更新処理
	//CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CRoomDoor::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CRoomDoor* CRoomDoor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CRoomDoor* pConveni = DBG_NEW CRoomDoor;

	//位置の設定
	pConveni->SetPos(pos);

	//向きの設定
	pConveni->SetRot(rot);

	//スケールの設定
	pConveni->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pConveni->SetModelIdx(pModel->Regist("data\\MODEL\\door.x"));
	pConveni->BindModel(pModel->GetMeshAdress(pConveni->GetModelIdx()),
		pModel->GetBuffMatAdress(pConveni->GetModelIdx()),
		pModel->GetNumMatAdress(pConveni->GetModelIdx()),
		pModel->GetTexIdx(pConveni->GetModelIdx()));

	//初期化処理
	pConveni->Init();

	//タイプを設定
	pConveni->SetType(TYPE::BUILDING);
	pConveni->SetBuildingType(BUILDING_TYPE::ROOMDOOR);

	return pConveni;
}