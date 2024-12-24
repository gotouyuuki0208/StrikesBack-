//==========================
// 
// ゲームオブジェクト[objectgame.h]
// Author Yuki Goto
//
//==========================
#ifndef _OBJECTGAME_H_
#define _OBJECTGAME_H_

//ibclude
#include "object.h"

//オブジェクトクラスの定義
class CObjectgame:public CObject
{
public:

	//定数
	static const int PRIORITY = 5;

	//メンバ関数
	CObjectgame(int nPriority = PRIORITY);//描画優先設定
	~CObjectgame()override;//デストラクタ
	HRESULT Init()override;//初期化処理
	void Uninit()override;//終了処理
	void Update()override;//更新処理
	void Draw()override;//描画処理
	D3DXVECTOR3& GetPos();//位置取得
	void SetPos(D3DXVECTOR3 pos);//位置設定
	D3DXVECTOR3& GetRot();//向き取得
	void SetRot(D3DXVECTOR3 rot);//向き設定
	D3DXVECTOR3& GetRotMove();//向き取得
	void SetRotMove(D3DXVECTOR3 rot);//向き設定
	D3DXVECTOR3& GetPosOld();//昔の位置取得
	void SetPosOld(D3DXVECTOR3 posord);//昔の位置設定
	D3DXVECTOR3& GetMove();//移動値取得
	void SetMove(D3DXVECTOR3 move);//移動値設定
	D3DXMATRIX& GetMtxWorld();//マトリックス取得
	void SetMtxWorld(D3DXMATRIX mtxWorld);//マトリックスの設定
	float GetRadius();//半径の取得
	void SetRadius(float radius);//半径の設定
	D3DXVECTOR3& GetScale();//拡大率の設定
	void SetScale(D3DXVECTOR3 scale);//拡大率の設定
	bool ColisionSphere(D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, float myradius, float partnerradius);//球の判定
	float RevisionRot(float objectiverot ,float currentrot,float Cur);//向きの補正
	float NormalizeAngle(float angle);//向きの正規化
	float VectorCalculation(float current, float purpose);//ベクトルの算出
private:
	//メンバ変数
	D3DXVECTOR3 m_pos;//位置
	D3DXVECTOR3 m_posmove;//位置の移動量
	D3DXVECTOR3 m_rot;//向き
	D3DXVECTOR3 m_posold;//前の位置
	D3DXMATRIX m_mtxWorld;//ワールドマトリックス
	float m_radius;//半径
	D3DXVECTOR3 m_scale;//拡大率
	D3DXVECTOR3 m_rotmove;//向きの移動量
};

#endif
