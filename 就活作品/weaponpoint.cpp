//==========================
// 
// 武器の位置表示[weaponpoint.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "weaponpoint.h"
#include "texture.h"
#include "manager.h"

//静的メンバ初期化
const int CWeaponPoint::PRIORITY = 3;//描画順
const float CWeaponPoint::MOVE = 0.1f;//移動量
const float CWeaponPoint::DISTANCE = 5.0f;//移動する距離

//==========================
//コンストラクタ
//==========================
CWeaponPoint::CWeaponPoint(int nPriority) :
CBillBoard(nPriority),//基底コンストラクタ
m_nTexIdx(0),//テクスチャの番号
m_MoveDirection(true),//移動方向切り替え判定
m_FirstPos(0.0f)//最初の位置
{

}

//==========================
//デストラクタ
//==========================
CWeaponPoint::~CWeaponPoint()
{

}

//==========================
//初期化処理
//==========================
HRESULT CWeaponPoint::Init()
{
	//初期設定
	CBillBoard::Init();

	//最初の位置を保存
	m_FirstPos = GetPos().y;
	
	return S_OK;
}

//==========================
//終了処理
//==========================
void CWeaponPoint::Uninit()
{
	//終了処理
	CBillBoard::Uninit();
}

//==========================
//更新処理
//==========================
void  CWeaponPoint::Update()
{
	//移動処理
	Move();

	//更新処理
	CBillBoard::Update();
}

//==========================
//描画処理
//==========================
void CWeaponPoint::Draw()
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
CWeaponPoint* CWeaponPoint::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンス生成
	CWeaponPoint* pWeaponPoint = DBG_NEW CWeaponPoint;

	//位置の設定
	pWeaponPoint->SetPos(pos);

	//大きさの設定
	pWeaponPoint->SetSize(size);

	//色の設定
	pWeaponPoint->SetCor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));//青に設定

	//初期化処理
	pWeaponPoint->Init();

	//テクスチャの設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pWeaponPoint->m_nTexIdx = pTex->Regist("data\\TEXTURE\\point.png");
	pWeaponPoint->BindTexture(pTex->GetAdress(pWeaponPoint->m_nTexIdx));

	return pWeaponPoint;
}

//==========================
//移動処理
//==========================
void CWeaponPoint::Move()
{
	if (m_MoveDirection)
	{
		//上がる
		SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + MOVE, GetPos().z));
	}
	else
	{
		//下がる
		SetPos(D3DXVECTOR3(GetPos().x, GetPos().y - MOVE, GetPos().z));
	}

	if (GetPos().y >= (m_FirstPos + DISTANCE))
	{//最初の位置から一定の距離高くなったとき

		GetPos().y = m_FirstPos + DISTANCE;
		m_MoveDirection = false;//下がる
	}
	else if (GetPos().y <= m_FirstPos)
	{//最初の位置から一定の距離低くなったとき

		GetPos().y = m_FirstPos;
		m_MoveDirection = true;//上がる
	}
}