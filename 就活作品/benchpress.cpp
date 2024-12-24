//==========================
// 
// ベンチプレス[benchpress.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "benchpress.h"
#include "manager.h"
#include "model.h"


//静的メンバ初期化
const int CBenchPress::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CBenchPress::CBenchPress(int nPriority) :CObjectX(nPriority), m_nModelIdx(0)
{

}

//==========================
//デストラクタ
//==========================
CBenchPress::~CBenchPress()
{

}

//==========================
//初期化処理
//==========================
HRESULT CBenchPress::Init()
{
	//サイズ設定
	//SetSize();

	//初期設定
	CObjectX::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CBenchPress::Uninit()
{
	//終了処理
	CObjectX::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CBenchPress::Update()
{
	//更新処理
	CObjectX::Update();
}

//==========================
//描画処理
//==========================
void CBenchPress::Draw()
{
	//描画処理
	CObjectX::Draw();
}

//==========================
//オブジェクト生成
//==========================
CBenchPress* CBenchPress::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CBenchPress* pBenchPress = DBG_NEW CBenchPress;

	//位置の設定
	pBenchPress->SetPos(pos);

	//スケールの設定
	pBenchPress->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBenchPress->m_nModelIdx = pModel->Regist("data\\MODEL\\benchpress.x");
	pBenchPress->BindModel(pModel->GetMeshAdress(pBenchPress->m_nModelIdx),
		pModel->GetBuffMatAdress(pBenchPress->m_nModelIdx),
		pModel->GetNumMatAdress(pBenchPress->m_nModelIdx),
		pModel->GetTexIdx(pBenchPress->m_nModelIdx));

	//初期化処理
	pBenchPress->Init();

	return pBenchPress;
}