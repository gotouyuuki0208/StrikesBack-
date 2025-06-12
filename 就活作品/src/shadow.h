//==========================
// 
// 影[shadow.h]
// Author Yuki Goto
//
//==========================
#ifndef _SHADOW_H_
#define _SHADOW_H_

//include
#include "object3D.h"

//クラスの定義
class CShadow :public CObject3D
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CShadow(int nPriority = PRIORITY);//コンストラクタ
	~CShadow() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CShadow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//オブジェクト生成
	void Move(D3DXVECTOR3 pos);//移動処理
private:
	int m_nTexIdx;//テクスチャの番号
};
#endif