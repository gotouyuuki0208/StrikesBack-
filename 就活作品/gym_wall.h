//==========================
// 
// �̈�ٕ�[gym_wall.h]
// Author Yuki Goto
//
//==========================
#ifndef _GYM_WALL_H_
#define _GYM_WALL_H_

//include
#include "building.h"

//�N���X�̒�`
class CGymwall :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CGymwall(int nPriority = PRIORITY);//�R���X�g���N�^
	~CGymwall() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CGymwall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif