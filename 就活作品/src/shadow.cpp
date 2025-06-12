//==========================
// 
// 影[shadow.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "shadow.h"
#include "manager.h"
#include "texture.h"

//静的メンバ初期化
const int CShadow::PRIORITY = 3;//描画順

//==========================
//コンストラクタ
//==========================
CShadow::CShadow(int nPriority):
CObject3D(nPriority),//基底コンストラクタ
m_nTexIdx(0)//テクスチャの番号
{

}

//==========================
//デストラクタ
//==========================
CShadow::~CShadow()
{

}

//==========================
//初期化処理
//==========================
HRESULT CShadow::Init()
{
	//初期設定
	CObject3D::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CShadow::Uninit()
{
	//終了処理
	CObject3D::Uninit();
}

//==========================
//更新処理
//==========================
void CShadow::Update()
{
	//更新処理
	CObject3D::Update();
}

//==========================
//描画処理
//==========================
void CShadow::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	//減算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//描画処理
	CObject3D::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==========================
//オブジェクト生成
//==========================
CShadow* CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンス生成
	CShadow* pShadow = DBG_NEW CShadow;

	//位置の設定
	pShadow->SetPos(pos);

	//大きさの設定
	pShadow->SetSize(size);

	//色の設定
	pShadow->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	//初期化処理
	pShadow->Init();

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pShadow->m_nTexIdx = pTex->Regist("data\\TEXTURE\\shadow000.jpg");
	pShadow->BindTexture(pTex->GetAdress(pShadow->m_nTexIdx));

	return pShadow;
}

//==========================
//移動処理
//==========================
void CShadow::Move(D3DXVECTOR3 pos)
{
	//位置を変更
	SetPos(D3DXVECTOR3(pos.x, 1.0f, pos.z));
}