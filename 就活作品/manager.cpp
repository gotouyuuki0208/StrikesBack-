//==========================
// 
// マネージャー[manager.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"manager.h"

//==========================
// コンストラクタ
//==========================
CManager::CManager(void):
m_pRenderer(nullptr),//レンダラー
m_pKeyboard(nullptr),//キーボード
m_pJoypad(nullptr),//キーボード
m_pSound(nullptr),//サウンド
m_Camera(nullptr),//カメラ情報取得
m_Light(nullptr),//ライト情報取得
m_Debug(nullptr),//デバッグ情報
m_Texture(nullptr),//テクスチャ
m_Model(nullptr),//モデル
m_pFade(nullptr),//フェード
m_pScene(nullptr),//現在の画面
m_Stage(nullptr),//ステージ
m_Tutorial(nullptr),//チュートリアル
m_GameManager(nullptr),//ゲーム管理
m_Collision(nullptr),//当たり判定
m_HudManager(nullptr)//HUDの管理
{
	
}

//==========================
// デストラクタ
//==========================
CManager::~CManager(void)
{

}

//==========================
// 初期設定
//==========================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//レンダラーの生成
	m_pRenderer = DBG_NEW CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//キーボード
	m_pKeyboard = DBG_NEW CInputKeyboard;
	m_pKeyboard->Init(hInstance, hWnd);

	//パッド
	m_pJoypad = DBG_NEW CInputJoypad;
	m_pJoypad->Init(hInstance, hWnd);

	//サウンド
	m_pSound = DBG_NEW CSound;
	m_pSound->Init(hWnd);
	
	//カメラ
	m_Camera = DBG_NEW CCamera;
	m_Camera->Init();

	//ライト
	m_Light = DBG_NEW CLight;
	m_Light->Init();

	//テクスチャ
	m_Texture = DBG_NEW CTexture;
	
	//モデル
	m_Model = DBG_NEW CModel;

	//フェード
	m_pFade = CFade::Create();
	//m_pFade->SetFade(CScene::MODE::TITLE);//最初のシーン設定
	m_pFade->SetFade(CScene::MODE::GAME);//最初のシーン設定
	
	//デバッグ
	m_Debug = DBG_NEW CDebug;

	//ステージ
	m_Stage = DBG_NEW CStageManager;

	//チュートリアル
	m_Tutorial = DBG_NEW CTutorialManager;

	//ゲーム管理
	m_GameManager = DBG_NEW CGameManager;

	//当たり判定
	m_Collision = DBG_NEW CCollision;

	//HUDの管理
	m_HudManager = DBG_NEW CHudManager;

	return S_OK;
}

