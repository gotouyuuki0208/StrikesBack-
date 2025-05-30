//==========================
// 
// ボス戦開始時の黒背景処理[directionbg.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"directionbg.h"
#include"manager.h"

//静的メンバの初期化
const int CDirectionBg::PRIORITY = 4;//描画優先度
//========================
//コンストラクタ
//========================
CDirectionBg::CDirectionBg(int nPriority) :
	CObject2D(nPriority),
	m_CountFlame(0),
	m_FirstPos({0.0f,0.0f,0.0f}),
	m_Delete(false)
{

}

//========================
//デストラクタ
//========================
CDirectionBg::~CDirectionBg()
{

}

//========================
//初期設定
//========================
HRESULT CDirectionBg::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//========================
//終了処理
//========================
void CDirectionBg::Uninit(void)
{
	CObject2D::Uninit();
}

//========================
//更新処理
//========================
void CDirectionBg::Update()
{
	CObject2D::Update();

	if (m_Delete)
	{//画面外にでた

		//終了処理
		Uninit();
	}
}

//========================
//描画処理
//========================
void CDirectionBg::Draw()
{
	CObject2D::Draw();
}

//========================
//オブジェクト2D生成
//========================
CDirectionBg* CDirectionBg::Create(D3DXVECTOR3 pos)
{
	//インスタンス生成
	CDirectionBg* pTutorialBg = DBG_NEW CDirectionBg;

	//位置の設定
	pTutorialBg->SetPos(pos);
	
	//最初の位置を保存
	pTutorialBg->m_FirstPos = pos;

	//サイズ設定
	pTutorialBg->SetSize(50.0f, SCREEN_WIDTH / 2);

	//色を設定
	pTutorialBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	//初期設定
	pTutorialBg->Init();

	return pTutorialBg;
}

//========================
//画面に入る
//========================
void CDirectionBg::EnterScreen()
{
	if (m_CountFlame > 5)
	{//5フレーム移動した
		return;
	}

	//フレーム数をカウント
	m_CountFlame++;

	if (m_FirstPos.y < 0.0f)
	{//上にあるポリゴン

		//位置を変更
		SetPos({ GetPos().x, GetPos().y + 10.0f ,GetPos().z });
	}
	else
	{//下にあるポリゴン

		//位置を変更
		SetPos({ GetPos().x, GetPos().y - 10.0f ,GetPos().z });
	}
}

//========================
//画面から出る
//========================
void CDirectionBg::ExitScreen()
{
	if (m_FirstPos.y < 0.0f)
	{//上にあるポリゴン

		//位置を変更
		SetPos({ GetPos().x, GetPos().y - 10.0f ,GetPos().z });

		if (GetPos().y <= m_FirstPos.y)
		{//画面外
			m_Delete = true;
		}
	}
	else
	{//下にあるポリゴン

		//位置を変更
		SetPos({ GetPos().x, GetPos().y + 10.0f ,GetPos().z });

		if (GetPos().y >= m_FirstPos.y)
		{//画面外
			m_Delete = true;
		}
	}
}