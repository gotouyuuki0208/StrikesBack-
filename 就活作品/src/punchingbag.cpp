//==========================
// 
// サンドバッグ[punchingbug.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "punchingbag.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
//静的メンバ初期化
const int CPunchingBag::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CPunchingBag::CPunchingBag(int nPriority) :CObjectX(nPriority), m_nModelIdx(0)
{

}

//==========================
//デストラクタ
//==========================
CPunchingBag::~CPunchingBag()
{

}

//==========================
//初期化処理
//==========================
HRESULT CPunchingBag::Init()
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
void  CPunchingBag::Uninit()
{
	//終了処理
	CObjectX::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CPunchingBag::Update()
{
	//更新処理
	CObjectX::Update();
}

//==========================
//描画処理
//==========================
void CPunchingBag::Draw()
{
	//描画処理
	CObjectX::Draw();
}

//==========================
//オブジェクト生成
//==========================
CPunchingBag* CPunchingBag::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CPunchingBag* pPunchingBag = DBG_NEW CPunchingBag;

	//位置の設定
	pPunchingBag->SetPos(pos);

	//スケールの設定
	pPunchingBag->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pPunchingBag->m_nModelIdx = pModel->Regist("data\\MODEL\\punchingbag.x");
	pPunchingBag->BindModel(pModel->GetMeshAdress(pPunchingBag->m_nModelIdx),
		pModel->GetBuffMatAdress(pPunchingBag->m_nModelIdx),
		pModel->GetNumMatAdress(pPunchingBag->m_nModelIdx),
		pModel->GetTexIdx(pPunchingBag->m_nModelIdx));

	//初期化処理
	pPunchingBag->Init();

	return pPunchingBag;
}