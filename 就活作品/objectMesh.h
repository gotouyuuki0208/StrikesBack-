//==========================
// 
// メッシュポリゴンの描画処理[objectmesh.h]
// Author Yuki Goto
//
//==========================
#ifndef _OBJECTEMSH_H_
#define _OBJECTEMSH_H_

//include
#include "objectgame.h"

//クラスの定義
class CObjectMesh :public CObjectgame
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CObjectMesh(int nPriority = PRIORITY);//コンストラクタ
	~CObjectMesh() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CObjectMesh* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int Width, int Vertical);//モデル生成
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);//テクスチャ割り当て
	void SetVerticalDiv(int vertical);//縦の分割数を設定
	int GetVerticalDiv();//縦の分割数を取得
	void SetWidthDiv(int width);//横の分割数を設定
	int GetWidthDiv();//横の分割数を取得
	void SetSize(D3DXVECTOR3 size);//サイズを設定
	D3DXVECTOR3& GetSize();//サイズを取得
	LPDIRECT3DVERTEXBUFFER9& GetVtxBuff();//頂点バッファを取得
	int GetNumVtx();//頂点数の取得
private:

	//メンバ関数
	void SetInit();//頂点バッファの初期設定
	void SeIdx();//インデックスバッファの設定

	//メンバ変数
	LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;//インデックスバッファへのポインタ
	D3DXVECTOR3 m_size;//ポリゴンのサイズ
	int m_WidthDiv;//横の分割数
	int m_VerticalDiv;//縦の分割数
	int m_NumVtx;//頂点数
	int m_NumIdx;//インデックス数
	int m_nTexIdx;
};
#endif 