//
// Page1_View.xaml.cpp
// Реализация класса Page1_View
//

#include "pch.h"
#include "Page1_View.xaml.h"
#include <wchar.h>
#include <wctype.h>
#include <string>

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

Page1_View::Page1_View()
{
	InitializeComponent();
}


void CryptoLabUI::Page1_View::TextBox_OnBeforeTextChanging(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxBeforeTextChangingEventArgs^ args)
{
	for(auto it : args->NewText)
	{
		if(!isdigit(it))
		{
			args->Cancel = true;
			break;
		}
	}
}


void CryptoLabUI::Page1_View::Evaluate1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str(Ex1->Text->Data());

	if (str.empty())
		return;

	auto num = static_cast<unsigned long long>(std::stoll(str));
	auto out = Mathemagics::GetPrimesBeforeThreshold(num);
	MainTextOut->Blocks->Clear();
	for (auto n : out)
	{
		Windows::UI::Xaml::Documents::Paragraph^ p = ref new Windows::UI::Xaml::Documents::Paragraph;
		Windows::UI::Xaml::Documents::Run^ r = ref new Windows::UI::Xaml::Documents::Run;
		r->Text = ref new Platform::String(std::to_wstring(n).c_str());
		p->Inlines->Append(r);
		MainTextOut->Blocks->Append(p);
	}
}


void CryptoLabUI::Page1_View::Evaluate2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str(Ex2->Text->Data());

	if (str.empty())
		return;

	auto num = static_cast<unsigned long long>(std::stoll(str));
	auto out = Mathemagics::GetReducedResidueSystem(num);
	MainTextOut->Blocks->Clear();
	for (auto n : out)
	{
		Windows::UI::Xaml::Documents::Paragraph^ p = ref new Windows::UI::Xaml::Documents::Paragraph;
		Windows::UI::Xaml::Documents::Run^ r = ref new Windows::UI::Xaml::Documents::Run;
		r->Text = ref new Platform::String(std::to_wstring(n).c_str());
		p->Inlines->Append(r);
		MainTextOut->Blocks->Append(p);
	}
}


void CryptoLabUI::Page1_View::Evaluate3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str(Ex3->Text->Data());

	if (str.empty())
		return;

	auto num = static_cast<unsigned long long>(std::stoll(str));
	auto out = Mathemagics::Phi(num);
	MainTextOut->Blocks->Clear();
	Windows::UI::Xaml::Documents::Paragraph^ p = ref new Windows::UI::Xaml::Documents::Paragraph;
	Windows::UI::Xaml::Documents::Run^ r = ref new Windows::UI::Xaml::Documents::Run;
	r->Text = ref new Platform::String(std::to_wstring(out).c_str());
	p->Inlines->Append(r);
	MainTextOut->Blocks->Append(p);
}


void CryptoLabUI::Page1_View::Evaluate4(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str(Ex4->Text->Data());

	if (str.empty())
		return;

	auto num = static_cast<unsigned long long>(std::stoll(str));
	auto out = Mathemagics::CanonicalPrimeFactorization(num);
	MainTextOut->Blocks->Clear();
	for (auto n : out)
	{
		Windows::UI::Xaml::Documents::Paragraph^ p = ref new Windows::UI::Xaml::Documents::Paragraph;
		Windows::UI::Xaml::Documents::Run^ r = ref new Windows::UI::Xaml::Documents::Run;
		r->Text = ref new Platform::String(std::to_wstring(n.first).c_str())+ ref new Platform::String(L"^") +ref new Platform::String(std::to_wstring(n.second).c_str());
		p->Inlines->Append(r);
		MainTextOut->Blocks->Append(p);
	}
}
