//==========================
// 
// �r���{�[�h�`��T���v��[sample_billboard.h]
// Author Yuki Goto
//
//==========================
#ifndef _SAMPLE_BILLBOARD_H_
#define _SAMPLE_BILLBOARD_H_

//include
#include "billboard.h"

//�N���X�̒�`
class CSampleBillBoard :public CBillBoard
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CSampleBillBoard(int nPriority = PRIORITY);//�R���X�g���N�^
	~CSampleBillBoard() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CSampleBillBoard* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//�I�u�W�F�N�g����
private:
	int m_nTexIdx;//�e�N�X�`���̔ԍ�
};
#endif