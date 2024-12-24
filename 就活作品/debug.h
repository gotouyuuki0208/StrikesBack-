//==========================
// 
// デバッグ情報[debug.h]
// Author Yuki Goto
//
//==========================
#ifndef _DEBUG_H_
#define _DEBUG_H_

//クラスの定義
class CDebug
{
public:
	//メンバ関数
	CDebug();//コンストラクタ
	~CDebug();//デストラクタ
	void Reset();//デバッグ情報をリセット
	bool GetPlayerTest();//プレイヤーのテスト
	void StartPlayerTest();//プレイヤーのテスト開始
	void FinishPlayerTest();//プレイヤーのテスト終了
	bool GetBossTest();//ボスのテスト
	void StartBossTest();//ボスのテスト開始
	void FinishBossTest();//ボスのテスト終了
	bool GetBattleTest();//戦闘のテスト
	void StartBattleTest();//戦闘のテスト開始
	void FinishBattleTest();//戦闘のテスト終了

	bool GetEdit();//配置ツール
	void StartEdit();//配置ツールの使用開始
	void FinishEdit();//配置ツールの使用終了
private:
	//メンバ変数
	bool m_TestPlayer;//プレイヤーのテスト
	bool m_TestBoss;//ボスのテスト
	bool m_TestBattle;//戦闘のデバッグ
	bool m_UseEdit;//配置ツール使用判定
};
#endif