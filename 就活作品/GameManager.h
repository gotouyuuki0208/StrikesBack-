//==========================
// 
// ゲーム全体管理[GameManager.h]
// Author Yuki Goto
//
//==========================
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

//クラスの定義
class CGameManager
{
public:

	enum class GAME
	{
		NONE = 0,
		CLEAR,
		OVER,
	};
	

	//メンバ関数
	CGameManager();//コンストラクタ
	~CGameManager();//デストラクタ
	void SetGame(GAME game);
	GAME GetGame();
private:

	//メンバ変数
	GAME GameClear;//

};

#endif