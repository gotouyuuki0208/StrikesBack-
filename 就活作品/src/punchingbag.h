//==========================
// 
// サンドバッグ[punchingbag.h]
// Author Yuki Goto
//
//==========================
#ifndef _PUNCHINGBUG_H_
#define _PUNCHINGBUG_H_

//include
#include "objectX.h"

//クラスの定義
class CPunchingBag :public CObjectX
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CPunchingBag(int nPriority = PRIORITY);//コンストラクタ
	~CPunchingBag() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CPunchingBag* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
private:
	//メンバ変数
	int m_nModelIdx;//モデルの番号
};
#endif