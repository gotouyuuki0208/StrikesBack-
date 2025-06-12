//==========================
// 
// �̈�ِ���[gym_front.h]
// Author Yuki Goto
//
//==========================
#ifndef _GYM_FRONT_H_
#define _GYM_FRONT_H_

//include
#include "building.h"

//�N���X�̒�`
class CGymfront :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CGymfront(int nPriority = PRIORITY);//�R���X�g���N�^
	~CGymfront() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CGymfront* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif