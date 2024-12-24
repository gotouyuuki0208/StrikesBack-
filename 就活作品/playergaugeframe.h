//==========================
// 
// プレイヤーHPゲージの枠[playergaugeframe.h]
// Author Yuki Goto
//
//==========================
#ifndef _PLAYERGAUGEFRAME_H_
#define _PLAYERGAUGEFRAME_H_

//include
#include "object2D.h"

//クラスの定義
class CPlayerHPGaugeFrame :public CObject2D
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CPlayerHPGaugeFrame(int nPriority = PRIORITY);//コンストラクタ
	~CPlayerHPGaugeFrame() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CPlayerHPGaugeFrame* Create(D3DXVECTOR3 pos, float vertical, float width);//オブジェクト生成
	void SetVtx();//頂点情報の設定
private:
	//メンバ変数
	int m_nTexIdx;//テクスチャの番号
};
#endif