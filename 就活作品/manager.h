//==========================
// 
// マネージャー[manager.h]
// Author Yuki Goto
//
//==========================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//include
#include"renderer.h"
#include"input.h"
#include"sound.h"
#include"camera.h"
#include"light.h"
#include"texture.h"
#include"model.h"
#include"scene.h"
#include"fade.h"
#include"debug.h"
#include"stagemanager.h"
#include"TutorialManager.h"
#include"GameManager.h"

//マネージャクラスの定義
class CManager
{
public:

	//メンバ関数
	~CManager();//デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);//初期設定
	void Uninit();//終了処理
	void Update();//更新処理
	void Draw();//描画処理

	static CManager* GetInstance();//インスタンス取得
	CRenderer* GetRenderer();//レンダラー取得
	CInputKeyboard*GetKeyboard();//キーボード入力取得
	CInputJoypad* GetJoypad();//パッド情報取得
	CSound* GetSound();//サウンド情報取得
	//CBlockManager* GetBlockManager();//ブロック情報取得
	CCamera* GetCamera();//カメラ情報取得
	CLight* GetLight();//ライト情報取得
	CTexture* GetTexture();//テクスチャ情報取得
	CModel* GetModel();//モデル情報取得
	CFade* GetFade();//フェードの取得
	CDebug* GetDebug();//デバッグの取得
	CStageManager* GetStageManager();//ステージの取得
	CTutorial* GetTutorial();//チュートリアルの取得
	CScene* GetScene();//シーンの取得
	CGameManager* GetGameManager();
	void SetMode(CScene::MODE mode);//画面の設定
private:

	//メンバ関数
	CManager();//コンストラクタ

	//メンバ変数
	CRenderer* m_pRenderer;//レンダラー
	CInputKeyboard* m_pKeyboard;//キーボード
	CInputJoypad* m_pJoypad;//キーボード
	CSound* m_pSound;//サウンド
	CCamera* m_Camera;//カメラ情報
	CLight* m_Light;//ライト情報
	CTexture* m_Texture;//テクスチャ
	CModel* m_Model;//モデル
	CScene* m_pScene;//現在の画面
	CFade* m_pFade;//フェード
	CDebug* m_Debug;//デバッグ
	CStageManager* m_Stage;//ステージ管理
	CTutorial* m_Tutorial;//チュートリアル管理
	CGameManager* m_GameManager;//ゲーム管理
};

#endif 
