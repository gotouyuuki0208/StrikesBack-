//==========================
// 
// ���C�g����[light.h]
// Author Yuki Goto
//
//==========================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//�}�N����`
#define MAX_LIGHT (4)//���C�g�̐�

//���C�g�N���X�̒�`
class CLight
{
public:
	//�����o�֐�
	CLight();//�R���X�g���N�^
	~CLight();//�f�X�g���N�^
	HRESULT Init();//����������
	void Uninit();//�I������
	void Update();//�X�V����
private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];//���C�g�\����
};

#endif