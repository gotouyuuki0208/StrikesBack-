//==========================
// 
// 3Dモデル描画サンプル[sample_objectX.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "sample_objectX.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int CSampleObjectX::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CSampleObjectX::CSampleObjectX(int nPriority):CObjectX(nPriority), m_nModelIdx(0)
{

}

//==========================
//デストラクタ
//==========================
CSampleObjectX::~CSampleObjectX()
{

}

//==========================
//初期化処理
//==========================
HRESULT CSampleObjectX::Init()
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
void  CSampleObjectX::Uninit()
{
	//終了処理
	CObjectX::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CSampleObjectX::Update()
{
	//更新処理
	CObjectX::Update();
}

//==========================
//描画処理
//==========================
void CSampleObjectX::Draw()
{
	//描画処理
	CObjectX::Draw();
}

//==========================
//オブジェクト生成
//==========================
CSampleObjectX* CSampleObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CSampleObjectX* pSampleObjectX = DBG_NEW CSampleObjectX;

	//位置の設定
	pSampleObjectX->SetPos(pos);

	//スケールの設定
	pSampleObjectX->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pSampleObjectX->m_nModelIdx = pModel->Regist("data\\MODEL\\soil.x");
	pSampleObjectX->BindModel(pModel->GetMeshAdress(pSampleObjectX->m_nModelIdx),
		pModel->GetBuffMatAdress(pSampleObjectX->m_nModelIdx),
		pModel->GetNumMatAdress(pSampleObjectX->m_nModelIdx),
		pModel->GetTexIdx(pSampleObjectX->m_nModelIdx));

	//初期化処理
	pSampleObjectX->Init();

	return pSampleObjectX;
}