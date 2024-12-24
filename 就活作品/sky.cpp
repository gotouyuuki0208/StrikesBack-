//==========================
// 
// 空[sky.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "sky.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int CSky::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CSky::CSky(int nPriority) :CObjectX(nPriority), m_nModelIdx(0)
{

}

//==========================
//デストラクタ
//==========================
CSky::~CSky()
{

}

//==========================
//初期化処理
//==========================
HRESULT CSky::Init()
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
void  CSky::Uninit()
{
	//終了処理
	CObjectX::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CSky::Update()
{
	//更新処理
	CObjectX::Update();
}

//==========================
//描画処理
//==========================
void CSky::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	//カリングをオフにする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	
	//描画処理
	CObjectX::Draw();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================
//オブジェクト生成
//==========================
CSky* CSky::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CSky* pSky = DBG_NEW CSky;

	//位置の設定
	pSky->SetPos(pos);

	//スケールの設定
	pSky->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pSky->m_nModelIdx = pModel->Regist("data\\MODEL\\sky.x");
	pSky->BindModel(pModel->GetMeshAdress(pSky->m_nModelIdx),
		pModel->GetBuffMatAdress(pSky->m_nModelIdx),
		pModel->GetNumMatAdress(pSky->m_nModelIdx),
		pModel->GetTexIdx(pSky->m_nModelIdx));

	//初期化処理
	pSky->Init();

	return pSky;
}