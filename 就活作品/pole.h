//==========================
// 
// �d��[pole.h]
// Author Yuki Goto
//
//==========================
#ifndef _POLE_H_
#define _POLE_H_

//include
#include "building.h"

//�N���X�̒�`
class CPole :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CPole(int nPriority = PRIORITY);//�R���X�g���N�^
	~CPole() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CPole* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif