//
// Page1_View.xaml.h
// Объявление класса Page1_View
//

#pragma once

#include "Page1_View.g.h"

namespace CryptoLabUI
{
	/// <summary>
	/// Пустая страница, которую можно использовать саму по себе или для перехода внутри фрейма.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Page1_View sealed
	{
	public:
		Page1_View();
	private:
		void TextBox_OnBeforeTextChanging(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxBeforeTextChangingEventArgs^ args);
		void Evaluate1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Evaluate2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Evaluate3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Evaluate4(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
