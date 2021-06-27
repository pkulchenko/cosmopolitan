#ifndef USOCKET_H
#define USOCKET_H
/*=========================================================================*\
* Socket compatibilization module for Unix
* LuaSocket toolkit
\*=========================================================================*/

/*=========================================================================*\
* BSD include files
\*=========================================================================*/
/* error codes */
#include <libc/isystem/errno.h>
/* close function */
#include <libc/isystem/unistd.h>
/* fnctnl function and associated constants */
#include <libc/isystem/fcntl.h>
/* struct sockaddr */
#include <libc/isystem/sys/types.h>
/* socket function */
#include <libc/isystem/sys/socket.h>
/* struct timeval */
#include <libc/isystem/sys/time.h>
/* sigpipe handling */
#include <libc/isystem/signal.h>
/* IP stuff*/
#include <libc/isystem/arpa/inet.h>

/* Some platforms use IPV6_JOIN_GROUP instead if
 * IPV6_ADD_MEMBERSHIP. The semantics are same, though. */
#ifndef IPV6_ADD_MEMBERSHIP
#ifdef IPV6_JOIN_GROUP
#define IPV6_ADD_MEMBERSHIP IPV6_JOIN_GROUP
#endif /* IPV6_JOIN_GROUP */
#endif /* !IPV6_ADD_MEMBERSHIP */

/* Same with IPV6_DROP_MEMBERSHIP / IPV6_LEAVE_GROUP. */
#ifndef IPV6_DROP_MEMBERSHIP
#ifdef IPV6_LEAVE_GROUP
#define IPV6_DROP_MEMBERSHIP IPV6_LEAVE_GROUP
#endif /* IPV6_LEAVE_GROUP */
#endif /* !IPV6_DROP_MEMBERSHIP */

typedef int t_socket;
typedef t_socket *p_socket;
typedef struct sockaddr_storage t_sockaddr_storage;

#define SOCKET_INVALID (-1)

#endif /* USOCKET_H */
