//==========================
// 
// �z�B��[deliveryperson.h]
// Author Yuki Goto
//
//==========================
#ifndef _DELIVERYPERSON_H_
#define _DELIVERYPERSON_H_

//include
#include "motionmodel.h"

//�N���X�̒�`
class CDeliveryPerson :public CMotionModel
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CDeliveryPerson(int nPriority = PRIORITY);//�R���X�g���N�^
	~CDeliveryPerson() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CDeliveryPerson* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
	void Damage(int Damage);//�_���[�W����
	void Movable();//�ړ��\��Ԃɂ���
	void Immovable();//�ړ��s�\��Ԃɂ���

private:
	//�����o�֐�
	void move();//�ړ�����

	//�����o�ϐ�
	int m_life;//����
	bool m_Move;//�ړ��̔���(true:�ړ��\ false:��~)
};
#endif