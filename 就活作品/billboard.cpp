//==========================
//
// �r���{�[�h�̕`�揈��[billboard.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"billboard.h"
#include"manager.h"

//�ÓI�����o������
const int CBillBoard::PRIORITY = 1;//�`��D��x

//========================
//�R���X�g���N�^
//========================
CBillBoard::CBillBoard(int nPriority) :CObjectgame(nPriority)
{
	m_pTexture = nullptr;//�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = nullptr;//���_�o�b�t�@�ւ̃|�C���^
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�傫��
	m_cor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�F�̐ݒ�
	m_nCntAnim = 0;//�A�j���[�V�����J�E���^�[
	m_nPatternAnim = 0;//�e�N�X�`���A�j���[�V�����̕�����
	m_aPosTexV = 0.0f;
}

//========================
//�f�X�g���N�^
//========================
CBillBoard::~CBillBoard()
{

}

//========================
//�����ݒ�
//========================
HRESULT CBillBoard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\block000.jpg", &m_pTexture);

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
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, -m_size.y, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
void CBillBoard::Uninit(void)
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
void CBillBoard::Update()
{
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, -m_size.y, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_cor;
	pVtx[1].col = m_cor;
	pVtx[2].col = m_cor;
	pVtx[3].col = m_cor;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//========================
//�`�揈��
//========================
void CBillBoard::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	D3DXMATRIX mtxTrans,a;//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;//�r���[�}�g���b�N�X�擾�p

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&GetMtxWorld());
	
	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	
	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&GetMtxWorld(), NULL, &mtxView);//�t�s������߂�
	GetMtxWorld()._41 = 0.0f;
	GetMtxWorld()._42 = 0.0f;
	GetMtxWorld()._43 = 0.0f;
	
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�r���{�[�h�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Z�o�b�t�@�ɏ�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//========================
//�e�N�X�`�����蓖��
//========================
void CBillBoard::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//========================
//�I�u�W�F�N�g3D����
//========================
CBillBoard* CBillBoard::Create(D3DXVECTOR3 pos)
{
	CBillBoard* pBillBoard = DBG_NEW CBillBoard;

	pBillBoard->SetPos(pos);
	pBillBoard->SetSize(D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	pBillBoard->Init();

	return pBillBoard;
}

//========================
//�傫���ݒ�
//========================
void CBillBoard::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//========================
//�傫�����擾
//========================
D3DXVECTOR3& CBillBoard::GetSize()
{
	return m_size;
}

//========================
//�F�̐ݒ�
//========================
void CBillBoard::SetCor(D3DXCOLOR cor)
{
	m_cor = cor;
}

//========================
//�F�̎擾
//========================
D3DXCOLOR& CBillBoard::GetCor()
{
	return m_cor;
}

//========================
//�A�j���[�V��������
//========================
void CBillBoard::Animetion(float vertical, int width)
{
	float fvertical = 1.0f / vertical;

	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_nCntAnim++;
	if (m_nCntAnim >= 5)
	{
		m_nPatternAnim++;
		if (m_nPatternAnim >= width)
		{
			m_nPatternAnim = 0;
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((1.0f / width) * m_nPatternAnim, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((1.0f / width) * (m_nPatternAnim + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((1.0f / width) * m_nPatternAnim, fvertical);
		pVtx[3].tex = D3DXVECTOR2((1.0f / width) * (m_nPatternAnim + 1), fvertical);

		m_nCntAnim = 0;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//========================
//�e�N�X�`���̃T�C�Y�ݒ�
//========================
void CBillBoard::Move()
{

	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̊J�n�ʒu�̍X�V
	m_aPosTexV += 0.0005f;

	//�e�N�X�`�����W�̍X�V	
	pVtx[0].tex = D3DXVECTOR2(0.0f + m_aPosTexV, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + m_aPosTexV, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + m_aPosTexV, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + m_aPosTexV, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//========================
//�e�N�X�`���̃T�C�Y�ݒ�
//========================
void CBillBoard::SetTexSize(float vertical, float width, float TexPos)
{
	float fvertical = 1.0f / vertical;

	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + TexPos * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(((1 / width) + TexPos * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + TexPos * 0.1f, fvertical);
	pVtx[3].tex = D3DXVECTOR2(((1 / width) + TexPos * 0.1f), fvertical);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//========================
//���_�o�b�t�@�̎擾
//========================
LPDIRECT3DVERTEXBUFFER9& CBillBoard::GetVtxBuff()
{
	return m_pVtxBuff;
}

//========================
//�e�N�X�`���̎擾
//========================
LPDIRECT3DTEXTURE9& CBillBoard::GetTex()
{
	return m_pTexture;
}