//==========================
// 
// �`���[�g���A���̔w�i����[tutorialbg.h]
// Author Yuki Goto
//
//==========================
#ifndef _TUTORIALBG_H_
#define _TUTORIALBG_H_

//include
#include "object2D.h"

//�N���X�̒�`
class CTutorialBg:public CObject2D
{
public:
	//�萔
	static const int PRIORITY;

	//�����o�֐�
	CTutorialBg(int nPriority = PRIORITY);//�R���X�g���N�^
	~CTutorialBg()override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
	static CTutorialBg* Create();//�I�u�W�F�N�g2D����
private:
};

#endif 
