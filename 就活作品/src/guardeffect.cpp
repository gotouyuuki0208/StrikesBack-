//==========================
// 
// ガードエフェクト[guardeffect.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "guardeffect.h"
#include "manager.h"
#include "texture.h"

//静的メンバ初期化
const int CGuardEffect::PRIORITY = 3;//描画順
const float CGuardEffect::SUB_COL = 0.03f;//色の減らす数値
//==========================
//コンストラクタ
//==========================
CGuardEffect::CGuardEffect(int nPriority) :
	CObject3D(nPriority),//基底コンストラクタ
	m_nTexIdx(0)//テクスチャの番号
{

}

//==========================
//デストラクタ
//==========================
CGuardEffect::~CGuardEffect()
{

}

//==========================
//初期化処理
//==========================
HRESULT CGuardEffect::Init()
{
	//初期設定
	CObject3D::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CGuardEffect::Uninit()
{
	//終了処理
	CObject3D::Uninit();
}

//==========================
//更新処理
//==========================
void CGuardEffect::Update()
{
	//更新処理
	CObject3D::Update();
	
	//色の変更
	ChangeCol();
}

//==========================
//描画処理
//==========================
void CGuardEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	//カリングをオフにする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//描画処理
	CObject3D::Draw();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//==========================
//オブジェクト生成
//==========================
CGuardEffect* CGuardEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CGuardEffect* pGuardEffect = DBG_NEW CGuardEffect;

	//位置の設定
	pGuardEffect->SetPos(pos);

	//向きの設定
	pGuardEffect->SetRot(rot);

	//大きさの設定
	pGuardEffect->SetSize(D3DXVECTOR3(15.0f, 15.0f, 0.0f));

	//色の設定
	pGuardEffect->SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.3f));

	//初期化処理
	pGuardEffect->Init();

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pGuardEffect->m_nTexIdx = pTex->Regist("data\\TEXTURE\\GuardEffect.png");
	pGuardEffect->BindTexture(pTex->GetAdress(pGuardEffect->m_nTexIdx));

	return pGuardEffect;
}

//==========================
//色の変更
//==========================
void CGuardEffect::ChangeCol()
{
	SetCol(D3DXCOLOR(GetCol().r, GetCol().g, GetCol().b, GetCol().a - SUB_COL));
}