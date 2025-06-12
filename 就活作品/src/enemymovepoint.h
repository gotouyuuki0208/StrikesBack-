//==========================
// 
// �G�̈ړ��n�_[enemymovepoint.h]
// Author Yuki Goto
//
//==========================
#ifndef _ENEMYMOVEPOINT_H_
#define _ENEMYMOVEPOINT_H_

//include
#include "fild.h"

//�N���X�̒�`
class CEnemyMovePoint :public CFild
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CEnemyMovePoint(int nPriority = PRIORITY);//�R���X�g���N�^
	~CEnemyMovePoint() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CEnemyMovePoint* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif