//==========================
// 
// [TitleLogo.h]
// Author Yuki Goto
//
//==========================
#ifndef _PEOPLENUM_H_
#define _PEOPLENUM_H_

//include
#include "object2D.h"

//�N���X�̒�`
class CPeopleNum :public CObject2D
{
public:
	//�萔
	static const int PRIORITY;

	//�����o�֐�
	CPeopleNum(int nPriority = PRIORITY);//�R���X�g���N�^
	~CPeopleNum()override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
	static CPeopleNum* Create(D3DXVECTOR3 pos);//�I�u�W�F�N�g2D����
private:
	static int m_nTexIdx;//�e�N�X�`��ID
};

#endif 
