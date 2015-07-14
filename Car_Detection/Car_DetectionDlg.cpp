
// Car_DetectionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Car_Detection.h"
#include "Car_DetectionDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define FRAME_WIDTH 230*2//480
#define FRAME_HEIGHT 168*2//360

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCar_DetectionDlg �Ի���




CCar_DetectionDlg::CCar_DetectionDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CCar_DetectionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	EnableVisualManagerStyle(TRUE, TRUE);
}

void CCar_DetectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VideoAddr, m_Edit_Route_Ctl);
	DDX_Control(pDX, IDC_Switch_OpenVideo, m_Switch_ROUTE);
	DDX_Control(pDX, ID_STOPSTART_BTN, m_VIDEO_OpenBTN);
	DDX_Control(pDX, ID_STOPSTART_BTN_PRE, m_VIDEO_OpenBTN_Pre);
}

BEGIN_MESSAGE_MAP(CCar_DetectionDlg, CBCGPDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_REGISTERED_MESSAGE(BCGM_ON_GAUGE_CLICK, OnGaugeClick)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(ID_STOPSTART_BTN, &CCar_DetectionDlg::OnBnClickedStopstartBtn)
	ON_BN_CLICKED(ID_STOPSTART_BTN_PRE, &CCar_DetectionDlg::OnBnClickedStopstartBtn2)
	ON_BN_CLICKED(IDC_BTN_ALLINIT, &CCar_DetectionDlg::OnBnClickedBtnAllinit)
END_MESSAGE_MAP()


// CCar_DetectionDlg ��Ϣ�������
BOOL CCar_DetectionDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	BCGPInit();//���ƿؼ���ʼ
	VideoInit();
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
void CCar_DetectionDlg::BCGPInit(void)
{
	//switch init
	CBCGPSwitchColors colorsVert;
	colorsVert.m_brFillOn = CBCGPBrush(CBCGPColor::Green, CBCGPColor::YellowGreen, CBCGPBrush::BCGP_GRADIENT_HORIZONTAL);
	colorsVert.m_brFillOff = CBCGPBrush(CBCGPColor::DarkRed, CBCGPColor::Red, CBCGPBrush::BCGP_GRADIENT_HORIZONTAL);
	colorsVert.m_brFillThumb = CBCGPBrush(CBCGPColor::LightGray, CBCGPColor::White, CBCGPBrush::BCGP_GRADIENT_RADIAL_TOP_LEFT);
	colorsVert.m_brLabelOff = CBCGPBrush(CBCGPColor::White);

	m_switch_ROUTE_State=FALSE;
	m_Switch_ROUTE.GetSwitch()->SetID(IDC_Switch_OpenVideo);
	m_Switch_ROUTE.GetSwitch()->SetColors(colorsVert);
	m_Switch_ROUTE.GetSwitch()->EnableOnOffLabels();
	m_Switch_ROUTE.GetSwitch()->SetStyle(CBCGPSwitchImpl::BCGP_SWITCH_CIRCLE);
}
void CCar_DetectionDlg::VideoInit(void)
{
	CString VideoAddrStr;
	VideoAddrStr=theApp.GetString(L"VideoAddress");
	m_Edit_Route_Ctl.EnableFileBrowseButton (NULL,L"(*.jpg;*.png;*.bmp;*.jpeg;)|*.jpg;*.png;*.bmp;*jpeg||");//��ȡ·����ʽ����
	m_Edit_Route_Ctl.SetWindowTextW(VideoAddrStr);
	m_ShowArea_Prime.m_LockRect(GetDlgItem(IDC_VideoRect));//�󶨵�Picture�ؼ�
	m_PrimeFrame.create(Size(FRAME_WIDTH,FRAME_HEIGHT),CV_8UC3);
}
void CCar_DetectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CBCGPDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCar_DetectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CBCGPDialog::OnPaint();
		//�ڴ����ػ�ʱ����ǰ·����ͼƬ���ؽ���

	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCar_DetectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CCar_DetectionDlg::OnGaugeClick(WPARAM wp, LPARAM /*lp*/)
{
	int nID = (int)wp;
	switch (nID)
	{
		case IDC_Switch_OpenVideo:
			{
				if(m_switch_ROUTE_State){
					//�ر�ͼƬ,���Խ��в������ã�ROI������£��������
					m_switch_ROUTE_State=FALSE;
					m_Edit_Route_Ctl.EnableWindow(TRUE);
				}
				else{
					//��ֹ��·�����ROI���������ܲ��
					m_switch_ROUTE_State=TRUE;
					m_Edit_Route_Ctl.GetWindowTextW(m_PrimePicture_Route);
					theApp.WriteString (L"VideoAddress",m_PrimePicture_Route);

					m_Edit_Route_Ctl.EnableWindow(FALSE);
					String VideoAddress=CT2A(m_PrimePicture_Route.GetBuffer());
					Mat Input=imread(VideoAddress);
					m_Prime_Pic_Size.width=Input.size().width;
					m_Prime_Pic_Size.height=Input.size().height;

					//��ͼƬ��ַ���д���
					int IndexTemp=m_PrimePicture_Route.Find('(');
					m_PrimePicture_Route_SubNum=m_PrimePicture_Route.Left(IndexTemp);
					CString InsideSubNum=m_PrimePicture_Route.Right(m_PrimePicture_Route.GetLength()-IndexTemp);
					IndexTemp=InsideSubNum.Find(')');
					m_PrimePicture_Route_Format=InsideSubNum.Right(InsideSubNum.GetLength()-IndexTemp-1);
					InsideSubNum=InsideSubNum.Left(IndexTemp);
					InsideSubNum=InsideSubNum.Right(1);
					m_PrimePicture_Route_Num=_ttoi(InsideSubNum);
					resize(Input,m_PrimeFrame,Size(FRAME_WIDTH,FRAME_HEIGHT));//����
					m_ShowArea_Prime.m_Mat2Rect(Input);//��ʾ�ڿؼ���
				}
			}
		break;
	}
	return 0L;
}
bool G_ifCrowed=false;//����ӵ�±�־
bool G_ifAllInit=false;//ȫ����ʼ��־λ
void CCar_DetectionDlg::OnBnClickedStopstartBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��û����������ʱ���ܽ����������

	if(!m_switch_ROUTE_State)return;
	
	m_SetCrowedPic();

	m_PrimePicture_Route.Format(L"%s(%d)%s",m_PrimePicture_Route_SubNum,++m_PrimePicture_Route_Num,m_PrimePicture_Route_Format);
	String addr=CT2A(m_PrimePicture_Route.GetBuffer());
	Mat Input=imread(addr); 

	if(!Input.data)
	{//���+1�����������¶�ȡԭͼ
		m_PrimePicture_Route_Num=1;
		m_PrimePicture_Route.Format(L"%s(%d)%s",m_PrimePicture_Route_SubNum,m_PrimePicture_Route_Num,m_PrimePicture_Route_Format);
		addr=CT2A(m_PrimePicture_Route.GetBuffer());
		Input=imread(addr);
		G_ifAllInit=false;
	}

	m_PrimePicture_Route=addr.c_str();
	m_Edit_Route_Ctl.SetWindowTextW(m_PrimePicture_Route);

	UpdateData(false);

	resize(Input,m_PrimeFrame,Size(FRAME_WIDTH,FRAME_HEIGHT));//����
	m_ShowArea_Prime.m_Mat2Rect(m_PrimeFrame);//��ʾ�ڿؼ���
	G_ifCrowed=false;
}
void CCar_DetectionDlg::OnBnClickedStopstartBtn2()
{//�����һ�Ű�ť
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_switch_ROUTE_State)return;
	G_ifCrowed=true;
	OnBnClickedStopstartBtn();
}

