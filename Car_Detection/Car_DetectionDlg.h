
// Car_DetectionDlg.h : 头文件
//

#pragma once
#include "CvvImage.h"
#include "afxwin.h"
#include "math.h"
#include <cv.h>
#include <highgui.h>
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/opencv.hpp" 
// CCar_DetectionDlg 对话框
using namespace cv;
using namespace std;

class CCar_DetectionDlg : public CBCGPDialog
{
// 构造
public:
	CCar_DetectionDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CAR_DETECTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnGaugeClick(WPARAM wp, LPARAM lp);
	afx_msg void OnBnClickedStopstartBtn();
	afx_msg void OnBnClickedStopstartBtn2();
	DECLARE_MESSAGE_MAP()
public:
	void BCGPInit(void);//控件初始化函数
	void VideoInit(void);
	CvvImage m_ShowArea_Prime;//原始数据显示区域
	CBCGPEdit m_Edit_Route_Ctl;//视频路径
	CBCGPSwitchCtrl m_Switch_ROUTE;//视频打开开关
	BOOL m_switch_ROUTE_State;//表示路径开关标志位
	Mat m_PrimeFrame;//原始帧数据
	CBCGPButton m_VIDEO_OpenBTN;//下一张按钮
	CBCGPButton m_VIDEO_OpenBTN_Pre;//上一张按钮
	CString m_PrimePicture_Route;//读入图片的原始路径
	CString m_PrimePicture_Route_SubNum;//读入图片的原始路径减去括号及数字
	CString m_PrimePicture_Route_Format;//读入图片文件格式
	int m_PrimePicture_Route_Num;//读入图片的路径小标
	
	// 设置图片拥堵状况
	void m_SetCrowedPic(void);
	afx_msg void OnBnClickedBtnAllinit();

	Size m_Prime_Pic_Size;
};
