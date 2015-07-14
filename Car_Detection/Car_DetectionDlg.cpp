
// Car_DetectionDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCar_DetectionDlg 对话框




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


// CCar_DetectionDlg 消息处理程序
BOOL CCar_DetectionDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	BCGPInit();//绘制控件初始
	VideoInit();
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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
	m_Edit_Route_Ctl.EnableFileBrowseButton (NULL,L"(*.jpg;*.png;*.bmp;*.jpeg;)|*.jpg;*.png;*.bmp;*jpeg||");//获取路径格式设置
	m_Edit_Route_Ctl.SetWindowTextW(VideoAddrStr);
	m_ShowArea_Prime.m_LockRect(GetDlgItem(IDC_VideoRect));//绑定到Picture控件
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCar_DetectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CBCGPDialog::OnPaint();
		//在窗口重绘时将当前路径的图片加载进来

	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
					//关闭图片,可以进行参数设置，ROI区域更新，距离测量
					m_switch_ROUTE_State=FALSE;
					m_Edit_Route_Ctl.EnableWindow(TRUE);
				}
				else{
					//禁止线路变更，ROI锁定，不能测距
					m_switch_ROUTE_State=TRUE;
					m_Edit_Route_Ctl.GetWindowTextW(m_PrimePicture_Route);
					theApp.WriteString (L"VideoAddress",m_PrimePicture_Route);

					m_Edit_Route_Ctl.EnableWindow(FALSE);
					String VideoAddress=CT2A(m_PrimePicture_Route.GetBuffer());
					Mat Input=imread(VideoAddress);
					m_Prime_Pic_Size.width=Input.size().width;
					m_Prime_Pic_Size.height=Input.size().height;

					//将图片地址进行处理
					int IndexTemp=m_PrimePicture_Route.Find('(');
					m_PrimePicture_Route_SubNum=m_PrimePicture_Route.Left(IndexTemp);
					CString InsideSubNum=m_PrimePicture_Route.Right(m_PrimePicture_Route.GetLength()-IndexTemp);
					IndexTemp=InsideSubNum.Find(')');
					m_PrimePicture_Route_Format=InsideSubNum.Right(InsideSubNum.GetLength()-IndexTemp-1);
					InsideSubNum=InsideSubNum.Left(IndexTemp);
					InsideSubNum=InsideSubNum.Right(1);
					m_PrimePicture_Route_Num=_ttoi(InsideSubNum);
					resize(Input,m_PrimeFrame,Size(FRAME_WIDTH,FRAME_HEIGHT));//缩放
					m_ShowArea_Prime.m_Mat2Rect(Input);//显示在控件内
				}
			}
		break;
	}
	return 0L;
}
bool G_ifCrowed=false;//设置拥堵标志
bool G_ifAllInit=false;//全部初始标志位
void CCar_DetectionDlg::OnBnClickedStopstartBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	//当没有锁定参数时不能进行运算操作

	if(!m_switch_ROUTE_State)return;
	
	m_SetCrowedPic();

	m_PrimePicture_Route.Format(L"%s(%d)%s",m_PrimePicture_Route_SubNum,++m_PrimePicture_Route_Num,m_PrimePicture_Route_Format);
	String addr=CT2A(m_PrimePicture_Route.GetBuffer());
	Mat Input=imread(addr); 

	if(!Input.data)
	{//如果+1不存在则重新读取原图
		m_PrimePicture_Route_Num=1;
		m_PrimePicture_Route.Format(L"%s(%d)%s",m_PrimePicture_Route_SubNum,m_PrimePicture_Route_Num,m_PrimePicture_Route_Format);
		addr=CT2A(m_PrimePicture_Route.GetBuffer());
		Input=imread(addr);
		G_ifAllInit=false;
	}

	m_PrimePicture_Route=addr.c_str();
	m_Edit_Route_Ctl.SetWindowTextW(m_PrimePicture_Route);

	UpdateData(false);

	resize(Input,m_PrimeFrame,Size(FRAME_WIDTH,FRAME_HEIGHT));//缩放
	m_ShowArea_Prime.m_Mat2Rect(m_PrimeFrame);//显示在控件内
	G_ifCrowed=false;
}
void CCar_DetectionDlg::OnBnClickedStopstartBtn2()
{//点击上一张按钮
	// TODO: 在此添加控件通知处理程序代码
	if(!m_switch_ROUTE_State)return;
	G_ifCrowed=true;
	OnBnClickedStopstartBtn();
}

// 设置图片拥堵状况
void CCar_DetectionDlg::m_SetCrowedPic(void)
{
	unsigned char Color=0;
	if(G_ifCrowed)//拥堵的情况
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

//全部初始化为不拥堵
void CCar_DetectionDlg::OnBnClickedBtnAllinit()
{
	// TODO: 在此添加控件通知处理程序代码
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
	str.Format(L"相片总数为：%d\r\n总共处理时间为：%fs\r\n单张平均处理时间为：%fms",NumOfPicture,totaltime,averagetime);
	BCGPMessageBox(L"相册所有照片处理结束\r\n"+str);
}
