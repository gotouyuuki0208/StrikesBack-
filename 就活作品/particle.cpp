//==========================
// 
// パーティクル処理[particle.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"particle.h"
#include"manager.h"
#include"texture.h"

//静的メンバ変数
const int CParticle::PRIORITY = 3;//描画順
//==========================
// コンストラクタ
//==========================
CParticle::CParticle(int priority):CBillBoard(priority),m_nLife(30), m_cor(1.0f), m_nTexIdx(0)
{
	m_posmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Width = 10.0f;//横
	m_Vertical = 10.0f;//縦
	m_speed = 0.0f;//速度
}

//==========================
// デストラクタ
//==========================
CParticle::~CParticle(void)
{

}

//==========================
// 初期設定
//==========================
HRESULT CParticle::Init(void)
{
	m_posmove.x = sinf((float)(rand() % 629 - 314) / 100.0f) * (float)(rand() % 100 + 1) / m_speed;
	m_posmove.y = sinf((float)(rand() % 629 - 314) / 100.0f) * (float)(rand() % 100 + 1) / m_speed;
	m_posmove.y = cosf((float)(rand() % 629) / 100.0f + 5.0f) * (float)(rand() % 100 + 1) / m_speed;

	CBillBoard::Init();

	return S_OK;
}

//==========================
// 終了処理
//==========================
void CParticle::Uninit(void)
{
	CBillBoard::Uninit();
}

//==========================
// 更新処理
//==========================
void CParticle::Update(void)
{
	m_nLife--;
	
	//位置設定
	SetPos(D3DXVECTOR3(GetPos().x + m_posmove.x, (GetPos().y + m_posmove.y) - 5.0f, GetPos().z + m_posmove.z));

	m_cor -= 0.01f;

	SetCor(D3DXCOLOR(GetCor().r, GetCor().g, GetCor().b, m_cor));//色の設定

	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	CBillBoard::Update();
}

//==========================
// 描画処理
//==========================
void CParticle::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillBoard::Draw();//描画処理

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
}

//========================
//オブジェクト2D生成
//========================
CParticle* CParticle::Create(D3DXVECTOR3 pos, D3DXCOLOR cor, int life, float Width, float Vertical,float speed)
{
	CParticle* pParticle = DBG_NEW CParticle;

	//位置の設定
	pParticle->SetPos(pos);

	//色の設定
	pParticle->SetCor(cor);

	//テクスチャ設定
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pParticle->m_nTexIdx = pTex->Regist("data\\TEXTURE\\effect000.jpg");
	pParticle->BindTexture(pTex->GetAdress(pParticle->m_nTexIdx));

	//サイズの設定
	pParticle->SetSize(D3DXVECTOR3(Width, Vertical, 0.0f));

	//移動速度の設定
	pParticle->m_speed = speed;
	
	//初期化処理
	pParticle->Init();

	//寿命の設定
	pParticle->m_nLife = life;

	return pParticle;
}