#include<pch.h>
#include"MyPage.h"
using namespace Windows::Foundation;
using namespace Windows::System;

MyPage::MyPage()
{
	Window::Current->CoreWindow->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs ^>(this, &MyPage::OnKeyDown);
	Grid^ grid = ref new Grid();
	textBlock = ref new TextBlock();
	textBlock->Text = "Hello WinRT EventArgs";
	textBlock->FontSize = 70;
	textBlock->FontWeight = Windows::UI::Text::FontWeights::Bold;
	textBlock->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	textBlock->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;

	Button ^ button = ref new Button();
	button->Content = "Click";
	button->Width = 400;
	button->Width = 100;
	button->BorderThickness= 10;
	button->FontSize = 28;
	button->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
	button->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Bottom;
	button->Click += ref new RoutedEventHandler(this, &MyPage::OnButtonClick);
	grid->Children->Append(textBlock);
	grid->Children->Append(button);
	this->Content = grid;

}

void MyPage::OnKeyDown(CoreWindow ^ Sender, KeyEventArgs ^ args)
{
	if (args->VirtualKey == VirtualKey::Space)
	{
		static unsigned KeyDown = 0;
		if (KeyDown == 1)
		{
			textBlock->Text = "Hello WinRT EventArgs";
		}
		else
		{
			textBlock->Text = "Space bar press event";
			KeyDown = 0;
		}
	}
}

void MyPage::OnButtonClick(Object^ Sender, RoutedEventArgs^ args)
{
	textBlock->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::SeaGreen);
}




