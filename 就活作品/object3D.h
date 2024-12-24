//==========================
// 
// 3Dポリゴンの描画処理[object3D.h]
// Author Yuki Goto
//
//==========================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//include
#include "objectgame.h"

//オブジェクト3Dクラスの定義
class CObject3D :public CObjectgame
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CObject3D(int nPriority = PRIORITY);//コンストラクタ
	~CObject3D() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CObject3D* Create();//オブジェクト3D生成
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);//テクスチャ割り当て
	void SetSize(D3DXVECTOR3 size);//大きさ設定
	D3DXVECTOR3& GetSize();//大きさ取得
	void SetCor(D3DXCOLOR cor);//色の設定
private:

	//メンバ変数
	LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//頂点バッファへのポインタ
	D3DXVECTOR3 m_size;//大きさ
	D3DXMATRIX m_mtxWorld;//ワールドマトリックス
	D3DXCOLOR m_cor;//色
};

#endif 
