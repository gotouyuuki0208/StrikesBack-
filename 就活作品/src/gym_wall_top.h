//==========================
// 
// �̈�ٕǏ㕔[gym_wall_top.h]
// Author Yuki Goto
//
//==========================
#ifndef _GYM_WALL_TOP_H_
#define _GYM_WALL_TOP_H_

//include
#include "building.h"

//�N���X�̒�`
class CGymwalltop :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CGymwalltop(int nPriority = PRIORITY);//�R���X�g���N�^
	~CGymwalltop() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CGymwalltop* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif