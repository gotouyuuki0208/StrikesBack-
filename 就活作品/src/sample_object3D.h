//==========================
// 
// 3Dポリゴン描画サンプル[sample_object3D.h]
// Author Yuki Goto
//
//==========================
#ifndef _SAMPLE_OBJECT3D_H_
#define _SAMPLE_OBJECT3D_H_

//include
#include "object3D.h"

//クラスの定義
class CSampleObject3D :public CObject3D
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CSampleObject3D(int nPriority = PRIORITY);//コンストラクタ
	~CSampleObject3D() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CSampleObject3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//オブジェクト生成
private:
	int m_nTexIdx;//テクスチャの番号
};
#endif