//==========================
// 
// 操作説明UI[opeUI.h]
// Author Yuki Goto
//
//==========================
#ifndef _OPEUI_H_
#define _OPEUI_H_

//include
#include "object2D.h"

//クラスの定義
class COpeUI :public CObject2D
{
public:
	//定数
	static const int PRIORITY;

	//メンバ関数
	COpeUI(int nPriority = PRIORITY);//コンストラクタ
	~COpeUI()override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
	static COpeUI* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,const char texname[256]);//オブジェクト2D生成
private:
	int m_nTexIdx;//テクスチャID
};

#endif 
