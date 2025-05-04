//==========================
// 
// �����蔻��[collision.cpp]
// Author Yuki Goto
//
//==========================

//inlude
#include"collision.h"

//==========================
//�R���X�g���N�^
//==========================
CCollision::CCollision()
{

}

//==========================
//�f�X�g���N�^
//==========================
CCollision::~CCollision()
{

}

//==========================
//���̔���
//==========================
bool CCollision::Sphere(D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, float myradius, float partnerradius)
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
//��`�̍�
//==========================
bool CCollision::RectangleLeft(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin)
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
//��`�̉E
//==========================
bool CCollision::RectangleRight(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin)
{
	if (posold.x - myvtxmax.x >= partnerpos.x + partnervtxmax.x
		&& mypos.x - myvtxmax.x < partnerpos.x + partnervtxmax.x
		&& mypos.z - myvtxmin.z < partnerpos.z + partnervtxmax.z
		&& mypos.z + myvtxmax.z > partnerpos.z + partnervtxmin.z)
	{//�E
		return true;
	}

	return false;
}

//==========================
//��`�̉�
//==========================
bool CCollision::RectangletBack(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin)
{

	if (posold.z - myvtxmin.z >= partnerpos.z + partnervtxmax.z
		&& mypos.z - myvtxmin.z < partnerpos.z + partnervtxmax.z
		&& mypos.x - myvtxmin.x < partnerpos.x + partnervtxmax.x
		&& mypos.x + myvtxmax.x > partnerpos.x + partnervtxmin.x)
	{//��
		return true;
	}

	return false;
}

//==========================
//��`�̐���
//==========================
bool CCollision::RectangleFront(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin)
{
	if (posold.z + myvtxmax.z <= partnerpos.z + partnervtxmin.z
		&& mypos.z + myvtxmax.z > partnerpos.z + partnervtxmin.z
		&& mypos.x - myvtxmin.x < partnerpos.x + partnervtxmax.x
		&& mypos.x + myvtxmax.x > partnerpos.x + partnervtxmin.x)
	{//��O
		return true;
	}

	return false;

}