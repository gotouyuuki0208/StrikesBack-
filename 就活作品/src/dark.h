//==========================
// 
// �w�i����[bg.h]
// Author Yuki Goto
//
//==========================
#ifndef _DARK_H_
#define _DARK_H_

//include
#include "object2D.h"

//�N���X�̒�`
class CDark :public CObject2D
{
public:
	//�萔
	static const int PRIORITY;

	//�����o�֐�
	CDark(int nPriority = PRIORITY);//�R���X�g���N�^
	~CDark()override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
	static CDark* Create();//�I�u�W�F�N�g2D����
private:
};

#endif 
