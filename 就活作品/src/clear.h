//==========================
// 
// [TitleLogo.h]
// Author Yuki Goto
//
//==========================
#ifndef _CLEAR_H_
#define _CLEAR_H_

//include
#include "object2D.h"

//�N���X�̒�`
class CClear :public CObject2D
{
public:
	//�萔
	static const int PRIORITY;

	//�����o�֐�
	CClear(int nPriority = PRIORITY);//�R���X�g���N�^
	~CClear()override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
	static CClear* Create(D3DXVECTOR3 pos);//�I�u�W�F�N�g2D����
private:
	static int m_nTexIdx;//�e�N�X�`��ID
};

#endif 
