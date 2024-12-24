//==========================
// 
// [KnockDown.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"knockdown.h"
#include"manager.h"

//静的メンバの初期化
const int CKnockDown::PRIORITY = 4;//描画優先度
int  CKnockDown::m_nTexIdx = 0;//テクスチャID

//========================
//コンストラクタ
//========================
CKnockDown::CKnockDown(int nPriority) :CObject2D(nPriority)
{

}

//========================
//デストラクタ
//========================
CKnockDown::~CKnockDown()
{

}

//========================
//初期設定
//========================
HRESULT CKnockDown::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//終了処理
//========================
void CKnockDown::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//更新処理
//========================
void CKnockDown::Update()
{
	CObject2D::Update();
}

//========================
//描画処理
//========================
void CKnockDown::Draw()
{
	CObject2D::Draw();
}

//========================
//オブジェクト2D生成
//========================
CKnockDown* CKnockDown::Create(D3DXVECTOR3 pos)
{
	//インスタンス生成
	CKnockDown* pKnockDown = DBG_NEW CKnockDown;

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pKnockDown->m_nTexIdx = pTex->Regist("data\\TEXTURE\\NumberOfPeopleDefeated.png");
	pKnockDown->BindTexture(pTex->GetAdress(pKnockDown->m_nTexIdx));

	//位置の設定
	pKnockDown->SetPos(pos);

	//サイズ設定
	pKnockDown->SetSize(50.0f, 200.0f);

	//色を設定
	pKnockDown->SetCor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//初期設定
	pKnockDown->Init();

	return pKnockDown;
}