// ����ͼƬӵ��״��
void CCar_DetectionDlg::m_SetCrowedPic(void)
{
	unsigned char Color=0;
	if(G_ifCrowed)//ӵ�µ����
		Color=255;
	for(int i=0;i<60;i++)
	{
		for(int j=0;j<20;j++)
		{
			m_PrimeFrame.at<unsigned char>(Point(i,j))=Color;
		}
	}
	m_PrimePicture_Route.Format(L"%s(%d).png",m_PrimePicture_Route_SubNum,m_PrimePicture_Route_Num);
	String addr=CT2A(m_PrimePicture_Route.GetBuffer());
	Mat write_Mat;
	resize(m_PrimeFrame,write_Mat,m_Prime_Pic_Size);
	imwrite(addr,write_Mat);
}

//ȫ����ʼ��Ϊ��ӵ��
void CCar_DetectionDlg::OnBnClickedBtnAllinit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_switch_ROUTE_State)return;

	G_ifAllInit=true;
	clock_t start,finish;
	double totaltime;
	int NumOfPicture=0;
	
	start=clock();
	while(G_ifAllInit)
	{
		OnBnClickedStopstartBtn();
		NumOfPicture++;
	}
	finish=clock();

	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	double averagetime=totaltime/NumOfPicture*1000;
	CString str;
	str.Format(L"��Ƭ����Ϊ��%d\r\n�ܹ�����ʱ��Ϊ��%fs\r\n����ƽ������ʱ��Ϊ��%fms",NumOfPicture,totaltime,averagetime);
	BCGPMessageBox(L"���������Ƭ�������\r\n"+str);
}
