//==========================
// 
// �x���`�v���X[benchpress.h]
// Author Yuki Goto
//
//==========================
#ifndef _BENCHPRESS_H_
#define _BENCHPRESS_H_

//include
#include "objectX.h"

//�N���X�̒�`
class CBenchPress :public CObjectX
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CBenchPress(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBenchPress() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBenchPress* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
private:
	//�����o�ϐ�
	int m_nModelIdx;//���f���̔ԍ�
};
#endif