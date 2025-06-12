//==========================
// 
// ガードエフェクト処理[guardeffect.h]
// Author Yuki Goto
//
//==========================
#ifndef _GUARDEFFECT_H_
#define _GUARDEFFECT_H_

//include
#include"object3D.h"

//プレイヤークラスの定義
class CGuardEffect :public CObject3D
{
public:
	//定数
	static const int PRIORITY;//描画順
	static const float SUB_COL;//色の減らす数値

	//メンバ関数
	CGuardEffect(int nPriority = PRIORITY);//コンストラクタ
	~CGuardEffect() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CGuardEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);//生成

private:
	//メンバ関数
	void ChangeCol();//色の変更

	//メンバ変数
	int m_nTexIdx;//テクスチャID
	int m_nLife;//寿命
};
#endif 
