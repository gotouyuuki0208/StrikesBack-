//==========================
// 
// �^�C�g����ʂ̏���[taitle.h]
// Author Yuki Goto
//
//==========================
#ifndef _TITLE_H_
#define _TITLE_H_

//include
#include "scene.h"

//�^�C�g���N���X�̒�`
class CTitle:public CScene
{
public:

	//�����o�֐�
	CTitle();//�R���X�g���N�^
	~CTitle() override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
private:

	//�����o�֐�
	void Bg();//�w�i
};

#endif 