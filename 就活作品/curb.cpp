//==========================
// 
// 縁石[curb.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "curb.h"
#include "manager.h"
#include "texture.h"

//静的メンバ初期化
const int CCurb::PRIORITY = 0;//描画順

//==========================
//コンストラクタ
//==========================
CCurb::CCurb(int nPriority):
CFild(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CCurb::~CCurb()
{

}

//==========================
//初期化処理
//==========================
HRESULT CCurb::Init()
{
	//初期設定
	CFild::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CCurb::Uninit()
{
	//終了処理
	CFild::Uninit();
}

//==========================
//更新処理
//==========================
void CCurb::Update()
{
	//更新処理
	CFild::Update();
}

//==========================
//描画処理
//==========================
void CCurb::Draw()
{
	//描画処理
	CFild::Draw();
}

//==========================
//オブジェクト生成
//==========================
CCurb* CCurb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CCurb* pFild = DBG_NEW CCurb;

	//位置の設定
	pFild->SetPos(D3DXVECTOR3(pos.x, 0.5f, pos.z));

	//大きさの設定
	pFild->SetSize(size);

	//大きさの設定
	pFild->SetRot(rot);

	//色の設定
	pFild->SetCor(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));

	//初期化処理
	pFild->Init();

	//テクスチャ設定
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pFild->m_nTexIdx = pTex->Regist("data\\TEXTURE\\blood.png");
	pFild->BindTexture(pTex->GetAdress(pFild->m_nTexIdx));*/

	//タイプ設定
	pFild->SetType(TYPE::FILD);
	pFild->SetFild(FILDTYPE::CURB);

	return pFild;
}