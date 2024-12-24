//==========================
// 
// �T���h�o�b�O[punchingbag.h]
// Author Yuki Goto
//
//==========================
#ifndef _PUNCHINGBUG_H_
#define _PUNCHINGBUG_H_

//include
#include "objectX.h"

//�N���X�̒�`
class CPunchingBag :public CObjectX
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CPunchingBag(int nPriority = PRIORITY);//�R���X�g���N�^
	~CPunchingBag() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CPunchingBag* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
private:
	//�����o�ϐ�
	int m_nModelIdx;//���f���̔ԍ�
};
#endif