//==========================
// 
// ポリゴンの描画処理[object2D.h]
// Author Yuki Goto
//
//==========================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//include
#include "objectgame.h"

//オブジェクト2Dクラスの定義
class CObject2D:public CObjectgame
{
public:
	//定数
	static const int PRIORITY;			//描画順

	//メンバ関数
	CObject2D(int nPriority = PRIORITY);						//コンストラクタ
	~CObject2D() override;										//デストラクタ
	HRESULT Init() override;									//初期化処理
	void Uninit() override;										//終了処理
	void Update() override;										//更新処理
	void Draw() override;										//描画処理
	static CObject2D* Create();									//オブジェクト2D生成
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);					//テクスチャ割り当て
	void Animetion(float vertical, int width);					//アニメーション
	float GetLength();											//対角線の長さ取得
	void SetCol(D3DCOLOR col);									//色の設定
	D3DCOLOR GetCol();											//色の取得
	void SetSize(float vertical, float width);					//大きさ設定
	void SetTexSize(float vertical, float width ,float TexPos);	//テクスチャの大きさ設定
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff();						//頂点バッファのポインタを取得
	float GetWidth();											//横のサイズを取得
	float GetVertical();										//縦のサイズを取得
private:

	//メンバ変数
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	D3DCOLOR m_col;						//色
	float m_fLength;					//対角線の長さ
	float m_fAngle;						//対角線の角度
	float m_fVertical;					//縦のサイズ
	float m_fWidth;						//横のサイズ
	int m_nCntAnim;						//テクスチャアニメーションの切り替え
	int m_nPatternAnim;					//テクスチャアニメーションの分割数
};

#endif 
