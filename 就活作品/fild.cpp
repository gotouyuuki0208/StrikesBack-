//==========================
// 
// 地面[fild.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "fild.h"
#include "manager.h"
#include "texture.h"

//静的メンバ初期化
const int CFild::PRIORITY = 0;//描画順

//==========================
//コンストラクタ
//==========================
CFild::CFild(int nPriority) :
CObject3D(nPriority),
m_nTexIdx(0),
m_FildType(FILDTYPE::NONE)
{

}

//==========================
//デストラクタ
//==========================
CFild::~CFild()
{

}

//==========================
//初期化処理
//==========================
HRESULT CFild::Init()
{
	//初期設定
	CObject3D::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CFild::Uninit()
{
	//終了処理
	CObject3D::Uninit();
}

//==========================
//更新処理
//==========================
void CFild::Update()
{
	//更新処理
	CObject3D::Update();
}

//==========================
//描画処理
//==========================
void CFild::Draw()
{
	//描画処理
	CObject3D::Draw();
}

//==========================
//オブジェクト生成
//==========================
CFild* CFild::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CFild* pFild = DBG_NEW CFild;

	//位置の設定
	pFild->SetPos(pos);

	//大きさの設定
	pFild->SetSize(size);
	
	//向きの設定
	pFild->SetRot(rot);

	//色の設定
	pFild->SetCol(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));
	//pFild->SetCor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	//初期化処理
	pFild->Init();

	//テクスチャ設定
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pFild->m_nTexIdx = pTex->Regist("data\\TEXTURE\\blood.png");
	pFild->BindTexture(pTex->GetAdress(pFild->m_nTexIdx));*/

	//タイプ設定
	pFild->SetType(TYPE::FILD);
	pFild->SetFild(FILDTYPE::FILD);

	return pFild;
}

//==========================
//地面の種類を取得
//==========================
CFild::FILDTYPE CFild::GetFildType()
{
	return m_FildType;
}

//==========================
//地面の種類を設定
//==========================
void CFild::SetFild(FILDTYPE type)
{
	m_FildType = type;
}

//==========================
//テクスチャ番号を設定
//==========================
void CFild::SetTexIdx(int Idx)
{
	m_nTexIdx = Idx;
}

//==========================
//テクスチャ番号を取得
//==========================
int CFild::GetTexIdx()
{
	return m_nTexIdx;
}