//
// App.xaml.h
// Declaration of the App class.
//

#pragma once

using namespace Platform;
using namespace Windows::ApplicationModel::Activation;


	ref class App sealed :public::Windows::UI::Xaml::Application
	{
	public:
		virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e) override;

	};

