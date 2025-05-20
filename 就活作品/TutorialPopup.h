//==========================
// 
// チュートリアルのポップアップ表示[TutorialPopup.h]
// Author Yuki Goto
//
//==========================
#ifndef _TUTORIALPOPUP_H_
#define _TUTORIALPOPUP_H_

//include
#include "object2D.h"

//クラスの定義
class CTutorialPopup :public CObject2D
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CTutorialPopup(int nPriority = PRIORITY);//コンストラクタ
	~CTutorialPopup() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CTutorialPopup* Create(const char texname[256]);//オブジェクト生成
	void KeyInput();//キー入力
private:

	//メンバ関数
	void MakeOpaque();//不透明にする
	void MakeTransparent();//透明にする
	

	//メンバ変数
	int m_nTexIdx;//テクスチャの番号
	float m_transparency;//透明度
	bool m_input;//入力判定
};
#endif