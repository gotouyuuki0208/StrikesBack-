//==========================
// 
// ����̈ʒu�\��[weaponpoint.h]
// Author Yuki Goto
//
//==========================
#ifndef _WEAPONPOINT_H_
#define _WEAPONPOINT_H_

//include
#include "billboard.h"

//�N���X�̒�`
class CWeaponPoint :public CBillBoard
{
public:
	//�萔
	static const int PRIORITY;//�`�揇
	static const float MOVE;//�ړ���
	static const float DISTANCE;//�ړ����鋗��

	//�����o�֐�
	CWeaponPoint(int nPriority = PRIORITY);//�R���X�g���N�^
	~CWeaponPoint() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CWeaponPoint* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//�I�u�W�F�N�g����
private:
	//�����o�֐�
	void Move();//�ړ�����

	//�����o�ϐ�
	int m_nTexIdx;//�e�N�X�`���̔ԍ�
	bool m_MoveDirection;//�ړ������؂�ւ�����
	float m_FirstPos;//�ŏ��̈ʒu
};
#endif