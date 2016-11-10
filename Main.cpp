# include <Siv3D.hpp>
# include "asc/TCPString.hpp"

void Main()
{
	asc::TCPStringClient client;
	client.connect(IPv4::localhost(), 50000);

	Window::SetTitle(L"接続待機中...");

	while (System::Update())
	{
		if (client.isConnected())
		{
			Window::SetTitle(L"接続完了！");

			client.sendString(L"Hello\n");
			Print(L"Send: Hello\n");

			String str;

			if (client.readLine(str))
			{
				Print(L"Receive: ", str);
			}
		}

		if (client.hasError())
		{
			client.disconnect();

			Window::SetTitle(L"再接続待機中...");

			client.connect(IPv4::localhost(), 50000);
		}
	}
}
