//==========================
// 
// �M���@[shingoki.h]
// Author Yuki Goto
//
//==========================
#ifndef _SHINGOKI_H_
#define _SHINGOKI_H_

//include
#include "building.h"

//�N���X�̒�`
class CShingoki :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CShingoki(int nPriority = PRIORITY);//�R���X�g���N�^
	~CShingoki() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CShingoki* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif