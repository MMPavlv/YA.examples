//
// Page1_12.xaml.cpp
// Реализация класса Page1_12
//

#include "pch.h"
#include "Page1_12.xaml.h"

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

Page1_12::Page1_12()
{
	InitializeComponent();
}


void CryptoLabUI::Page1_12::Encrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str1(Text1->Text->Data());
	std::wstring out;
	std::wstring key(TextK->Text->Data());

	vector<wchar_t> S(256);
	//
	for (int i = 0; i < 256; i++)
		S[i] = i;
	wchar_t j = 0;
	for (int i = 0; i < 256; i++)
	{
		j = (j + S[i] + key[i%key.size()]) % 256;
		auto temp = S[i];
		S[i] = S[j];
		S[j] = temp;
	}
	//
	wchar_t i = 0;
	j = 0;
	wchar_t K;
	for (int it = 0; it < str1.size(); it++)
	{
		i = (i++) % 256;
		j = (j + S[i]) % 256;

		auto temp = S[i];
		S[i] = S[j];
		S[j] = temp;

		auto t = (S[i] + S[j]) % 256;
		K = S[t];

		out.push_back(str1[it] ^ K);
	}
	Text2->Text = ref new Platform::String(out.c_str());
}


void CryptoLabUI::Page1_12::Decrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}
