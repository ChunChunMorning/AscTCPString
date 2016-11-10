# pragma once
#include <Siv3D.hpp>

namespace asc
{
	using namespace s3d;

	class TCPStringClient : public TCPClient
	{
	public:

		bool readLine(String& to)
		{
			std::string buffer;

			for (;;)
			{
				if (hasError())
					return false;

				char character;

				if (!read(character))
					continue;

				if (character == '\n')
					break;

				buffer.push_back(character);
			}

			to = FromUTF8(buffer);
			return true;
		}
	};
}