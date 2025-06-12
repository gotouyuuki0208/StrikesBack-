//==========================
// 
// �̈�ٓ���[gym_entrance.h]
// Author Yuki Goto
//
//==========================
#ifndef _GYM_ENTRANCE_H_
#define _GYM_ENTRANCE_H_

//include
#include "building.h"

//�N���X�̒�`
class CGymentrance :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CGymentrance(int nPriority = PRIORITY);//�R���X�g���N�^
	~CGymentrance() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CGymentrance* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif