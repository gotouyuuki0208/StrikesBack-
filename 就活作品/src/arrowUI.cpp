//==========================
// 
// 矢印表示[arrowUI.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "arrowUI.h"
#include "manager.h"
#include "texture.h"
#include"arrowpoint.h"

//静的メンバ初期化
const int CArrowUI::PRIORITY = 3;//描画順

//==========================
//コンストラクタ
//==========================
CArrowUI::CArrowUI(int nPriority) :
CObject3D(nPriority),
m_nTexIdx(0),
m_Draw(false)
{

}

//==========================
//デストラクタ
//==========================
CArrowUI::~CArrowUI()
{

}

//==========================
//初期化処理
//==========================
HRESULT CArrowUI::Init()
{
	//初期設定
	CObject3D::Init();

	m_ArrowPoint = CArrowPoint::Create({ 200.0f, 0.0f,0.0f }, { 50.0f,0.0f ,50.0f });;

	return S_OK;
}

//==========================
//終了処理
//==========================
void CArrowUI::Uninit()
{
	//終了処理
	CObject3D::Uninit();
}

//==========================
//更新処理
//==========================
void CArrowUI::Update()
{
	//描画判定
	JudgeDraw();

	//向きの変更
	ChangeDirection();

	//更新処理
	CObject3D::Update();
}

//==========================
//描画処理
//==========================
void CArrowUI::Draw()
{
	if (!m_Draw)
	{
		return;
	}

	//描画処理
	CObject3D::Draw();
}

//==========================
//オブジェクト生成
//==========================
CArrowUI* CArrowUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンス生成
	CArrowUI* pArrowUI = DBG_NEW CArrowUI;

	//位置の設定
	pArrowUI->SetPos(pos);

	//大きさの設定
	pArrowUI->SetSize(size);

	//色の設定
	pArrowUI->SetCol({ 1.0f,0.0f,0.0f,1.0f });

	//初期化処理
	pArrowUI->Init();

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pArrowUI->m_nTexIdx = pTex->Regist("data\\TEXTURE\\arrow.png");
	pArrowUI->BindTexture(pTex->GetAdress(pArrowUI->m_nTexIdx));

	return pArrowUI;
}

//==========================
//描画するか判定
//==========================
void CArrowUI::JudgeDraw()
{
	m_Draw = false;

	//行動中の敵の数を取得
	int Enemynum = CManager::GetInstance()->GetGameManager()->GetActiveEnemy();

	if (Enemynum <= 0)
	{//敵がいない

		//描画する
		m_Draw = true;
	}
}

//==========================
//向きの変更
//==========================
void CArrowUI::ChangeDirection()
{
	//ベクトルを算出
	D3DXVECTOR3 pos = m_ArrowPoint->GetPos() - GetPos();

	//ベクトルを正規化
	D3DXVec3Normalize(&pos, &pos);

	float m_roty = atan2f(pos.x, pos.z);

	SetRot({ 0.0f,m_roty ,0.0f });
}