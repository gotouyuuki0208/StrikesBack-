//==========================
// 
// 地面[fild.h]
// Author Yuki Goto
//
//==========================
#ifndef _FILD_H_
#define _FILD_H_

//include
#include "object3D.h"

//クラスの定義
class CFild :public CObject3D
{
public:

	enum class FILDTYPE
	{
		NONE=0,
		FILD,//地面
		CURB,//縁石
		ENEMYMOVEPOINT,//敵の移動地点
		STAGECHANGE,
		GYMFILD,
		ARROWPOINT,
	};

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CFild(int nPriority = PRIORITY);//コンストラクタ
	~CFild() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CFild* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);//オブジェクト生成
	FILDTYPE GetFildType();//地面の種類を取得
	void SetFild(FILDTYPE type);//地面の種類を設定
	void SetTexIdx(int Idx);//テクスチャ番号を設定
	int GetTexIdx();//テクスチャ番号を取得

private:

	//メンバ変数
	int m_nTexIdx;//テクスチャの番号
	FILDTYPE m_FildType;//地面の種類
};
#endif