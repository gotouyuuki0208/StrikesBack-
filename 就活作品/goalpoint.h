//==========================
// 
// �X�e�[�W�J�ڈʒu�̈ʒu�\��[goalpoint.h]
// Author Yuki Goto
//
//==========================
#ifndef _GOALPOINT_H_
#define _GOALPOINT_H_

//include
#include "billboard.h"

//�N���X�̒�`
class CGoalPoint :public CBillBoard
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CGoalPoint(int nPriority = PRIORITY);//�R���X�g���N�^
	~CGoalPoint() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CGoalPoint* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//�I�u�W�F�N�g����
private:
	int m_nTexIdx;//�e�N�X�`���̔ԍ�
};
#endif