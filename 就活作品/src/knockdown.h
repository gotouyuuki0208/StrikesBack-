//==========================
// 
// タイトル説明[TitleStart.h]
// Author Yuki Goto
//
//==========================
#ifndef _KNOCKDOWN_H_
#define _KNOCKDOWN_H_

//include
#include "object2D.h"

//クラスの定義
class CKnockDown :public CObject2D
{
public:
	//定数
	static const int PRIORITY;

	//メンバ関数
	CKnockDown(int nPriority = PRIORITY);//コンストラクタ
	~CKnockDown()override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
	static CKnockDown* Create(D3DXVECTOR3 pos);//オブジェクト2D生成
private:
	static int m_nTexIdx;//テクスチャID
};

#endif 
