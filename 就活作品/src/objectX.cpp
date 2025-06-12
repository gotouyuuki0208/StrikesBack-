//==========================
// 
// ���f���̕`�揈��[objectX.cpp]
// Author Yuki Goto
//
//==========================

//incelude
#include"objectX.h"
#include"manager.h"

//�ÓI�����o�ϐ�������
const int CObjectX::PRIORITY = 3;//�`�揇
//==========================
// �R���X�g���N�^
//==========================
CObjectX::CObjectX(int nPriority):
CObjectgame(nPriority),
m_pMesh(nullptr),
m_pBuffMat(nullptr),
m_dwNumMat(0),
m_pTexture(nullptr),
m_pTexture2(nullptr),
m_Size({ 0.0f, 0.0f, 0.0f }),
m_vtxMin({0.0f, 0.0f, 0.0f}),
m_vtxMax({0.0f, 0.0f, 0.0f}),
m_Transparent(1.0f)
{
	
	
}

//==========================
// �f�X�g���N�^
//==========================
CObjectX::~CObjectX(void)
{

}

//==========================
// ����������
//==========================
HRESULT CObjectX::Init(void)
{
	return S_OK;
}

//==========================
// �I������
//==========================
void CObjectX::Uninit(void)
{
	//���b�V���̔j��
	if (m_pMesh != nullptr)
	{
		m_pMesh = nullptr;
	}

	//�}�e���A���̔j��
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat = nullptr;
	}

	if (m_pTexture2 != nullptr)
	{
		delete[] m_pTexture2;
		m_pTexture2 = nullptr;
	}
}

//==========================
// �X�V����
//==========================
void CObjectX::Update(void)
{

}

//==========================
// �`�揈��
//==========================
void CObjectX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�}�g���b�N�X�̍쐬
	CreateMtx();

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());

	//���݂̃}�g���b�N�X���擾
	pDevice->GetMaterial(&matDef);

	//�@���̒�����1�ɂ���
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//�����x��ݒ�
		pMat[nCntMat].MatD3D.Diffuse.a = m_Transparent;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		pDevice->SetTexture(0, m_pTexture2[nCntMat]);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}


	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

//==========================
// ���f������
//==========================
CObjectX* CObjectX::Create(void)
{
	CObjectX* pModel = DBG_NEW CObjectX;

	//����������
	pModel->Init();

	return pModel;
}

//==========================
//���f�����蓖��
//==========================
void CObjectX::BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPDIRECT3DTEXTURE9* pTexture)
{
	m_pMesh = pMesh;		//���b�V��
	m_pBuffMat = pBuffMat;  //�}�e���A��
	m_dwNumMat = dwNumMat;  //�}�e���A���̐�

	m_pTexture2 = DBG_NEW LPDIRECT3DTEXTURE9[int(dwNumMat)];//�e�N�X�`��

	for (int i = 0; i < int(dwNumMat); i++)
	{
		m_pTexture2[i] = pTexture[i];
	}
}

//========================
//�T�C�Y���擾
//========================
void CObjectX::SetSize(void)
{
	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		vtx.x *= GetScale().x;
		vtx.y *= GetScale().y;
		vtx.z *= GetScale().z;

		//�ő�̒��_���擾
		if (vtx.x > m_vtxMax.x)
		{
			m_vtxMax.x = floor(vtx.x);
		}
		if (vtx.y > m_vtxMax.y)
		{
			m_vtxMax.y = floor(vtx.y);
		}
		if (vtx.z > m_vtxMax.z)
		{
			m_vtxMax.z = floor(vtx.z);
		}

		//�ŏ��̒��_���擾
		if (vtx.x < m_vtxMin.x)
		{
			m_vtxMin.x = floor(vtx.x);
		}
		if (vtx.y < m_vtxMin.y)
		{
			m_vtxMin.y = floor(vtx.y);
		}

		if (vtx.z < m_vtxMin.z)
		{
			m_vtxMin.z = floor(vtx.z);
		}

		pVtxBuff += sizeFVF;
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pMesh->UnlockVertexBuffer();

	m_Size.x = m_vtxMax.x - m_vtxMin.x;
	m_Size.y = m_vtxMax.y - m_vtxMin.y;
	m_Size.z = m_vtxMax.z - m_vtxMin.z;
}

//========================
//�e�N�X�`�����蓖��
//========================
void CObjectX::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//========================
//���_�̍ŏ��̏ꏊ���擾
//========================
D3DXVECTOR3& CObjectX::GetVtxMin(void)
{
	return m_vtxMin;
}

//========================
//���_�̍ő�̏ꏊ���擾
//========================
D3DXVECTOR3& CObjectX::GetVtxMax(void)
{
	return m_vtxMax;
}

//========================
//�T�C�Y�擾
//========================
D3DXVECTOR3& CObjectX::GetSize(void)
{
	return m_Size;
}

//========================
//���b�V��(���_���)�ւ̃|�C���^
//========================
LPD3DXMESH& CObjectX::GetMesh()
{
	return m_pMesh;
}

//========================
//�}�e���A���ւ̃|�C���^
//========================
LPD3DXBUFFER& CObjectX::GetBuffMat()
{
	return m_pBuffMat;
}

//========================
//�}�e���A���̐�
//========================
DWORD& CObjectX::GetNumMat()
{
	return m_dwNumMat;
}

//========================
//�����x��ݒ�
//========================
void CObjectX::SetTransparent(float cor)
{
	m_Transparent = cor;
}

//========================
//�����x���擾
//========================
float CObjectX::GetTransparent()
{
	return m_Transparent;
}

//========================
//�s��̐���
//========================
void CObjectX::CreateMtx()
{
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&GetMtxWorld());

	//�X�P�[���ݒ�
	D3DXMatrixScaling(&mtxScale, GetScale().x, GetScale().y, GetScale().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxScale);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxTrans);
}

//========================
//���f���̕`��
//========================
void CObjectX::DrawModel()
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���݂̃}�g���b�N�X���擾
	pDevice->GetMaterial(&matDef);

	//�@���̒�����1�ɂ���
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//�����x��ݒ�
		pMat[nCntMat].MatD3D.Diffuse.a = m_Transparent;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		pDevice->SetTexture(0, m_pTexture2[nCntMat]);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}


	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}