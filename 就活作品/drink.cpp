//==========================
// 
// 飲み物[drink.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "drink.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int CDrink::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CDrink::CDrink(int nPriority) :CItem(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CDrink::~CDrink()
{

}

//==========================
//初期化処理
//==========================
HRESULT CDrink::Init()
{
	//初期設定
	CItem::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CDrink::Uninit()
{
	//終了処理
	CItem::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CDrink::Update()
{
	//更新処理
	CItem::Update();
}

//==========================
//描画処理
//==========================
void CDrink::Draw()
{
	//描画処理
	CItem::Draw();
}

//==========================
//オブジェクト生成
//==========================
CDrink* CDrink::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CDrink* pDrink = DBG_NEW CDrink;

	//位置の設定
	pDrink->SetPos(pos);

	//スケールの設定
	pDrink->SetScale(scale);

	
	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pDrink->SetModelIdx(pModel->Regist("data\\MODEL\\drink.x"));
	pDrink->BindModel(pModel->GetMeshAdress(pDrink->GetModelIdx()),
		pModel->GetBuffMatAdress(pDrink->GetModelIdx()),
		pModel->GetNumMatAdress(pDrink->GetModelIdx()),
		pModel->GetTexIdx(pDrink->GetModelIdx()));

	//初期化処理
	pDrink->Init();

	return pDrink;
}