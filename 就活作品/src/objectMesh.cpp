//==========================
// 
// ���b�V���|���S���̕`�揈��[objectMesh.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"objectMesh.h"
#include"manager.h"
#include"texture.h"

//�ÓI�����o������
const int CObjectMesh::PRIORITY = 0;//�`��D��x

//========================
//�R���X�g���N�^
//========================
CObjectMesh::CObjectMesh(int nPriority) :
CObjectgame(nPriority),
m_pTexture(nullptr),
m_pVtxBuff(nullptr),
m_pIdxBuff(nullptr),
m_size{},
m_WidthDiv(0),
m_VerticalDiv(0),
m_NumVtx(0),
m_NumIdx(0),
m_nTexIdx(0)
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

	if (m_pTexture != nullptr)
	{//�e�N�X�`���̉��
		m_pTexture = nullptr;
	}

	Release();
}

//========================
//�X�V����
//========================
void CObjectMesh::Update()
{

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
	D3DXMatrixTranslation(&mtxTrans,GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxTrans);

	GetMtxWorld()._41 = 0.0f;
	GetMtxWorld()._42 = 0.0f;
	GetMtxWorld()._43 = 0.0f;

	//�J�����O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

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

	//�|���S����
	int polygon = ((m_VerticalDiv * m_WidthDiv) * 2) + (4 * (m_VerticalDiv - 1));

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_NumVtx, 0, polygon);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

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
	pObjectMesh->SetSize(size);

	//���̕�����
	pObjectMesh->SetWidthDiv(Width);

	//�c�̕�����
	pObjectMesh->SetVerticalDiv(Vertical);

	//�����ݒ�
	pObjectMesh->Init();

	//�e�N�X�`���ݒ�
	CTexture* pTex = CManager::GetInstance()->GetTexture();
	pObjectMesh->m_nTexIdx = pTex->Regist("data\\TEXTURE\\effect000.png");
	pObjectMesh->BindTexture(pTex->GetAdress(pObjectMesh->m_nTexIdx));

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
	float Height = (m_size.y * 2) / m_VerticalDiv;

	//���_�̏c�����Z�o
	float Vertical = (m_size.z * 2) / m_VerticalDiv;
	
	//���_�̉��̈ʒu
	int WidthPos = 0;

	//���_�̏c�̈ʒu
	int VerticalPos = 0;

	//���_���W�̐ݒ�
	for (int i = 0; i < m_NumVtx; i++)
	{
		pVtx[i].pos = D3DXVECTOR3(-m_size.x + (Width * WidthPos), m_size.y + (-Height * VerticalPos), m_size.z - (Vertical * VerticalPos));
		if (WidthPos == m_WidthDiv)
		{//���_�̉������Ō�ɂȂ���
			WidthPos = 0;
			VerticalPos++;
		}
		else
		{
			WidthPos++;
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
		pVtx[i].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f);
	}
	

	Width = 1.0f / m_WidthDiv;
	Vertical = 1.0f / m_VerticalDiv;
	WidthPos = 0;
	VerticalPos = 0;
	//�e�N�X�`�����W�̐ݒ�
	for (int i = 0; i < m_NumVtx; i++)
	{
		pVtx[i].tex = D3DXVECTOR2(0.0f + (Width * WidthPos), 0.0f + (-Vertical * VerticalPos));
		if (WidthPos == m_WidthDiv)
		{//���_�̉������Ō�ɂȂ���
			WidthPos = 0;
			VerticalPos++;
		}
		else
		{
			WidthPos++;
		}
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
	int IdxNum = 0;

	for (int i = 0; i < m_VerticalDiv; i++)
	{//�c�̕�����

		for (int n = 0; n < m_WidthDiv+1; n++)
		{//���̕�����
			pIdx[IdxNum] = (m_WidthDiv + 1) * (i + 1) + n;
			pIdx[IdxNum + 1] = (m_WidthDiv + 1) * i + n;
			IdxNum += 2;
		}

		if (i != m_VerticalDiv - 1)
		{
			pIdx[IdxNum] = (m_WidthDiv + 1) * (1 + i) - 1;
			pIdx[IdxNum + 1] = (m_WidthDiv + 1) * (2 + i);
			IdxNum += 2;
		}
	}

	for (int i = 0; i < m_NumIdx; i++)
	{
		int a = pIdx[i];
		a = 0;
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();
}

//========================
//�c�̕�������ݒ�
//========================
void CObjectMesh::SetVerticalDiv(int vertical)
{
	m_VerticalDiv = vertical;
}

//========================
//�c�̕��������擾
//========================
int CObjectMesh::GetVerticalDiv()
{
	return m_VerticalDiv;
}

//========================
//���̕�������ݒ�
//========================
void CObjectMesh::SetWidthDiv(int width)
{
	m_WidthDiv = width;
}

//========================
//���̕�������ݒ�
//========================
int CObjectMesh::GetWidthDiv()
{
	return m_WidthDiv;
}

//========================
//�T�C�Y��ݒ�
//========================
void CObjectMesh::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//========================
//�T�C�Y���擾
//========================
D3DXVECTOR3& CObjectMesh::GetSize()
{
	return m_size;
}

//========================
//���_�o�b�t�@���擾
//========================
LPDIRECT3DVERTEXBUFFER9& CObjectMesh::GetVtxBuff()
{
	return m_pVtxBuff;
}

//========================
//���_���̎擾
//========================
int CObjectMesh::GetNumVtx()
{
	return m_NumVtx;
}

//========================
//�e�N�X�`�����蓖��
//========================
void CObjectMesh::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}