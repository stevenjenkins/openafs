/*
 * Copyright 2005-2008, Sine Nomine Associates and others.
 * All Rights Reserved.
 * 
 * This software has been released under the terms of the IBM Public
 * License.  For details, see the LICENSE file in the top-level source
 * directory or online at http://www.openafs.org/dl/license10.html
 */

#ifndef _AFS_VOL_VOLUME_INLINE_H
#define _AFS_VOL_VOLUME_INLINE_H 1

#include "volume.h"
/**
 * tell caller whether the given program type represents a salvaging
 * program.
 *
 * @param type  program type enumeration
 *
 * @return whether program state is a salvager
 *   @retval 0  type is a non-salvaging program
 *   @retval 1  type is a salvaging program
 */
static_inline int
VIsSalvager(ProgramType type)
{
    switch(type) {
    case salvager:
    case salvageServer:
    case volumeSalvager:
	return 1;
    default:
	return 0;
    }
}

/**
 * tells caller whether or not we need to lock the entire partition when
 * attaching a volume.
 *
 * @return whether or not we need to lock the partition
 *  @retval 0  no, we do not
 *  @retval 1  yes, we do
 */
static_inline int
VRequiresPartLock(void)
{
    switch (programType) {
    case volumeServer:
    case volumeUtility:
        return 1;
    default:
        return 0;
    }
}

/**
 * tells caller whether we should check the inUse field in the volume
 * header when attaching a volume.
 *
 * If we check inUse, that generally means we will salvage the volume
 * (or put it in an error state) if we detect that another program
 * claims to be using the volume when we try to attach. We don't always
 * want to do that, since sometimes we know that the volume may be in
 * use by another program, e.g. when we are attaching with V_PEEK, and
 * we don't care.
 *
 * @param mode  the mode of attachment for the volume
 *
 * @return whether or not we should check inUse
 *  @retval 0  no, we should not check inUse
 *  @retval 1  yes, we should check inUse
 */
static_inline int
VShouldCheckInUse(int mode)
{
    if (programType == fileServer) {
       return 1;
    }
    if (VCanUseFSSYNC() && mode != V_SECRETLY && mode != V_PEEK) {
       /* If we can FSSYNC, we assume we checked out the volume from
        * the fileserver, so inUse should not be set. If we checked out
        * with V_SECRETLY or V_PEEK, though, we didn't ask the
        * fileserver, so don't check inUse. */
       return 1;
    }
    return 0;
}

/***************************************************/
/* demand attach fs state machine routines         */
/***************************************************/

#ifdef AFS_DEMAND_ATTACH_FS
/**
 * tells caller whether or not the current state requires
 * exclusive access without holding glock.
 *
 * @param state  volume state enumeration
 *
 * @return whether volume state is a mutually exclusive state
 *   @retval 0  no, state is re-entrant
 *   @retval 1  yes, state is mutually exclusive
 *
 * @note DEMAND_ATTACH_FS only
 */
static_inline int
VIsExclusiveState(VolState state)
{
    switch (state) {
    case VOL_STATE_UPDATING:
    case VOL_STATE_ATTACHING:
    case VOL_STATE_GET_BITMAP:
    case VOL_STATE_HDR_LOADING:
    case VOL_STATE_HDR_ATTACHING:
    case VOL_STATE_OFFLINING:
    case VOL_STATE_DETACHING:
    case VOL_STATE_SALVSYNC_REQ:
    case VOL_STATE_VNODE_ALLOC:
    case VOL_STATE_VNODE_GET:
    case VOL_STATE_VNODE_CLOSE:
    case VOL_STATE_VNODE_RELEASE:
    case VOL_STATE_VLRU_ADD:
	return 1;
    default:
	return 0;
    }
}

/**
 * tell caller whether V_attachState is an error condition.
 *
 * @param state  volume state enumeration
 *
 * @return whether volume state is in error state
 *   @retval 0  state is not an error state
 *   @retval 1  state is an error state
 *
 * @note DEMAND_ATTACH_FS only
 */
