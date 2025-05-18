//==========================
// 
// フェード処理[fade.h]
// Author Yuki Goto
//
//==========================
#ifndef _FADE_H_
#define _FADE_H_

//include
#include"object2D.h"
#include"scene.h"

//フェードクラスの定義
class CFade :public CObject2D
{
public:
	//フェードの状態
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
	CFade(int priority= PRIORITY);//コンストラクタ
	~CFade() override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
	void SetFade(CScene::MODE modenext);//フェードの設定処理
	FADE GetFade();//フェードの状態取得
	static CFade* Create();//生成
	void InGameFade();//ゲーム内でのフェード
	float GetTransparency();//透明度の取得

private:
	FADE m_fade;//フェードの状態
	CScene::MODE g_modenext;//次のシーン
	float m_Transparency;//色の透明度
	bool m_InGame;//ゲーム中か判定
};

#endif 