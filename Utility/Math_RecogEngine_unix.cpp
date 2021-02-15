#include "Math_RecogEngine.h"

CMathRecogEngine* CMathRecogEngine::CreateMathRecognizer()
{
    return 0;
}
void CMathRecogEngine::DeleteMathRecognizer(CMathRecogEngine*& pRecog)
{
}
void CMathRecogEngine::setSystemFilePath(const QString& strFilePath)
{
}

long CMathRecogEngine::RecognizeAndShow(long * data, long hDC, float x, float y, long color, long fontSize) {
    return 0;
}

QPixmap* CMathRecogEngine::GetRecognizeBitmap(long* data, QWidget* pWidget) {
    return 0;
}

void CMathRecogEngine::deleteBitmap(QPixmap* pBitmap) {

}
