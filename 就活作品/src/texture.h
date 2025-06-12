//==========================
// 
// テクスチャ管理[texture.h]
// Author Yuki Goto
//
//==========================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//テクスチャクラスの定義
class CTexture
{
public:
	//定数
	static const int NUM_TEX = 100;//テクスチャの最大数

	//メンバ関数
	CTexture();//コンストラクタ
	~CTexture();//デストラクタ
	void UnLoad();//テクスチャのアンロード
	int Regist(const char* pTextureName);//テクスチャ登録
	LPDIRECT3DTEXTURE9 GetAdress(int nIdx);//テクスチャ取得
private:

	//メンバ変数
	LPDIRECT3DTEXTURE9 m_apTexture[NUM_TEX];//テクスチャへのポインタ
	string m_aTextureName[NUM_TEX];//作成済みのテクスチャ名保管データ配列
	int m_numAll;//テクスチャの総数
};

#endif