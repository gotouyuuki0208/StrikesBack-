//==========================
// 
// モデルの描画処理[objectX.h]
// Author Yuki Goto
//
//==========================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//include
#include "objectgame.h"

//オブジェクトXクラスの定義
class CObjectX :public CObjectgame
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CObjectX(int nPriority = PRIORITY);//コンストラクタ
	~CObjectX() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CObjectX* Create();//モデル生成
	void BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPDIRECT3DTEXTURE9 * pTexture);//モデル割り当て
	void SetSize();//モデルのサイズを設定
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);//テクスチャ割り当て
	D3DXVECTOR3& GetVtxMin();//頂点の最小の場所を取得
	D3DXVECTOR3& GetVtxMax();//頂点の最大の場所を取得
	D3DXVECTOR3& GetSize();//サイズ取得
	LPD3DXMESH& GetMesh();//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER& GetBuffMat();//マテリアルへのポインタ
	DWORD& GetNumMat();//マテリアルの数
	void SetTransparent(float cor);//透明度を設定
	float GetTransparent();//透明度を取得

private:
	//メンバ変数
	LPD3DXMESH m_pMesh;//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER m_pBuffMat;//マテリアルへのポインタ
	DWORD m_dwNumMat;//マテリアルの数
	LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャへのポインタ
	D3DXVECTOR3 m_Size;//モデルの大きさ
	D3DXVECTOR3 m_vtxMin;//頂点の最小
	D3DXVECTOR3 m_vtxMax;//頂点の最大
	LPDIRECT3DTEXTURE9* m_pTexture2;//モデルのテクスチャのポインタ
	float m_Transparent;//透明度
};
#endif 