//
// Page3_View.xaml.h
// Объявление класса Page3_View
//

#pragma once

#include "Page3_View.g.h"

namespace CryptoLabUI
{
	/// <summary>
	/// Пустая страница, которую можно использовать саму по себе или для перехода внутри фрейма.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Page3_View sealed
	{
	public:
		Page3_View();
	private:
		void Evaluate(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void TextBox_OnBeforeTextChanging(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxBeforeTextChangingEventArgs^ args);
	};
}
