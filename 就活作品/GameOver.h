//==========================
// 
// [TitleLogo.h]
// Author Yuki Goto
//
//==========================
#ifndef _OVER_H_
#define _OVER_H_

//include
#include "object2D.h"

//�N���X�̒�`
class COver :public CObject2D
{
public:
	//�萔
	static const int PRIORITY;

	//�����o�֐�
	COver(int nPriority = PRIORITY);//�R���X�g���N�^
	~COver()override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
	static COver* Create(D3DXVECTOR3 pos);//�I�u�W�F�N�g2D����
private:
	static int m_nTexIdx;//�e�N�X�`��ID
};

#endif 
