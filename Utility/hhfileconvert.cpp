#include "hhfileconvert.h"
#include <comdef.h>
#include <gdiplus.h>
#include <fstream>
#include <QFileInfo>

using namespace Gdiplus;
ULONG_PTR gdiplusToken;
GdiplusStartupInput startupInput;

int getEncoderClsid( const WCHAR *format, CLSID *pClsid ) {
    UINT     num   =   0;                     //   number   of   image   encoders
    UINT     size   =   0;                   //   size   of   the   image   encoder   array   in   bytes

    ImageCodecInfo*   pImageCodecInfo   =   NULL;

    GetImageEncodersSize(&num,   &size);
    if(size   ==   0)
        return   -1;     //   Failure

    pImageCodecInfo   =   (ImageCodecInfo*)(malloc(size));
    if(pImageCodecInfo   ==   NULL)
        return   -1;     //   Failure

    GetImageEncoders(num,   size,   pImageCodecInfo);

    for(UINT   j   =   0;   j   <   num;   ++j)
    {
        if(   wcscmp(pImageCodecInfo[j].MimeType,   format)   ==   0   )
        {
            *pClsid   =   pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return   j;     //   Success
        }
    }

    free(pImageCodecInfo);
    return   -1;     //   Failure
}


//.image 文件解密
Bitmap* DecryptImage( QString source ) {
    //Open Input File
    const wchar_t *wSource = reinterpret_cast<const wchar_t *>( source.utf16() );
    std::ifstream inFile( wSource, std::ios::binary );
    if (!inFile)
        return NULL;

    inFile.seekg(0, std::ios::end);
    SIZE_T dwFileSize = inFile.tellg();
    SIZE_T dwHeaderSize = 128;
    if (dwFileSize <= dwHeaderSize)
        return NULL;

    dwFileSize -= dwHeaderSize;
    SIZE_T dwEncryptHeaderSize = (dwFileSize < 1024)? dwFileSize : 1024;
    ///////////Computing the file header///////////////////
    //Computing the signature
    char cSignature[32+1] = {0};
    char cResType[8+1] = {0};//1=Image;2=Audio;3=Video;4=Flash

    inFile.seekg(0, std::ios::beg);
    //Reading the Signature
    inFile.read(cSignature, 32);
    //Compare the signatures
    if (memcmp(cSignature, "HHTRESOURCE", sizeof("HHTRESOURCE")) != 0)
    {
        return NULL;
    }
    //Reading the Resource Type
    inFile.read(cResType, 8);
    //Compare the Resource Type
    if (memcmp(cResType, "1", sizeof("1")) != 0)
    {
        return NULL;
    }
    //////////////////////////////////////////////////////////////////////////
    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);
    if (hGlobal == NULL)
        return NULL;
    IStream* pStream = NULL;
    CreateStreamOnHGlobal(hGlobal, TRUE, &pStream);
    if (pStream == NULL)
    {
        GlobalFree(hGlobal);
        return NULL;
    }

    char* pBuffer = (char*)GlobalLock(hGlobal);
    //////////////////////////////////////////////////////////////////////////
    inFile.seekg(dwHeaderSize, std::ios::beg);
    inFile.read(pBuffer, dwFileSize);
    for (unsigned i = 0; i < dwEncryptHeaderSize; i++)
        pBuffer[i] -= 1;
    //////////////////////////////////////////////////////////////////////////
    GlobalUnlock(hGlobal);

    Bitmap* pImage = Bitmap::FromStream(pStream);
    pStream->Release();

    return pImage;
}

HHFileConvert::HHFileConvert( QString strPath ) {
    GdiplusStartup( &gdiplusToken, &startupInput, NULL );
    connect( this, SIGNAL(finished(int)), this, SLOT(sltFinished(int) ) );
    m_path = strPath;
}

void HHFileConvert::convertImage( QString source, QString dest ) {
    const wchar_t *wSource = reinterpret_cast<const wchar_t *>( source.utf16() );
    Bitmap *image = NULL;
    if( QFileInfo( source ).suffix().toLower() == "image" )
        image = DecryptImage( source );
    else
        image = Bitmap::FromFile( wSource );
    if( image == NULL )
        return;

    CLSID Clsid;
    getEncoderClsid( L"image/png", &Clsid );

    const wchar_t *wDest = reinterpret_cast<const wchar_t *>( dest.utf16() );
    image->Save( wDest, &Clsid );

    m_source = source;
    m_dest = dest;
//    QString command = "cmd /c " + m_path + "convert.exe" + " \"%1\" \"%2\"";
//    command = command.arg( source ).arg( dest );
//    start( command );
//    waitForFinished();
}



void HHFileConvert::convertVideo(QString source, QString dest) {
    m_source = source;
    m_dest = dest;
    auto command = QString( "cmd /c ffmpeg.exe -i \"%1\" \"%2\"" ).arg( source ).arg( dest );
    start( command );
}

void HHFileConvert::sltFinished( int exitCode ) {
    emit sigFinishedConvert( m_source, m_dest );
}

