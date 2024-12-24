//==========================
// 
// ���փh�A[entrance.h]
// Author Yuki Goto
//
//==========================
#ifndef _ENTRANCE_H_
#define _ENTRANCE_H_

//include
#include "building.h"

//�N���X�̒�`
class CEntrance :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CEntrance(int nPriority = PRIORITY);//�R���X�g���N�^
	~CEntrance() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CEntrance* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif