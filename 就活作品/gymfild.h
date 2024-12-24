//==========================
// 
// ����[curb.h]
// Author Yuki Goto
//
//==========================
#ifndef _GYMFILD_H_
#define _GYMFILD_H_

//include
#include "fild.h"

//�N���X�̒�`
class CGymFild :public CFild
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CGymFild(int nPriority = PRIORITY);//�R���X�g���N�^
	~CGymFild() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CGymFild* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif