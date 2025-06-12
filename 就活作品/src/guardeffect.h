//==========================
// 
// �K�[�h�G�t�F�N�g����[guardeffect.h]
// Author Yuki Goto
//
//==========================
#ifndef _GUARDEFFECT_H_
#define _GUARDEFFECT_H_

//include
#include"object3D.h"

//�v���C���[�N���X�̒�`
class CGuardEffect :public CObject3D
{
public:
	//�萔
	static const int PRIORITY;//�`�揇
	static const float SUB_COL;//�F�̌��炷���l

	//�����o�֐�
	CGuardEffect(int nPriority = PRIORITY);//�R���X�g���N�^
	~CGuardEffect() override;//�f�X�g���N�^
	HRESULT Init() override;//����������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��
	static CGuardEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);//����

private:
	//�����o�֐�
	void ChangeCol();//�F�̕ύX

	//�����o�ϐ�
	int m_nTexIdx;//�e�N�X�`��ID
	int m_nLife;//����
};
#endif 
