#include "streamio.h"

namespace NaiSys {

std::ostringstream *StreamIO::sBufferStream =
        new std::ostringstream(std::ostringstream::ate);
std::ostream *StreamIO::sOutputStream = &std::cout;

StreamIO::StreamIO()
{
}

StreamIO::StreamIO(const std::ostream &out)
{

}

size_t StreamIO::println(const char *wrd, ...)
{
    va_list args;
    va_start(args, wrd);

    std::string v = wrd;
    size_t arg_count = std::count(v.begin(), v.end(), '%');
    //size_t arg_count = v.find_last_of("%arg");

    for(int i=0; i<(int)arg_count; ++i){
        size_t pos = v.find("%arg");
        if(pos < v.length()-1){
            auto val = va_arg(args,char *);
            v.replace(pos, 4, val);
        }
    }

    *StreamIO::sBufferStream << v <<"\n";
    //FIXME: Find a way to make writing to stdout faster...
    *StreamIO::sOutputStream << v <<"\n";

    va_end(args);
    return sizeof(wrd);
}

std::ostringstream *StreamIO::getSBufferStream()
{
    return sBufferStream;
}

//=========================================

StreamIO::IODevice::IODevice(std::stringstream &buffer)
    : m_data{buffer},
      m_bufferdata{buffer.str()},
      m_cursor{0}
{
    std::string temp;
    while (std::getline(m_data, temp, '\n')) {
        m_vecbuffer.push_back(temp);
    }
    m_lineCount = m_vecbuffer.size();
    m_lineCount > 0 ? m_canReadLine = true : m_canReadLine = false;
}

const std::string StreamIO::IODevice::readLine()
{
    auto const ret = m_vecbuffer[m_cursor];
    m_cursor < m_lineCount-1 ?
                m_canReadLine = true :
                m_canReadLine = false;
    m_canReadLine ? m_cursor += 1 : m_cursor += 0;
    return ret;
}

bool StreamIO::IODevice::canReadLine() const
{return m_canReadLine;}

int StreamIO::IODevice::lineCount() const
{return m_lineCount;}

int StreamIO::IODevice::cursor() const
{return m_cursor;}

void StreamIO::IODevice::setCursor(int newCursor)
{
    m_cursor = newCursor;
    m_cursor < m_lineCount-1 ?
                m_canReadLine = true :
                m_canReadLine = false;
}

std::stringstream &StreamIO::IODevice::data() const
{return m_data;}

} // namespace NaiSys
