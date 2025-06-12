//==========================
// 
// ������[house_white.h]
// Author Yuki Goto
//
//==========================
#ifndef _HOUSE_WHITE_H_
#define _HOUSE_WHITE_H_

//include
#include "building.h"

//�N���X�̒�`
class CHouseWhite :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CHouseWhite(int nPriority = PRIORITY);//�R���X�g���N�^
	~CHouseWhite() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CHouseWhite* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif