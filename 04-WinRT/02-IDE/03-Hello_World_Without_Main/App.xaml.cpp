//
// App.xaml.cpp
// Implementation of the App class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace Hello_World_Without_Main;

using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;


App::App()
{
    InitializeComponent();
    Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
}


void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e)
{
	Page^ page = ref new Page();
	Grid^ grid = ref new Grid();
	grid->Background = ref new SolidColorBrush(Windows::UI::Colors::DarkSalmon);
	TextBlock^ textBlock = ref new TextBlock();
	textBlock->Text = "Hello WinRT!!! ";
	textBlock->FontSize = 60;
	textBlock->FontStyle = Windows::UI::Text::FontStyle::Oblique;
	textBlock->FontWeight = Windows::UI::Text::FontWeights::Bold;
	textBlock->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	textBlock->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
	grid->Children->Append(textBlock);
	page->Content = grid;
	Window::Current->Content = page;
	Window::Current->Activate();
}


void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
    (void) sender;  // Unused parameter
    (void) e;   // Unused parameter

    //TODO: Save application state and stop any background activity
}


void App::OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e)
{
    throw ref new FailureException("Failed to load Page " + e->SourcePageType.Name);
}