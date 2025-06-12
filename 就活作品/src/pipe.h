//==========================
// 
// 鉄パイプ[pipe.h]
// Author Yuki Goto
//
//==========================
#ifndef _PIPE_H_
#define _PIPE_H_

//include
#include "smallweapon.h"

//クラスの定義
class CPipe :public CSmallWeapon
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CPipe(int nPriority = PRIORITY);//コンストラクタ
	~CPipe() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CPipe* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//オブジェクト生成
private:
};
#endif