#pragma once
#include<pch.h>

using namespace Platform;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

ref class MyPage sealed :public Page {
	private:
		TextBlock ^ textBlock;
	public:
		MyPage();
		void OnKeyDown(CoreWindow^ Sender, KeyEventArgs^ args);
		void OnButtonClick(Object^ Sender, RoutedEventArgs^ args);
};

