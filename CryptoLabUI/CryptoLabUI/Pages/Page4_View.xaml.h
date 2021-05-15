//
// Page4_View.xaml.h
// Объявление класса Page4_View
//

#pragma once

#include "Page4_View.g.h"

namespace CryptoLabUI
{
	/// <summary>
	/// Пустая страница, которую можно использовать саму по себе или для перехода внутри фрейма.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Page4_View sealed
	{
	public:
		Page4_View();
	private:
		void Encrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Decrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
