#include "hhofficeoperator.h"
#include <QWidget>
#include <QDebug>

OfficeThread::OfficeThread( HHOfficeOperator *mainwindow ) :
    QThread( mainwindow ) {
}
void OfficeThread::run() {
}

HHOfficeOperator::HHOfficeOperator( bool bExport ) {
}

HHOfficeOperator::HHOfficeOperator( QRect rect, QWidget *whiteboard ) {
}

HHOfficeOperator::~HHOfficeOperator() {
}

void HHOfficeOperator::sltDetectOffice() {
}

void HHOfficeOperator::startDetect() {
}

void HHOfficeOperator::stopDetect() {
}

void HHOfficeOperator::embedImage( QString strFile, QRect rectEmbeded, QString strDoc ) {
}

void HHOfficeOperator::setPPTPlayingNext() {
}

void HHOfficeOperator::setPPTPlayingPrevious() {
}

void HHOfficeOperator::setPPTPlayingEnd() {
}

bool HHOfficeOperator::exportPPT(QString fileName, QStringList picList) {
    return false;
}

bool HHOfficeOperator::exportPDF(QString fileName, QStringList picList) {
    return false;
}

bool HHOfficeOperator::exportWORD(QString fileName, QStringList picList) {
    return false;
}

bool HHOfficeOperator::exportHTML(QString fileName, QStringList picList) {
    return false;
}

bool HHOfficeOperator::exportImage(QString fileName, QStringList picList) {
    return false;
}

bool HHOfficeOperator::exportEXCEL(QString fileName, QStringList picList) {
    return false;
}

QStringList HHOfficeOperator::importPPT(QString fileName, QString saveDir) {
    return QStringList();
}

void HHOfficeOperator::sltRefreshPPTPlaying() {
}

void HHOfficeOperator::setWPSPPTPlayingPenType( QString strType ) {
}

bool HHOfficeOperator::exportWPSWord( QString fileName, QStringList picList ) {
    return false;
}

bool HHOfficeOperator::exportWPSExcel( QString fileName, QStringList picList ) {
    return false;
}

bool HHOfficeOperator::exportWPSPpt( QString fileName, QStringList picList ) {
    return false;
}
