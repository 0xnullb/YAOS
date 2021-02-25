#include "tty_driver.h"

TtyDriver::TtyDriver()
{
    m_width = VgaHelper::GetVgaWidth();
    m_height = VgaHelper::GetVgaHeight();
    m_terminal_color = VgaHelper::MakeColor(VgaColor::LightGray, VgaColor::Black);
    m_cursor_x = 0;
    m_cursor_y = 0;
}

int TtyDriver::GetTerminalColor()
{
    return m_terminal_color;
}

void TtyDriver::SetTerminalColor(VgaColor fg, VgaColor bg)
{
    m_terminal_color = VgaHelper::MakeColor(fg, bg);
}

void TtyDriver::Write(char c)
{
    unsigned int width = VgaHelper::GetVgaWidth();
    unsigned int i = m_cursor_y * width + m_cursor_x;
    unsigned char* vidmem = (unsigned char*) 0xB8000; // extract to const??

    vidmem[i++] = c;
    vidmem[i] = m_terminal_color;
    m_cursor_x++;

    if (m_cursor_x > width) {
        m_cursor_x = 0;
        m_cursor_y += 2;
    }
}
