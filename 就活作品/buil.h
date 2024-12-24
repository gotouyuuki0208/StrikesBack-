//==========================
// 
// �r��[buil.h]
// Author Yuki Goto
//
//==========================
#ifndef _BUIL_H_
#define _BUIL_H_

//include
#include "building.h"

//�N���X�̒�`
class CBuil :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CBuil(int nPriority = PRIORITY);//�R���X�g���N�^
	~CBuil() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CBuil* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif