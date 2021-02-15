#include "mainwindow.h"
#include "hh3dtoolswidget.h"
#include ".\3dtoolDialog\hh3dtoolspanel.h"
#include <QApplication>
//#include "ArgumentParser.h"
//#include <osgViewer/CompositeViewer>
#include "viewerwidget.h"

int main( int argc, char** argv )
{  
	osg::ArgumentParser arguments(&argc, argv);
    QApplication app(argc, argv);

	if (false)
	{
		QString strImageDir = "../Resouce/";
		QVariantMap params3D;
		QString strNailIconPath = strImageDir + "qml/ID_CUSTOM_NAIL.png";
		QString strNailedIconPath = strImageDir + "qml/ID_CUSTOM_NAILD.png";

		params3D["imageDir"] = strImageDir;
		params3D["NailIconPath"] = strNailIconPath;
		params3D["NailedIconPath"] = strNailedIconPath;
		params3D["CloseIconPath"] = strImageDir + "qml/ID_SYSTEM_SETUP_CLOSE_TOOL.png";
		params3D["btnImageDir"] = strImageDir + "64_64";
		params3D["scalefactor"] = 1.0;
		params3D["IConSize"] = 10;
		params3D["FontSize"] = 20;

		HH3DToolsWidget Panel;
		//Panel.setGeometry(100, 100, 800, 600);
		Panel.init(params3D);
		Panel.show();
		return app.exec();
	}

	if(false)
	{
		ViewerWidget*  vw = new ViewerWidget;
		vw->show();
		return app.exec();
	}

	QString strImageDir = "../Resouce/";
	QVariantMap params3D;
	QString strNailIconPath = strImageDir + "qml/ID_CUSTOM_NAIL.png";
	QString strNailedIconPath = strImageDir + "qml/ID_CUSTOM_NAILD.png";

	params3D["imageDir"] = strImageDir;
	params3D["NailIconPath"] = strNailIconPath;
	params3D["NailedIconPath"] = strNailedIconPath;
	params3D["CloseIconPath"] = strImageDir + "qml/ID_SYSTEM_SETUP_CLOSE_TOOL.png";
	params3D["btnImageDir"] = strImageDir + "64_64";
	params3D["scalefactor"] = 5;
	params3D["IConSize"] = QSize(5,5);
	params3D["FontSize"] = 10;

	HH3DToolsWidget* Panel = new HH3DToolsWidget;
	//Panel->setGeometry(100, 100, 800, 600);
	Panel->init(params3D);
	Panel->show();
	return app.exec();
}
