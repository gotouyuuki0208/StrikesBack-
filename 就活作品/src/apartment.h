//==========================
// 
//	�A�p�[�g[apartment.h]
// Author Yuki Goto
//
//==========================
#ifndef _APARTMENT_H_
#define _APARTMENT_H_

//include
#include "building.h"

//�N���X�̒�`
class CApartment :public CBuilding
{
public:
	
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CApartment(int nPriority = PRIORITY);//�R���X�g���N�^
	~CApartment() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CApartment* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif