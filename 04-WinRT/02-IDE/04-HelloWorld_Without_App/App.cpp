//
// App.xaml.cpp
// Implementation of the App class.
//

#include<pch.h>
#include "App.h"


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
	TextBlock^ textBlock = ref new TextBlock();
	textBlock->Text = "Hello WinRT";
	textBlock->FontSize = 60;
	textBlock->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Indigo);
	textBlock->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	textBlock->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
	Window::Current->Content = textBlock;
	Window::Current->Activate();
}

