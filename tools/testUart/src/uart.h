#ifndef UART_H
#define UART_H

#include <string>
#include <unistd.h>
#include <termios.h>

struct Uart {
	int         _fd;
	bool        _opened;
	std::string _filename;

public:
	static Uart & get();

	Uart(std::string const &);

    bool open(speed_t baudrate);
	void close();

	template <typename Buffer>
	ssize_t write(Buffer &&, size_t) const;

	template <typename Buffer>
	ssize_t read(Buffer &&, size_t) const;
};

template <typename Buffer>
ssize_t Uart::write(Buffer && buf, size_t size) const {
	return ::write(_fd, std::forward<Buffer>(buf), size);
}

template <typename Buffer>
ssize_t Uart::read(Buffer && buf, size_t size) const {
	return ::read(_fd, std::forward<Buffer>(buf), size);
}

#endif
