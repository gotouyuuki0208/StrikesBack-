//==========================
// 
// �J��������[camera.h]
// Author Yuki Goto
//
//==========================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//�J�����N���X�̒�`
class CCamera
{
public:
	//�萔
	static const float Y_DISTANCE;//����
	static const float Z_DISTANCE;//����

	//�����o�֐�
	CCamera();//�R���X�g���N�^
	~CCamera();//�f�X�g���N�^
	HRESULT Init();//����������
	void Uninit();//�I������
	void Update();//�X�V����
	void SetCamera();//�J�����̐ݒ�
	void SetShape(int flame, int scale);//�J�����h��ݒ�
	void Move(D3DXVECTOR3 pos);//�J�����̈ړ�
	void VerticalMove(D3DXVECTOR3 pos);//�J�����̏c�ړ�
	D3DXVECTOR3& GetPosR();//�����_�̎擾
	void OutGame(D3DXVECTOR3 pos);//�C���Q�[���ȊO�̃J����
	D3DXVECTOR3& GetRot();//�����̎擾
	void Overhead(D3DXVECTOR3 pos);//���ォ��ʂ�
private:
	//�����o�֐�
	void Input();//���͏���

	//�����o�ϐ�
	D3DXVECTOR3 m_posV;//���_
	D3DXVECTOR3 m_posR;//�����_
	D3DXVECTOR3 m_targetposV;//���_
	D3DXVECTOR3 m_targetposR;//�����_
	D3DXVECTOR3 m_vecU;//�����
	D3DXVECTOR3 m_rot;//����
	D3DXVECTOR3 move;//�ړ��l
	D3DXMATRIX m_mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;//�r���[�}�g���b�N�X
	float m_PosVY;//���_��Y���W
	float m_PosRY;//�����_��Y���W
	int m_nFlame;//�t���[����
	int m_fShapeScale;//�h��̗�
};

#endif