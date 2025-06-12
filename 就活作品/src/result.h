//==========================
// 
// リザルト画面の処理[result.h]
// Author Yuki Goto
//
//==========================
#ifndef _RESULT_H_
#define _RESULT_H_

//include
#include "scene.h"

//クラスの定義
class CResult :public CScene
{
public:

	//メンバ関数
	CResult();//コンストラクタ
	~CResult() override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
private:
	void Bg();//背景
};

#endif 