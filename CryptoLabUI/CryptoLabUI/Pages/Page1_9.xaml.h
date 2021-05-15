//
// Page1_9.xaml.h
// Объявление класса Page1_9
//

#pragma once

#include "Page1_9.g.h"

namespace CryptoLabUI
{
	/// <summary>
	/// Пустая страница, которую можно использовать саму по себе или для перехода внутри фрейма.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Page1_9 sealed
	{
	public:
		Page1_9();
	private:
		void Encrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Decrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
