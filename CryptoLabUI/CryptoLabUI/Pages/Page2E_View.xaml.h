//
// Page2E_View.xaml.h
// Объявление класса Page2E_View
//

#pragma once

#include "Page2E_View.g.h"

namespace CryptoLabUI
{
	/// <summary>
	/// Пустая страница, которую можно использовать саму по себе или для перехода внутри фрейма.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Page2E_View sealed
	{
	public:
		Page2E_View();
	private:
		void Encrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Decrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
