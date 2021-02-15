#include "Chem_RecogEngine.h"
#include "math_chem.tlh"
#include <atlbase.h>
#include <QLibrary>
#include <QBitmap>
#include <QWidget>
#include <qwinfunctions.h>
#include <QApplication>
#include <atlapp.h>
namespace ATL
{

class _U_RECT
{
public:
    _U_RECT(LPRECT lpRect) : m_lpRect(lpRect)
    { }
    _U_RECT(RECT& rc) : m_lpRect(&rc)
    { }
    LPRECT m_lpRect;
};

class _U_MENUorID
{
public:
    _U_MENUorID(HMENU hMenu) : m_hMenu(hMenu)
    { }
    _U_MENUorID(UINT nID) : m_hMenu((HMENU)LongToHandle(nID))
    { }
    HMENU m_hMenu;
};

class _U_STRINGorID
{
public:
    _U_STRINGorID(LPCTSTR lpString) : m_lpstr(lpString)
    { }
    _U_STRINGorID(UINT nID) : m_lpstr(MAKEINTRESOURCE(nID))
    { }
    LPCTSTR m_lpstr;
};

}; // namespace ATL

#include <atlgdi.h>
#include <atlstr.h>

typedef HRESULT(__stdcall *pDllGetClassObject)(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
static QString s_strFilePath;
static CChemRecogEngine* s_MathRecogEngine = NULL;


static void getImageWideAndHeight(QImage& qi, int& nWidth, int& nHeith, QColor& colorCompare)
{
    int nW = qi.width();
    int nH = qi.height();
    int nXMax = -1;
    int hYMax = -1;
    int i = 0;
    int j = 0;
    for (i = 0; i < nW; ++i)
    {
        for (j = 0; j < nH; ++j)
        {
            QColor color = qi.pixel(i, j);

            if (colorCompare.red() == color.red() && colorCompare.green() == color.green() && colorCompare.blue() == color.blue())
            {
                if (nXMax < i)
                {
                    nXMax = i;
                }

                if (hYMax < j)
                {
                    hYMax = j;
                }
            }
        }
    }

    nWidth = nXMax + 1;
    nHeith = hYMax + 1;
}

class  CLocalChemRecogEngine : public CChemRecogEngine
{
public:
	CLocalChemRecogEngine();
	virtual ~CLocalChemRecogEngine(){}
    virtual long RecognizeAndShow(long * data, long hDC, float x, float y, long color, long fontSize);
    virtual class QPixmap* GetRecognizeBitmap(long* data);
    virtual void deleteBitmap(QPixmap* pBitmap);
protected:
    CComPtr< IChemRecognizer >		m_recognizier;
};

void CLocalChemRecogEngine::deleteBitmap(QPixmap* pBitmap)
{
    delete  pBitmap;
}

CLocalChemRecogEngine::CLocalChemRecogEngine()
{
    QString strFilePath = QApplication::applicationDirPath() + "\\Math_Chem.dll";
    QLibrary hMyScriptEngine;
    hMyScriptEngine.setFileName(strFilePath);
    if (hMyScriptEngine.load())
    {
        pDllGetClassObject pfGetClassObj = (pDllGetClassObject)hMyScriptEngine.resolve("DllGetClassObject");
        CComPtr< IClassFactory > pFac;
        HRESULT hr = pfGetClassObj(CLSID_ChemRecognizer, IID_IClassFactory, (void **)&pFac);
        hr = pFac->CreateInstance(NULL, DIID_IChemRecognizer, (void**)&m_recognizier);

        CComBSTR license(_T("Intelligence"));
        m_recognizier->VerifyLicenseKey(&license);
    }
}

QPixmap* CLocalChemRecogEngine::GetRecognizeBitmap(long* data)
{
    if (NULL == data)
    {
        return NULL;
    }

	QWidget  widget;
	HWND hwnd = (HWND)widget.winId();

    WTL::CClientDC dc(hwnd);
    WTL::CDC MemDC;
    MemDC.CreateCompatibleDC(dc.m_hDC);
    WTL::CBitmap MemBitmap;//??????????????

    MemBitmap.CreateCompatibleBitmap(dc.m_hDC, 700,700);
    MemDC.SelectBitmap((HBITMAP)MemBitmap);

    m_recognizier->RecognizeAndShow(data, ( LONG )MemDC.m_hDC, 0, 0, RGB(10, 10, 10), 2);
    QImage qi = QtWin::imageFromHBITMAP(dc.m_hDC, (HBITMAP)MemBitmap, 700, 700);

    int nWidth = 0;
    int nHeigth = 0;
    QColor colorCompare(10, 10, 10);
    getImageWideAndHeight(qi, nWidth, nHeigth, colorCompare);
	nWidth += 10;
    QImage qiTemp = qi.copy(0, 0, nWidth, nHeigth);
    QPixmap* pBitmap = new QPixmap();
    pBitmap->convertFromImage(qiTemp);
    return pBitmap;
}

long CLocalChemRecogEngine::RecognizeAndShow(long * data, long hDC, float x, float y, long color, long fontSize)
{
    if (NULL != m_recognizier)
    {
        BSTR bstrReco;
        m_recognizier->RecognizeAndShow(data,hDC, 0, 0, RGB(255, 0, 255), 4);
    }
    return 1;
}

CChemRecogEngine* CChemRecogEngine::CreateChemRecognizer()
{
    if (NULL == s_MathRecogEngine)
    {
		s_MathRecogEngine = new CLocalChemRecogEngine();
    }

    return s_MathRecogEngine;
}
void CChemRecogEngine::DeleteChemRecognizer(CChemRecogEngine*& pRecog)
{
    if (NULL != pRecog)
    {
        delete pRecog;
        pRecog = NULL;
        s_MathRecogEngine = NULL;
    }
    else
    {
        delete s_MathRecogEngine;
        s_MathRecogEngine = NULL;
    }
}
void CChemRecogEngine::setSystemFilePath(const QString& strFilePath)
{
    s_strFilePath = strFilePath;
}
