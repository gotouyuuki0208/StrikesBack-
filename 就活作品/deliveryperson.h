//==========================
// 
// 配達員[deliveryperson.h]
// Author Yuki Goto
//
//==========================
#ifndef _DELIVERYPERSON_H_
#define _DELIVERYPERSON_H_

//include
#include "motionmodel.h"

//クラスの定義
class CDeliveryPerson :public CMotionModel
{
public:

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CDeliveryPerson(int nPriority = PRIORITY);//コンストラクタ
	~CDeliveryPerson() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CDeliveryPerson* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//オブジェクト生成
	void Damage(int Damage);//ダメージ処理
	void Movable();//移動可能状態にする
	void Immovable();//移動不可能状態にする

private:
	//メンバ関数
	void move();//移動処理

	//メンバ変数
	int m_life;//寿命
	bool m_Move;//移動の判定(true:移動可能 false:停止)
};
#endif