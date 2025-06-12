//==========================
// 
// �{�X��J�n���̍��w�i����[directionbg.h]
// Author Yuki Goto
//
//==========================
#ifndef _DIRECTIONBG_H_
#define _DIRECTIONBG_H_

//include
#include "object2D.h"

//�N���X�̒�`
class CDirectionBg :public CObject2D
{
public:
	//�萔
	static const int PRIORITY;

	//�����o�֐�
	CDirectionBg(int nPriority = PRIORITY);//�R���X�g���N�^
	~CDirectionBg()override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
	static CDirectionBg* Create(D3DXVECTOR3 pos);//�I�u�W�F�N�g2D����
	void EnterScreen();//��ʂɓ���
	void ExitScreen();//��ʂ���o��
private:

	//�����o�ϐ�
	D3DXVECTOR3 m_FirstPos;//�ŏ��ɂ����ʒu
	int m_CountFlame;//�t���[�����J�E���g�p
	bool m_Delete;//��ʂɂł����������
};

#endif 
