//==========================
// 
// 3Dポリゴン描画サンプル[sample_object3D.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "sample_object3D.h"
#include "manager.h"
#include "texture.h"

//静的メンバ初期化
const int CSampleObject3D::PRIORITY = 0;//描画順

//==========================
//コンストラクタ
//==========================
CSampleObject3D::CSampleObject3D(int nPriority):CObject3D(nPriority), m_nTexIdx(0)
{

}

//==========================
//デストラクタ
//==========================
CSampleObject3D::~CSampleObject3D()
{

}

//==========================
//初期化処理
//==========================
HRESULT CSampleObject3D::Init()
{
	//初期設定
	CObject3D::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CSampleObject3D::Uninit()
{
	//終了処理
	CObject3D::Uninit();
}

//==========================
//更新処理
//==========================
void CSampleObject3D::Update()
{
	//更新処理
	CObject3D::Update();
}

//==========================
//描画処理
//==========================
void CSampleObject3D::Draw()
{
	//描画処理
	CObject3D::Draw();
}

//==========================
//オブジェクト生成
//==========================
CSampleObject3D* CSampleObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンス生成
	CSampleObject3D* pSampleObject3D = DBG_NEW CSampleObject3D;

	//位置の設定
	pSampleObject3D->SetPos(pos);

	//大きさの設定
	pSampleObject3D->SetSize(size);

	//初期化処理
	pSampleObject3D->Init();

	//テクスチャ設定
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pSampleObject3D->m_nTexIdx = pTex->Regist("data\\TEXTURE\\blood.png");
	pSampleObject3D->BindTexture(pTex->GetAdress(pSampleObject3D->m_nTexIdx));*/

	return pSampleObject3D;
}