//==========================
// 終了処理
//==========================
void CManager::Uninit(void)
{

	//全オブジェクト解放
	CObject::ReleaseAll();

	if (m_pRenderer != nullptr)
	{//レンダラー
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pScene != nullptr)
	{//シーン
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	if (m_pKeyboard != nullptr)
	{//キーボード
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}
	
	if (m_pJoypad != nullptr)
	{//パッド
		m_pJoypad->Uninit();
		delete m_pJoypad;
		m_pJoypad = nullptr;
	}

	if (m_pSound != nullptr)
	{//サウンド
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_Camera != nullptr)
	{//カメラ
		m_Camera->Uninit();
		delete m_Camera;
		m_Camera = nullptr;
	}

	if (m_Light != nullptr)
	{//ライト
		m_Light->Uninit();
		delete m_Light;
		m_Light = nullptr;
	}

	if (m_Texture != nullptr)
	{//テクスチャ
		m_Texture->UnLoad();
		delete m_Texture;
		m_Texture = nullptr;
	}

	if (m_Model != nullptr)
	{//モデル
		m_Model->UnLoad();
		delete m_Model;
		m_Model = nullptr;
	}

	if (m_pFade != nullptr)
	{//フェード
		m_pFade->CObject2D::Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	if (m_Debug != nullptr)
	{//デバッグ
		delete m_Debug;
		m_Debug = nullptr;
	}

	if (m_Stage != nullptr)
	{//ステージ
		m_Stage->Uninit();
		delete m_Stage;
		m_Stage = nullptr;
	}

	if (m_Tutorial != nullptr)
	{//チュートリアル
		delete m_Tutorial;
		m_Tutorial = nullptr;
	}

	if (m_GameManager != nullptr)
	{//ゲーム管理
		delete m_GameManager;
		m_GameManager = nullptr;
	}

	if (m_Collision != nullptr)
	{//当たり判定
		delete m_Collision;
		m_Collision = nullptr;
	}

	if (m_HudManager != nullptr)
	{//HUDの管理
		delete m_HudManager;
		m_HudManager = nullptr;
	}
}

//==========================
// 更新処理
//==========================
void CManager::Update(void)
{
	m_pRenderer->Update();//レンダラーの更新

	m_pKeyboard->Update();//キーボードの更新

	m_pJoypad->Update();//パッドの更新

	//if (m_pFade->GetFade() == CFade::FADE::FADE_NONE)
	if (m_pScene != nullptr)
	{//フェードしてないとき
		m_pScene->Update();//シーンの更新
	}
	
	m_Camera->Update();//カメラの更新
}

//==========================
// 描画処理
//==========================
void CManager::Draw(void)
{
	m_pRenderer->Draw();//レンダラーの描画

	//if (m_pFade->GetFade() == CFade::FADE::FADE_NONE)
	if (m_pScene != nullptr)
	{//フェードしてないとき
		m_pScene->Draw();//シーンの描画
	}
}

//=====================
//レンダラー取得
//=====================
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=====================
//キーボード取得
//=====================
CInputKeyboard* CManager::GetKeyboard(void)
{
	return m_pKeyboard;
}

//=====================
//パッド取得
//=====================
CInputJoypad* CManager::GetJoypad(void)
{
	return m_pJoypad;
}

//=====================
//サウンド取得
//=====================
CSound* CManager::GetSound(void)
{
	return m_pSound;
}

//=====================
//インスタンス取得
//=====================
CManager* CManager::GetInstance()
{
	static CManager instance;
	return &instance;
}

//=====================
//カメラ情報取得
//=====================
CCamera* CManager::GetCamera(void)
{
	return m_Camera;
}

//=====================
//ライト情報取得
//=====================
CLight* CManager::GetLight(void)
{
	return m_Light;
}

//=====================
//テクスチャ情報取得
//=====================
CTexture* CManager::GetTexture(void)
{
	return m_Texture;
}

//=====================
//モデル情報取得
//=====================
CModel* CManager::GetModel()
{
	return m_Model;
}

//=====================
//フェードの取得
//=====================
CFade* CManager::GetFade()
{
	return m_pFade;
}

//=====================
//デバッグの取得
//=====================
CDebug* CManager::GetDebug()
{
	return m_Debug;
}

//=====================
//ステージの取得
//=====================
CStageManager* CManager::GetStageManager()
{
	return m_Stage;
}

//=====================
//チュートリアルの取得
//=====================
CTutorialManager* CManager::GetTutorial()
{
	return m_Tutorial;
}

//=====================
//シーンの取得
//=====================
CScene* CManager::GetScene()
{
	return m_pScene;
}

//=====================
//ゲーム管理の取得
//=====================
CGameManager* CManager::GetGameManager()
{
	return m_GameManager;
}

//=====================
//当たり判定の取得
//=====================
CCollision* CManager::GetCollision()
{
	return m_Collision;
}

//=====================
//HUDの管理
//=====================
CHudManager* CManager::GetHudManager()
{
	return m_HudManager;
}

//=====================
//シーンの設定
//=====================
void CManager::SetMode(CScene::MODE mode)
{
	//終了処理
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//生成
	m_pScene = CScene::Create(mode);
	m_pScene->Init();
	m_Camera->Init();
}