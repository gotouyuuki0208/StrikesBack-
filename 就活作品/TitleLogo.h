//==========================
// 
// �^�C�g�����S[TitleLogo.h]
// Author Yuki Goto
//
//==========================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

//include
#include "object2D.h"

//�N���X�̒�`
class CTitleLogo :public CObject2D
{
public:
	//�萔
	static const int PRIORITY;

	//�����o�֐�
	CTitleLogo(int nPriority = PRIORITY);//�R���X�g���N�^
	~CTitleLogo()override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
	static CTitleLogo* Create(D3DXVECTOR3 pos);//�I�u�W�F�N�g2D����
private:
	static int m_nTexIdx;//�e�N�X�`��ID
};

#endif 
