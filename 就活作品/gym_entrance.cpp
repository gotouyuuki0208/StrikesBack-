//==========================
// 
// 体育館入口[gym_entrance.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "gym_entrance.h"
#include "model.h"
#include "manager.h"

//静的メンバ初期化
const int CGymentrance::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CGymentrance::CGymentrance(int nPriority) :
	CBuilding(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CGymentrance::~CGymentrance()
{

}

//==========================
//初期化処理
//==========================
HRESULT CGymentrance::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CGymentrance::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CGymentrance::Update()
{
	//更新処理
	CBuilding::Update();
}

//==========================
//描画処理
//==========================
void CGymentrance::Draw()
{
	//描画処理
	CBuilding::Draw();
}

//==========================
//オブジェクト生成
//==========================
CGymentrance* CGymentrance::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CGymentrance* pGymentrance = DBG_NEW CGymentrance;

	//位置の設定
	pGymentrance->SetPos(pos);

	//向きの設定
	pGymentrance->SetRot(rot);

	//スケールの設定
	pGymentrance->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pGymentrance->SetModelIdx(pModel->Regist("data\\MODEL\\gym_entrance.x"));
	pGymentrance->BindModel(pModel->GetMeshAdress(pGymentrance->GetModelIdx()),
		pModel->GetBuffMatAdress(pGymentrance->GetModelIdx()),
		pModel->GetNumMatAdress(pGymentrance->GetModelIdx()),
		pModel->GetTexIdx(pGymentrance->GetModelIdx()));

	//初期化処理
	pGymentrance->Init();

	//タイプを設定
	pGymentrance->SetType(TYPE::BUILDING);
	pGymentrance->SetBuildingType(BUILDING_TYPE::GYMENTRANCE);

	return pGymentrance;
}