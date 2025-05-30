//==========================
// 
// HUDの管理[hudmanager.h]
// Author Yuki Goto
//
//==========================
#ifndef _HUDMANAGER_H_
#define _HUDMANAGER_H_

//前方宣言
class CPlayerHPGauge;//雑魚敵のHPゲージクラス
class CBossHPGauge;//ボスのHPゲージクラス

//クラスの定義
class CHudManager
{
public:

	//メンバ関数
	CHudManager();//コンストラクタ
	~CHudManager();//デストラクタ
	void ChangePlayerHP(int hp);//プレイヤーHPが変更された
	void ChangeBossHP(int hp);//ボスのHPが変更された
	void CreatePlayerHPGauge();//プレイヤーのゲージを生成
	void CreateBossHPGauge();//ボスのゲージを生成
	void Reset();//リセット
	void DisplayUI();//須佐説明のUI表示
private:

	//メンバ変数
	CPlayerHPGauge* m_pPlayerHPGauge;//プレイヤーのHPゲージの情報
	CBossHPGauge* m_pBossHPGauge;//ボスのHPゲージの情報
};

#endif