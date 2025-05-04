//==========================
// 
// 当たり判定[collision.h]
// Author Yuki Goto
//
//==========================
#ifndef _COLLISION_H_
#define _COLLISION_H_

//クラス定義
class CCollision
{
public:
	CCollision();//コンストラクタ
	~CCollision();//デストラクタ
	bool Sphere(D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, float myradius, float partnerradius);//球の判定
	bool RectangleLeft(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin);//矩形の左
	bool RectangleRight(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin);//矩形の右
	bool RectangletBack(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin);//矩形の奥
	bool RectangleFront(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin);//矩形の正面
};

#endif