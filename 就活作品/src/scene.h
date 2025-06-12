//==========================
// 
// シーン管理[scene.h]
// Author Yuki Goto
//
//==========================
#ifndef _SCENE_H_
#define _SCENE_H_

//シーンクラスの定義
class CScene
{
public:
	//画面の種類
	enum class MODE
	{
		TITLE = 0,//タイトル
		GAME,//ゲーム
		RESULT,//リザルト
		MAX,
	};

	//メンバ関数
	CScene();//コンストラクタ
	virtual ~CScene();//デストラクタ
	virtual HRESULT Init();//初期化処理
	virtual void Uninit();//終了処理
	virtual void Update();//更新処理
	virtual void Draw();//描画処理
	static CScene* Create(MODE mode);//生成
	MODE GetScene();//現在のシーンを取得
private:
	MODE m_mode;//現在のモード
};

#endif 