/****************************************************************************
 *  apps/include/netutils/ssl_connection.h
 * Header file for the SSL client socket
 *
 *   Copyright 2020 Sony Semiconductor Solutions Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef __APPS_INCLUDE_NETUTILS_SSL_CONNECTION_METHODS_H
#define __APPS_INCLUDE_NETUTILS_SSL_CONNECTION_METHODS_H

/****************************************************************************
 * Public types
 ****************************************************************************/

struct sock_methods_s
{
  int (*connect)(int use_ssl, FAR const char *host, uint16_t port);
  ssize_t (*send)(int fd, FAR const void *buf, size_t len, int flags);
  ssize_t (*recv)(int fd, FAR void *buf, size_t len, int flags);
  int (*close)(int fd);
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/* 
 * Platform must be provided of this get_sslsock_connection_methods()
 * to set sock_methods_s for SSL/TLS connection.
 */

void get_sslsocket_methods(FAR struct sock_methods_s *methods);

#endif /* __APPS_INCLUDE_NETUTILS_CONNECTION_METHODS_H */
