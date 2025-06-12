//==========================
// 
// ウェーブで消える壁[wavewall.h]
// Author Yuki Goto
//
//==========================
#ifndef _WAVEWALL_H_
#define _WAVEWALL_H_

//include
#include "building.h"

//クラスの定義
class CWaveWall :public CBuilding
{
public:

	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CWaveWall(int nPriority = PRIORITY);//コンストラクタ
	~CWaveWall() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CWaveWall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot,int wave);//オブジェクト生成
	int GetMyWave();//自分のウェーブを取得
private:

	//メンバ変数
	int m_MyWave;//自分のウェーブ
};
#endif