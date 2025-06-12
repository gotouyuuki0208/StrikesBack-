//==========================
// 
// �^�C�g������[TitleStart.h]
// Author Yuki Goto
//
//==========================
#ifndef _TITLESTART_H_
#define _TITLESTART_H_

//include
#include "object2D.h"

//�N���X�̒�`
class CTitleStart :public CObject2D
{
public:
	//�萔
	static const int PRIORITY;

	//�����o�֐�
	CTitleStart(int nPriority = PRIORITY);//�R���X�g���N�^
	~CTitleStart()override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
	static CTitleStart* Create(D3DXVECTOR3 pos);//�I�u�W�F�N�g2D����
private:
	static int m_nTexIdx;//�e�N�X�`��ID
};

#endif 
