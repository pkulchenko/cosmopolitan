#ifndef SOCKET_H
#define SOCKET_H
/*=========================================================================*\
* Socket compatibilization module
* LuaSocket toolkit
*
* BSD Sockets and WinSock are similar, but there are a few irritating
* differences. Also, not all *nix platforms behave the same. This module
* (and the associated usocket.h and wsocket.h) factor these differences and
* creates a interface compatible with the io.h module.
\*=========================================================================*/
#include "io.h"

/*=========================================================================*\
* Platform specific compatibilization
\*=========================================================================*/
#include "usocket.h"

/*=========================================================================*\
* The connect and accept functions accept a timeout and their
* implementations are somewhat complicated. We chose to move
* the timeout control into this module for these functions in
* order to simplify the modules that use them. 
\*=========================================================================*/
#include "timeout.h"

/* convenient shorthand */
typedef struct sockaddr SA;

#include <libc/sock/select.h>

#include <libc/sysv/consts/sock.h>
#include <libc/sysv/consts/af.h>
#include <libc/sysv/consts/inaddr.h>
#include <libc/sysv/consts/ipproto.h>
#include <libc/sysv/consts/ipv6.h>
#include <libc/sysv/consts/ip.h>
#include <libc/sysv/consts/sol.h>
#include <libc/sysv/consts/so.h>
#include <libc/sysv/consts/tcp.h>
#include <libc/dns/dns.h>

typedef unsigned short u_short;
typedef unsigned long u_long;
typedef unsigned char u_char;

// in6addr.h
typedef struct in6_addr {
  union {
    unsigned char Byte[16];
    unsigned short Word[8];
  } u;
} in6_addr;

#define _S6_un		u
#define _S6_u8		Byte
#define s6_addr		_S6_un._S6_u8

// ws2ipdef.h
struct sockaddr_in6 {
  short sin6_family;
  unsigned short sin6_port;
  unsigned long sin6_flowinfo;
  struct in6_addr sin6_addr;
  unsigned long sin6_scope_id;
};

struct ipv6_mreq {
    struct in6_addr    ipv6mr_multiaddr;    /* IPv6 multicast addr */
    unsigned int       ipv6mr_interface;    /* interface index */
};

#define IN6ADDR_ANY_INIT {{{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }}}

struct servent{
  char  *s_name;         /* official service name                            */
  char **s_aliases;      /* alias list                                       */
  int    s_port;         /* port number, network-byte order                  */
  char  *s_proto;        /* protocol to use                                  */
};

struct hostent {
    char  *h_name;            /* official name of host */
    char **h_aliases;         /* alias list */
    int    h_addrtype;        /* host address type */
    int    h_length;          /* length of address */
    char **h_addr_list;       /* list of addresses */
};
#define h_addr h_addr_list[0]

#define INET6_ADDRSTRLEN 46

#define HOST_NOT_FOUND	1        /* Authoritative Answer Host not found.  */
#define TRY_AGAIN	2        /* Non-Authoritative Host not found, or SERVERFAIL.  */
#define NO_RECOVERY	3        /* Non recoverable errors, FORMERR, REFUSED, NOTIMP.  */
#define NO_DATA		4        /* Valid name, no data record of requested type.  */

#define SUCCESS 0
#define YES 1
#define NO  0

static struct gni_afd {
    int a_af;
    int a_addrlen;
    int a_socklen;
    int a_off;
} gni_afd;

struct gni_sockinet {
    u_char      si_len;
    u_char      si_family;
    u_short     si_port;
};

#define ENI_NOSOCKET    0
#define ENI_NOSERVNAME  1
#define ENI_NOHOSTNAME  2
#define ENI_MEMORY      3
#define ENI_SYSTEM      4
#define ENI_FAMILY      5
#define ENI_SALEN       6

/*=========================================================================*\
* Functions bellow implement a comfortable platform independent 
* interface to sockets
\*=========================================================================*/

#ifndef _WIN32
#pragma GCC visibility push(hidden)
#endif

int socket_waitfd(p_socket ps, int sw, p_timeout tm);
int socket_open(void);
int socket_close(void);
void socket_destroy(p_socket ps);
int socket_select(t_socket n, fd_set *rfds, fd_set *wfds, fd_set *efds, p_timeout tm);
int socket_create(p_socket ps, int domain, int type, int protocol);
int socket_bind(p_socket ps, SA *addr, socklen_t addr_len); 
int socket_listen(p_socket ps, int backlog);
void socket_shutdown(p_socket ps, int how); 
int socket_connect(p_socket ps, SA *addr, socklen_t addr_len, p_timeout tm); 
int socket_accept(p_socket ps, p_socket pa, SA *addr, socklen_t *addr_len, p_timeout tm);
int socket_send(p_socket ps, const char *data, size_t count, size_t *sent, p_timeout tm);
int socket_sendto(p_socket ps, const char *data, size_t count, size_t *sent, SA *addr, socklen_t addr_len, p_timeout tm);
int socket_recv(p_socket ps, char *data, size_t count, size_t *got, p_timeout tm);
int socket_recvfrom(p_socket ps, char *data, size_t count, size_t *got, SA *addr, socklen_t *addr_len, p_timeout tm);
int socket_write(p_socket ps, const char *data, size_t count, size_t *sent, p_timeout tm);
int socket_read(p_socket ps, char *data, size_t count, size_t *got, p_timeout tm);
void socket_setblocking(p_socket ps);
void socket_setnonblocking(p_socket ps);
int socket_gethostbyaddr(const char *addr, socklen_t len, struct hostent **hp);
int socket_gethostbyname(const char *addr, struct hostent **hp);
const char *socket_hoststrerror(int err);
const char *socket_strerror(int err);
const char *socket_ioerror(p_socket ps, int err);
const char *socket_gaistrerror(int err);

#ifndef _WIN32
#pragma GCC visibility pop
#endif

#endif /* SOCKET_H */
