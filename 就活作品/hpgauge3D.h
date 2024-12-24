//==========================
// 
// ビルボードのHPゲージ[hpgauge3D.h]
// Author Yuki Goto
//
//==========================
#ifndef _HPGAUGE3D_H_
#define _HPGAUGE3D_H_

//include
#include "billboard.h"

//クラスの定義
class CHPGauge3D :public CBillBoard
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CHPGauge3D(int nPriority = PRIORITY);//コンストラクタ
	~CHPGauge3D() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CHPGauge3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int hp);//オブジェクト生成
	void SetHP(int hp);//hpを設定
	void EraseGauge();//表示しない
	void DrawGauge();//表示する
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
	bool m_Draw;//描画判定
};
#endif