//==========================
// 
// ゲーム画面の処理[game.h]
// Author Yuki Goto
//
//==========================
#ifndef _GAME_H_
#define _GAME_H_

//include
#include"scene.h"
#include"edit.h"

//ゲームクラスの定義
class CGame :public CScene
{
public:

	//メンバ関数
	CGame();//コンストラクタ
	~CGame() override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
private:

	//メンバ関数
	void UseEdit();//配置ツールの使用

	//メンバ変数
	CEdit* m_Edit;//オブジェクト配置クラスの情報
	
};

#endif 