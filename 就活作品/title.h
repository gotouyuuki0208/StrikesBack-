//==========================
// 
// タイトル画面の処理[taitle.h]
// Author Yuki Goto
//
//==========================
#ifndef _TITLE_H_
#define _TITLE_H_

//include
#include "scene.h"

//タイトルクラスの定義
class CTitle:public CScene
{
public:

	//メンバ関数
	CTitle();//コンストラクタ
	~CTitle() override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
private:

	//メンバ関数
	void Bg();//背景
};

#endif 