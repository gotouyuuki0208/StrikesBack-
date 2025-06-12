//==========================
// 
// 懸垂機[pullup.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "pullup.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int CPullUp::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CPullUp::CPullUp(int nPriority) :CObjectX(nPriority), m_nModelIdx(0)
{

}

//==========================
//デストラクタ
//==========================
CPullUp::~CPullUp()
{

}

//==========================
//初期化処理
//==========================
HRESULT CPullUp::Init()
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
void  CPullUp::Uninit()
{
	//終了処理
	CObjectX::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CPullUp::Update()
{
	//更新処理
	CObjectX::Update();
}

//==========================
//描画処理
//==========================
void CPullUp::Draw()
{
	//描画処理
	CObjectX::Draw();
}

//==========================
//オブジェクト生成
//==========================
CPullUp* CPullUp::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CPullUp* pPullUp = DBG_NEW CPullUp;

	//位置の設定
	pPullUp->SetPos(pos);

	//スケールの設定
	pPullUp->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pPullUp->m_nModelIdx = pModel->Regist("data\\MODEL\\pullup.x");
	pPullUp->BindModel(pModel->GetMeshAdress(pPullUp->m_nModelIdx),
		pModel->GetBuffMatAdress(pPullUp->m_nModelIdx),
		pModel->GetNumMatAdress(pPullUp->m_nModelIdx),
		pModel->GetTexIdx(pPullUp->m_nModelIdx));

	//初期化処理
	pPullUp->Init();

	return pPullUp;
}