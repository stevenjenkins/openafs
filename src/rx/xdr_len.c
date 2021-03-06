/*
 * Copyright (c) 2010 Your Filesystem Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR `AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <afsconfig.h>
#include <afs/param.h>

#ifdef KERNEL
# include "afs/sysincludes.h"
#else
# include <stdlib.h>
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

static void
xdrlen_destroy(AFS_XDRS_T axdrs)
{
}

static bool_t
xdrlen_getint32(AFS_XDRS_T axdrs, afs_int32 * lp)
{
    return (FALSE);
}

static bool_t
xdrlen_putint32(AFS_XDRS_T axdrs, afs_int32 * lp)
{
    XDR * xdrs = (XDR *)axdrs;

    xdrs->x_handy += sizeof(afs_int32);
    return (TRUE);
}

static bool_t
xdrlen_getbytes(AFS_XDRS_T axdrs, caddr_t addr, u_int len)
{
    return (FALSE);
}

static bool_t
xdrlen_putbytes(AFS_XDRS_T axdrs, caddr_t addr, u_int len)
{
    XDR * xdrs = (XDR *)axdrs;

    xdrs->x_handy += len;
    return (TRUE);
}

static u_int
xdrlen_getpos(AFS_XDRS_T axdrs)
{
    XDR * xdrs = (XDR *)axdrs;

    return xdrs->x_handy;
}

static bool_t
xdrlen_setpos(AFS_XDRS_T axdrs, u_int pos)
{
    XDR * xdrs = (XDR *)axdrs;

    xdrs->x_handy = pos;
    return (TRUE);
}

static afs_int32 *
xdrlen_inline(AFS_XDRS_T axdrs, u_int len)
{
    return NULL;
}

static struct xdr_ops xdrlen_ops = {
#if defined(AFS_NT40_ENV) || (defined(AFS_SGI_ENV) && !defined(__c99))
    /* Windows does not support labeled assigments */
    xdrlen_getint32,    /* not supported */
    xdrlen_putint32,    /* serialize an afs_int32 */
    xdrlen_getbytes,    /* not supported */
    xdrlen_putbytes,    /* serialize counted bytes */
    xdrlen_getpos,      /* get offset in the stream */
    xdrlen_setpos,      /* set offset in the stream */
    xdrlen_inline,      /* not supported */
    xdrlen_destroy      /* destroy stream */
#else
#if defined(UKERNEL)
    .x_getlong = xdrlen_getint32,
    .x_putlong = xdrlen_putint32,
#else
    .x_getint32 = xdrlen_getint32,
    .x_putint32 = xdrlen_putint32,
#endif
    .x_getbytes = xdrlen_getbytes,
    .x_putbytes = xdrlen_putbytes,
    .x_getpostn = xdrlen_getpos,
    .x_setpostn = xdrlen_setpos,
    .x_inline = xdrlen_inline,
    .x_destroy = xdrlen_destroy
#endif
};

/**
 * Initialise an XDR stream to calculate the space required to encode
 *
 * This initialises an XDR stream object which can be used to calculate
 * the space required to encode a particular structure into memory. No
 * encoding is actually performed, a later call using xdrmem is necessary
 * to do so.
 *
 * @param xdrs
 * 	A pointer to a preallocated XDR sized block of memory.
 */
void
xdrlen_create(XDR * xdrs)
{
    xdrs->x_op = XDR_ENCODE;
    xdrs->x_ops = &xdrlen_ops;
    xdrs->x_handy = 0;
}
