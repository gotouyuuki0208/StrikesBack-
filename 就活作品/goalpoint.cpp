//==========================
// 
// ステージ遷移位置の位置表示[Goalpoint.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "Goalpoint.h"
#include "texture.h"
#include "manager.h"

//静的メンバ初期化
const int CGoalPoint::PRIORITY = 3;//描画順

//==========================
//コンストラクタ
//==========================
CGoalPoint::CGoalPoint(int nPriority) :CBillBoard(nPriority), m_nTexIdx(0)
{

}

//==========================
//デストラクタ
//==========================
CGoalPoint::~CGoalPoint()
{

}

//==========================
//初期化処理
//==========================
HRESULT CGoalPoint::Init()
{
	//初期設定
	CBillBoard::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CGoalPoint::Uninit()
{
	//終了処理
	CBillBoard::Uninit();
}

//==========================
//更新処理
//==========================
void  CGoalPoint::Update()
{
	//更新処理
	CBillBoard::Update();
}

//==========================
//描画処理
//==========================
void CGoalPoint::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//描画処理
	CBillBoard::Draw();

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//==========================
//オブジェクト2D生成
//==========================
CGoalPoint* CGoalPoint::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンス生成
	CGoalPoint* pGoalPoint = DBG_NEW CGoalPoint;

	//位置の設定
	pGoalPoint->SetPos(pos);

	//大きさの設定
	pGoalPoint->SetSize(size);

	//色の設定
	pGoalPoint->SetCor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));//緑に設定

	//初期化処理
	pGoalPoint->Init();

	//テクスチャの設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pGoalPoint->m_nTexIdx = pTex->Regist("data\\TEXTURE\\point.png");
	pGoalPoint->BindTexture(pTex->GetAdress(pGoalPoint->m_nTexIdx));

	return pGoalPoint;
}