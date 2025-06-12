//==========================
// 
// チュートリアルの背景処理[tutorialbg.h]
// Author Yuki Goto
//
//==========================
#ifndef _TUTORIALBG_H_
#define _TUTORIALBG_H_

//include
#include "object2D.h"

//クラスの定義
class CTutorialBg:public CObject2D
{
public:
	//定数
	static const int PRIORITY;

	//メンバ関数
	CTutorialBg(int nPriority = PRIORITY);//コンストラクタ
	~CTutorialBg()override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
	static CTutorialBg* Create();//オブジェクト2D生成
private:
};

#endif 
