//==========================
// 
// アウトゲームのキャラクター[outgamecharactar.h]
// Author Yuki Goto
//
//==========================
#ifndef _OUTGAMECHARACTAR_H_
#define _OUTGAMECHARACTAR_H_

//include
#include "motionmodel.h"

//クラスの定義
class COutGameChara :public CMotionModel
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	COutGameChara(int nPriority = PRIORITY);//コンストラクタ
	~COutGameChara() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static COutGameChara* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
private:
};
#endif