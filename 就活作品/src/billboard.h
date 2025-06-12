//==========================
// 
// ビルボード処理[billboard.h]
// Author Yuki Goto
//
//==========================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//include
#include"object3D.h"

//ビルボードクラスの定義
class CBillBoard :public CObjectgame
{
public:
	//定数
	static const int PRIORITY;									//描画順
	static const int ANIM_FRAME;								//アニメーションのフレーム数

	//メンバ関数
	CBillBoard(int nPriority = PRIORITY);						//コンストラクタ
	~CBillBoard() override;										//デストラクタ
	HRESULT Init() override;									//初期化処理
	void Uninit() override;										//終了処理
	void Update() override;										//更新処理
	void Draw() override;										//描画処理
	static CBillBoard* Create(D3DXVECTOR3 pos);					//生成処理
	void SetSize(D3DXVECTOR3 size);								//大きさ設定
	D3DXVECTOR3& GetSize();										//大きさを取得
	void SetCol(D3DXCOLOR col);									//色の設定
	D3DXCOLOR& GetCol();										//色の取得
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);					//テクスチャ割り当て
	void SetTexSize(float vertical, float width, float TexPos);	//テクスチャのサイズ設定
	void Animetion(float vertical, int width);					//アニメーション
	LPDIRECT3DVERTEXBUFFER9& GetVtxBuff();						//頂点バッファの取得
	LPDIRECT3DTEXTURE9& GetTex();								//テクスチャの取得
	void TexMove();												//テクスチャを動かす
private:

	//メンバ変数
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	D3DXCOLOR m_col;					//色
	D3DXVECTOR3 m_size;					//大きさ
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
	int m_nCntAnim;						//アニメーションカウンター
	int m_nPatternAnim;					//テクスチャアニメーションの分割数
	float m_PosTexV;					//テクスチャの縦の位置
};

#endif