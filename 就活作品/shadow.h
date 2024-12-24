//==========================
// 
// �e[shadow.h]
// Author Yuki Goto
//
//==========================
#ifndef _SHADOW_H_
#define _SHADOW_H_

//include
#include "object3D.h"

//�N���X�̒�`
class CShadow :public CObject3D
{
public:
	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CShadow(int nPriority = PRIORITY);//�R���X�g���N�^
	~CShadow() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CShadow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//�I�u�W�F�N�g����
	void Move(D3DXVECTOR3 pos);//�ړ�����
private:
	int m_nTexIdx;//�e�N�X�`���̔ԍ�
};
#endif