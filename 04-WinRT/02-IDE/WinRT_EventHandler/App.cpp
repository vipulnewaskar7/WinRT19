#include<pch.h>
#include "App.h"
#include "MyPage.h"

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;



void HelloWorldCallback(ApplicationInitializationCallbackParams^ params)
{
	App^ app = ref new App();
}

int main(Array<String^>^ args)
{
	ApplicationInitializationCallback^ callback = ref new ApplicationInitializationCallback(HelloWorldCallback);
	Application::Start(callback);
	return (0);
}

void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e)
{
	MyPage ^myPage = ref new MyPage();
	Window::Current->Content = myPage;
	Window::Current->Activate();
}


