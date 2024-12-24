//==========================
// 
//	��[fence.h]
// Author Yuki Goto
//
//==========================
#ifndef _FENCE_H_
#define _FENCE_H_

//include
#include "building.h"

//�N���X�̒�`
class CFence :public CBuilding
{
public:

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CFence(int nPriority = PRIORITY);//�R���X�g���N�^
	~CFence() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CFence* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
private:
};
#endif