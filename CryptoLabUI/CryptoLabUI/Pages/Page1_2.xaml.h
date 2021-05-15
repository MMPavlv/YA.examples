//
// Page1_2.xaml.h
// Объявление класса Page1_2
//

#pragma once

#include "Page1_2.g.h"

namespace CryptoLabUI
{
	/// <summary>
	/// Пустая страница, которую можно использовать саму по себе или для перехода внутри фрейма.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Page1_2 sealed
	{
	public:
		Page1_2();
	private:
		void TextBox_OnBeforeTextChanging(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxBeforeTextChangingEventArgs^ args);
		void Evaluate1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Evaluate2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Evaluate3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Evaluate4(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Evaluate5(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
