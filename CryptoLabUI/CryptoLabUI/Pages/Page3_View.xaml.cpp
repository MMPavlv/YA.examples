//
// Page3_View.xaml.cpp
// Реализация класса Page3_View
//

#include "pch.h"
#include "Page3_View.xaml.h"

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
using namespace Windows::UI::Popups;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;

// Документацию по шаблону элемента "Пустая страница" см. по адресу https://go.microsoft.com/fwlink/?LinkId=234238

Page3_View::Page3_View()
{
	InitializeComponent();
}


void CryptoLabUI::Page3_View::TextBox_OnBeforeTextChanging(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxBeforeTextChangingEventArgs^ args)
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


void CryptoLabUI::Page3_View::Evaluate(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring str1(Ex1->Text->Data());
	std::wstring str2(Ex2->Text->Data());
	std::wstring str3(Ex3->Text->Data());

	if (str1.empty() || str2.empty() || str3.empty())
		return;

	auto num1 = static_cast<unsigned long long>(std::stoll(str1));
	auto num2 = static_cast<unsigned long long>(std::stoll(str2));
	auto num3 = static_cast<unsigned long long>(std::stoll(str3));

	if(num3 < 2)
	{
		MessageDialog^ msg = ref new MessageDialog("Modulo should be more than 1");
		msg->ShowAsync();
		return;
	}

	auto out = Mathemagics::pow_(num1, num2, num3);

	OutBlock->Inlines->Clear();
	Windows::UI::Xaml::Documents::Run^ r = ref new Windows::UI::Xaml::Documents::Run;
	r->Text = ref new Platform::String(std::to_wstring(out).c_str());
	OutBlock->Inlines->Append(r);
}

