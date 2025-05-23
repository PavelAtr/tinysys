#ifndef _TERMIOS_H
#define _TERMIOS_H

typedef unsigned char	cc_t;
typedef unsigned int	speed_t;
typedef unsigned int	tcflag_t;

struct winsize {
        unsigned short ws_row;
        unsigned short ws_col;
        unsigned short ws_xpixel;
        unsigned short ws_ypixel;
};

#define NCCS 32
struct termios
  {
    tcflag_t c_iflag;           /* input mode flags */
    tcflag_t c_oflag;           /* output mode flags */
    tcflag_t c_cflag;           /* control mode flags */
    tcflag_t c_lflag;           /* local mode flags */
    cc_t c_line;                        /* line discipline */
    cc_t c_cc[NCCS];            /* control characters */
    speed_t c_ispeed;           /* input speed */
    speed_t c_ospeed;           /* output speed */
#define _HAVE_STRUCT_TERMIOS_C_ISPEED 1
#define _HAVE_STRUCT_TERMIOS_C_OSPEED 1
  };

/* tcflow() and TCXONC use these */
#define TCOOFF          0
#define TCOON           1
#define TCIOFF          2
#define TCION           3

/* tcflush() and TCFLSH use these */
#define TCIFLUSH        0
#define TCOFLUSH        1
#define TCIOFLUSH       2



struct termios2 {
	tcflag_t c_iflag;		/* input mode flags */
	tcflag_t c_oflag;		/* output mode flags */
	tcflag_t c_cflag;		/* control mode flags */
	tcflag_t c_lflag;		/* local mode flags */
	cc_t c_line;			/* line discipline */
	cc_t c_cc[NCCS];		/* control characters */
	speed_t c_ispeed;		/* input speed */
	speed_t c_ospeed;		/* output speed */
};

struct ktermios {
	tcflag_t c_iflag;		/* input mode flags */
	tcflag_t c_oflag;		/* output mode flags */
	tcflag_t c_cflag;		/* control mode flags */
	tcflag_t c_lflag;		/* local mode flags */
	cc_t c_line;			/* line discipline */
	cc_t c_cc[NCCS];		/* control characters */
	speed_t c_ispeed;		/* input speed */
	speed_t c_ospeed;		/* output speed */
};

/* c_cc characters */
#define VINTR		 0
#define VQUIT		 1
#define VERASE		 2
#define VKILL		 3
#define VEOF		 4
#define VTIME		 5
#define VMIN		 6
#define VSWTC		 7
#define VSTART		 8
#define VSTOP		 9
#define VSUSP		10
#define VEOL		11
#define VREPRINT	12
#define VDISCARD	13
#define VWERASE		14
#define VLNEXT		15
#define VEOL2		16

/* c_iflag bits */
#define IUCLC	0x0200
#define IXON	0x0400
#define IXOFF	0x1000
#define IMAXBEL	0x2000
#define IUTF8	0x4000

/* c_oflag bits */
#define OLCUC	0x00002
#define ONLCR	0x00004
#define NLDLY	0x00100
#define   NL0	0x00000
#define   NL1	0x00100
#define CRDLY	0x00600
#define   CR0	0x00000
#define   CR1	0x00200
#define   CR2	0x00400
#define   CR3	0x00600
#define TABDLY	0x01800
#define   TAB0	0x00000
#define   TAB1	0x00800
#define   TAB2	0x01000
#define   TAB3	0x01800
#define   XTABS	0x01800
#define BSDLY	0x02000
#define   BS0	0x00000
#define   BS1	0x02000
#define VTDLY	0x04000
#define   VT0	0x00000
#define   VT1	0x04000
#define FFDLY	0x08000
#define   FF0	0x00000
#define   FF1	0x08000

