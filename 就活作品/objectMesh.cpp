//==========================
// 
// ���b�V���|���S���̕`�揈��[objectMesh.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"objectMesh.h"
#include"manager.h"
#include"particle.h"
//�ÓI�����o������
const int CObjectMesh::PRIORITY = 0;//�`��D��x

//========================
//�R���X�g���N�^
//========================
CObjectMesh::CObjectMesh(int nPriority) :
CObjectgame(nPriority),//���R���X�g���N�^
m_pTexture(nullptr),//�e�N�X�`���ւ̃|�C���^
m_pVtxBuff(nullptr),//���_�o�b�t�@�ւ̃|�C���^
m_pIdxBuff(nullptr),//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
m_size{},//�|���S���̃T�C�Y
m_WidthDiv(0),//���̕�����
m_VerticalDiv(0),//�c�̕�����
m_NumVtx(0),//���_��
m_NumIdx(0)//�C���f�b�N�X��
{

}

//========================
//�f�X�g���N�^
//========================
CObjectMesh::~CObjectMesh()
{

}

//========================
//�����ݒ�
//========================
HRESULT CObjectMesh::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	//���_���̎Z�o
	m_NumVtx = (m_WidthDiv + 1) * (m_VerticalDiv + 1);

	//�C���f�b�N�X���̎Z�o
	m_NumIdx = ((m_WidthDiv + 1) * 2) * m_VerticalDiv + (2 * (m_VerticalDiv - 1));

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_NumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_NumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	SetInit();//���_���̏����ݒ�
	
	SeIdx();//�C���f�b�N�X�o�b�t�@�̐ݒ�

	return S_OK;
}

//========================
//�I������
//========================
void CObjectMesh::Uninit(void)
{

	if (m_pTexture != nullptr)
	{//�e�N�X�`���̉��
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	if (m_pVtxBuff != nullptr)
	{//���_�o�b�t�@�̉��
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pIdxBuff != nullptr)
	{//�C���f�b�N�X�o�b�t�@�̉��
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	Release();
}

//========================
//�X�V����
//========================
void CObjectMesh::Update()
{
	for (int a = 0; a < 30; a++)
	{
    
	CParticle::Create(GetPos(), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 10, 10.0f, 10.0f, 10.0f);
	}
}

//========================
//�`�揈��
//========================
void CObjectMesh::Draw()
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
	D3DXMatrixTranslation(&mtxTrans,0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���̐ݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_NumVtx, 0, ((m_VerticalDiv * m_WidthDiv) * 2) + (4 * (m_VerticalDiv - 1)));
}

//========================
//�I�u�W�F�N�gMesh����
//========================
CObjectMesh* CObjectMesh::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int Width, int Vertical)
{
	CObjectMesh* pObjectMesh = DBG_NEW CObjectMesh;

	//�ʒu�̐ݒ�
	pObjectMesh->SetPos(pos);

	//�T�C�Y�̐ݒ�
	pObjectMesh->m_size = size;

	//���̕�����
	pObjectMesh->m_WidthDiv = Width;

	//�c�̕�����
	pObjectMesh->m_VerticalDiv = Vertical;

	//�����ݒ�
	pObjectMesh->Init();

	return pObjectMesh;
}

//========================
//���_�o�b�t�@�̐ݒ�
//========================
void CObjectMesh::SetInit()
{
	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̉������Z�o
	float Width = (m_size.x * 2) / m_WidthDiv;

	//���_�̏c�����Z�o
	float Vertical = (m_size.z * 2) / m_VerticalDiv;

	//���_�̉��̈ʒu
	int a = 0;

	//���_�̏c�̈ʒu
	int b = 0;

	//���_���W�̐ݒ�
	for (int i = 0; i < m_NumVtx; i++)
	{
		pVtx[i].pos = D3DXVECTOR3(-m_size.x + (Width * a), 0.0f, m_size.z - (Vertical * b));
		if (a == m_WidthDiv)
		{//���_�̉������Ō�ɂȂ���
			a = 0;
			b++;
		}
		else
		{
			a++;
		}
	}

	//�@���x�N�g���̐ݒ�
	for (int i = 0; i < m_NumVtx; i++)
	{
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

	//���_�J���[�̐ݒ�
	for (int i = 0; i < m_NumVtx; i++)
	{
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	
	//�e�N�X�`�����W�̐ݒ�
	for (int i = 0; i < m_NumVtx; i++)
	{
		pVtx[i].tex = D3DXVECTOR2(0.0f, 0.0f);
	}
	
	
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//========================
//�C���f�b�N�X�o�b�t�@�̐ݒ�
//========================
void CObjectMesh::SeIdx()
{
	//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X�̐ݒ�
	int a = 0;

	for (int i = 0; i < m_VerticalDiv; i++)
	{//�c�̕�����

		for (int n = 0; n < m_WidthDiv; n++)
		{//���̕�����
			pIdx[a] = (m_WidthDiv + 1) * (i + 1) + n;
			pIdx[a + 1] = (m_WidthDiv + 1) * i + n;
			a += 2;
		}

		if (i != m_VerticalDiv - 1)
		{
			pIdx[a] = (m_WidthDiv + 1) * (1 + i) - 1;
			pIdx[a + 1] = (m_WidthDiv + 1) * (2 + i);
		}
}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();
}