//
// MainPage.xaml.cpp
// Реализация класса MainPage.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "Page1_2.xaml.h"
#include "Page1_9.xaml.h"
#include "Page1_10.xaml.h"
#include "Page1_12.xaml.h"
#include "Page1_View.xaml.h"
#include "Page2R_View.xaml.h"
#include "Page2E_View.xaml.h"
#include "Page3_View.xaml.h"
#include "Page4_View.xaml.h"
#include "Page5_View.xaml.h"

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

// Документацию по шаблону элемента "Пустая страница" см. по адресу https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x419

MainPage::MainPage()
{
	InitializeComponent();
}


void CryptoLabUI::MainPage::nvTopLevelNav_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	
	for (int i = 0; i < nvTopLevelNav->MenuItems->Size; i++)
	{
		NavigationViewItemBase^ item = (NavigationViewItemBase^) nvTopLevelNav->MenuItems->GetAt(i);
		if(item->Tag->ToString() == "FirstPage")
		{
			nvTopLevelNav->SelectedItem = item;
			nvTopLevelNav->Header = "Work 1";
			break;
		}
	}
	contentFrame->Navigate(Windows::UI::Xaml::Interop::TypeName(Page1_View::typeid));
}


void CryptoLabUI::MainPage::nvTopLevelNav_SelectionChanged(Windows::UI::Xaml::Controls::NavigationView^ sender, Windows::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs^ args)
{
	
}


void CryptoLabUI::MainPage::nvTopLevelNav_ItemInvoked(Windows::UI::Xaml::Controls::NavigationView^ sender, Windows::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs^ args)
{
	NavigationViewItemBase^ ItemContent = safe_cast<NavigationViewItemBase^>(nvTopLevelNav->SelectedItem);
	
	if (ItemContent != nullptr)
	{
		if(ItemContent->Tag->ToString() == "FirstPage")
			contentFrame->Navigate(Windows::UI::Xaml::Interop::TypeName(Page1_View::typeid));
		else if(ItemContent->Tag->ToString() == "ThirdPage")
			contentFrame->Navigate(Windows::UI::Xaml::Interop::TypeName(Page3_View::typeid));
		else if (ItemContent->Tag->ToString() == "FourthPage")
			contentFrame->Navigate(Windows::UI::Xaml::Interop::TypeName(Page4_View::typeid));
		else if (ItemContent->Tag->ToString() == "FifthPage")
			contentFrame->Navigate(Windows::UI::Xaml::Interop::TypeName(Page5_View::typeid));
		else if (ItemContent->Tag->ToString() == "Page1_2")
			contentFrame->Navigate(Windows::UI::Xaml::Interop::TypeName(Page1_2::typeid));
		else if (ItemContent->Tag->ToString() == "Page1_9")
			contentFrame->Navigate(Windows::UI::Xaml::Interop::TypeName(Page1_9::typeid));
		else if (ItemContent->Tag->ToString() == "Page1_10")
			contentFrame->Navigate(Windows::UI::Xaml::Interop::TypeName(Page1_10::typeid));
		else if (ItemContent->Tag->ToString() == "Page1_12")
			contentFrame->Navigate(Windows::UI::Xaml::Interop::TypeName(Page1_12::typeid));
		else if (ItemContent->Tag->ToString() == "RabinPage")
			contentFrame->Navigate(Windows::UI::Xaml::Interop::TypeName(Page2R_View::typeid));
		else if (ItemContent->Tag->ToString() == "ElgamalPage")
			contentFrame->Navigate(Windows::UI::Xaml::Interop::TypeName(Page2E_View::typeid));
	}
}
