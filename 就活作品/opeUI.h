//==========================
// 
// �������UI[opeUI.h]
// Author Yuki Goto
//
//==========================
#ifndef _OPEUI_H_
#define _OPEUI_H_

//include
#include "object2D.h"

//�N���X�̒�`
class COpeUI :public CObject2D
{
public:
	//�萔
	static const int PRIORITY;

	//�����o�֐�
	COpeUI(int nPriority = PRIORITY);//�R���X�g���N�^
	~COpeUI()override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
	static COpeUI* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,const char texname[256]);//�I�u�W�F�N�g2D����
private:
	int m_nTexIdx;//�e�N�X�`��ID
};

#endif 
