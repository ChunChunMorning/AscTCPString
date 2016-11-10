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

		bool readChar(wchar& to)
		{
			if (m_buffer.length() > 0)
			{
				to = FromUTF8(m_buffer.substr(0, 1))[0];
				m_buffer = m_buffer.substr(1);
			}

			std::string buffer;

			if (!read(buffer[0]))
				return false;

			to = FromUTF8(buffer)[0];
			return true;
		}

		bool readString(size_t length, String& to)
		{
			if (m_buffer.length() >= length)
			{
				to = FromUTF8(m_buffer.substr(0, length));
				m_buffer = m_buffer.substr(length);
				return true;
			}

			for(;;)
			{
				char character;

				if (!read(character))
					return false;

				m_buffer.push_back(character);

				if (m_buffer.length() >= length)
				{
					to = FromUTF8(m_buffer.substr(0, length));
					m_buffer = m_buffer.substr(length);
					return true;
				}
			}

			return false;
		}

		bool readLine(String& to)
		{
			return readUntil(to, '\n');
		}

		bool readUntil(String& to, char end)
		{
			for (;;)
			{
				char character;

				if (!read(character))
					return false;

				if (character == end)
					break;

				m_buffer.push_back(character);
			}

			to = FromUTF8(m_buffer);
			return true;
		}
	};
}