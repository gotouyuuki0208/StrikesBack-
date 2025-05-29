//==========================
// 
// 当たり判定[collision.cpp]
// Author Yuki Goto
//
//==========================

//inlude
#include"collision.h"

//==========================
//球の判定
//==========================
bool Collision::Sphere(D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, float myradius, float partnerradius)
{
	D3DXVECTOR3 DisPos = D3DXVECTOR3(mypos.x - partnerpos.x, mypos.y - partnerpos.y, mypos.z - partnerpos.z);
	float Distance = sqrtf((DisPos.x * DisPos.x) + (DisPos.y * DisPos.y) + (DisPos.z * DisPos.z));

	if (Distance < myradius + partnerradius)
	{
		return true;
	}

	return false;
}

//==========================
//矩形の左
//==========================
bool Collision::RectangleLeft(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin)
{
	if (posold.x + myvtxmax.x <= partnerpos.x + partnervtxmin.x
		&& mypos.x + myvtxmax.x > partnerpos.x + partnervtxmin.x
		&& mypos.z - myvtxmin.z < partnerpos.z + partnervtxmax.z
		&& mypos.z + myvtxmax.z > partnerpos.z + partnervtxmax.z)
	{
		return true;
	}

	return false;
}

//==========================
//矩形の右
//==========================
bool Collision::RectangleRight(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin)
{
	if (posold.x - myvtxmax.x >= partnerpos.x + partnervtxmax.x
		&& mypos.x - myvtxmax.x < partnerpos.x + partnervtxmax.x
		&& mypos.z - myvtxmin.z < partnerpos.z + partnervtxmax.z
		&& mypos.z + myvtxmax.z > partnerpos.z + partnervtxmin.z)
	{//右
		return true;
	}

	return false;
}

//==========================
//矩形の奥
//==========================
bool Collision::RectangletBack(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin)
{

	if (posold.z - myvtxmin.z >= partnerpos.z + partnervtxmax.z
		&& mypos.z - myvtxmin.z < partnerpos.z + partnervtxmax.z
		&& mypos.x - myvtxmin.x < partnerpos.x + partnervtxmax.x
		&& mypos.x + myvtxmax.x > partnerpos.x + partnervtxmin.x)
	{//奥
		return true;
	}

	return false;
}

//==========================
//矩形の正面
//==========================
bool Collision::RectangleFront(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin)
{
	if (posold.z + myvtxmax.z <= partnerpos.z + partnervtxmin.z
		&& mypos.z + myvtxmax.z > partnerpos.z + partnervtxmin.z
		&& mypos.x - myvtxmin.x < partnerpos.x + partnervtxmax.x
		&& mypos.x + myvtxmax.x > partnerpos.x + partnervtxmin.x)
	{//手前
		return true;
	}

	return false;

}