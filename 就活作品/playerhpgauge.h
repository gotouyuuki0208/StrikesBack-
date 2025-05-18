//==========================
// 
// HPゲージ[playerhpgauge.h]
// Author Yuki Goto
//
//==========================
#ifndef _PLAYERHPGAUGE_H_
#define _PLAYERHPGAUGE_H_

//include
#include "object2D.h"

//クラスの定義
class CPlayerHPGauge :public CObject2D
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CPlayerHPGauge(int nPriority = PRIORITY);//コンストラクタ
	~CPlayerHPGauge() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CPlayerHPGauge* Create(D3DXVECTOR3 pos, float vertical, float width);//オブジェクト生成
	void SetHP(int hp);//hpを設定
private:

	//メンバ関数
	void SetVtx();//頂点情報の設定
	void SwitchCor();//色の変更
	void SetLength();//ゲージの長さを設定

	//メンバ変数
	int m_nTexIdx;//テクスチャの番号
	int m_HP;//HPの数値
	int m_MaxHP;//最大HPの数値
	float m_Targetlength;//目的の長さ
	float m_length;//長さ
	float m_Ratio;//HPの割合
};
#endif