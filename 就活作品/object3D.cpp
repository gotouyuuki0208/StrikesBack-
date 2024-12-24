//==========================
// 
// �|���S���̕`�揈��[object3D.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"object3D.h"
#include"manager.h"

//�ÓI�����o������
const int CObject3D::PRIORITY = 2;//�`��D��x

//========================
//�R���X�g���N�^
//========================
CObject3D::CObject3D(int nPriority) :CObjectgame(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;

	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_cor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//========================
//�f�X�g���N�^
//========================
CObject3D::~CObject3D()
{

}

//========================
//�����ݒ�
//========================
HRESULT CObject3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, -m_size.y, +m_size.z);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x, -m_size.y, +m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, +m_size.y, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, +m_size.y, -m_size.z);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_cor;
	pVtx[1].col = m_cor;
	pVtx[2].col = m_cor;
	pVtx[3].col = m_cor;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//========================
//�I������
//========================
void CObject3D::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}

	Release();
}

//========================
//�X�V����
//========================
void CObject3D::Update()
{
	
}

//========================
//�`�揈��
//========================
void CObject3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&GetMtxWorld());

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);

	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�t�B�[���h�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//========================
//�I�u�W�F�N�g3D����
//========================
CObject3D* CObject3D::Create(void)
{
	CObject3D* pObject3D = DBG_NEW CObject3D;

	pObject3D->Init();

	return pObject3D;
}

//========================
//�e�N�X�`�����蓖��
//========================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//========================
//�傫���ݒ�
//========================
void CObject3D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//========================
//�T�C�Y�擾
//========================
D3DXVECTOR3& CObject3D::GetSize(void)
{
	return m_size;
}

//========================
///�F�̐ݒ�
//========================
void CObject3D::SetCor(D3DXCOLOR cor)
{
	m_cor = cor;
}