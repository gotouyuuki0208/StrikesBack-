//==========================
// 
// ブロック[block.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "block.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int CBlock::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CBlock::CBlock(int nPriority) :CObjectX(nPriority), m_nModelIdx(0)
{

}

//==========================
//デストラクタ
//==========================
CBlock::~CBlock()
{

}

//==========================
//初期化処理
//==========================
HRESULT CBlock::Init()
{
	//サイズ設定
	SetSize();

	//初期設定
	CObjectX::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CBlock::Uninit()
{
	//終了処理
	CObjectX::Uninit();

	Release();
}

//==========================
//更新処理
//==========================
void CBlock::Update()
{
	//更新処理
	CObjectX::Update();
}

//==========================
//描画処理
//==========================
void CBlock::Draw()
{
	//描画処理
	CObjectX::Draw();
}

//==========================
//オブジェクト生成
//==========================
CBlock* CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CBlock* pBlock = DBG_NEW CBlock;

	//位置の設定
	pBlock->SetPos(pos);

	//スケールの設定
	pBlock->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pBlock->m_nModelIdx = pModel->Regist("data\\MODEL\\soil.x");
	pBlock->BindModel(pModel->GetMeshAdress(pBlock->m_nModelIdx),
		pModel->GetBuffMatAdress(pBlock->m_nModelIdx),
		pModel->GetNumMatAdress(pBlock->m_nModelIdx),
		pModel->GetTexIdx(pBlock->m_nModelIdx));

	//初期化処理
	pBlock->Init();

	pBlock->SetType(TYPE::BLOCK);
	return pBlock;
}