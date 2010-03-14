#include <Existence.h>
using namespace Gen;

#include "RainGame.h"

#if defined __PLATFORM_WIN32
int WINAPI WinMain(	HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR	lpCmdLine,
				   int		nCmdShow)
#elif defined __PLATFORM_LINUX
int main()
#endif
{
	Debug::EnableBreakOnAlloc();

	RainGame* game = new RainGame();
	Engine::Instance().SetGame(game);

	// 创建并初始化渲染窗口
	System::Instance().CreateRenderWindow("Rain", 640, 480, 32, false);
	Engine::Instance().Initialize();

	System::Instance().LoadResources("resources.cfg");

	Engine::Instance().Run();
	Engine::Instance().Shutdown();
	System::Instance().DestroyRenderWindow();

	delete game;
	return 1;
}
