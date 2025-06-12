//==========================
// 
// [darkbg.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"darkbg.h"
#include"manager.h"

//静的メンバ変数初期化
const int CDarkBg::PRIORITY = 5;
//==========================
// コンストラクタ
//==========================
CDarkBg::CDarkBg(int priority) :CObject2D(priority)
{
	m_cor = 0.0f;
	m_fade = FADE::FADE_NONE;
}

//==========================
// デストラクタ
//==========================
CDarkBg::~CDarkBg()
{

}

//==========================
// 初期設定
//==========================
HRESULT CDarkBg::Init()
{
	SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	SetSize(360.0f, 640.0f);
	CObject2D::Init();

	return S_OK;
}

//==========================
// 終了処理
//==========================
void CDarkBg::Uninit()
{

}

//==========================
// 更新処理
//==========================
void CDarkBg::Update()
{
	if (m_fade != FADE::FADE_NONE)
	{
		if (m_fade == FADE::FADE_IN)
		{//フェードイン状態
			m_cor -= 0.05f;

			if (m_cor <= 0.0f)
			{
				m_cor = 0.0f;
				m_fade = FADE::FADE_NONE;
			}
		}
		else if (m_fade == FADE::FADE_OUT)
		{//フェードアウト状態
			m_cor += 0.05f;

			if (m_cor >= 1.0f)
			{
				m_cor = 1.0f;
				m_fade = FADE::FADE_IN;
			}
		}
	}

	SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_cor));//色の設定
	CObject2D::Update();//更新処理

}

//==========================
// 描画処理
//==========================
void CDarkBg::Draw()
{
	CObject2D::Draw();
}

//==========================
//フェードの設定処理
//==========================
void CDarkBg::SetFade()
{
	m_fade = FADE::FADE_OUT;
}

//==========================
//フェードの状態取得
//==========================
CDarkBg::FADE CDarkBg::GetFade()
{
	return m_fade;
}

//==========================
//生成
//==========================
CDarkBg* CDarkBg::Create()
{
	CDarkBg* pDarkBg = DBG_NEW CDarkBg;

	pDarkBg->Init();

	pDarkBg->SetType(TYPE::FADE);
	return pDarkBg;
}

//==========================
//透明度の取得
//==========================
float CDarkBg::GetCol()
{
	return m_cor;
}