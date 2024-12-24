//==========================
// 
// �|���S���̕`�揈��[object2D.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"object2D.h"
#include"manager.h"

//�ÓI�����o������
const int CObject2D::PRIORITY = 2;//�`��D��x

//========================
//�R���X�g���N�^
//========================
CObject2D::CObject2D(int nPriority):CObjectgame(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;

	m_cor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_fAngle = 0.0f;
	m_fLength = 0.0f;//�Ίp���̒���
	m_fVertical = 0.0f;//�c�̃T�C�Y
	m_fWidth = 0.0f;//���̃T�C�Y
	m_nCntAnim = 0;//�e�N�X�`���A�j���[�V�����̐؂�ւ�
	m_nPatternAnim = 0;//�e�N�X�`���A�j���[�V�����̕�����
}

//========================
//�f�X�g���N�^
//========================
CObject2D::~CObject2D()
{

}

//========================
//�����ݒ�
//========================
HRESULT CObject2D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(GetPos().x - m_fWidth, GetPos().y - m_fVertical, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + m_fWidth, GetPos().y - m_fVertical, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x - m_fWidth, GetPos().y + m_fVertical, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetPos().x + m_fWidth, GetPos().y + m_fVertical, 0.0f);

	//pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[0].pos.z = 0.0f;											 
	//																 
	//pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[1].pos.z = 0.0f;

	//pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + -(D3DX_PI * 0.5f)) * m_fWidth / 2;
	//pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + -(D3DX_PI * 0.5f)) * m_fWidth / 2;
	//pVtx[2].pos.z = 0.0f;

	//pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI * 0.5f)) * m_fWidth / 2;
	//pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI * 0.5f)) * m_fWidth / 2;
	//pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
void CObject2D::Uninit(void)
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
void CObject2D::Update()
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_cor;
	pVtx[1].col = m_cor;
	pVtx[2].col = m_cor;
	pVtx[3].col = m_cor;
	
	pVtx[0].pos = D3DXVECTOR3(GetPos().x - m_fWidth, GetPos().y - m_fVertical, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + m_fWidth, GetPos().y - m_fVertical, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x - m_fWidth, GetPos().y + m_fVertical, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetPos().x + m_fWidth, GetPos().y + m_fVertical, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//========================
//�A�j���[�V��������
//========================
void CObject2D::Animetion(float vertical, int width)
{
	float fvertical = 1.0f / vertical;

	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

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
//�`�揈��
//========================
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//========================
//�I�u�W�F�N�g2D����
//========================
CObject2D* CObject2D::Create(void)
{
	CObject2D* pObject2D = DBG_NEW CObject2D;

	pObject2D->Init();

	return pObject2D;
}

//========================
//�e�N�X�`�����蓖��
//========================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}


//========================
//�Ίp���̒����擾
//========================
float CObject2D::GetLength(void)
{
	return m_fLength;
}

//========================
//�F�̐ݒ�
//========================
void CObject2D::SetCor(D3DCOLOR cor)
{
	m_cor = cor;
}

//========================
//�F�̎擾
//========================
D3DCOLOR CObject2D::GetCor()
{
	return m_cor;
}

//========================
//�傫���ݒ�
//========================
void CObject2D::SetSize(float vertical, float width)
{
	m_fWidth = width;//���̒����ݒ�

	m_fVertical = vertical;//�c�̒����ݒ�

	m_fAngle = atan2f(width, (vertical * 2.0f));//�Ίp���̊p�x�ݒ�

	m_fLength = sqrtf(width * width + (vertical * 2.0f) * (vertical * 2.0f)) / 2;//�Ίp���̒����ݒ�
}

//========================
//�e�N�X�`���̑傫���ݒ�
//========================
void CObject2D::SetTexSize(float vertical, float width, float TexPos)
{
	float fvertical = 1.0f / vertical;

	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

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
//���_�o�b�t�@�̃|�C���^���擾
//========================
LPDIRECT3DVERTEXBUFFER9 CObject2D::GetVtxBuff()
{
	return m_pVtxBuff;
}

//========================
//���̃T�C�Y���擾
//========================
float CObject2D::GetWidth()
{
	return m_fWidth;
}

//========================
//�c�̃T�C�Y���擾
//========================
float CObject2D::GetVertical()
{
	return m_fVertical;
}