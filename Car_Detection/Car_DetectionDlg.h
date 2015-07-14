
// Car_DetectionDlg.h : ͷ�ļ�
//

#pragma once
#include "CvvImage.h"
#include "afxwin.h"
#include "math.h"
#include <cv.h>
#include <highgui.h>
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/opencv.hpp" 
// CCar_DetectionDlg �Ի���
using namespace cv;
using namespace std;

class CCar_DetectionDlg : public CBCGPDialog
{
// ����
public:
	CCar_DetectionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CAR_DETECTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnGaugeClick(WPARAM wp, LPARAM lp);
	afx_msg void OnBnClickedStopstartBtn();
	afx_msg void OnBnClickedStopstartBtn2();
	DECLARE_MESSAGE_MAP()
public:
	void BCGPInit(void);//�ؼ���ʼ������
	void VideoInit(void);
	CvvImage m_ShowArea_Prime;//ԭʼ������ʾ����
	CBCGPEdit m_Edit_Route_Ctl;//��Ƶ·��
	CBCGPSwitchCtrl m_Switch_ROUTE;//��Ƶ�򿪿���
	BOOL m_switch_ROUTE_State;//��ʾ·�����ر�־λ
	Mat m_PrimeFrame;//ԭʼ֡����
	CBCGPButton m_VIDEO_OpenBTN;//��һ�Ű�ť
	CBCGPButton m_VIDEO_OpenBTN_Pre;//��һ�Ű�ť
	CString m_PrimePicture_Route;//����ͼƬ��ԭʼ·��
	CString m_PrimePicture_Route_SubNum;//����ͼƬ��ԭʼ·����ȥ���ż�����
	CString m_PrimePicture_Route_Format;//����ͼƬ�ļ���ʽ
	int m_PrimePicture_Route_Num;//����ͼƬ��·��С��
	
	// ����ͼƬӵ��״��
	void m_SetCrowedPic(void);
	afx_msg void OnBnClickedBtnAllinit();

	Size m_Prime_Pic_Size;
};
