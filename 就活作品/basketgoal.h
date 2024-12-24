//==========================
// 
// �o�X�P�b�g�S�[��[basketgoal.h]
// Author Yuki Goto
//
//==========================
#ifndef _BASKETGOAL_H_
#define _BASKETGOAL_H_

//include
#include "building.h"

//�N���X�̒�`
class CBasketgoal :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CBasketgoal(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBasketgoal() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBasketgoal* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif