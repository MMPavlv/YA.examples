//
// Page2R_View.xaml.h
// Объявление класса Page2R_View
//

#pragma once

#include "Page2R_View.g.h"

namespace CryptoLabUI
{
	/// <summary>
	/// Пустая страница, которую можно использовать саму по себе или для перехода внутри фрейма.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Page2R_View sealed
	{
	public:
		Page2R_View();
	private:
		void Encrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Decrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void TextBox_OnBeforeTextChanging(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxBeforeTextChangingEventArgs^ args);
	};
}
