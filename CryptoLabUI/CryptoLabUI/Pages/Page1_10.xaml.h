//
// Page1_10.xaml.h
// Объявление класса Page1_10
//

#pragma once

#include "Page1_10.g.h"

namespace CryptoLabUI
{
	/// <summary>
	/// Пустая страница, которую можно использовать саму по себе или для перехода внутри фрейма.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Page1_10 sealed
	{
	public:
		Page1_10();
	private:
		void Encrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Decrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Generate(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
