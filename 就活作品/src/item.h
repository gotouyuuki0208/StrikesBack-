//==========================
// 
// �񕜃A�C�e��[item.h]
// Author Yuki Goto
//
//==========================
#ifndef _ITEM_H_
#define _ITEM_H_

//include
#include "objectX.h"

//�N���X�̒�`
class CItem :public CObjectX
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CItem(int nPriority = PRIORITY);//�R���X�g���N�^
	~CItem() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CItem* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
	int GetModelIdx();//���f���̔ԍ����擾
	void SetModelIdx(int Idx);//���f���̔ԍ���ݒ�

private:

	//�����o�֐�
	void ColisionPlayer();//�v���C���[�Ƃ̓����蔻��

	//�����o�ϐ�
	int m_nModelIdx;//���f���̔ԍ�
};
#endif