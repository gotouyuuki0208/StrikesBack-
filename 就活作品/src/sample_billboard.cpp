//==========================
// 
// ビルボード描画サンプル[sample_billBoard.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "sample_billBoard.h"
#include "texture.h"
#include "manager.h"

//静的メンバ初期化
const int CSampleBillBoard::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CSampleBillBoard::CSampleBillBoard(int nPriority) :CBillBoard(nPriority), m_nTexIdx(0)
{

}

//==========================
//デストラクタ
//==========================
CSampleBillBoard::~CSampleBillBoard()
{

}

//==========================
//初期化処理
//==========================
HRESULT CSampleBillBoard::Init()
{
	//初期設定
	CBillBoard::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CSampleBillBoard::Uninit()
{
	//終了処理
	CBillBoard::Uninit();
}

//==========================
//更新処理
//==========================
void  CSampleBillBoard::Update()
{
	//更新処理
	CBillBoard::Update();
}

//==========================
//描画処理
//==========================
void CSampleBillBoard::Draw()
{
	//描画処理
	CBillBoard::Draw();
}

//==========================
//オブジェクト2D生成
//==========================
CSampleBillBoard* CSampleBillBoard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンス生成
	CSampleBillBoard* pSampleBillBoard = DBG_NEW CSampleBillBoard;

	//位置の設定
	pSampleBillBoard->SetPos(pos);

	//大きさの設定
	pSampleBillBoard->SetSize(size);

	//初期化処理
	pSampleBillBoard->Init();

	//テクスチャの設定
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pSampleBillBoard->m_nTexIdx = pTex->Regist("data\\TEXTURE\\effect000.jpg");
	pSampleBillBoard->BindTexture(pTex->GetAdress(pSampleBillBoard->m_nTexIdx));*/

	return pSampleBillBoard;
}