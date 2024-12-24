//==========================
// 
// �u���b�N[block.h]
// Author Yuki Goto
//
//==========================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//include
#include "objectX.h"

//�N���X�̒�`
class CBlock :public CObjectX
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CBlock(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBlock() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBlock* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
private:

	//�����o�ϐ�
	int m_nModelIdx;//�e�N�X�`���̔ԍ�
};
#endif