/* c_cflag bit meaning */
#define CBAUD		0x0000100f
#define CSIZE		0x00000030
#define   CS5		0x00000000
#define   CS6		0x00000010
#define   CS7		0x00000020
#define   CS8		0x00000030
#define CSTOPB		0x00000040
#define CREAD		0x00000080
#define PARENB		0x00000100
#define PARODD		0x00000200
#define HUPCL		0x00000400
#define CLOCAL		0x00000800
#define CBAUDEX		0x00001000
#define BOTHER		0x00001000
#define     B57600	0x00001001
#define    B115200	0x00001002
#define    B230400	0x00001003
#define    B460800	0x00001004
#define    B500000	0x00001005
#define    B576000	0x00001006
#define    B921600	0x00001007
#define   B1000000	0x00001008
#define   B1152000	0x00001009
#define   B1500000	0x0000100a
#define   B2000000	0x0000100b
#define   B2500000	0x0000100c
#define   B3000000	0x0000100d
#define   B3500000	0x0000100e
#define   B4000000	0x0000100f
#define CIBAUD		0x100f0000	/* input baud rate */

/* c_lflag bits */
#define ISIG	0x00001
#define ICANON	0x00002
#define XCASE	0x00004
#define ECHO	0x00008
#define ECHOE	0x00010
#define ECHOK	0x00020
#define ECHONL	0x00040
#define NOFLSH	0x00080
#define TOSTOP	0x00100
#define ECHOCTL	0x00200
#define ECHOPRT	0x00400
#define ECHOKE	0x00800
#define FLUSHO	0x01000
#define PENDIN	0x04000
#define IEXTEN	0x08000
#define EXTPROC	0x10000

/* tcsetattr uses these */
#define	TCSANOW		0
#define	TCSADRAIN	1
#define	TCSAFLUSH	2

int tcgetattr(int fd, struct termios *termios_p);
int tcsetattr(int fd, int optional_actions,
  const struct termios *termios_p);

int tcsendbreak(int fd, int duration);
int tcdrain(int fd);
int tcflush(int fd, int queue_selector);
int tcflow(int fd, int action);

void cfmakeraw(struct termios *termios_p);

speed_t cfgetispeed(const struct termios *termios_p);
speed_t cfgetospeed(const struct termios *termios_p);

int cfsetispeed(struct termios *termios_p, speed_t speed);
int cfsetospeed(struct termios *termios_p, speed_t speed);
int cfsetspeed(struct termios *termios_p, speed_t speed);

/* c_iflag bits */
#define IGNBRK	0x001			/* Ignore break condition */
#define BRKINT	0x002			/* Signal interrupt on break */
#define IGNPAR	0x004			/* Ignore characters with parity errors */
#define PARMRK	0x008			/* Mark parity and framing errors */
#define INPCK	0x010			/* Enable input parity check */
#define ISTRIP	0x020			/* Strip 8th bit off characters */
#define INLCR	0x040			/* Map NL to CR on input */
#define IGNCR	0x080			/* Ignore CR */
#define ICRNL	0x100			/* Map CR to NL on input */
#define IXANY	0x800			/* Any character will restart after stop */

/* c_oflag bits */
#define OPOST	0x01			/* Perform output processing */
#define OCRNL	0x08
#define ONOCR	0x10
#define ONLRET	0x20
#define OFILL	0x40
#define OFDEL	0x80

/* c_cflag bit meaning */
/* Common CBAUD rates */
#define     B0		0x00000000	/* hang up */
#define    B50		0x00000001
#define    B75		0x00000002
#define   B110		0x00000003
#define   B134		0x00000004
#define   B150		0x00000005
#define   B200		0x00000006
#define   B300		0x00000007
#define   B600		0x00000008
#define  B1200		0x00000009
#define  B1800		0x0000000a
#define  B2400		0x0000000b
#define  B4800		0x0000000c
#define  B9600		0x0000000d
#define B19200		0x0000000e
#define B38400		0x0000000f
#define EXTA		B19200
#define EXTB		B38400

#define ADDRB		0x20000000	/* address bit */
#define CMSPAR		0x40000000	/* mark or space (stick) parity */
#define CRTSCTS		0x80000000	/* flow control */

#define IBSHIFT		16		/* Shift from CBAUD to CIBAUD */

/* tcflow() ACTION argument and TCXONC use these */
#define TCOOFF		0		/* Suspend output */
#define TCOON		1		/* Restart suspended output */
#define TCIOFF		2		/* Send a STOP character */
#define TCION		3		/* Send a START character */

/* tcflush() QUEUE_SELECTOR argument and TCFLSH use these */
#define TCIFLUSH	0		/* Discard data received but not yet read */
#define TCOFLUSH	1		/* Discard data written but not yet sent */
#define TCIOFLUSH	2		/* Discard all pending data */

#endif
