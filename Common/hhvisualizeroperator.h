#ifndef HHVISUALIZEROPERATOR_H
#define HHVISUALIZEROPERATOR_H

#include "lib_booth.h"
//#include "qedit.h"
#ifdef WIN32
#include <atlbase.h>
#include "DShow.h"
#endif


#include <QObject>
#include <QWidget>
#include <QMap>

#define SAFE_RELEASE(x) {if(NULL != x){x->Release(); x=NULL;}}

class HHVisualizerWidget;
class IMoniker;
class ICaptureGraphBuilder2;
class IGraphBuilder;
class IMediaControl;
class IVideoWindow;
class IBaseFilter;
class IMediaEventEx;
class IPin;
class ISettingsInterface;

class LIB_EXPORT_BOOTH HHVisualizerOperator : public QObject /*, public ISampleGrabberCB*/{
    Q_OBJECT
public:
    HHVisualizerOperator();
    HHVisualizerOperator( WId wid );
    virtual ~HHVisualizerOperator();

    bool initCamera();
    bool start();
    bool stop();
    void changeRectSize();
    bool changeCamera();
    bool restartCamera();
    /*
     *  getResolutions()
     *  返回当前摄像头支持的分辨率列表，列表最后一项为当前分辨率的宽度
     */
    QStringList getResolutions();

    /*
     *  changeResolution
     *  修改分辨率
     *  width: 目标分辨率的宽度
     *  strResolution:目标分辨率（100x100）
     *  返回true标示修改成功并捕获到相应画面
     */
    bool changeResolution(int width);
    bool changeResolution(QString strResolution);

    /*
     *  getColorSpaces()
     *  返回当前摄像头支持的颜色空间列表，列表最后一项为当前颜色空间
     */
    QStringList getColorSpaces();
    bool changeColorSpaces(QString colorSpace);

    //可控展台通过DLL操作
    void optArmLight();
    void optBottomLight();
    void optCloseLight();
    void optAutoFocus();
    void optAddFocus();
    void optSubFocus();

    bool rotateOperation(QString strDegree);
    bool getRotateFilterState();
    QString getCurrentRotateDegree();

    /*
    HRESULT STDMETHODCALLTYPE SampleCB(double SampleTime, IMediaSample *pSample);
    HRESULT STDMETHODCALLTYPE BufferCB(double SampleTime, BYTE *pBuffer, long BufferLen);
    */
    bool isGaoPaiYiMi();
    bool isHaiTianWei();
    float getDigitalFocusRate();
signals:
    void sigCameraCount(int count);
    /*
     * sigCanControl 通知连接的展台是否可控，及支持的灯类型
     * bCtrl         true:可控展台， false:不可控-此时lightType无效
     * lightType     0:底灯壁灯均不支持； 1:支持底灯； 2:支持壁灯； -1:默认都支持
     */
    void sigCanControl(bool bCtrl, int lightType);
    void sigCameraLost();

private slots:
    void sltCameraLost();

private:
    bool initGraphFilters();
    bool initIMoniker();
    bool discriminateHHTDevice(QString devName = "");
    bool initHHTDeviceLightInfo();
    void releaseComInstance();
    bool getCameraResolutions();
    bool setOutPinParams();
    void doDigitalFocus(bool isAdd);

    bool rotate(QString strDegree);
    void deleteGaoPaiYiSpecifyRes();



#ifdef WIN32
    void deleteMediaType(AM_MEDIA_TYPE *mt);
    void setRenderWndSize(RECT rc);
    GUID getColorSpaceGUID();
#endif

    bool initRotateFilter();

private:
#ifdef WIN32
    HWND                    m_visualizerWnd;
#endif
    HHVisualizerWidget      *m_visualizerWidget;

    IMoniker                *m_cameraMoniker;
    ICaptureGraphBuilder2   *m_capGraphBuilder2;
    IGraphBuilder           *m_graphBuilder;
    IMediaControl           *m_mediaCtrl;
    IVideoWindow            *m_renderVideoWnd;
    IBaseFilter             *m_srcFilter;
    IMediaEventEx           *m_eventEx;

    int                     m_devIndex;
    int                     m_cameraNum;
    bool                    m_isGaoPaiYi;
    bool                    m_isHHTDev;//可控设备标志

    //鸿合展台和高拍仪配置项，保存ResolutionConfig.ini配置文件中的配置值
    QString                 m_hhtConfigCP;//颜色空间，0-使用全部；
    QString                 m_hhtConfigResolution;//默认显示分辨率，0-默认通用值
    QString                 m_hhtFullScreen;
    QString                 m_hhtAdd;
    QMap<int, int>          m_mapResolution;
    QStringList             m_listResolution;//width x height,给菜单显示用
    int                     m_currentResWidth;

    float                     m_digitalFocusRate;

    QMap< QString, QMap<int, int> >     m_mapColorRes;//记录摄像机颜色空间及对应的分辨率列表
    QString                 m_currentColorSpace;
    QStringList             m_listColorSpace;//给菜单显示用

    //for visualizer rotated
    IBaseFilter             *m_rotateFilter;
    IPin                    *m_pinOut;
    IPin                    *m_pinIn;
    QString                 m_strCurDegree;
    ISettingsInterface      *m_pSettingsInterface;
    bool                    m_bRotateState;
    bool                    m_bRotateHaiTianWei;
};

#endif
