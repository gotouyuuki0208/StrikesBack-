//==========================
// 
// 2Dポリゴン描画サンプル[sample_object2D.h]
// Author Yuki Goto
//
//==========================
#ifndef _SAMPLE_OBJECT2D_H_
#define _SAMPLE_OBJECT2D_H_

//include
#include "object2D.h"

//クラスの定義
class CSampleObject2D :public CObject2D
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CSampleObject2D(int nPriority = PRIORITY);//コンストラクタ
	~CSampleObject2D() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CSampleObject2D* Create(D3DXVECTOR3 pos, float vertical, float width);//オブジェクト生成
private:
	int m_nTexIdx;//テクスチャの番号
};
#endif