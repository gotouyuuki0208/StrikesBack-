//==========================
// 
// 軌跡の描画処理[trajectory.h]
// Author Yuki Goto
//
//==========================
#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

//include
#include "objectMesh.h"

//クラスの定義
class CTrajectory :public CObjectMesh
{
public:
	//定数
	static const int PRIORITY;//描画順

	//メンバ関数
	CTrajectory(int nPriority = PRIORITY);//コンストラクタ
	~CTrajectory() override;//デストラクタ
	HRESULT Init() override;//初期化処理
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理
	static CTrajectory* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int Width, int Vertical);//モデル生成
	void SetNewPos(D3DXVECTOR3 pos);//新しい頂点座標の位置を設定
private:

	//メンバ関数
	void SetVertexPos();//頂点座標の設定
	void InitVtxPos();//頂点情報の初期設定

	//メンバ変数
	D3DXVECTOR3 m_NewPos;//新しい頂点座標の位置
	int m_nTexIdx;//テクスチャの番号
};
#endif 