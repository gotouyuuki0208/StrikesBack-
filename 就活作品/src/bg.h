//==========================
// 
// �w�i����[bg.h]
// Author Yuki Goto
//
//==========================
#ifndef _BG_H_
#define _BG_H_

//include
#include "object2D.h"

//�N���X�̒�`
class CBg:public CObject2D
{
public:
	//�萔
	static const int PRIORITY;

	//�����o�֐�
	CBg(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBg()override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
	static CBg* Create(const char texname[256]);//�I�u�W�F�N�g2D����
private:
	static int m_nTexIdx;//�e�N�X�`��ID
};

#endif 
