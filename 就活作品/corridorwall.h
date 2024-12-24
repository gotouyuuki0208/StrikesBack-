//==========================
// 
// �L���̕�[corridorwall.h]
// Author Yuki Goto
//
//==========================
#ifndef _CORRIDORWALL_H_
#define _CORRIDORWALL_H_

//include
#include "building.h"

//�N���X�̒�`
class CCorridorWall :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CCorridorWall(int nPriority = PRIORITY);//�R���X�g���N�^
	~CCorridorWall() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CCorridorWall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif