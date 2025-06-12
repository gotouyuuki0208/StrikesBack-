//==========================
// 
// タイトルとリザルト画面の壁[OutGameWall.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "OutGameWall.h"
#include "model.h"
#include "manager.h"

//静的メンバ初期化
const int COutGameWall::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
COutGameWall::COutGameWall(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
COutGameWall::~COutGameWall()
{

}

//==========================
//初期化処理
//==========================
HRESULT COutGameWall::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  COutGameWall::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void COutGameWall::Update()
{
	//更新処理
	//CBuilding::Update();
}

//==========================
//描画処理
//==========================
void COutGameWall::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
COutGameWall* COutGameWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	COutGameWall* pOutGameWall = DBG_NEW COutGameWall;

	//位置の設定
	pOutGameWall->SetPos(pos);

	//向きの設定
	pOutGameWall->SetRot(rot);

	//スケールの設定
	pOutGameWall->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pOutGameWall->SetModelIdx(pModel->Regist("data\\MODEL\\outgamewall.x"));
	pOutGameWall->BindModel(pModel->GetMeshAdress(pOutGameWall->GetModelIdx()),
		pModel->GetBuffMatAdress(pOutGameWall->GetModelIdx()),
		pModel->GetNumMatAdress(pOutGameWall->GetModelIdx()),
		pModel->GetTexIdx(pOutGameWall->GetModelIdx()));

	//初期化処理
	pOutGameWall->Init();

	//タイプを設定
	pOutGameWall->SetType(TYPE::BUILDING);

	return pOutGameWall;
}