//
// Page1_9.xaml.cpp
// Реализация класса Page1_9
//

#include "pch.h"
#include <random>
#include <algorithm>
#include <iterator>
#include "Page1_9.xaml.h"
#include <ppltasks.h>

using namespace CryptoLabUI;

using namespace concurrency;
using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::FileProperties;
using namespace Windows::Storage::Streams;
using namespace Microsoft::WRL;
using namespace Streams;

// Документацию по шаблону элемента "Пустая страница" см. по адресу https://go.microsoft.com/fwlink/?LinkId=234238

Page1_9::Page1_9()
{
	InitializeComponent();
	Mathemagics::init_it++;

	if (Mathemagics::init_it == 1)
	{
		for (int i = 0; i < 256; i++)
		{
			Mathemagics::table.push_back(unsigned char(i));
		}
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(Mathemagics::table.begin(), Mathemagics::table.end(), g);
	}
	else
	{
		auto a = Mathemagics::table;
	}
	//Mathemagics::table
}


void CryptoLabUI::Page1_9::Encrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FileOpenPicker^ openPicker = ref new FileOpenPicker();
	openPicker->FileTypeFilter->Append("*");
	create_task(openPicker->PickSingleFileAsync()).then([this](StorageFile^ file)
	{
		if (file != nullptr)
		{
			auto FileName = file->Path;
			create_task(FileIO::ReadBufferAsync(file)).then([this, file](IBuffer^ buffer)
			{
				try
				{
					auto fileData = ref new Platform::Array<byte>(buffer->Length);
					DataReader::FromBuffer(buffer)->ReadBytes(fileData);
					auto b = fileData;

					//create_task(FileIO::WriteBytesAsync)
				}
				catch (COMException^ ex)
				{
					
				}
			});
			//task<StorageFile^> GetFileTask(KnownFolders::DocumentsLibrary->GetFileAsync(FileName));
		}
		else
		{
			return;
		}
	});
}


void CryptoLabUI::Page1_9::Decrypt(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}
