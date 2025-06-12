//==========================
// 
// 片手武器[smallweapon.h]
// Author Yuki Goto
//
//==========================
#ifndef _SMALLWEAPON_H_
#define _SMALLWEAPON_H_

//include
#include "weapon.h"
#include"trajectory.h"

//クラスの定義
class CSmallWeapon :public CWeapon
{
public:

	enum class SMALLWEAPON
	{
		NONE = 0,
		BAT,//バット
		PIPE,//パイプ
		SYOKAKI,//消火器
	};

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CSmallWeapon(int nPriority = PRIORITY);//コンストラクタ
	~CSmallWeapon() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CSmallWeapon* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, const char ModelName[256]);//オブジェクト生成
	void SetSmallWeapon(SMALLWEAPON type);//片手武器の種類を設定
	SMALLWEAPON GetSmallWeapon();//片手武器の種類を取得
private:

	SMALLWEAPON m_SmallWeapontype;//片手武器の種類を設定
};
#endif