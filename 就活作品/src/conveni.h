//==========================
// 
// �R���r�j[conveni.h]
// Author Yuki Goto
//
//==========================
#ifndef _CONVENI_H_
#define _CONVENI_H_

//include
#include "building.h"

//�N���X�̒�`
class CConveni :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CConveni(int nPriority = PRIORITY);//�R���X�g���N�^
	~CConveni() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CConveni* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif