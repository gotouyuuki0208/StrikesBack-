//==========================
// 
// �����蔻�����[collisionvisual.h]
// Author Yuki Goto
//
//==========================
#ifndef _COLLISONVISUAL_H_
#define _COLLISONVISUAL_H_

//�N���X�̒�`
class CCollisionVisual
{
public:
	
	//�����o�֐�
	CCollisionVisual();//�R���X�g���N�^
	~CCollisionVisual();//�f�X�g���N�^
	HRESULT Init();//����������
	void Uninit();//�I������
	void Update();//�X�V����
	void Draw();//�`�揈��
	static CCollisionVisual* Create(D3DXVECTOR3 pos, float radius);//�I�u�W�F�N�g����
	void SetPos(D3DXVECTOR3 pos);//�ʒu�̐ݒ�
	void SetCorNomal();//�ʏ�̐F�ɐݒ�
	void SetCorCollision();//�Փ˂��Ă���Ƃ��̐F�ɐݒ�
	float GetRadius();//���a���擾
	D3DXVECTOR3& GetPos();//�ʒu���擾
private:
	//�����o�ϐ�
	LPD3DXMESH m_pMesh;//���b�V��(���_���)�ւ̃|�C���^
	float m_radius;//���a
	D3DXVECTOR3 m_pos;//�ʒu
	D3DXVECTOR3 m_rot;//����
	D3DXMATRIX m_mtxWorld;//���[���h�}�g���b�N�X
	D3DXCOLOR m_cor;//�F�̐�
};

#endif