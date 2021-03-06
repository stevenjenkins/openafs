/*
 * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
 * unrestricted use provided that this legend is included on all tape
 * media and as a part of the software program in whole or part.  Users
 * may copy or modify Sun RPC without charge, but are not authorized
 * to license or distribute it to anyone else except as part of a product or
 * program developed by the user.
 * 
 * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
 * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 * 
 * Sun RPC is provided with no support and without any obligation on the
 * part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 * 
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
 * OR ANY PART THEREOF.
 * 
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 * 
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043
 */
#include <afsconfig.h>
#include <afs/param.h>

/*
 * xdr_mem.h, XDR implementation using memory buffers.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 *
 * If you have some data to be interpreted as external data representation
 * or to be converted to external data representation in a memory buffer,
 * then this is the package for you.
 *
 */

#ifdef KERNEL
# include "afs/sysincludes.h"
#else
# include <string.h>
# include <limits.h>
# ifndef AFS_NT40_ENV
#  include <netinet/in.h>
# endif
#endif

#ifndef KERNEL
#include "xdr.h"
#elif !defined(UKERNEL)
#include "rx/xdr.h"
#else
#include "rpc/types.h"
#include "rpc/xdr.h"
#define AFS_XDRS_T XDR *
#endif

static bool_t xdrmem_getint32(AFS_XDRS_T axdrs, afs_int32 * lp);
static bool_t xdrmem_putint32(AFS_XDRS_T axdrs, afs_int32 * lp);
static bool_t xdrmem_getbytes(AFS_XDRS_T axdrs, caddr_t addr, u_int len);
static bool_t xdrmem_putbytes(AFS_XDRS_T axdrs, caddr_t addr, u_int len);
static u_int xdrmem_getpos(AFS_XDRS_T axdrs);
static bool_t xdrmem_setpos(AFS_XDRS_T axdrs, u_int pos);
static afs_int32 *xdrmem_inline(AFS_XDRS_T axdrs, u_int len);
static void xdrmem_destroy(AFS_XDRS_T axdrs);

static struct xdr_ops xdrmem_ops = {
#if defined(AFS_NT40_ENV) || (defined(AFS_SGI_ENV) && !defined(__c99))
    /* Windows does not support labeled assigments */
    xdrmem_getint32,    /* deserialize an afs_int32 */
    xdrmem_putint32,    /* serialize an afs_int32 */
    xdrmem_getbytes,    /* deserialize counted bytes */
    xdrmem_putbytes,    /* serialize counted bytes */
    xdrmem_getpos,      /* get offset in the stream: not supported. */
    xdrmem_setpos,      /* set offset in the stream: not supported. */
    xdrmem_inline,      /* prime stream for inline macros */
    xdrmem_destroy      /* destroy stream */
#else
#if defined(UKERNEL)
    .x_getlong = xdrmem_getint32,
    .x_putlong = xdrmem_putint32,
#else
    .x_getint32 = xdrmem_getint32,       /* deserialize an afs_int32 */
    .x_putint32 = xdrmem_putint32,       /* serialize an afs_int32 */
#endif
    .x_getbytes = xdrmem_getbytes,
    .x_putbytes = xdrmem_putbytes,
    .x_getpostn = xdrmem_getpos,
    .x_setpostn = xdrmem_setpos,
    .x_inline = xdrmem_inline,
    .x_destroy = xdrmem_destroy
#endif
};

/*
 * The procedure xdrmem_create initializes a stream descriptor for a
 * memory buffer.  
 */
void
xdrmem_create(XDR * xdrs, caddr_t addr, u_int size, enum xdr_op op)
{
    xdrs->x_op = op;
    xdrs->x_ops = &xdrmem_ops;
    xdrs->x_private = xdrs->x_base = addr;
    xdrs->x_handy = (size > INT_MAX) ? INT_MAX : size;	/* XXX */
}

static void
xdrmem_destroy(AFS_XDRS_T axdrs)
{
}

static bool_t
xdrmem_getint32(AFS_XDRS_T axdrs, afs_int32 * lp)
{
    XDR * xdrs = (XDR *)axdrs;

    if (xdrs->x_handy < sizeof(afs_int32))
	return (FALSE);
    else
	xdrs->x_handy -= sizeof(afs_int32);
    *lp = ntohl(*((afs_int32 *) (xdrs->x_private)));
    xdrs->x_private += sizeof(afs_int32);
    return (TRUE);
}

static bool_t
xdrmem_putint32(AFS_XDRS_T axdrs, afs_int32 * lp)
{
    XDR * xdrs = (XDR *)axdrs;

    if (xdrs->x_handy < sizeof(afs_int32))
	return (FALSE);
    else
	xdrs->x_handy -= sizeof(afs_int32);
    *(afs_int32 *) xdrs->x_private = htonl(*lp);
    xdrs->x_private += sizeof(afs_int32);
    return (TRUE);
}

static bool_t
xdrmem_getbytes(AFS_XDRS_T axdrs, caddr_t addr, u_int len)
{
    XDR * xdrs = (XDR *)axdrs;

    if (xdrs->x_handy < len)
	return (FALSE);
    else
	xdrs->x_handy -= len;
    memcpy(addr, xdrs->x_private, len);
    xdrs->x_private += len;
    return (TRUE);
}

static bool_t
xdrmem_putbytes(AFS_XDRS_T axdrs, caddr_t addr, u_int len)
{
    XDR * xdrs = (XDR *)axdrs;

    if (xdrs->x_handy < len)
	return (FALSE);
    else
	xdrs->x_handy -= len;
    memcpy(xdrs->x_private, addr, len);
    xdrs->x_private += len;
    return (TRUE);
}

static u_int
xdrmem_getpos(AFS_XDRS_T axdrs)
{
    XDR * xdrs = (XDR *)axdrs;

    return ((u_int)((char *)xdrs->x_private - xdrs->x_base));
}

static bool_t
xdrmem_setpos(AFS_XDRS_T axdrs, u_int pos)
{
    XDR * xdrs = (XDR *)axdrs;

    caddr_t newaddr = xdrs->x_base + pos;
    caddr_t lastaddr = xdrs->x_private + xdrs->x_handy;

    if (newaddr > lastaddr)
	return (FALSE);
    xdrs->x_private = newaddr;
    xdrs->x_handy = (int)(lastaddr - newaddr);
    return (TRUE);
}

static afs_int32 *
xdrmem_inline(AFS_XDRS_T axdrs, u_int len)
{
    XDR * xdrs = (XDR *)axdrs;

    afs_int32 *buf = 0;

    if (len >= 0 && xdrs->x_handy >= len) {
	xdrs->x_handy -= len;
	buf = (afs_int32 *) xdrs->x_private;
	xdrs->x_private += len;
    }
    return (buf);
}
