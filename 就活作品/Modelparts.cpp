//==========================
// 
// ���f���̃p�[�c�̏���[modelparts.h]
// Author Yuki Goto
//
//==========================

//include
#include"modelparts.h"
#include"manager.h"

//==========================
// �R���X�g���N�^
//==========================
CModelParts::CModelParts(void)
{
	m_ParentParts = nullptr;
	m_modelIdx = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_motionpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_motionrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;//�}�e���A���ւ̃|�C���^
	m_dwNumMat = 0;//�}�e���A���̐�
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_corDamage = false;
	D3DXMatrixIdentity(&m_mtxWorld);

	for (int i = 0; i < 100; i++)
	{
		m_Diffuse[i] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	m_Visual = nullptr;
}

//==========================
// �f�X�g���N�^
//==========================
CModelParts::~CModelParts(void)
{

}

//==========================
// �����ݒ�
//==========================
HRESULT CModelParts::Init(void)
{
	SetSize();
	return S_OK;
}

//==========================
// �I������
//==========================
void CModelParts::Uninit(void)
{

	if (m_Visual != nullptr)
	{
		m_Visual-> Uninit();
		m_Visual = nullptr;
	}

	delete this;
}

//==========================
// �X�V����
//==========================
void CModelParts::Update(void)
{
	
}

//==========================
// �`�揈��
//==========================
void CModelParts::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	CreateMtx();//�s��̍쐬

	D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxTransMotion;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	D3DXMATRIX mtxParent;

	if (m_ParentParts != nullptr)
	{
		mtxParent = m_ParentParts->m_mtxWorld;
	}
	else
	{
		//�X�P�[���ݒ�
		D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);


		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�g���b�N�X���擾
	pDevice->GetMaterial(&matDef);

	//�@���̒�����1�ɂ���
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (m_corDamage)
		{
			pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else if (!m_corDamage)
		{
			pMat[nCntMat].MatD3D.Diffuse = m_Diffuse[nCntMat];
		}
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	if (m_Visual != nullptr)
	{
		m_Visual->SetPos(D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43));
		m_Visual->Draw();
	}
}

//========================
//�s��̐���
//========================
void CModelParts::CreateMtx()
{
	D3DXMATRIX mtxRot, mtxTrans, mtxTransMotion;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	D3DXMatrixTranslation(&mtxTransMotion, m_motionpos.x, m_motionpos.y, m_motionpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransMotion);
	
}

//========================
//�I�u�W�F�N�g2D����
//========================
CModelParts* CModelParts::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModelParts* Parent, int ModelPartsNum, D3DXVECTOR3 scale)
{
	CModelParts* pModelParts = DBG_NEW CModelParts;

	//�ʒu�ݒ�
	pModelParts->m_pos = pos;
	pModelParts->m_rot = rot;
	pModelParts->SetParents(Parent);
	pModelParts->m_scale = scale;

	//���f���̐���
	CModel* pModel = CManager::GetInstance()->GetModel();

	//���f���̔ԍ���ۑ�
	pModelParts->m_modelIdx = ModelPartsNum;

	pModelParts->m_pMesh = pModel->GetMeshAdress(ModelPartsNum);
	pModelParts->m_pBuffMat = pModel->GetBuffMatAdress(ModelPartsNum);
	pModelParts->m_dwNumMat = pModel->GetNumMatAdress(ModelPartsNum);

	for (int i = 0; i < (int)pModelParts->m_dwNumMat; i++)
	{
		pModelParts->m_Diffuse[i] = pModel->GetDiffuse(ModelPartsNum, i);
	}

	//����������
	if (SUCCEEDED(pModelParts->Init()))
	{

	}

	return pModelParts;
}

//========================
//�e���f���̐ݒ�
//========================
void CModelParts::SetParents(CModelParts* Parent)
{
	m_ParentParts = Parent;
}

//========================
//�e���f�����擾
//========================
CModelParts* CModelParts::GetParent()
{
	return m_ParentParts;
}

//========================
//�ʒu�̐ݒ�
//========================
void CModelParts::SetMotionPos(D3DXVECTOR3 pos)
{
	m_motionpos = pos;
}

//========================
//���[�V�����ł̈ʒu�̎擾
//========================
D3DXVECTOR3& CModelParts::GetMotionPos()
{
	return m_motionpos;
}

//========================
//�ʒu�̐ݒ�
//========================
void CModelParts::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//========================
//�����̐ݒ�
//========================
void CModelParts::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//========================
//�ʒu�̎擾
//========================
D3DXVECTOR3& CModelParts::GetPos()
{
	return m_pos;
}

//========================
//�����̎擾
//========================
D3DXVECTOR3& CModelParts::GetRot()
{
	return m_rot;
}

//========================
//�e�p�[�c�����邩�̎擾
//========================
bool CModelParts::GetExistParent()
{
	if (m_ParentParts == nullptr)
	{
		return false;
	}

	return true;
}

//==========================
//�}�g���b�N�X�擾
//==========================
D3DXMATRIX& CModelParts::GetMtxWorld()
{
	return m_mtxWorld;
}

//==========================
//�T�C�Y�̐ݒ�
//==========================
void CModelParts::SetSize()
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

		vtx.x *= m_scale.x;
		vtx.y *= m_scale.y;
		vtx.z *= m_scale.z;
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

	//�T�C�Y��ݒ�
	/*m_vtxMax.x *= SCALIING;
	m_vtxMin.x *= SCALIING;
	m_vtxMax.y *= SCALIING;
	m_vtxMin.y *= SCALIING;
	m_vtxMax.z *= SCALIING;
	m_vtxMin.z *= SCALIING;*/

	m_Size.x = m_vtxMax.x - m_vtxMin.x;
	m_Size.y = m_vtxMax.y - m_vtxMin.y;
	m_Size.z = m_vtxMax.z - m_vtxMin.z;
}

//==========================
//���_�̍ŏ��̏ꏊ���擾
//==========================
D3DXVECTOR3& CModelParts::GetVtxMin()
{
	return m_vtxMin;
}

//==========================
//���_�̍ő�̏ꏊ���擾
//==========================
D3DXVECTOR3& CModelParts::GetVtxMax()
{
	return m_vtxMax;
}

//==========================
//�F�̐ݒ�
//==========================
void CModelParts::SetCor()
{
	m_corDamage = !m_corDamage;
}

//==========================
//���f���̔ԍ����擾
//==========================
int CModelParts::GetModelNum()
{
	return m_modelIdx;
}

//==========================
//�����蔻����������郁�b�V���𐶐�
//==========================
void CModelParts::CreateVisual(D3DXVECTOR3 pos, float radius)
{
	if (m_Visual == nullptr)
	{
		m_Visual = CCollisionVisual::Create(pos, radius);
		return;
	}

	if (m_Visual->GetRadius() != radius)
	{
		m_Visual->Uninit();
		m_Visual = CCollisionVisual::Create(pos, radius);
	}
}

//==========================
//�����蔻��̌����ڂ��폜
//==========================
void CModelParts::VisualDelete()
{
	if (m_Visual != nullptr)
	{
		m_Visual->Uninit();
		m_Visual = nullptr;
	}
}

//==========================
//�������������蔻��̏��
//==========================
CCollisionVisual* CModelParts::GetVisual()
{
	if (m_Visual != nullptr)
	{
		return m_Visual;
	}

	return nullptr;
}