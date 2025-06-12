//==========================
// 
// ���\��[arrowUI.h]
// Author Yuki Goto
//
//==========================
#ifndef _ARROWUI_H_
#define _ARROWUI_H_

//include
#include "object3D.h"

//�O���錾
class CArrowPoint;

//�N���X�̒�`
class CArrowUI :public CObject3D
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CArrowUI(int nPriority = PRIORITY);//�R���X�g���N�^
	~CArrowUI() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CArrowUI* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//�I�u�W�F�N�g����
private:

	//�����o�֐�
	void JudgeDraw();//�`�悷�邩����
	void ChangeDirection();//�����̕ύX

	//�����o�ϐ�
	int m_nTexIdx;//�e�N�X�`���̔ԍ�
	bool m_Draw;//�`�攻��
	CArrowPoint* m_ArrowPoint;
};
#endif