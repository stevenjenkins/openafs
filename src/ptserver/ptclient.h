/*
 * Copyright 2000, International Business Machines Corporation and others.
 * All Rights Reserved.
 * 
 * This software has been released under the terms of the IBM Public
 * License.  For details, see the LICENSE file in the top-level source
 * directory or online at http://www.openafs.org/dl/license10.html
 */

#if defined(UKERNEL)
#include "afs/lock.h"
#include "ubik.h"
#include "afs/ptint.h"
#include "afs/ptserver.h"
#else /* defined(UKERNEL) */
#include <lock.h>
#include <ubik.h>
#include "ptint.h"
#include "ptserver.h"
#endif /* defined(UKERNEL) */

#define pr_ErrorMsg afs_error_message
