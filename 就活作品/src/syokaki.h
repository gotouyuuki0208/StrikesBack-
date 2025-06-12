//==========================
// 
// バット[bat.h]
// Author Yuki Goto
//
//==========================
#ifndef _syokaki_H_
#define _syokaki_H_

//include
#include "smallweapon.h"

//クラスの定義
class CSyokaki :public CSmallWeapon
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CSyokaki(int nPriority = PRIORITY);//コンストラクタ
	~CSyokaki() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CSyokaki* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//オブジェクト生成
private:
};
#endif