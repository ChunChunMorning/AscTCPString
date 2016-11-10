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
			String buffer = FromUTF8(m_buffer);

			if (buffer.length > 0)
			{
				to = buffer[0];
				m_buffer = ToUTF8(buffer.substr(1));
				return true;
			}

			char character;

			if(!read(character))
				return false;

			m_buffer.push_back(character);
			buffer = FromUTF8(m_buffer);

			if (buffer.length > 0)
			{
				to = buffer[0];
				m_buffer = ToUTF8(buffer.substr(1));
				return true;
			}

			return false;
		}

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