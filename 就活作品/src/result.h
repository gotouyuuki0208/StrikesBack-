//==========================
// 
// ���U���g��ʂ̏���[result.h]
// Author Yuki Goto
//
//==========================
#ifndef _RESULT_H_
#define _RESULT_H_

//include
#include "scene.h"

//�N���X�̒�`
class CResult :public CScene
{
public:

	//�����o�֐�
	CResult();//�R���X�g���N�^
	~CResult() override;//�f�X�g���N�^
	HRESULT Init()override;//����������
	void Uninit()override;//�I������
	void Update()override;//�X�V����
	void Draw()override;//�`�揈��
private:
	void Bg();//�w�i
};

#endif 