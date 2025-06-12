//==========================
// 
// ���\�����w�������ʒu[arrowpoint.h]
// Author Yuki Goto
//
//==========================
#ifndef _ARROWPOINT_H_
#define _ARROWPOINT_H_

//include
#include "fild.h"

//�O���錾
class CPlayer;

//�N���X�̒�`
class CArrowPoint :public CFild
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CArrowPoint(int nPriority = PRIORITY);//�R���X�g���N�^
	~CArrowPoint() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CArrowPoint* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//�I�u�W�F�N�g����
private:
	//�����o�֐�
	void GetPlayerinfo();//�v���C���[�̏����擾
	void CollisionPlayer();//�v���C���[���������Ă邩����

	//�����o�ϐ�
	CPlayer* m_player;//�v���C���[�̏��
};
#endif