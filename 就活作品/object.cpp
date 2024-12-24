//==========================
// 
// �I�u�W�F�N�g�Ǘ�[object.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"object.h"

//�ÓI�����o�̏�����
int CObject::m_nNumAll = 0;
CObject* CObject::m_apObject[PRIORITY][MAX_OBJECT] = {};
CObject* CObject::m_pTop[PRIORITY] = {};//�ŏ��̃I�u�W�F�N�g
CObject* CObject::m_pCur[PRIORITY] = {};//�Ō���̃I�u�W�F�N�g
//========================
//�`��D��ݒ�
//========================
CObject::CObject(int nPriority) :m_nID(0), m_pNext(nullptr), m_pPrev(nullptr), m_bDeath(false)
{
	m_Type = TYPE::NONE;//�I�u�W�F�N�g�^�C�v
	
	m_nPriority = nPriority;//�`��D��x�ݒ�

	if (m_pTop[m_nPriority] == nullptr)
	{//�ŏ��̃I�u�W�F�N�g���o�^����ĂȂ�

		m_pTop[m_nPriority] = this;//�ŏ��̃I�u�W�F�N�g�ɓo�^
		m_pCur[m_nPriority] = this;//���݂̃I�u�W�F�N�g�ɓo�^
	}
	else if(m_pTop[m_nPriority] != nullptr)
	{//�ŏ��̃I�u�W�F�N�g���o�^����Ă���

		m_pPrev = m_pCur[m_nPriority];//�O�̃I�u�W�F�N�g�ɍŌ���̃I�u�W�F�N�g��o�^
		m_pPrev->m_pNext = this;//�O�̃I�u�W�F�N�g�̎��Ɏ�����o�^
		m_pCur[m_nPriority] = this;//�Ō���̃I�u�W�F�N�g�Ɏ�����o�^
	}

	

	/*for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[m_nPriority][i] == nullptr)
		{
			m_apObject[m_nPriority][i] = this;
			m_nID = i;
			m_nNumAll++;
			break;
		}
	}*/

}

//========================
//�f�X�g���N�^
//========================
CObject::~CObject()
{
	
}

//========================
//�S�I�u�W�F�N�g���
//========================
void CObject::ReleaseAll(void)
{
	/*for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		for (int obj = 0; obj < MAX_OBJECT; obj++)
		{
			if (m_apObject[nPriority][obj] != nullptr)
			{
				m_apObject[nPriority][obj]->Uninit();
				m_apObject[i]->Release();
				m_apObject[nPriority][obj] = nullptr;
			}
		}
	}*/

	for (int i = 0; i < PRIORITY; i++)
	{
		CObject* pObj = m_pTop[i];

		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;

			pObj->Uninit();
			
			pObj = pNext;
		}
	}
	

	//���S�t���O�������Ă�I�u�W�F�N�g���폜
	ReleseDeath();
}

//========================
//�S�I�u�W�F�N�g�X�V
//========================
void CObject::UpdateAll(void)
{
	/*for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		for (int obj = 0; obj < MAX_OBJECT; obj++)
		{
			if (m_apObject[nPriority][obj] != nullptr)
			{
				m_apObject[nPriority][obj]->Update();
			}
		}
	}*/

	for (int i = 0; i < PRIORITY; i++)
	{
		CObject* pObj = m_pTop[i];

		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;

			pObj->Update();

			pObj = pNext;
		}

	}
	
	//���S�t���O�������Ă�I�u�W�F�N�g���폜
	ReleseDeath();
}

//========================
//�S�I�u�W�F�N�g�`��
//========================
void CObject::DrawAll(void)
{
	/*for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		for (int obj = 0; obj < MAX_OBJECT; obj++)
		{
			if (m_apObject[nPriority][obj] != nullptr)
			{
				m_apObject[nPriority][obj]->Draw();
			}
		}
	}*/

	//���S�t���O�������Ă�I�u�W�F�N�g���폜
	ReleseDeath();

	for (int i = 0; i < PRIORITY; i++)
	{
		CObject* pObj = m_pTop[i];

		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;

			pObj->Draw();

			pObj = pNext;
		}
	}
}

//========================
//�������g�̉��
//========================
void CObject::Release(void)
{
	/*int nID = m_nID;
	int nPriority = m_nPriority;*/

	/*if (m_apObject[nPriority][nID] != nullptr)
	{
		delete m_apObject[nPriority][nID];
		m_apObject[nPriority][nID] = nullptr;
		m_nNumAll--;
	}*/

	//���S�t���O�𗧂Ă�
	SwitchDeath();
}

//========================
//�I�u�W�F�N�g�擾
//========================
CObject* CObject::GetObj(CObject* Object, int priority)
{
	if (Object != nullptr)
	{
		return Object->m_pNext;
	}

	return m_pTop[priority];
}

//========================
//�^�C�v�擾
//========================
CObject::TYPE CObject::GetType(void)
{
	return m_Type;
}

//========================
//�^�C�v�ݒ�
//========================
void CObject::SetType(TYPE type)
{
	m_Type = type;
}

//========================
//���̃I�u�W�F�N�g���擾
//========================
CObject* CObject::GetNextObj()
{
	return m_pNext;
}

//========================
//�O�̃I�u�W�F�N�g���擾
//========================
CObject* CObject::GetPrevObj()
{
	return m_pPrev;
}

//========================
//���S�t���O�̐؂�ւ�
//========================
void CObject::SwitchDeath()
{
	m_bDeath = true;
}

//========================
//���S�t���O�������Ă�I�u�W�F�N�g�폜
//========================
void CObject::ReleseDeath()
{

	for (int i = 0; i < PRIORITY; i++)
	{
		CObject* pObj = m_pTop[i];

		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;

			if (pObj->m_bDeath)
			{
				pObj->DisengageList();//�t���O����폜
				delete pObj;
			}
			pObj = pNext;
		}
	}
}

//========================
//���X�g����؂藣��
//========================
void CObject::DisengageList()
{
	if (m_pTop[m_nPriority] == this)
	{//�������ŏ��̃I�u�W�F�N�g

		if (m_pNext != nullptr)
		{//���̃I�u�W�F�N�g������

			//�ŏ��̃I�u�W�F�N�g�����̃I�u�W�F�N�g�ɕς���
			m_pTop[m_nPriority] = m_pNext;
			m_pNext->m_pPrev = nullptr;
		}
		if (m_pNext == nullptr)
		{
			m_pTop[m_nPriority] = nullptr;
			m_pCur[m_nPriority] = nullptr;
		}
	}
	else if (m_pCur[m_nPriority] == this)
	{//�������Ō�̃I�u�W�F�N�g

		//�O�̃I�u�W�F�N�g���Ō�ɓo�^����
		m_pCur[m_nPriority] = m_pPrev;
		m_pPrev->m_pNext = nullptr;

	}
	else
	{
		if (m_pPrev != nullptr)
		{
			//�O�̃I�u�W�F�N�g�ɓo�^����Ă��鎟�̃I�u�W�F�N�g�������̎��ɂ���
			m_pPrev->m_pNext = m_pNext;
		}
		
		if (m_pNext != nullptr)
		{//���̃I�u�W�F�N�g������

			//���̃I�u�W�F�N�g�ɓo�^����Ă�O�̃I�u�W�F�N�g�������̑O�ɂ���
			m_pNext->m_pPrev = m_pPrev;
		}
	}
}