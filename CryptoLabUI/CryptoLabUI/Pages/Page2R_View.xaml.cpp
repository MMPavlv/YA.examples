//
// Page2R_View.xaml.cpp
// Реализация класса Page2R_View
//

#include "pch.h"
#include "Page2R_View.xaml.h"

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

Page2R_View::Page2R_View()
{
	InitializeComponent();
}


void CryptoLabUI::Page2R_View::Encrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str(TextIn->Text->Data());
	std::wstring out;
	for (int i = 0; i < str.size(); i++)
	{
		auto en = Mathemagics::Rabin::Encrypt(str[i], Mathemagics::pbk);
		out.push_back(en);
	}
	TextEn->Text = ref new Platform::String(out.c_str());
}


void CryptoLabUI::Page2R_View::Decrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str(TextIn->Text->Data());
	std::wstring out1;
	std::wstring out2;
	std::wstring out3;
	std::wstring out4;

	for (int i = 0; i < str.size(); i++)
	{
		auto dc = Mathemagics::Rabin::Decrypt(str[i], Mathemagics::prk, Mathemagics::pbk);
		out1.push_back(dc[0]);
		out2.push_back(dc[1]);
		out3.push_back(dc[2]);
		out4.push_back(dc[3]);
	}

	Text1->Text = ref new Platform::String(out1.c_str());
	Text2->Text = ref new Platform::String(out2.c_str());
	Text3->Text = ref new Platform::String(out3.c_str());
	Text4->Text = ref new Platform::String(out4.c_str());
}


void CryptoLabUI::Page2R_View::TextBox_OnBeforeTextChanging(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxBeforeTextChangingEventArgs^ args)
{
	for (auto it : args->NewText)
	{
		if (!isdigit(it))
		{
			args->Cancel = true;
			break;
		}
	}
}
