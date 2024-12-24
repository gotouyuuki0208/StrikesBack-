//==========================
// 
// �A�E�g�Q�[���̃L�����N�^�[[outgamecharactar.h]
// Author Yuki Goto
//
//==========================
#ifndef _OUTGAMECHARACTAR_H_
#define _OUTGAMECHARACTAR_H_

//include
#include "motionmodel.h"

//�N���X�̒�`
class COutGameChara :public CMotionModel
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	COutGameChara(int nPriority = PRIORITY);//�R���X�g���N�^
	~COutGameChara() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static COutGameChara* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//�I�u�W�F�N�g����
private:
};
#endif