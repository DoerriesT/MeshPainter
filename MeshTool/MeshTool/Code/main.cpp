#include "MeshTool.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSurfaceFormat format;
	format.setVersion(3, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	//format.setDepthBufferSize(24);
	//format.setStencilBufferSize(8);
	QSurfaceFormat::setDefaultFormat(format);

	MeshTool w;
	w.show();
	return a.exec();
}
