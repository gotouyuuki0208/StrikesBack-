//==========================
// 
// �������UI�̔w�i[UIbg.h]
// Author Yuki Goto
//
//==========================
#ifndef _UIBG_H_
#define _UIBG_H_

//include
#include "object2D.h"

//�N���X�̒�`
class CUIBg :public CObject2D
{
public:
	//�萔
	static const int PRIORITY;

	//�����o�֐�
	CUIBg(int nPriority = PRIORITY);//�R���X�g���N�^
	~CUIBg()override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
	static CUIBg* Create(D3DXVECTOR3 pos);//�I�u�W�F�N�g2D����
private:
};

#endif 
