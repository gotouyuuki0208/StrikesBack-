//==========================
// 
// 軌跡の描画処理[trajectory.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "trajectory.h"
#include "manager.h"
#include "texture.h"

//静的メンバ初期化
const int CTrajectory::PRIORITY = 3;//描画順

//==========================
//コンストラクタ
//==========================
CTrajectory::CTrajectory(int nPriority) :
	CObjectMesh(nPriority),
	m_nTexIdx(0)
{

}

//==========================
//デストラクタ
//==========================
CTrajectory::~CTrajectory()
{

}

//==========================
//初期化処理
//==========================
HRESULT CTrajectory::Init()
{
	//初期設定
	CObjectMesh::Init();

	//頂点情報の初期化
	InitVtxPos();

	//頂点座標の設定
	//SetVertexPos();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CTrajectory::Uninit()
{
	//終了処理
	CObjectMesh::Uninit();
}

//==========================
//更新処理
//==========================
void CTrajectory::Update()
{
	//頂点座標の設定
	SetVertexPos();

	//更新処理
	CObjectMesh::Update();
}

//==========================
//描画処理
//==========================
void CTrajectory::Draw()
{
	//描画処理
	CObjectMesh::Draw();
}

//==========================
//オブジェクト生成
//==========================
CTrajectory* CTrajectory::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int Width, int Vertical)
{
	//インスタンス生成
	CTrajectory* pTrajectory = DBG_NEW CTrajectory;

	//位置の設定
	pTrajectory->SetPos(pos);

	//サイズの設定
	pTrajectory->SetSize(size);

	//横の分割数
	pTrajectory->SetWidthDiv(Width);

	//縦の分割数
	pTrajectory->SetVerticalDiv(Vertical);

	//最初の頂点の位置を設定
	pTrajectory->m_NewPos = pos;

	//初期設定
	pTrajectory->Init();

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pTrajectory->m_nTexIdx = pTex->Regist("data\\TEXTURE\\effect.png");
	pTrajectory->BindTexture(pTex->GetAdress(pTrajectory->m_nTexIdx));

	return pTrajectory;
}

//==========================
//頂点座標の設定
//==========================
void CTrajectory::SetVertexPos()
{
	if (GetVtxBuff() == nullptr)
	{
		return;
	}

	VERTEX_3D* pVtx; //頂点情報へのポインタ

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//頂点バッファを取得

	//頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の横の位置
	int WidthPos = 0;

	//頂点の縦の位置
	int VerticalPos = 0;

	//頂点の縦幅を算出
	float Height = (GetSize().y * 2) / GetVerticalDiv();

	int a = GetNumVtx();
	//頂点座標を移動
	for (int i = 0; i < GetNumVtx(); i++)
	{
		if (WidthPos == (VerticalPos + GetWidthDiv()))
		{//頂点の横幅が最後になった
			VerticalPos += (GetVerticalDiv() + 1);
		}
		else
		{
			int ChangeNum = i + 1;
			pVtx[i].pos = pVtx[ChangeNum].pos;
		}

		WidthPos++;
	}

	//新しい座標を入れる
	for (int i = 0; i <= GetVerticalDiv(); i++)
	{
		int VtxNum = i * (GetVerticalDiv() + 1) + GetWidthDiv();
		pVtx[VtxNum].pos = D3DXVECTOR3(m_NewPos.x, m_NewPos.y + (GetSize().y + (-Height * i)), m_NewPos.z);
	}

	//頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//==========================
//頂点情報の初期設定
//==========================
void CTrajectory::InitVtxPos()
{
	VERTEX_3D* pVtx; //頂点情報へのポインタ

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();//頂点バッファを取得

	//頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の縦幅を算出
	float Height = (GetSize().y * 2) / GetVerticalDiv();

	//新しい座標を入れる
	for (int i = 0; i < GetNumVtx(); i++)
	{
		pVtx[i].pos = D3DXVECTOR3(m_NewPos.x, m_NewPos.y + (GetSize().y + (-Height * i)), m_NewPos.z);
	}

	//頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//==========================
//新しい頂点座標の位置を設定
//==========================
void CTrajectory::SetNewPos(D3DXVECTOR3 pos)
{
	m_NewPos = pos;
}