//==========================
// 
// 2Dポリゴン描画サンプル[sample_object2D.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "sample_object2D.h"
#include "texture.h"
#include "manager.h"

//静的メンバ初期化
const int CSampleObject2D::PRIORITY = 3;//描画順

//==========================
//コンストラクタ
//==========================
CSampleObject2D::CSampleObject2D(int nPriority):CObject2D(nPriority),m_nTexIdx(0)
{

}

//==========================
//デストラクタ
//==========================
CSampleObject2D::~CSampleObject2D()
{

}

//==========================
//初期化処理
//==========================
HRESULT CSampleObject2D::Init()
{
	//初期設定
	CObject2D::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CSampleObject2D::Uninit()
{
	//終了処理
	CObject2D::Uninit();
}

//==========================
//更新処理
//==========================
void  CSampleObject2D::Update()
{
	//アニメーション
	//CObject2D::Animetion(2.0f, 5, 10);

	//更新処理
	CObject2D::Update();
}

//==========================
//描画処理
//==========================
void CSampleObject2D::Draw()
{
	//描画処理
	CObject2D::Draw();
}

//==========================
//オブジェクト2D生成
//==========================
CSampleObject2D* CSampleObject2D::Create(D3DXVECTOR3 pos,float vertical, float width)
{
	//インスタンス生成
	CSampleObject2D* pSampleObject2D = DBG_NEW CSampleObject2D;

	//位置の設定
	pSampleObject2D->SetPos(pos);

	//大きさの設定
	pSampleObject2D->SetSize(vertical, width);

	//初期化処理
	pSampleObject2D->Init();
	
	//色の設定
	pSampleObject2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//テクスチャの設定
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pSampleObject2D->m_nTexIdx = pTex->Regist("data\\TEXTURE\\runningman102.png");
	pSampleObject2D->BindTexture(pTex->GetAdress(pSampleObject2D->m_nTexIdx));*/

	//テクスチャの大きさ設定
	//pSampleObject2D->SetTexSize(2.0f, 5, 0);

	return pSampleObject2D;
}