//
// Page1_2.xaml.cpp
// Реализация класса Page1_2
//

#include "pch.h"
#include "Page1_2.xaml.h"
#include <locale>
#include <codecvt>
#include <string>
#include <cctype>
#include <sstream>

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

Page1_2::Page1_2()
{
	InitializeComponent();
}


void CryptoLabUI::Page1_2::TextBox_OnBeforeTextChanging(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxBeforeTextChangingEventArgs^ args)
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

inline bool term(char c) {
	return c==',';
}

inline bool notspace(char c) {
	return !std::isspace(c);
}

std::vector<int> split_(const std::string& s) {
	std::vector<int> vect;

	std::stringstream ss(s);

	int i;

	while (ss >> i)
	{
		vect.push_back(i);

		if (ss.peek() == ',')
			ss.ignore();
	}
	return vect;
}

void CryptoLabUI::Page1_2::Evaluate1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str(Ex1->Text->Data());

	if (str.empty())
		return;
	auto num = static_cast<unsigned long long>(std::stoll(str));
	auto out = Mathemagics::PowerOf2Divider(num);

	MainTextOut->Blocks->Clear();
	Windows::UI::Xaml::Documents::Paragraph^ p = ref new Windows::UI::Xaml::Documents::Paragraph;
	Windows::UI::Xaml::Documents::Run^ r = ref new Windows::UI::Xaml::Documents::Run;
	r->Text = ref new Platform::String(std::to_wstring(out).c_str());
	p->Inlines->Append(r);
	MainTextOut->Blocks->Append(p);
}


void CryptoLabUI::Page1_2::Evaluate2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str(Ex2->Text->Data());

	if (str.empty())
		return;
	auto num = static_cast<unsigned long long>(std::stoll(str));
	auto out = Mathemagics::Closest2Divider(num);

	MainTextOut->Blocks->Clear();
	Windows::UI::Xaml::Documents::Paragraph^ p = ref new Windows::UI::Xaml::Documents::Paragraph;
	Windows::UI::Xaml::Documents::Run^ r = ref new Windows::UI::Xaml::Documents::Run;
	r->Text = ref new Platform::String(std::to_wstring(out).c_str());
	p->Inlines->Append(r);
	MainTextOut->Blocks->Append(p);
}


void CryptoLabUI::Page1_2::Evaluate3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str(Ex3->Text->Data());

	if (str.empty())
		return;
	auto num = static_cast<unsigned long long>(std::stoll(str));
	auto out = Mathemagics::AllBitsXor(num);

	MainTextOut->Blocks->Clear();
	Windows::UI::Xaml::Documents::Paragraph^ p = ref new Windows::UI::Xaml::Documents::Paragraph;
	Windows::UI::Xaml::Documents::Run^ r = ref new Windows::UI::Xaml::Documents::Run;
	r->Text = ref new Platform::String(std::to_wstring(out).c_str());
	p->Inlines->Append(r);
	MainTextOut->Blocks->Append(p);
}


void CryptoLabUI::Page1_2::Evaluate4(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str(Ex4->Text->Data());
	std::wstring str_(Ex4_1->Text->Data());
	if (str.empty() || str_.empty())
		return;
	auto num = static_cast<unsigned long long>(std::stoll(str));
	auto bits = static_cast<unsigned long long>(std::stoll(str_));
	unsigned long long out;
	if ((Platform::String^)OpSelec->SelectedItem == L"Right")
	{
		out = Mathemagics::CyclicShiftRight(num, bits);
	}
	else if ((Platform::String^)OpSelec->SelectedItem == L"Left")
	{
		out = Mathemagics::CyclicShiftLeft(num, bits);
	}

	MainTextOut->Blocks->Clear();
	Windows::UI::Xaml::Documents::Paragraph^ p = ref new Windows::UI::Xaml::Documents::Paragraph;
	Windows::UI::Xaml::Documents::Run^ r = ref new Windows::UI::Xaml::Documents::Run;
	r->Text = ref new Platform::String(std::to_wstring(out).c_str());
	p->Inlines->Append(r);
	MainTextOut->Blocks->Append(p);
}


void CryptoLabUI::Page1_2::Evaluate5(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring num(Ex5->Text->Data());
	auto number = std::stoll(num);

	std::wstring str(Ex6->Text->Data());
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	auto st = converterX.to_bytes(str);
	auto pos = split_(st);

	for (int i = 0; i < pos.size(); i++)
	{

	}
}
