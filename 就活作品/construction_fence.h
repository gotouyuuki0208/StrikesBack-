//==========================
// 
// �H������̍�[Construction_fence.h]
// Author Yuki Goto
//
//==========================
#ifndef _CONSTRUCTION_FENCE_H_
#define _CONSTRUCTION_FENCE_H_

//include
#include "building.h"

//�N���X�̒�`
class CConstruction :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CConstruction(int nPriority = PRIORITY);//�R���X�g���N�^
	~CConstruction() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CConstruction* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif