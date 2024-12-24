//==========================
// 
// �̈�ٓV��[corridorfloor.h]
// Author Yuki Goto
//
//==========================
#ifndef _GYMCEILING_H_
#define _GYMCEILING_H_

//include
#include "building.h"

//�N���X�̒�`
class CGymCeiling :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CGymCeiling(int nPriority = PRIORITY);//�R���X�g���N�^
	~CGymCeiling() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CGymCeiling* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif