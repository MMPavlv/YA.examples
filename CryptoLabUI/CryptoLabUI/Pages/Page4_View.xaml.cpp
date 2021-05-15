//
// Page4_View.xaml.cpp
// Реализация класса Page4_View
//

#include "pch.h"
#include "Page4_View.xaml.h"
#include "Header4.hpp"
#include <locale>
#include <codecvt>
#include <string>
#include <cctype>

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

Page4_View::Page4_View()
{
	InitializeComponent();
}

inline bool space(char c) {
	return std::isspace(c);
}

inline bool notspace(char c) {
	return !std::isspace(c);
}

//break a sentence into words
std::vector<std::string> split(const std::string& s) {
	typedef std::string::const_iterator iter;
	std::vector<std::string> ret;
	iter i = s.begin();
	while (i != s.end()) {
		i = std::find_if(i, s.end(), notspace); // find the beginning of a word
		iter j = std::find_if(i, s.end(), space); // find the end of the same word
		if (i != s.end()) {
			ret.push_back(std::string(i, j)); //insert the word into vector
			i = j; // repeat 1,2,3 on the rest of the line.
		}
	}
	return ret;
}

std::wstring StringToWString(const std::string& s)
{
	std::wstring temp(s.length(), L' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp;
}

void CryptoLabUI::Page4_View::Encrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Mathemagics::RSA rsa;
	Mathemagics::Key key = rsa.produce_keys();
	TextA->Text = ref new Platform::String(std::to_wstring(key.dkey).c_str());
	TextB->Text = ref new Platform::String(std::to_wstring(key.pkey).c_str());
	std::wstring str1(Text1->Text->Data());

	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	auto st = converterX.to_bytes(str1);
	std::string st_out = "";
	std::wstring wst_out = L"";
	Windows::UI::Xaml::Documents::Run^ r = ref new Windows::UI::Xaml::Documents::Run;
	for (size_t i = 0; i < st.length(); i++)
	{
		long msg_des = rsa.endecrypt(st[i], key.ekey, key.pkey);
		wst_out += std::to_wstring(msg_des) + L" ";
	}

	Text2->Text = ref new Platform::String(wst_out.c_str());
}


void CryptoLabUI::Page4_View::Decrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::wstring strA(TextA->Text->Data());
	std::wstring strB(TextB->Text->Data());
	long dkey = std::stol(strA);
	long pkey = std::stol(strB);

	Mathemagics::RSA rsa;
	std::wstring str1(Text2->Text->Data());
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	auto st = converterX.to_bytes(str1);
	std::string out = "";
	auto v = split(st);
	for (auto wrd : v)
	{
		out += (char)rsa.endecrypt(std::stol(wrd), dkey, pkey);
	}
	Text1->Text = ref new Platform::String(StringToWString(out).c_str());
}
