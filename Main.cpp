# include <Siv3D.hpp>
# include "asc/AscTCPStringClient.hpp"

void Main()
{
	asc::TCPStringClient client;
	client.connect(IPv4::localhost(), 1435);

	while (System::Update())
	{
		Println(L"Loop: ", System::FrameCount());

		if (client.isConnected())
		{
			std::string str = "Hello\n";
			String wstr;

			client.send(str.data(), sizeof(char) * str.length());

			Print(L"Send: ", Widen(str));

			if (client.readLine(wstr))
			{
				Println(L"Receive: ", wstr);
			}
			else
			{
				Println(L"Failed");
			}
		}

		if (client.hasError())
		{
			client.disconnect();

			client.connect(IPv4::localhost(), 1435);
		}
	}
}
