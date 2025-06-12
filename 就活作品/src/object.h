//==========================
// 
// オブジェクト管理[object.h]
// Author Yuki Goto
//
//==========================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//オブジェクトクラスの定義
class CObject
{
public:

	//オブジェクトのタイプ
	enum class TYPE
	{
		NONE = 0,//無し
		FADE,	 //フェード
		ENEMY,	 //敵
		PLAYER,	 //プレイヤー
		FILD,	 //フィールド
		WEAPON,	 //武器
		BLOCK,	 //ブロック
		BUILDING,//建物
		JIHANKI, //自販機
		DELIVERY,//配達員
		MAX,
	};

	//定数
	static const int PRIORITY = 6;		//描画順
	static const int MAX_OBJECT = 2000;	//オブジェクトの最大数

	//メンバ関数
	
	CObject(int nPriority = PRIORITY);					//描画優先設定
	virtual~CObject();									//デストラクタ
	virtual HRESULT Init() = 0;							//初期化処理
	virtual void Uninit() = 0;							//終了処理
	virtual void Update() = 0;							//更新処理
	virtual void Draw() = 0;							//描画処理
	static void ReleaseAll();							//全オブジェクト解放
	static void UpdateAll();							//全オブジェクト更新
	static void DrawAll();								//全オブジェクト描画
	static CObject* GetObj(CObject*Object,int priority);//オブジェクト取得
	static void ReleseDeath();							//死亡フラグが立ってるオブジェクト削除
	TYPE GetType();										//タイプ取得
	void SetType(TYPE type);							//タイプ設定
	CObject* GetNextObj();								//次のオブジェクトを取得
	CObject* GetPrevObj();								//前のオブジェクトを取得
protected:

	//メンバ関数
	void Release();	//自分自身の解放	

private:

	//メンバ関数
	void SwitchDeath();	 //死亡フラグの切り替え
	void DisengageList();//リストから切り離す

	//メンバ変数
	static CObject* m_apObject[PRIORITY][MAX_OBJECT];//オブジェクト管理
	static CObject* m_pTop[PRIORITY];				 //先頭のオブジェクト
	static CObject* m_pCur[PRIORITY];				 //最後尾のポインタ
	CObject* m_pPrev;								 //前のオブジェクトのポインタ
	CObject* m_pNext;								 //次のオブジェクトのポインタ
	bool m_bDeath;									 //死亡判定フラグ
	static int m_nNumAll;							 //オブジェクト総数
	int m_nID;										 //自分自身のID
	TYPE m_Type;									 //オブジェクトタイプ
	int m_nPriority;								 //描画優先度
};

#endif