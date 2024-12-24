//==========================
// 
// タイトルロゴ[PeopleNum.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"peoplenum.h"
#include"manager.h"

//静的メンバの初期化
const int CPeopleNum::PRIORITY = 4;//描画優先度
int  CPeopleNum::m_nTexIdx = 0;//テクスチャID
//========================
//コンストラクタ
//========================
CPeopleNum::CPeopleNum(int nPriority) :CObject2D(nPriority)
{

}

//========================
//デストラクタ
//========================
CPeopleNum::~CPeopleNum()
{

}

//========================
//初期設定
//========================
HRESULT CPeopleNum::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//終了処理
//========================
void CPeopleNum::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//更新処理
//========================
void CPeopleNum::Update()
{
	CObject2D::Update();
}

//========================
//描画処理
//========================
void CPeopleNum::Draw()
{
	CObject2D::Draw();
}

//========================
//オブジェクト2D生成
//========================
CPeopleNum* CPeopleNum::Create(D3DXVECTOR3 pos)
{
	//インスタンス生成
	CPeopleNum* pPeopleNum = DBG_NEW CPeopleNum;

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pPeopleNum->m_nTexIdx = pTex->Regist("data\\TEXTURE\\People.png");
	pPeopleNum->BindTexture(pTex->GetAdress(pPeopleNum->m_nTexIdx));

	//位置の設定
	pPeopleNum->SetPos(pos);

	//サイズ設定
	pPeopleNum->SetSize(50.0f, 50.0f);

	//色を設定
	pPeopleNum->SetCor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//初期設定
	pPeopleNum->Init();

	return pPeopleNum;
}