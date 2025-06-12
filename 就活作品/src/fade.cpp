//==========================
// 
// フェード処理[fade.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "fade.h"
#include"manager.h"

//静的メンバ変数初期化
const int CFade::PRIORITY = 5;
//==========================
// コンストラクタ
//==========================
CFade::CFade(int priority):
CObject2D(priority),			//基底コンストラクタ
m_Transparency(0.0f),					//色
m_fade(FADE::FADE_NONE),		//フェードの状態
g_modenext(CScene::MODE::TITLE),//次のシーン
m_InGame(false)					//ゲーム中か判定
{
	
}

//==========================
// デストラクタ
//==========================
CFade::~CFade()
{

}

//==========================
// 初期設定
//==========================
HRESULT CFade::Init()
{
	//位置の設定
	SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	
	//大きさの設定
	SetSize(360.0f, 640.0f);
	
	//初期設定
	CObject2D::Init();

	return S_OK;
}

//==========================
// 終了処理
//==========================
void CFade::Uninit()
{

}

//==========================
// 更新処理
//==========================
void CFade::Update()
{
	if (m_fade != FADE::FADE_NONE)
	{
		if (m_fade == FADE::FADE_IN)
		{//フェードイン状態
			m_Transparency -= 0.05f;

			if (m_Transparency <= 0.0f)
			{
				m_Transparency = 0.0f;
				m_fade = FADE::FADE_NONE;
			}
		}
		else if (m_fade == FADE::FADE_OUT)
		{//フェードアウト状態
			m_Transparency += 0.05f;

			if (m_Transparency >= 1.0f)
			{
				m_Transparency = 1.0f;
				m_fade = FADE::FADE_IN;

				if (!m_InGame)
				{
					CManager::GetInstance()->SetMode(g_modenext);
				}

				m_InGame = false;
			}
		}
	}

	SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_Transparency));//色の設定
	CObject2D::Update();//更新処理

}

//==========================
// 描画処理
//==========================
void CFade::Draw()
{
	CObject2D::Draw();
}

//==========================
//フェードの設定処理
//==========================
void CFade::SetFade(CScene::MODE modenext)
{
	g_modenext = modenext;
	m_fade = FADE::FADE_OUT;
}

//==========================
//フェードの状態取得
//==========================
CFade::FADE CFade::GetFade()
{
	return m_fade;
}

//==========================
//生成
//==========================
CFade* CFade::Create()
{
	CFade* pFade = DBG_NEW CFade;

	pFade->Init();

	pFade->SetType(TYPE::FADE);

	return pFade;
}

//==========================
//ゲーム内でのフェード
//==========================
void CFade::InGameFade()
{
	m_fade = FADE::FADE_OUT;
	m_InGame = true;
}

//==========================
//透明度の取得
//==========================
float CFade::GetTransparency()
{
	return m_Transparency;
}