# pragma once
#include <Siv3D.hpp>

namespace asc
{
	using namespace s3d;

	class TCPStringClient : public TCPClient
	{
	private:

		std::string m_buffer;

	public:

		bool readLine(String& to)
		{
			for (;;)
			{
				char character;

				if (!read(character))
					return false;

				if (character == '\n')
					break;

				m_buffer.push_back(character);
			}

			to = FromUTF8(m_buffer);
			return true;
		}
	};
}