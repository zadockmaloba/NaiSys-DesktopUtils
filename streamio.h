#ifndef NAISYS_STREAMIO_H
#define NAISYS_STREAMIO_H

#include <ostream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>

#include <stdarg.h>

#define NAISYS_BUFFER_DEV(x,y)     std::stringstream x;\
                                   x << NaiSys::StreamIO::getSBufferStream()->str();\
                                   NaiSys::StreamIO::IODevice y(x);

#define QSTRING_TO_CSTR(x) x.toStdString().c_str()

namespace NaiSys {

class StreamIO
{
public:
    class IODevice
    {
    public:
        IODevice(std::stringstream &buffer);
        const std::string readLine();

        std::stringstream &data() const;
        int cursor() const;
        void setCursor(int newCursor);
        int lineCount() const;
        bool canReadLine() const;

    private:
        std::stringstream &m_data;
        std::string m_bufferdata;
        std::vector<std::string> m_vecbuffer;
        int m_cursor, m_lineCount;
        bool m_canReadLine;
    };

public:
    StreamIO();
    StreamIO(const std::ostream &out);
    static size_t println(const char *wrd, ...);
    static std::ostringstream *getSBufferStream();

private://static objects
    static std::ostringstream *sBufferStream;
    static std::ostream *sOutputStream;
};

} // namespace NaiSys

#endif // NAISYS_STREAMIO_H
