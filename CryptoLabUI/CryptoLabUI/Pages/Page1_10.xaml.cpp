//
// Page1_10.xaml.cpp
// Реализация класса Page1_10
//

#include "pch.h"
#include "Page1_10.xaml.h"

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

Page1_10::Page1_10()
{
	InitializeComponent();
}


void CryptoLabUI::Page1_10::Encrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str1(Text1->Text->Data());
	std::wstring str2(Text2->Text->Data());
	std::wstring str3;

	if (str1.size() != str2.size())
		return;

	for (int i = 0; i < str1.size(); i++)
	{
		auto c = str1[i] ^ str2[i];
		str3.push_back(str1[i]^str2[i]);
	}

	Text3->Text = ref new Platform::String(str3.c_str());
}


void CryptoLabUI::Page1_10::Decrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str1(Text3->Text->Data());
	std::wstring str2(Text2->Text->Data());
	std::wstring str3;

	//System::Security::Cryptography::DES();

	if (str1.size() != str2.size())
		return;

	for (int i = 0; i < str1.size(); i++)
	{
		auto c = str1[i] ^ str2[i];
		str3.push_back(str1[i] ^ str2[i]);
	}

	Text1->Text = ref new Platform::String(str3.c_str());
}


void CryptoLabUI::Page1_10::Generate(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//std::wstring str1(Text1->Text->Data());
	//TODO generation
}
