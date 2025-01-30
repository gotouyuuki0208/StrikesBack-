//==========================
// 
//�v���R���p�C���ς݃w�b�_�[[Pch.h]
// Author Yuki Goto
//
//==========================
#pragma once

//include
#include<windows.h>
#include"d3dx9.h"//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0X0800)//�r���h���̌x���Ώ��p�}�N��
#include"dinput.h"//���͏����ɕK�v
#include"xaudio2.h"//�T�E���h�����ɕK�v
#include"Xinput.h"//�W���C�p�b�h�����ɕK�v
#include<assert.h>
#include<iostream>
#include<fstream>
#include<random>
#include<string>
#include<cmath>
#include<iterator>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

using namespace std;

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"xinput.lib")//�W���C�p�b�h�����ɕK�v

//�}�N����`
#define SCREEN_WIDTH (1280)//�E�C���h�E�̕�
#define SCREEN_HEIGHT (720)//����
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define CLASS_NAME "windowClass"//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "Strikes Back"//�E�C���h�E�̖��O

#ifdef _DEBUG
#define DBG_NEW new (_NORMAL_BLOCK , __FILE__, __LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

//���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;//���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
}VERTEX_2D;

//���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	D3DXVECTOR3 nor;//�@���x�N�g��
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
}VERTEX_3D;