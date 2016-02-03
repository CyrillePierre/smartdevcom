
#include <string.h>
#include <fcntl.h>
#include <errno.h>                            
#include <stdio.h>
#include <pthread.h>

#include "uart.h"

Uart & Uart::get() {
	static Uart uart("/dev/ttyAMA0");
	return uart;
}

/**
 * filename : le nom du fichier du port série
 */
Uart::Uart(std::string const & filename) 
	: _fd(-1), _opened(false),_filename(filename)
{
}

/**
 * Cette fonction permet d'ouvrir et de configurer le port serie
 * pour la communication rs-232
 * @return false si une erreur est survenue sinon true
 */
bool Uart::open(speed_t baudrate) {
	struct termios options;
	//  fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
	_fd = ::open(_filename.c_str(), O_RDWR); // open device for read&write
	if (_fd < 0) return false;

	fcntl(_fd,F_SETFL,0);
	//    fcntl(fd, F_SETFL, FNDELAY); //ne pas bloquer sur le read
	tcgetattr(_fd,&options);
	usleep(10000);
    cfsetospeed(&options, baudrate);
    cfsetispeed(&options, baudrate);
	options.c_cflag &= ~PARENB; /* Parite   : none */
	options.c_cflag &= ~CSTOPB; /* Stop bit : 1    */
	options.c_cflag &= ~CSIZE;  /* Bits     : 8    */
	options.c_cflag |= CS8;
	options.c_oflag &= ~CRTSCTS;
	// options.c_iflag &= ~(IXON);
	// tcsetattr(fd,TCSANOW,&options);
	options.c_oflag &= ~OPOST;
	options.c_lflag &= ~(ICANON | ECHO | ECHONL|IEXTEN | ISIG);
	// c_cc
	options.c_cc[VMIN] = 1;
	options.c_cc[VTIME] = 4;		// timeout = 0.4s
	// flush!
	//    tcflush(fd,TCIOFLUSH);
	tcsetattr(_fd, TCSANOW, &options);
	tcflush(_fd,TCIOFLUSH);
	usleep(10000);

	return true;
}

/**
 * Cette fonction permet de fermer le port serie
 */
void Uart::close() {
	::close(_fd);
}

