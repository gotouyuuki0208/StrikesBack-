//==========================
// 
// �����蔻��[collision.h]
// Author Yuki Goto
//
//==========================
#ifndef _COLLISION_H_
#define _COLLISION_H_

//�N���X��`
class CCollision
{
public:
	CCollision();//�R���X�g���N�^
	~CCollision();//�f�X�g���N�^
	bool Sphere(D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, float myradius, float partnerradius);//���̔���
	bool RectangleLeft(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin);//��`�̍�
	bool RectangleRight(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin);//��`�̉E
	bool RectangletBack(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin);//��`�̉�
	bool RectangleFront(D3DXVECTOR3 posold, D3DXVECTOR3 mypos, D3DXVECTOR3 partnerpos, D3DXVECTOR3 myvtxmax, D3DXVECTOR3 myvtxmin, D3DXVECTOR3  partnervtxmax, D3DXVECTOR3  partnervtxmin);//��`�̐���
};

#endif