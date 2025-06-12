//==========================
// 
// �^�C�g���ƃ��U���g��ʂ̕�[gym_wall_top.h]
// Author Yuki Goto
//
//==========================
#ifndef _OUTGAMEWALL_H_
#define _OUTGAMEWALL_H_

//include
#include "building.h"

//�N���X�̒�`
class COutGameWall :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	COutGameWall(int nPriority = PRIORITY);//�R���X�g���N�^
	~COutGameWall() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static COutGameWall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif