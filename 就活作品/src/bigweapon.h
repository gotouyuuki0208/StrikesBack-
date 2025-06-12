//==========================
// 
// 大きい武器[bigweapon.h]
// Author Yuki Goto
//
//==========================
#ifndef _BIGWEAPON_H_
#define _BIGWEAPON_H_

//include
#include "weapon.h"

//クラスの定義
class CBigWeapon :public CWeapon
{
public:
	enum class BIGWEAPON
	{
		NONE=0,
		BICYCLE,//自転車
		CONE,
	};

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CBigWeapon(int nPriority = PRIORITY);//コンストラクタ
	~CBigWeapon() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CBigWeapon* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,const char ModelName[256]);//オブジェクト生成
	void SetBigWeapon(BIGWEAPON type);//両手武器の種類を設定
	BIGWEAPON GetBigWeapon();//両tr武器の種類を取得
private:
	BIGWEAPON m_BigWeapontype;//両手武器の種類
};
#endif