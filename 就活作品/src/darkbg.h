//==========================
// 
// [darkbg.h]
// Author Yuki Goto
//
//==========================
#ifndef _DARKBG_H_
#define _DARKBG_H_

//include
#include"object2D.h"

//クラスの定義
class CDarkBg :public CObject2D
{
public:
	
	enum class FADE
	{
		FADE_NONE = 0,//何もしていない状態
		FADE_IN,//フェードイン状態
		FADE_OUT,//フェードアウト状態
		FADE_MAX
	};

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CDarkBg(int priority = PRIORITY);//コンストラクタ
	~CDarkBg() override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
	void SetFade();//フェードの設定処理
	FADE GetFade();//フェードの状態取得
	static CDarkBg* Create();//生成
	float GetCol();//透明度の取得

private:

	//メンバ変数
	FADE m_fade;//フェードの状態
	float m_cor;//色の透明度
};

#endif 