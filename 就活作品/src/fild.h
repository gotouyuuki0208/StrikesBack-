//==========================
// 
// �n��[fild.h]
// Author Yuki Goto
//
//==========================
#ifndef _FILD_H_
#define _FILD_H_

//include
#include "object3D.h"

//�N���X�̒�`
class CFild :public CObject3D
{
public:

	enum class FILDTYPE
	{
		NONE=0,
		FILD,//�n��
		CURB,//����
		ENEMYMOVEPOINT,//�G�̈ړ��n�_
		STAGECHANGE,
		GYMFILD,
		ARROWPOINT,
	};

	//�萔
	static const int PRIORITY;//�`�揇

	//�����o�֐�
	CFild(int nPriority = PRIORITY);//�R���X�g���N�^
	~CFild() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CFild* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);//�I�u�W�F�N�g����
	FILDTYPE GetFildType();//�n�ʂ̎�ނ��擾
	void SetFild(FILDTYPE type);//�n�ʂ̎�ނ�ݒ�
	void SetTexIdx(int Idx);//�e�N�X�`���ԍ���ݒ�
	int GetTexIdx();//�e�N�X�`���ԍ����擾

private:

	//�����o�ϐ�
	int m_nTexIdx;//�e�N�X�`���̔ԍ�
	FILDTYPE m_FildType;//�n�ʂ̎��
};
#endif