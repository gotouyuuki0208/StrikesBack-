//==========================
// 
// モデル管理[model.h]
// Author Yuki Goto
//
//==========================
#ifndef _MODEL_H_
#define _MODEL_H_

//モデルクラスの定義
class CModel
{
public:
	//メンバ関数
	CModel();//コンストラクタ
	~CModel();//デストラクタ
	void UnLoad();//テクスチャのアンロード
	int Regist(const char* pModelName);//モデル登録
	LPD3DXMESH GetMeshAdress(int nIdx);//モデルのメッシュ取得
	LPD3DXBUFFER GetBuffMatAdress(int nIdx);//モデルのマテリアル取得
	DWORD GetNumMatAdress(int nIdx);//モデルのマテリアルの数取得
	D3DCOLORVALUE GetDiffuse(int nIdx, int CorNum);//モデルの色
	LPDIRECT3DTEXTURE9 * GetTexIdx(int nIdx);//モデルのテクスチャ番号取得
private:

	//定数
	static const int NUM_MODEL = 150;//モデルの種類数

	//メンバ変数
	LPD3DXMESH m_pMesh[NUM_MODEL];//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER m_pBuffMat[NUM_MODEL];//マテリアルへのポインタ
	DWORD m_dwNumMat[NUM_MODEL];//マテリアルの数
	D3DCOLORVALUE m_Diffuse[NUM_MODEL][NUM_MODEL];//色の保存用
	LPDIRECT3DTEXTURE9 m_apTexture[NUM_MODEL][NUM_MODEL];
	int m_TexIdx[NUM_MODEL];//モデルのテクスチャ番号
	string m_aModelName[NUM_MODEL];//作成済みのテクスチャ名保管データ配列
	int m_numAll;//テクスチャの総数
};
#endif