//==========================
// 
// ビルボード描画サンプル[sample_billboard.h]
// Author Yuki Goto
//
//==========================
#ifndef _SAMPLE_BILLBOARD_H_
#define _SAMPLE_BILLBOARD_H_

//include
#include "billboard.h"

//クラスの定義
class CSampleBillBoard :public CBillBoard
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CSampleBillBoard(int nPriority = PRIORITY);//コンストラクタ
	~CSampleBillBoard() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CSampleBillBoard* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//オブジェクト生成
private:
	int m_nTexIdx;//テクスチャの番号
};
#endif