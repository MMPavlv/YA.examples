//
// Page2E_View.xaml.cpp
// Реализация класса Page2E_View
//

#include "pch.h"
#include "Page2E_View.xaml.h"

using namespace CryptoLabUI;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// Документацию по шаблону элемента "Пустая страница" см. по адресу https://go.microsoft.com/fwlink/?LinkId=234238

Page2E_View::Page2E_View()
{
	InitializeComponent();
}


void CryptoLabUI::Page2E_View::Encrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str(Text1->Text->Data());
	std::wstring out1;
	std::wstring out2;
	unsigned long long k = 2000;
	unsigned long long a = Mathemagics::pow_(Mathemagics::g, k, Mathemagics::P);
	
	for (int i = 0; i < str.size(); i++)
	{
		unsigned long long b = (Mathemagics::pow_(Mathemagics::y, k, Mathemagics::P)*str[i])%Mathemagics::P;
		out2.push_back(b);
	}

	Text2->Text = ref new Platform::String(out2.c_str());
}


void CryptoLabUI::Page2E_View::Decrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str(Text1->Text->Data());
	unsigned long long k = 2000;
	unsigned long long a = Mathemagics::pow_(Mathemagics::g, k, Mathemagics::P);
	std::wstring out;
	for (int i = 0; i < str.size(); i++)
	{
		unsigned long long M = (Mathemagics::pow_(a, Mathemagics::P-Mathemagics::x-1, Mathemagics::P)*str[i]) % Mathemagics::P;
		out.push_back(M);
	}
	Text2->Text = ref new Platform::String(out.c_str());
}
