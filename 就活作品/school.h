//==========================
// 
// �w�Z[school.h]
// Author Yuki Goto
//
//==========================
#ifndef _SCHOOL_H_
#define _SCHOOL_H_

//include
#include "building.h"

//�N���X�̒�`
class CSchool :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CSchool(int nPriority = PRIORITY);//�R���X�g���N�^
	~CSchool() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CSchool* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif