//==========================
// 
// ライト処理[light.h]
// Author Yuki Goto
//
//==========================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//マクロ定義
#define MAX_LIGHT (4)//ライトの数

//ライトクラスの定義
class CLight
{
public:
	//メンバ関数
	CLight();//コンストラクタ
	~CLight();//デストラクタ
	HRESULT Init();//初期化処理
	void Uninit();//終了処理
	void Update();//更新処理
private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];//ライト構造体
};

#endif