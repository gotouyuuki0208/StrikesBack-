//==========================
// 
// 掲示板[board.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"board.h"
#include"model.h"
#include"manager.h"

//静的メンバ初期化
const int CBoard::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CBoard::CBoard(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CBoard::~CBoard()
{

}

//==========================
//初期化処理
//==========================
HRESULT CBoard::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CBoard::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CBoard::Update()
{
	//更新処理
	//CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CBoard::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CBoard* CBoard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CBoard* pConveni = DBG_NEW CBoard;

	//位置の設定
	pConveni->SetPos(pos);

	//向きの設定
	pConveni->SetRot(rot);

	//スケールの設定
	pConveni->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pConveni->SetModelIdx(pModel->Regist("data\\MODEL\\bulletinboard.x"));
	pConveni->BindModel(pModel->GetMeshAdress(pConveni->GetModelIdx()),
		pModel->GetBuffMatAdress(pConveni->GetModelIdx()),
		pModel->GetNumMatAdress(pConveni->GetModelIdx()),
		pModel->GetTexIdx(pConveni->GetModelIdx()));

	//初期化処理
	pConveni->Init();

	//タイプを設定
	pConveni->SetType(TYPE::BUILDING);
	pConveni->SetBuildingType(BUILDING_TYPE::BOARD);

	return pConveni;
}