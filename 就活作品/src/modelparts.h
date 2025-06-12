//==========================
// 
// ���f���̃p�[�c�̏���[modelparts.h]
// Author Yuki Goto
//
//==========================
#ifndef _MODELPARTS_H_
#define _MODELPARTS_H_

//include
#include"collisionvisual.h"

//�N���X�̒�`
class CModelParts
{
public:

	//�����o�֐�
	CModelParts();//�R���X�g���N�^
	~CModelParts();//�f�X�g���N�^
	HRESULT Init();//����������
	void Uninit();//�I������
	void Update();//�X�V����
	void Draw();//�`�揈��
	static CModelParts* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModelParts* Parent,int ModelPartsNum, D3DXVECTOR3 scale);//����
	void SetParents(CModelParts* Parent);//�e���f���̐ݒ�
	CModelParts* GetParent();//�e���f�����擾
	void SetMotionPos(D3DXVECTOR3 pos);//�ʒu�̐ݒ�
	D3DXVECTOR3& GetMotionPos();//���[�V�����ł̈ʒu�̎擾
	void SetPos(D3DXVECTOR3 pos);//�ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot);//�����̐ݒ�
	D3DXVECTOR3& GetPos();//�ʒu�̎擾
	D3DXVECTOR3& GetRot();//�����̎擾
	D3DXVECTOR3& GetScale();//�X�P�[���̎擾
	bool GetExistParent();//�e�p�[�c�����邩�̎擾
	D3DXMATRIX& GetMtxWorld();//�}�g���b�N�X�擾
	void SetSize();//�T�C�Y�̐ݒ�
	D3DXVECTOR3& GetVtxMin();//���_�̍ŏ��̏ꏊ���擾
	D3DXVECTOR3& GetVtxMax();//���_�̍ő�̏ꏊ���擾
	void SetCol();//�F�̐ݒ�
	int GetModelNum();//���f���̔ԍ����擾
	void CreateVisual(D3DXVECTOR3 pos,float radius);//�����蔻����������郁�b�V���𐶐�
	void CreateMtx();//�s��̐���
	void VisualDelete();//�����蔻��̌����ڂ��폜
	CCollisionVisual* GetVisual();//�������������蔻��̏��
	void SubCol(float m_col);//�����x�����炷
private:

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;//�I�t�Z�b�g�ʒu
	D3DXVECTOR3 m_rot;//�I�t�Z�b�g����
	D3DXVECTOR3 m_motionpos;//�I�t�Z�b�g�ʒu
	D3DXVECTOR3 m_motionrot;//�I�t�Z�b�g����

	D3DXMATRIX m_mtxWorld;//���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;//�}�e���A���̐�
	D3DCOLORVALUE m_Diffuse[100];//�F�̐�
	D3DXVECTOR3 m_vtxMin;//���_�̍ŏ�
	D3DXVECTOR3 m_vtxMax;//���_�̍ő�
	D3DXVECTOR3 m_Size;//���f���̑傫��
	CModelParts* m_ParentParts;//�e���f���̃|�C���^
	bool m_corDamage;//��e�����Ƃ��̐F�ɕύX���邩����
	int m_modelIdx;//���f���̔ԍ�
	D3DXVECTOR3 m_scale;//�X�P�[��
	CCollisionVisual* m_Visual;//�����蔻��̉���
	float m_Color;//���f���̓����x

};
#endif