static_inline int
VIsErrorState(VolState state)
{
    switch (state) {
    case VOL_STATE_ERROR:
    case VOL_STATE_SALVAGING:
	return 1;
    default:
	return 0;
    }
}

/**
 * tell caller whether V_attachState is an offline condition.
 *
 * @param state  volume state enumeration
 *
 * @return whether volume state is in offline state
 *   @retval 0  state is not an offline state
 *   @retval 1  state is an offline state
 *
 * @note DEMAND_ATTACH_FS only
 */
static_inline int
VIsOfflineState(VolState state)
{
    switch (state) {
    case VOL_STATE_UNATTACHED:
    case VOL_STATE_ERROR:
    case VOL_STATE_SALVAGING:
	return 1;
    default:
	return 0;
    }
}

/**
 * tell caller whether V_attachState is valid.
 *
 * @param state  volume state enumeration
 *
 * @return whether volume state is a mutually exclusive state
 *   @retval 0  no, state is not valid
 *   @retval 1  yes, state is a valid enumeration member
 *
 * @note DEMAND_ATTACH_FS only
 *
 * @note do we really want to treat VOL_STATE_FREED as valid?
 */
static_inline int
VIsValidState(VolState state)
{
    if ((state >= 0) && 
	(state < VOL_STATE_COUNT)) {
	return 1;
    }
    return 0;
}

/**
 * increment volume-package internal refcount.
 *
 * @param vp  volume object pointer
 *
 * @internal volume package internal use only
 *
 * @pre VOL_LOCK must be held
 *
 * @post volume waiters refcount is incremented
 *
 * @see VCancelReservation_r
 *
 * @note DEMAND_ATTACH_FS only
 */
static_inline void
VCreateReservation_r(Volume * vp)
{
    vp->nWaiters++;
}

/**
 * wait for the volume to change states.
 *
 * @param vp  volume object pointer
 *
 * @pre VOL_LOCK held; ref held on volume
 *
 * @post VOL_LOCK held; volume state has changed from previous value
 *
 * @note DEMAND_ATTACH_FS only
 */
static_inline void
VWaitStateChange_r(Volume * vp)
{
    VolState state_save = V_attachState(vp);

    assert(vp->nWaiters || vp->nUsers);
    do {
	VOL_CV_WAIT(&V_attachCV(vp));
    } while (V_attachState(vp) == state_save);
    assert(V_attachState(vp) != VOL_STATE_FREED);
}

/**
 * wait for blocking ops to end.
 *
 * @pre VOL_LOCK held; ref held on volume
 *
 * @post VOL_LOCK held; volume not in exclusive state
 *
 * @param vp  volume object pointer
 *
 * @note DEMAND_ATTACH_FS only
 */
static_inline void
VWaitExclusiveState_r(Volume * vp)
{
    assert(vp->nWaiters || vp->nUsers);
    while (VIsExclusiveState(V_attachState(vp))) {
	VOL_CV_WAIT(&V_attachCV(vp));
    }
    assert(V_attachState(vp) != VOL_STATE_FREED);
}

/**
 * change state, and notify other threads,
 * return previous state to caller.
 *
 * @param vp         pointer to volume object
 * @param new_state  new volume state value
 * @pre VOL_LOCK held
 *
 * @post volume state changed; stats updated
 *
 * @return previous volume state
 *
 * @note DEMAND_ATTACH_FS only
 */
static_inline VolState
VChangeState_r(Volume * vp, VolState new_state)
{
    VolState old_state = V_attachState(vp);

    /* XXX profiling need to make sure these counters
     * don't kill performance... */
    VStats.state_levels[old_state]--;
    VStats.state_levels[new_state]++;

    V_attachState(vp) = new_state;
    assert(pthread_cond_broadcast(&V_attachCV(vp)) == 0);
    return old_state;
}

#endif /* AFS_DEMAND_ATTACH_FS */

#endif /* _AFS_VOL_VOLUME_INLINE_H */
