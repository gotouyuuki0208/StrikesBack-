//==========================
// 
// ���C������[main.cpp]
// Author Yuki Goto
//
//==========================
//include
#include"main.h"
#include"manager.h"

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//�E�C���h�E�v���V�[�W��
void ToggleFullscreen(HWND hWnd);

//�O���[�o���ϐ�
int g_nCountFPS = 0;
bool g_isFullscreen = false;			// �E�B���h�E��؂�ւ��邽�߂̃t���O
RECT g_windowRect;						// �E�B���h�E��؂�ւ��邽�߂̕ϐ�

//==========================
//���C���֐�
//==========================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)

	};

	HWND hWnd;
	MSG msg;

	RECT rect = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };

	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, (rect.right - rect.left), (rect.bottom - rect.top), NULL, NULL, hInstance, NULL);

	DWORD dwCurrentTime;//���ݎ���
	DWORD dwExecLastTime;//�Ō�ɏ�����������
	DWORD dwFrameCount;//�t���[���J�E���g
	DWORD dwFPSLastTime;//�Ō��FPS���v����������

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;//����������
	dwExecLastTime = timeGetTime();//���ݎ������擾(�ۑ�)

	//������������
	CManager *pManager = CManager::GetInstance();

	if (FAILED(pManager->Init(hInstance,hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}	
	

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烋�[�v�𔲂��o��
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();//���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;//FPS���v������������ۑ�
				dwFrameCount = 0;//�t���[���J�E���g���N���A
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��

				dwExecLastTime = dwCurrentTime;//�����J�n�̎���[���ݎ���]��ۑ�

				//�X�V����
				pManager->Update();

				//�`�揈��
				pManager->Draw();

				dwFrameCount++;//�t���[���J�E���g�����Z
			}

		}
	}

	//����\��߂�
	timeEndPeriod(1);

	//�I������
	pManager->Uninit();

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//==========================
//�E�C���h�E�v���V�[�W��
//==========================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);//�E�C���h�E��j������
			}
			break;

		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;

	case WM_CLOSE:
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);//�E�C���h�E��j������
		}
		else
		{
			return 0;
		}
		break;

	case WM_LBUTTONDOWN:
		SetFocus(hWnd);
		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//�K��̏�����Ԃ�
}

//===========
//fps�擾
//===========
int GetFps(void)
{
	return g_nCountFPS;
}

//============================================
// �E�B���h�E���t���X�N���[���ɕς��鏈��
//============================================
void ToggleFullscreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}