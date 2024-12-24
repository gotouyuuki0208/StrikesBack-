//==========================
// 
// 柵[fence.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "fence.h"
#include "model.h"
#include "manager.h"

//静的メンバ初期化
const int CFence::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CFence::CFence(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CFence::~CFence()
{

}

//==========================
//初期化処理
//==========================
HRESULT CFence::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CFence::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CFence::Update()
{
	//更新処理
	CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CFence::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CFence* CFence::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CFence* pFence = DBG_NEW CFence;

	//位置の設定
	pFence->SetPos(pos);

	//向きの設定
	pFence->SetRot(rot);

	//スケールの設定
	pFence->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pFence->SetModelIdx(pModel->Regist("data\\MODEL\\Fence.x"));
	pFence->BindModel(pModel->GetMeshAdress(pFence->GetModelIdx()),
		pModel->GetBuffMatAdress(pFence->GetModelIdx()),
		pModel->GetNumMatAdress(pFence->GetModelIdx()),
		pModel->GetTexIdx(pFence->GetModelIdx()));

	//初期化処理
	pFence->Init();

	//タイプを設定
	pFence->SetType(TYPE::BUILDING);
	pFence->SetBuildingType(BUILDING_TYPE::FENCE);

	return pFence;
}