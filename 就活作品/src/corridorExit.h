//==========================
// 
//	�L���̏o��[corridorExit.h]
// Author Yuki Goto
//
//==========================
#ifndef _CORRIDOREXIT_H_
#define _CORRIDOREXIT_H_

//include
#include "building.h"

//�N���X�̒�`
class CCorridorExit :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CCorridorExit(int nPriority = PRIORITY);//�R���X�g���N�^
	~CCorridorExit() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CCorridorExit* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif