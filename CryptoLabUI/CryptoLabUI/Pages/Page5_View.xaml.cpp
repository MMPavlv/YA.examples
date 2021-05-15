//
// Page5_View.xaml.cpp
// Реализация класса Page5_View
//

#include "pch.h"
#include "Page5_View.xaml.h"
#include "Header5.hpp"
#include <locale>
#include <codecvt>

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

Page5_View::Page5_View()
{
	InitializeComponent();
}


void CryptoLabUI::Page5_View::TextBox_OnBeforeTextChanging(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxBeforeTextChangingEventArgs^ args)
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

std::string ws2s(const std::wstring& wstr)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}

void CryptoLabUI::Page5_View::Evaluate1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str1(Ex1->Text->Data());
	std::wstring str2(Ex2->Text->Data());

	if (str1.empty() || str2.empty())
		return;

	unsigned long long num1 = static_cast<unsigned long long>(std::stoll(str1));
	//auto num2 = static_cast<unsigned long long>(std::stoll(str2));

	Mathemagics::GF a(num1, ws2s(str2));
	auto str = a.PolynomOut();
	Out1->Inlines->Clear();
	Windows::UI::Xaml::Documents::Run^ r = ref new Windows::UI::Xaml::Documents::Run;
	std::wstring wstr(str.begin(), str.end());
	r->Text = ref new Platform::String(wstr.c_str());
	Out1->Inlines->Append(r);
}


void CryptoLabUI::Page5_View::Evaluate2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str1(Ex3->Text->Data());
	std::wstring str2(Ex4->Text->Data());
	std::wstring str3(Ex5->Text->Data());

	if (str1.empty() || str2.empty() || str3.empty())
		return;

	unsigned long long num1 = static_cast<unsigned long long>(std::stoll(str1));
	Mathemagics::GF a(num1, ws2s(str2));
	Mathemagics::GF b(num1, ws2s(str3));
	Mathemagics::GF Out(num1, ws2s(str3));
	if((Platform::String^)OpSelec->SelectedItem == "+")
	{
		Out = a + b;
	}
	else if ((Platform::String^)OpSelec->SelectedItem == "*")
	{
		Out = a * b;
	}

	Out2->Inlines->Clear();
	Windows::UI::Xaml::Documents::Run^ r = ref new Windows::UI::Xaml::Documents::Run;

	if ((Platform::String^)OutSelec->SelectedItem == "Polynomial Output")
	{
		Out = a + b;
		auto str = Out.PolynomOut();
		std::wstring wstr(str.begin(), str.end());
		r->Text = ref new Platform::String(wstr.c_str());
	}
	else
	{
		Out = a + b;
		auto z = Out.GetIrreduciblePolynomials();
		auto str = Out.Out();
		std::wstring wstr(str.begin(), str.end());
		r->Text = ref new Platform::String(wstr.c_str());
	}

	Out2->Inlines->Append(r);
}


void CryptoLabUI::Page5_View::Evaluate3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str1(Ex6->Text->Data());
	std::wstring str2(Ex7->Text->Data());

	if (str1.empty() || str2.empty())
		return;

	unsigned long long num1 = static_cast<unsigned long long>(std::stoll(str1));
	//auto num2 = static_cast<unsigned long long>(std::stoll(str2));

	Mathemagics::GF a(num1, ws2s(str2));
	auto b = a.GetMultiplicativeInverse();
	auto str = b.PolynomOut();
	Out3->Inlines->Clear();
	Windows::UI::Xaml::Documents::Run^ r = ref new Windows::UI::Xaml::Documents::Run;
	std::wstring wstr(str.begin(), str.end());
	r->Text = ref new Platform::String(wstr.c_str());
	Out3->Inlines->Append(r);
}
