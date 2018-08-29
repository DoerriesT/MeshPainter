#include "GLFunctions.h"

QOpenGLFunctions_3_3_Core *getGLFunctions()
{
	static QOpenGLFunctions_3_3_Core *funcs;

	if (!funcs)
	{
		funcs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
		if (!funcs)
		{
			//qWarning() << "Could not obtain required OpenGL context version";
			exit(1);
		}
		funcs->initializeOpenGLFunctions();
	}
	
	return funcs;
}
