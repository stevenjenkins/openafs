/*
 * Copyright 2000, International Business Machines Corporation and others.
 * All Rights Reserved.
 * 
 * This software has been released under the terms of the IBM Public
 * License.  For details, see the LICENSE file in the top-level source
 * directory or online at http://www.openafs.org/dl/license10.html
 */

#ifndef _AFS_PROTOTYPES_H_
#define _AFS_PROTOTYPES_H_

/* afs_analyze.c */
extern int afs_Analyze(register struct afs_conn *aconn, afs_int32 acode,
		       struct VenusFid *afid, register struct vrequest *areq,
		       int op, afs_int32 locktype, struct cell *cellp);

/* afs_axscache.c */
extern afs_rwlock_t afs_xaxs;
extern struct axscache *afs_SlowFindAxs(struct axscache **cachep,
					afs_int32 id);
extern struct axscache *axs_Alloc(void);
extern void afs_RemoveAxs(struct axscache **headp, struct axscache *axsp);
extern void afs_FreeAllAxs(struct axscache **headp);
extern void shutdown_xscache(void);

/* afs_buffer.c */
extern void DInit(int abuffers);
extern void *DRead(register struct dcache * fid, register int page);
extern int DVOffset(register void *ap);
extern void DZap(struct dcache * fid);
extern void DFlush(void);
extern void DFlushDCache(struct dcache *);
extern void *DNew(register struct dcache * fid, register int page);
extern void shutdown_bufferpackage(void);

/* afs_call.c */
extern int afs_cold_shutdown;
extern afs_int32 afs_setTime;
extern char afs_rootVolumeName[64];
extern void afs_shutdown(void);
extern void afs_FlushCBs(void);
extern int afs_CheckInit(void);
extern void afs_shutdown(void);
extern void shutdown_afstest(void);
extern int afs_syscall_call(long parm, long parm2, long parm3,
			    long parm4, long parm5, long parm6);
#if defined(AFS_DARWIN100_ENV)
extern int afs_syscall64_call(user_addr_t parm, user_addr_t parm2,
			      user_addr_t parm3, user_addr_t parm4,
			      user_addr_t parm5, user_addr_t parm6);
#endif


/* afs_callback.c */
extern afs_int32 afs_allCBs;
extern afs_int32 afs_oddCBs;
extern afs_int32 afs_evenCBs;
extern afs_int32 afs_allZaps;
extern afs_int32 afs_oddZaps;
extern afs_int32 afs_evenZaps;
extern afs_int32 afs_connectBacks;
extern unsigned long lastCallBack_vnode;
extern unsigned int lastCallBack_dv;
extern osi_timeval_t lastCallBack_time;
extern struct interfaceAddr afs_cb_interface;

extern int afs_RXCallBackServer(void);
extern int SRXAFSCB_GetCE(struct rx_call *a_call, afs_int32 a_index,
			  struct AFSDBCacheEntry *a_result);
extern int SRXAFSCB_GetCE64(struct rx_call *a_call, afs_int32 a_index,
			    struct AFSDBCacheEntry64 *a_result);
extern int SRXAFSCB_GetLock(struct rx_call *a_call, afs_int32 a_index,
			    struct AFSDBLock *a_result);
extern int SRXAFSCB_CallBack(struct rx_call *a_call,
			     register struct AFSCBFids *a_fids,
			     struct AFSCBs *a_callbacks);
extern int SRXAFSCB_Probe(struct rx_call *a_call);
extern int SRXAFSCB_InitCallBackState(struct rx_call *a_call);
extern int SRXAFSCB_XStatsVersion(struct rx_call *a_call,
				  afs_int32 * a_versionP);
extern int SRXAFSCB_GetXStats(struct rx_call *a_call,
			      afs_int32 a_clientVersionNum,
			      afs_int32 a_collectionNumber,
			      afs_int32 * a_srvVersionNumP,
			      afs_int32 * a_timeP, AFSCB_CollData * a_dataP);
extern int afs_RXCallBackServer(void);
extern int shutdown_CB(void);
extern int SRXAFSCB_InitCallBackState2(struct rx_call *a_call,
				       struct interfaceAddr *addr);
extern int SRXAFSCB_WhoAreYou(struct rx_call *a_call,
			      struct interfaceAddr *addr);
extern int SRXAFSCB_InitCallBackState3(struct rx_call *a_call,
				       afsUUID * a_uuid);
extern int SRXAFSCB_ProbeUuid(struct rx_call *a_call, afsUUID * a_uuid);
extern int SRXAFSCB_GetServerPrefs(struct rx_call *a_call, afs_int32 a_index,
				   afs_int32 * a_srvr_addr,
				   afs_int32 * a_srvr_rank);
extern int SRXAFSCB_GetCellServDB(struct rx_call *a_call, afs_int32 a_index,
				  char **a_name, serverList * a_hosts);
extern int SRXAFSCB_GetLocalCell(struct rx_call *a_call, char **a_name);
extern int SRXAFSCB_GetCacheConfig(struct rx_call *a_call,
				   afs_uint32 callerVersion,
				   afs_uint32 * serverVersion,
				   afs_uint32 * configCount,
				   cacheConfig * config);
extern int SRXAFSCB_FetchData(struct rx_call *rxcall, struct AFSFid *Fid,
			      afs_int32 Fd, afs_int64 Position,
			      afs_int64 Length, afs_int64 * TotalLength);
extern int SRXAFSCB_StoreData(struct rx_call *rxcall, struct AFSFid *Fid,
			      afs_int32 Fd, afs_int64 Position,
			      afs_int64 Length, afs_int64 * TotalLength);


/* afs_cbqueue.c */
extern afs_rwlock_t afs_xcbhash;
extern void afs_QueueCallback(struct vcache *avc, unsigned int atime,
			      struct volume *avp);
extern void afs_CheckCallbacks(unsigned int secs);
extern void afs_FlushCBs(void);
extern void afs_FlushServerCBs(struct server *srvp);
extern int afs_BumpBase(void);
extern void afs_InitCBQueue(int doLockInit);
extern void afs_DequeueCallback(struct vcache *avc);

/* afs_cell.c */
extern afs_int32 afs_cellindex;
extern afs_rwlock_t afs_xcell;
extern afs_rwlock_t afsdb_client_lock;
extern afs_rwlock_t afsdb_req_lock;
extern struct afs_q CellLRU;           

extern void afs_CellInit(void);
extern void shutdown_cell(void);
extern int afs_cellname_init(afs_dcache_id_t *inode, int lookupcode);
extern int afs_cellname_write(void);
extern afs_int32 afs_NewCell(char *acellName, afs_int32 * acellHosts,
			     int aflags, char *linkedcname, u_short fsport,
			     u_short vlport, int timeout);
extern afs_int32 afs_SetPrimaryCell(char *acellName);
extern struct cell *afs_GetCell(afs_int32 acell, afs_int32 locktype);
extern struct cell *afs_GetCellStale(afs_int32 acell, afs_int32 locktype);
extern struct cell *afs_GetCellByHandle(void *handle, afs_int32 locktype);
extern struct cell *afs_GetCellByIndex(afs_int32 cellidx, afs_int32 locktype);
extern struct cell *afs_GetCellByName(char *acellName, afs_int32 locktype);
extern struct cell *afs_GetPrimaryCell(afs_int32 locktype);
extern int afs_IsPrimaryCellNum(afs_int32 cellnum);
extern int afs_IsPrimaryCell(struct cell *cell);
extern void *afs_TraverseCells(void *(*cb) (struct cell *, void *),
			       void *arg);
extern int afs_CellOrAliasExists(char *aname);
extern int afs_CellNumValid(afs_int32 cellnum);
extern afs_int32 afs_NewCellAlias(char *alias, char *cell);
extern struct cell_alias *afs_GetCellAlias(int index);
extern void afs_PutCellAlias(struct cell_alias *a);
extern int afs_AFSDBHandler(char *acellName, int acellNameLen,
			    afs_int32 * kernelMsg);
extern void afs_LookupAFSDB(char *acellName);
extern void afs_StopAFSDB(void);
extern void afs_RemoveCellEntry(struct server *srvp);

/* afs_chunk.c */
extern afs_int32 afs_FirstCSize;
extern afs_int32 afs_OtherCSize;
extern afs_int32 afs_LogChunk;

/* afs_cell.c */
extern struct cell *afs_GetRealCellByIndex(register afs_int32 cellindex,
					   afs_int32 locktype,
					   afs_int32 refresh);

/* afs_conn.c */
extern afs_int32 cryptall;
extern afs_rwlock_t afs_xinterface;
extern afs_rwlock_t afs_xconn;
extern struct afs_conn *afs_Conn(register struct VenusFid *afid,
			     register struct vrequest *areq,
			     afs_int32 locktype);
extern struct afs_conn *afs_ConnBySA(struct srvAddr *sap, unsigned short aport,
				 afs_int32 acell, struct unixuser *tu,
				 int force_if_down, afs_int32 create,
				 afs_int32 locktype);
extern struct afs_conn *afs_ConnByMHosts(struct server *ahosts[],
				     unsigned short aport, afs_int32 acell,
				     register struct vrequest *areq,
				     afs_int32 locktype);
extern struct afs_conn *afs_ConnByHost(struct server *aserver,
				   unsigned short aport, afs_int32 acell,
				   struct vrequest *areq, int aforce,
				   afs_int32 locktype);
extern void afs_PutConn(register struct afs_conn *ac, afs_int32 locktype);
extern void ForceNewConnections(struct srvAddr *sap);


/* afs_daemons.c */
extern afs_lock_t afs_xbrs;
extern short afs_brsWaiters;
extern short afs_brsDaemons;
extern struct brequest afs_brs[NBRS];
extern struct afs_osi_WaitHandle AFS_WaitHandler, AFS_CSWaitHandler;
extern afs_int32 afs_gcpags;
extern afs_int32 afs_gcpags_procsize;
extern afs_int32 afs_CheckServerDaemonStarted;
extern afs_int32 afs_probe_interval;
extern afs_int32 afs_preCache;

extern void afs_Daemon(void);
extern struct brequest *afs_BQueue(register short aopcode,
				   register struct vcache *avc,
				   afs_int32 dontwait, afs_int32 ause,
				   afs_ucred_t *acred,
				   afs_size_t asparm0, afs_size_t asparm1,
				   void *apparm0, void *apparm1,
				   void *apparm2);
extern void afs_SetCheckServerNATmode(int isnat);
extern void afs_CheckServerDaemon(void);
extern int afs_CheckRootVolume(void);
extern void afs_BRelease(register struct brequest *ab);
extern int afs_BBusy(void);
extern int afs_BioDaemon(afs_int32 nbiods);
extern void afs_BackgroundDaemon(void);
extern void shutdown_daemons(void);
extern int afs_sgidaemon(void);


/* afs_dcache.c */
extern u_int afs_min_cache;
extern afs_int32 *afs_dvhashTbl;
extern afs_int32 afs_dhashsize;
extern afs_rwlock_t afs_xdcache;
extern afs_size_t afs_vmMappingEnd;
extern afs_int32 afs_blocksUsed;
extern afs_int32 afs_blocksDiscarded;
extern int afs_WaitForCacheDrain;
extern int cacheDiskType;
extern afs_uint32 afs_tpct1, afs_tpct2, splitdcache;
extern unsigned char *afs_indexFlags;
extern struct afs_cacheOps *afs_cacheType;
extern afs_dcache_id_t cacheInode;
extern struct osi_file *afs_cacheInodep;
extern void afs_dcacheInit(int afiles, int ablocks, int aDentries, int achunk,
			   int aflags);
extern int afs_PutDCache(register struct dcache *adc);
extern void afs_FlushDCache(register struct dcache *adc);
extern void shutdown_dcache(void);
extern void afs_CacheTruncateDaemon(void);
extern afs_int32 afs_fsfragsize;
extern struct dcache *afs_MemGetDSlot(register afs_int32 aslot,
				      register struct dcache *tmpdc);
extern struct dcache *afs_GetDCache(register struct vcache *avc,
				    afs_size_t abyte,
				    register struct vrequest *areq,
				    afs_size_t * aoffset, afs_size_t * alen,
				    int aflags);
extern struct dcache *afs_FindDCache(register struct vcache *avc,
				     afs_size_t abyte);
extern void afs_StoreWarn(register afs_int32 acode, afs_int32 avolume,
			  register afs_int32 aflags);
extern void afs_MaybeWakeupTruncateDaemon(void);
extern void afs_CacheTruncateDaemon(void);
extern void afs_AdjustSize(register struct dcache *adc,
			   register afs_int32 newSize);
extern int afs_HashOutDCache(struct dcache *adc, int zap);
extern int afs_MaybeFreeDiscardedDCache(void);
extern int afs_RefDCache(struct dcache *adc);
extern void afs_TryToSmush(register struct vcache *avc,
			   afs_ucred_t *acred, int sync);
extern void updateV2DC(int lockVc, struct vcache *v, struct dcache *d,
		       int src);
extern void afs_WriteThroughDSlots(void);
extern struct dcache *afs_UFSGetDSlot(register afs_int32 aslot,
				      register struct dcache *tmpdc);
extern int afs_WriteDCache(register struct dcache *adc, int atime);
extern int afs_wakeup(register struct vcache *avc);
extern int afs_InitCacheFile(char *afile, ino_t ainode);
extern int afs_DCacheMissingChunks(struct vcache *avc);
extern struct dcache *afs_ObtainDCacheForWriting(struct vcache *avc, 
						 afs_size_t filePos, 
						 afs_size_t len, 
						 struct vrequest *areq,
						 int noLock);
extern void afs_PopulateDCache(struct vcache *avc, afs_size_t apos, 
			       struct vrequest *areq);

/* afs_disconnected.c */

/* afs_dynroot.c */
extern int afs_IsDynrootFid(struct VenusFid *fid);
extern int afs_IsDynrootMountFid(struct VenusFid *fid);
extern int afs_IsDynrootAnyFid(struct VenusFid *fid);
extern void afs_GetDynrootFid(struct VenusFid *fid);
extern void afs_GetDynrootMountFid(struct VenusFid *fid);
extern int afs_IsDynroot(struct vcache *avc);
extern int afs_IsDynrootMount(struct vcache *avc);
extern int afs_IsDynrootAny(struct vcache *avc);
extern void afs_DynrootInvalidate(void);
extern void afs_GetDynroot(char **dynrootDir, int *dynrootLen,
			   struct AFSFetchStatus *status);
extern void afs_GetDynrootMount(char **dynrootDir, int *dynrootLen,
			   struct AFSFetchStatus *status);
extern void afs_PutDynroot(void);
extern int afs_DynrootNewVnode(struct vcache *avc,
			       struct AFSFetchStatus *status);
extern int afs_InitDynroot(void);
extern int afs_SetDynrootEnable(int enable);
extern int afs_GetDynrootEnable(void);
extern int afs_DynrootVOPRemove(struct vcache *avc, afs_ucred_t *acred,
				char *aname);
extern int afs_DynrootVOPSymlink(struct vcache *avc, afs_ucred_t *acred,
				 char *aname, char *atargetName);

/* afs_error.c */
extern void init_et_to_sys_error(void);
extern afs_int32 et_to_sys_error(afs_int32 in);
extern void afs_FinalizeReq(struct vrequest *areq);
extern int afs_CheckCode(afs_int32 acode, struct vrequest *areq, int where);
extern void afs_CopyError(register struct vrequest *afrom,
			  register struct vrequest *ato);
extern void init_sys_error_to_et(void);

/* afs_exporter.c */
extern struct afs_exporter *root_exported;
extern struct afs_exporter *exporter_find(int type);
extern void shutdown_exporter(void);

/* afs_fetchstore.c */
extern int afs_UFSCacheFetchProc(struct rx_call *, struct osi_file *,
                                 afs_size_t, struct dcache *,
                                 struct vcache *, afs_size_t *,
                                 afs_size_t *, afs_int32);

extern int afs_UFSCacheStoreProc(struct rx_call *, struct osi_file *,
                                 afs_int32, struct vcache *,
                                 int *, afs_size_t *,
                                 afs_size_t *);

/* afs_icl.c */
extern struct afs_icl_set *afs_icl_allSets;
extern int afs_icl_InitLogs(void);
extern void shutdown_icl(void);
extern int afs_icl_CreateLog(char *name, afs_int32 logSize,
			     struct afs_icl_log **outLogpp);
extern int afs_icl_CreateLogWithFlags(char *name, afs_int32 logSize,
				      afs_uint32 flags,
				      struct afs_icl_log **outLogpp);
extern int afs_icl_CopyOut(register struct afs_icl_log *logp,
			   afs_int32 * bufferp, afs_int32 * bufSizep,
			   afs_uint32 * cookiep, afs_int32 * flagsp);
extern int afs_icl_GetLogParms(struct afs_icl_log *logp, afs_int32 * maxSizep,
			       afs_int32 * curSizep);
extern int afs_icl_LogHold(register struct afs_icl_log *logp);
extern int afs_icl_LogHoldNL(register struct afs_icl_log *logp);
extern int afs_icl_LogUse(register struct afs_icl_log *logp);
extern int afs_icl_LogFreeUse(register struct afs_icl_log *logp);
extern int afs_icl_LogSetSize(register struct afs_icl_log *logp,
			      afs_int32 logSize);
extern int afs_icl_ZapLog(register struct afs_icl_log *logp);
extern int afs_icl_LogRele(register struct afs_icl_log *logp);
extern int afs_icl_LogReleNL(register struct afs_icl_log *logp);
extern int afs_icl_ZeroLog(register struct afs_icl_log *logp);
extern int afs_icl_LogFree(register struct afs_icl_log *logp);
extern struct afs_icl_log *afs_icl_FindLog(char *name);
extern int
  afs_icl_EnumerateLogs(int (*aproc)

			  (char *name, char *arock, struct afs_icl_log * tp),
			char *arock);
extern int afs_icl_CreateSet(char *name, struct afs_icl_log *baseLogp,
			     struct afs_icl_log *fatalLogp,
			     struct afs_icl_set **outSetpp);
extern int afs_icl_CreateSetWithFlags(char *name,
				      struct afs_icl_log *baseLogp,
				      struct afs_icl_log *fatalLogp,
				      afs_uint32 flags,
				      struct afs_icl_set **outSetpp);
extern int afs_icl_SetEnable(struct afs_icl_set *setp, afs_int32 eventID,
			     int setValue);
extern int afs_icl_GetEnable(struct afs_icl_set *setp, afs_int32 eventID,
			     int *getValuep);
extern int afs_icl_ZeroSet(struct afs_icl_set *setp);
extern int
  afs_icl_EnumerateSets(int (*aproc)

			  (char *name, char *arock, struct afs_icl_log * tp),
			char *arock);
extern int afs_icl_AddLogToSet(struct afs_icl_set *setp,
			       struct afs_icl_log *newlogp);
extern int afs_icl_SetSetStat(struct afs_icl_set *setp, int op);
extern int afs_icl_SetHold(register struct afs_icl_set *setp);
extern int afs_icl_ZapSet(register struct afs_icl_set *setp);
extern int afs_icl_SetRele(register struct afs_icl_set *setp);
extern int afs_icl_SetFree(register struct afs_icl_set *setp);
extern struct afs_icl_set *afs_icl_FindSet(char *name);

extern int afs_icl_Event4(register struct afs_icl_set *setp,
			  afs_int32 eventID, afs_int32 lAndT, long p1,
			  long p2, long p3, long p4);
extern int afs_icl_Event3(register struct afs_icl_set *setp,
			  afs_int32 eventID, afs_int32 lAndT, long p1,
			  long p2, long p3);
extern int afs_icl_Event2(register struct afs_icl_set *setp,
			  afs_int32 eventID, afs_int32 lAndT, long p1,
			  long p2);
extern int afs_icl_Event1(register struct afs_icl_set *setp,
			  afs_int32 eventID, afs_int32 lAndT, long p1);
extern int afs_icl_Event0(register struct afs_icl_set *setp,
			  afs_int32 eventID, afs_int32 lAndT);
extern void afs_icl_AppendRecord(register struct afs_icl_log *logp,
				 afs_int32 op, afs_int32 types, long p1,
				 long p2, long p3, long p4);
extern int Afscall_icl(long opcode, long p1, long p2, long p3, long p4,
		       long *retval);
#ifdef AFS_DARWIN100_ENV
extern int Afscall64_icl(int opcode, user_addr_t p1, user_addr_t p2,
		       user_addr_t p3, user_addr_t p4, int *retval);
#endif

/* afs_init.c */
extern struct cm_initparams cm_initParams;
extern int afs_resourceinit_flag;
extern afs_rwlock_t afs_puttofileLock;
extern char *afs_sysname;
extern char *afs_sysnamelist[MAXNUMSYSNAMES];
extern int afs_sysnamecount;
extern int afs_sysnamegen;
extern afs_int32 cacheInfoModTime;
extern int afs_CacheInit(afs_int32 astatSize, afs_int32 afiles,
			 afs_int32 ablocks, afs_int32 aDentries,
			 afs_int32 aVolumes, afs_int32 achunk,
			 afs_int32 aflags, afs_int32 ninodes,
			 afs_int32 nusers, afs_int32 dynamic_vcaches);
extern void afs_ComputeCacheParms(void);
extern int afs_InitCacheInfo(register char *afile);
extern int afs_InitVolumeInfo(char *afile);
extern int afs_InitCellInfo(char *afile);
extern int afs_ResourceInit(int preallocs);
extern void shutdown_cache(void);
extern void shutdown_vnodeops(void);
extern void shutdown_AFS(void);
extern int afs_LookupInodeByPath(char *filename, afs_ufs_dcache_id_t *inode,
				 struct vnode **fvpp);

/* afs_lock.c */
extern void Lock_Init(register struct afs_lock *lock);
extern void ObtainLock(register struct afs_lock *lock, int how,
		       unsigned int src_indicator);
extern void ReleaseLock(register struct afs_lock *lock, int how);
extern int Afs_Lock_Trace(int op, struct afs_lock *alock, int type,
			  char *file, int line);
extern void Afs_Lock_Obtain(register struct afs_lock *lock, int how);
extern void Afs_Lock_ReleaseR(register struct afs_lock *lock);
extern void Afs_Lock_ReleaseW(register struct afs_lock *lock);
extern void afs_osi_SleepR(register char *addr,
			   register struct afs_lock *alock);
extern void afs_osi_SleepW(register char *addr,
			   register struct afs_lock *alock);
extern void afs_osi_SleepS(register char *addr,
			   register struct afs_lock *alock);
#ifndef AFS_NOBOZO_LOCK
extern void afs_BozonLock(struct afs_bozoLock *alock, struct vcache *avc);
extern void afs_BozonUnlock(struct afs_bozoLock *alock, struct vcache *avc);
extern void afs_BozonInit(struct afs_bozoLock *alock, struct vcache *avc);
extern int afs_CheckBozonLock(struct afs_bozoLock *alock);
extern int afs_CheckBozonLockBlocking(struct afs_bozoLock *alock);
#endif




/* afs_mariner.c */
extern afs_int32 afs_mariner;
extern afs_int32 afs_marinerHost;
extern struct rx_service *afs_server;
extern int afs_AddMarinerName(register char *aname,
			      register struct vcache *avc);
extern char *afs_GetMariner(register struct vcache *avc);
extern void afs_MarinerLogFetch(register struct vcache *avc,
				register afs_int32 off,
				register afs_int32 bytes,
				register afs_int32 idx);
extern void afs_MarinerLog(register char *astring,
			   register struct vcache *avc);
extern void shutdown_mariner(void);

/* afs_fetchstore.c */
extern int afs_CacheStoreVCache(struct dcache **dcList, struct vcache *avc,
				struct vrequest *areq,
				int sync, unsigned int minj,
				unsigned int high, unsigned int moredata,
				afs_hyper_t *anewDV,
                                 afs_size_t *amaxStoredLength);
extern int afs_CacheFetchProc(struct afs_conn *tc, struct osi_file *fP,
				afs_size_t abase, struct dcache *adc,
				struct vcache *avc, afs_int32 size,
				struct afs_FetchOutput *tsmall);

/* afs_memcache.c */
extern int afs_InitMemCache(int blkCount, int blkSize, int flags);
extern int afs_MemCacheClose(struct osi_file *file);
extern void *afs_MemCacheOpen(afs_dcache_id_t *ainode);
extern int afs_MemReadBlk(register struct osi_file *fP, int offset,
			  void *dest, int size);
extern int afs_MemReadvBlk(register struct memCacheEntry *mceP, int offset,
			   struct iovec *iov, int nio, int size);
extern int afs_MemReadUIO(afs_dcache_id_t *ainode, struct uio *uioP);
extern int afs_MemWriteBlk(register struct osi_file *fP, int offset,
			   void *src, int size);
extern int afs_MemWritevBlk(register struct memCacheEntry *mceP, int offset,
			    struct iovec *iov, int nio, int size);
extern int afs_MemWriteUIO(afs_dcache_id_t *ainode, struct uio *uioP);
extern int afs_MemCacheTruncate(register struct osi_file *fP,
				int size);
extern void shutdown_memcache(void);


/* afs_nfsclnt.c */
extern struct afs_exporter *afs_nfsexported;
extern struct afs_exporter *afs_nfsexporter;
extern void afs_nfsclient_init(void);
extern int afs_nfsclient_reqhandler(struct afs_exporter *exporter,
				    afs_ucred_t **cred,
				    afs_int32 host, afs_int32 *pagparam,
				    struct afs_exporter **outexporter);
extern void shutdown_nfsclnt(void);

/* afs_osi.c */
extern afs_lock_t afs_ftf;
extern void afs_osi_Invisible(void);
extern void afs_osi_Visible(void);
extern void afs_osi_RxkRegister(void);
extern void afs_osi_MaskSignals(void);
extern void afs_osi_UnmaskRxkSignals(void);
extern void afs_osi_MaskUserLoop(void);
extern void osi_Init(void);
extern void afs_osi_MaskSignals(void);
extern void afs_osi_UnmaskRxkSignals(void);
extern void afs_osi_RxkRegister(void);
extern void afs_osi_Invisible(void);
extern void shutdown_osi(void);
extern void shutdown_osinet(void);
extern int afs_osi_suser(void *credp);
extern void afs_osi_TraverseProcTable(void);
#if defined(KERNEL) && !defined(UKERNEL)
extern const afs_ucred_t *afs_osi_proc2cred(afs_proc_t * pr);
#endif

/* afs_osi_alloc.c */
#ifndef AFS_FBSD_ENV
extern afs_lock_t osi_fsplock;
extern afs_lock_t osi_flplock;
#endif
extern void *afs_osi_Alloc_debug(size_t x, char *func, int line);
#ifndef afs_osi_Alloc_NoSleep
extern void *afs_osi_Alloc_NoSleep(size_t x);
#endif
#ifndef afs_osi_Free
extern void afs_osi_Free(void *x, size_t asize);
#endif
#if !defined(AFS_OBSD44_ENV)
extern void afs_osi_FreeStr(char *x);
#endif
extern void osi_FreeLargeSpace(void *adata);
extern void osi_FreeSmallSpace(void *adata);
extern void *osi_AllocLargeSpace(size_t size);
extern void *osi_AllocSmallSpace(size_t size);
extern void shutdown_osinet(void);

/* afs_osi_pag.c */
#if defined(AFS_SUN5_ENV)
extern int afs_setpag(afs_ucred_t **credpp);
#elif defined(AFS_DARWIN_ENV) || defined(AFS_XBSD_ENV)
extern int afs_setpag(afs_proc_t *p, void *args, int *retval);
#else
extern int afs_setpag(void);
#endif
	
extern afs_uint32 genpag(void);
extern afs_uint32 getpag(void);
#if defined(AFS_DARWIN_ENV) || defined(AFS_XBSD_ENV)
extern int AddPag(afs_proc_t *p, afs_int32 aval, afs_ucred_t **credpp);
#else
extern int AddPag(afs_int32 aval, afs_ucred_t **credpp);
#endif
extern int afs_InitReq(register struct vrequest *av, afs_ucred_t *acred);
extern afs_uint32 afs_get_pag_from_groups(gid_t g0a, gid_t g1a);
extern void afs_get_groups_from_pag(afs_uint32 pag, gid_t * g0p, gid_t * g1p);
extern afs_int32 PagInCred(afs_ucred_t *cred);

/* afs_osi_uio.c */
extern int afsio_copy(struct uio *ainuio, struct uio *aoutuio,
		      struct iovec *aoutvec);
extern int afsio_trim(struct uio *auio, afs_int32 asize);
extern int afsio_skip(struct uio *auio, afs_int32 asize);

/* afs_osi_vm.c */
extern int osi_Active(register struct vcache *avc);
extern void osi_FlushPages(register struct vcache *avc,
			   afs_ucred_t *credp);
extern void osi_FlushText_really(register struct vcache *vp);
extern int osi_VMDirty_p(struct vcache *avc);
#ifndef UKERNEL
extern void osi_ReleaseVM(struct vcache *avc, afs_ucred_t *acred);
#endif


/* LINUX/osi_fetchstore.c */
#ifdef AFS_LINUX26_ENV
extern int afs_linux_storeproc(struct storeOps *, void *, struct dcache *,
			       int *, afs_size_t *);
#endif

/* ARCH/osi_misc.c */
extern void afs_osi_SetTime(osi_timeval_t * atv);

/* LINUX/osi_misc.c */
#ifdef AFS_LINUX20_ENV
#ifdef AFS_LINUX24_ENV
extern int osi_lookupname(char *aname, uio_seg_t seg, int followlink,
			  struct dentry **dpp);
extern int osi_InitCacheInfo(char *aname);
extern int osi_rdwr(struct osi_file *osifile, uio_t * uiop, int rw);
extern void setup_uio(uio_t * uiop, struct iovec *iovecp, const char *buf,
		      afs_offs_t pos, int count, uio_flag_t flag,
		      uio_seg_t seg);
extern int uiomove(char *dp, int length, uio_flag_t rw, uio_t * uiop);
extern void osi_linux_free_inode_pages(void);
#endif
extern void osi_linux_mask(void);
extern void osi_linux_unmask(void);
extern int setpag(cred_t ** cr, afs_uint32 pagvalue, afs_uint32 * newpag,
		  int change_parent);
#endif


/* ARCH/osi_sleep.c */
extern void afs_osi_InitWaitHandle(struct afs_osi_WaitHandle *achandle);
extern void afs_osi_CancelWait(struct afs_osi_WaitHandle *achandle);
extern int afs_osi_Wait(afs_int32 ams, struct afs_osi_WaitHandle *ahandle,
			int aintok);
extern int afs_osi_TimedSleep(void *event, afs_int32 ams, int aintok);
#ifndef afs_osi_Wakeup
extern int afs_osi_Wakeup(void *event);
#endif
#ifndef afs_osi_Sleep
extern void afs_osi_Sleep(void *event);
#endif
#ifndef afs_osi_SleepSig
extern int afs_osi_SleepSig(void *event);
#endif


/* ARCH/osi_inode.c */
#ifdef AFS_SUN5_ENV
extern int afs_syscall_icreate(dev_t, long, long, long, long, long, 
		               rval_t *, afs_ucred_t *);
extern int afs_syscall_iopen(dev_t, int, int, rval_t *, afs_ucred_t *);
extern int afs_syscall_iincdec(dev_t, int, int, int, rval_t *, 
			       afs_ucred_t *);
#elif defined(AFS_SGI65_ENV)
extern int afs_syscall_icreate(afs_uint32, afs_uint32, afs_uint32, afs_uint32, afs_uint32, afs_uint32, rval_t *);
extern int afs_syscall_iopen(int, ino_t, int, rval_t *);
extern int afs_syscall_iincdec(int, int, int, int);
#elif defined(AFS_DARWIN_ENV) || defined(AFS_XBSD_ENV)
extern int afs_syscall_icreate(long, long, long, long, long, long, long*);
extern int afs_syscall_iopen(int dev, int inode, int usrmod, long *retval);
extern int afs_syscall_iincdec(int dev, int inode, int inode_p1, int amount);
#else
extern int afs_syscall_icreate(long, long, long, long, long, long);
extern int afs_syscall_iopen(int, int, int);
extern int afs_syscall_iincdec(int, int, int, int);
#endif

/* ARCH/osi_file.c */
extern int afs_osicred_initialized;
extern void *osi_UFSOpen(afs_dcache_id_t *ainode);
#if defined(AFS_LINUX22_ENV)
extern void osi_get_fh(struct dentry *dp, afs_ufs_dcache_id_t *ainode);
#endif
extern int afs_osi_Stat(register struct osi_file *afile,
			register struct osi_stat *astat);
extern int osi_UFSClose(register struct osi_file *afile);
extern int osi_UFSTruncate(register struct osi_file *afile, afs_int32 asize);
extern void osi_DisableAtimes(struct vnode *avp);
extern int afs_osi_Read(register struct osi_file *afile, int offset,
			void *aptr, afs_int32 asize);
extern int afs_osi_Write(register struct osi_file *afile, afs_int32 offset,
			 void *aptr, afs_int32 asize);
extern int afs_osi_MapStrategy(int (*aproc) (struct buf * bp),
			       register struct buf *bp);
extern void shutdown_osifile(void);


/* ARCH/osi_groups.c */
#if defined(UKERNEL)
extern int usr_setpag(afs_ucred_t **cred, afs_uint32 pagvalue,
		      afs_uint32 * newpag, int change_parent);
#else
# if defined AFS_XBSD_ENV
#  if !defined(AFS_DFBSD_ENV)
extern int setpag(afs_proc_t *proc, struct ucred **cred, afs_uint32 pagvalue,
		  afs_uint32 * newpag, int change_parent);
#  endif
# endif
#endif

#if defined(AFS_LINUX26_ENV)
extern afs_int32 osi_get_group_pag(afs_ucred_t *cred);
#endif



/* ARCH/osi_vm.c */
extern int osi_VM_FlushVCache(struct vcache *avc, int *slept);
extern void osi_VM_StoreAllSegments(struct vcache *avc);
extern void osi_VM_TryToSmush(struct vcache *avc, afs_ucred_t *acred,
			      int sync);
extern void osi_VM_FlushPages(struct vcache *avc, afs_ucred_t *credp);
extern void osi_VM_Truncate(struct vcache *avc, int alen,
			    afs_ucred_t *acred);
extern void osi_VM_TryReclaim(struct vcache *avc, int *slept);
extern void osi_VM_NukePages(struct vnode *vp, off_t offset, off_t size);
extern int osi_VM_Setup(struct vcache *avc, int force);

#ifdef AFS_SUN5_ENV
extern int osi_VM_GetDownD(struct vcache *avc, struct dcache *adc);
extern void osi_VM_PreTruncate(struct vcache *avc, int alen,
			       afs_ucred_t *acred);
#endif


/* ARCH/osi_vnodeops.c */
extern struct vnodeops Afs_vnodeops;
extern int afs_inactive(struct vcache *avc, afs_ucred_t *acred);

/* afs_osifile.c */

/* afs_osi_pag.c */
extern afs_uint32 pag_epoch;
extern afs_uint32 pagCounter;

/* OS/osi_vfsops.c */
#if defined(AFS_XBSD_ENV) || defined(AFS_DARWIN_ENV)
extern struct mount *afs_globalVFS;
#else
extern struct vfs *afs_globalVFS;
#endif
extern struct vcache *afs_globalVp;
#ifdef AFS_LINUX20_ENV
extern void vcache2inode(struct vcache *avc);
extern void vcache2fakeinode(struct vcache *rootvp, struct vcache *mpvp);
#endif

#ifdef UKERNEL
extern int afs_mount(struct vfs *afsp, char *path, void *data);
extern int afs_root(OSI_VFS_DECL(afsp), struct vnode **avpp);
extern int afs_unmount(struct vfs *afsp);
#endif

/* afs_pag_call.c */
extern afs_int32 afs_nfs_server_addr;
extern void afspag_Init(afs_int32 nfs_server_addr);
extern void afspag_Shutdown(void);

/* afs_pag_cred.c */
extern afs_rwlock_t afs_xpagcell;
extern afs_rwlock_t afs_xpagsys;
extern int afspag_PUnlog(char *ain, afs_int32 ainSize,
			 afs_ucred_t **acred);
extern int afspag_PSetTokens(char *ain, afs_int32 ainSize,
			     afs_ucred_t **acred);
extern int afspag_PSetSysName(char *ain, afs_int32 ainSize,
                              afs_ucred_t **acred);

/* afs_pioctl.c */
extern struct VenusFid afs_rootFid;
extern afs_int32 afs_waitForever;
extern short afs_waitForeverCount;
extern afs_int32 afs_showflags;
extern int afs_defaultAsynchrony;
#if defined(AFS_DARWIN100_ENV)
extern int afs_syscall64_pioctl(user_addr_t path, unsigned int com,
				user_addr_t cmarg, int follow, \
				afs_ucred_t *credp);
#endif
#ifdef AFS_SUN5_ENV
extern int afs_syscall_pioctl(char *path, unsigned int com, caddr_t cmarg, 
			      int follow, rval_t *rvp, afs_ucred_t *credp);
#elif defined(AFS_DARWIN_ENV) || defined(AFS_XBSD_ENV)
extern int afs_syscall_pioctl(char *path, unsigned int com, caddr_t cmarg, 
			      int follow, afs_ucred_t *credp);
#else
extern int afs_syscall_pioctl(char *path, unsigned int com, caddr_t cmarg,
			      int follow);
#endif
extern int HandleIoctl(register struct vcache *avc, register afs_int32 acom,
		       struct afs_ioctl *adata);


/* afs_segments.c */
extern int afs_StoreAllSegments(register struct vcache *avc,
				struct vrequest *areq, int sync);
extern int afs_InvalidateAllSegments(struct vcache *avc);
extern int afs_ExtendSegments(struct vcache *avc,
			      afs_size_t alen, struct vrequest *areq);
extern int afs_TruncateAllSegments(register struct vcache *avc,
				   afs_size_t alen, struct vrequest *areq,
				   afs_ucred_t *acred);

/* afs_server.c */
extern afs_rwlock_t afs_xsrvAddr;
extern afs_rwlock_t afs_xserver;
extern afs_rwlock_t afs_icl_lock;
extern struct srvAddr *afs_srvAddrs[NSERVERS];
extern struct server *afs_servers[NSERVERS];
extern int afs_totalServers;
extern struct server *afs_setTimeHost;
extern struct server *afs_FindServer(afs_int32 aserver, afs_uint16 aport,
				     afsUUID * uuidp, afs_int32 locktype);
extern struct server *afs_GetServer(afs_uint32 * aserver, afs_int32 nservers,
				    afs_int32 acell, u_short aport,
				    afs_int32 locktype, afsUUID * uuidp,
				    afs_int32 addr_uniquifier);
extern void ForceAllNewConnections(void);
extern void afs_MarkServerUpOrDown(struct srvAddr *sa, int a_isDown);
extern afs_int32 afs_ServerDown(struct srvAddr *sa);
extern void afs_CountServers(void);
extern void afs_CheckServers(int adown, struct cell *acellp);
extern unsigned int afs_random(void);
extern int afs_randomMod15(void);
extern int afs_randomMod127(void);
extern void afs_SortOneServer(struct server *asp);
extern void afs_SortServers(struct server *aservers[], int count);
extern void afs_FlushServer(struct server *srvp);
extern void afs_RemoveSrvAddr(struct srvAddr *sap);
extern void afs_ActivateServer(struct srvAddr *sap);
#ifdef AFS_USERSPACE_IP_ADDR
extern void afsi_SetServerIPRank(struct srvAddr *sa, afs_int32 addr,
				afs_uint32 subnetmask);
#else
#if (!defined(AFS_SUN5_ENV)) && defined(USEIFADDR)
void afsi_SetServerIPRank(struct srvAddr *sa, struct in_ifaddr *ifa);
#endif
#endif
extern int afs_HaveCallBacksFrom(struct server *aserver);
extern void afs_RemoveAllConns(void);
extern void afs_MarkAllServersUp(void);

/* afs_osidnlc.c */
extern int osi_dnlc_enter(struct vcache *adp, char *aname, struct vcache *avc,
			  afs_hyper_t * avno);
extern struct vcache *osi_dnlc_lookup(struct vcache *adp, char *aname,
				      int locktype);
extern int osi_dnlc_remove(struct vcache *adp, char *aname,
			   struct vcache *avc);
extern int osi_dnlc_purgedp(struct vcache *adp);
extern int osi_dnlc_purgevp(struct vcache *avc);
extern int osi_dnlc_purge(void);
extern int osi_dnlc_purgevol(struct VenusFid *fidp);
extern int osi_dnlc_init(void);
extern int osi_dnlc_shutdown(void);

/* afs_pag_cred.c */
extern void afspag_SetPrimaryCell(char *acell);

/* afs_stat.c */
extern struct afs_CMStats afs_cmstats;
extern struct afs_stats_CMPerf afs_stats_cmperf;
extern struct afs_stats_CMFullPerf afs_stats_cmfullperf;
extern afs_int32 afs_stats_XferSumBytes[AFS_STATS_NUM_FS_XFER_OPS];
extern void afs_InitStats(void);
extern void afs_GetCMStat(char **ptr, unsigned *size);
#ifndef AFS_NOSTATS
extern void afs_AddToMean(struct afs_MeanStats *oldMean, afs_int32 newValue);
#endif

/* afs_syscall.c */
#ifdef AFS_DARWIN100_ENV
extern int copyin_afs_ioctl(user_addr_t cmarg, struct afs_ioctl *dst);
#else
extern int copyin_afs_ioctl(caddr_t cmarg, struct afs_ioctl *dst);
#endif

#if defined(AFS_DARWIN_ENV) || defined(AFS_XBSD_ENV)
#ifdef AFS_DARWIN100_ENV
extern int afs3_syscall(afs_proc_t *p, void *args, unsigned int *retval);
#elif defined(AFS_FBSD50_ENV)
extern int afs3_syscall(struct thread *p, void *args, long *retval);
#else
extern int afs3_syscall(afs_proc_t *p, void *args, long *retval);
#endif
#endif

#ifdef UKERNEL
extern int Afs_syscall(void);
#endif

/* UKERNEL/afs_usrops.c */
#ifdef UKERNEL
extern void uafs_Shutdown(void);
extern void osi_ReleaseVM(struct vcache *avc, int len,
			  afs_ucred_t *credp);
extern int osi_GetTime(struct timeval *tv);
extern int iodone(struct usr_buf *bp);
extern int usr_ioctl(void);
extern int lookupname(char *fnamep, int segflg, int followlink,
		      struct usr_vnode **compvpp);
extern int usr_uiomove(char *kbuf, int n, int rw, struct usr_uio *uio);
extern int afs_osi_VOP_RDWR(struct usr_vnode *vnodeP, struct usr_uio *uioP,
		            int rw, int flags, afs_ucred_t *credP);

#endif

/* afs_user.c */
extern afs_rwlock_t afs_xuser;
extern struct unixuser *afs_users[NUSERS];
extern struct unixuser *afs_FindUser(afs_int32 auid, afs_int32 acell,
				     afs_int32 locktype);
extern struct unixuser *afs_GetUser(register afs_int32 auid, afs_int32 acell,
				    afs_int32 locktype);
#if AFS_GCPAGS
extern afs_int32 afs_GCPAGs(afs_int32 * ReleasedCount);
extern void afs_GCPAGs_perproc_func(afs_proc_t * pproc);
#endif /* AFS_GCPAGS */
extern void afs_ComputePAGStats(void);
extern void afs_PutUser(register struct unixuser *au, afs_int32 locktype);
extern void afs_GCUserData(int aforce);
extern void afs_CheckTokenCache(void);
extern void afs_ResetAccessCache(afs_int32 uid, int alock);
extern void afs_ResetUserConns(register struct unixuser *auser);
extern void afs_SetPrimary(register struct unixuser *au, register int aflag);


/* afs_util.c */
extern afs_int32 afs_calc_inum (afs_int32 volume, afs_int32 vnode);
#ifndef afs_cv2string
extern char *afs_cv2string(char *ttp, afs_uint32 aval);
#endif
#ifndef afs_strcasecmp
extern int afs_strcasecmp(char *s1, char *s2);
#endif
#ifndef afs_strcat
extern char *afs_strcat(char *s1, char *s2);
#endif
#ifdef AFS_OBSD34_ENV
extern char *afs_strcpy(char *s1, char *s2);
#endif
#ifndef afs_strchr
extern char *afs_strchr(char *s, int c);
#endif
#ifndef afs_strrchr
extern char *afs_strrchr(char *s, int c);
#endif
extern char *afs_strdup(char *s);
extern void print_internet_address(char *preamble, struct srvAddr *sa,
				   char *postamble, int flag);
extern afs_int32 afs_data_pointer_to_int32(const void *p);

extern void afs_CheckLocks(void);
extern int afs_badop(void);
extern int afs_noop(void);
extern afs_int32 afs_data_pointer_to_int32(const void *p);

/* afs_warn.c */

#ifdef AFS_AIX_ENV
/* AIX doesn't have usable va_args support in its kernel */
extern void afs_warn();
extern void afs_warnuser();
#else
extern void afs_warn(char *fmt, ...)
	AFS_ATTRIBUTE_FORMAT(__printf__, 1, 2);
extern void afs_warnuser(char *fmt, ...)
	AFS_ATTRIBUTE_FORMAT(__printf__, 1, 2);
#endif

/* afs_vcache.c */
extern int afs_ShakeLooseVCaches(afs_int32 anumber);
extern afs_int32 afs_maxvcount;
extern afs_int32 afs_vcount;
extern int afsvnumbers;
extern afs_rwlock_t afs_xvreclaim;
extern afs_rwlock_t afs_xvcache;
extern afs_rwlock_t afs_xvcdirty;
extern afs_lock_t afs_xvcb;
extern struct afs_q VLRU;
extern afs_int32 vcachegen;
extern unsigned int afs_paniconwarn;
extern struct afs_q afs_vhashTV[VCSIZE];
extern afs_int32 afs_bulkStatsLost;
extern int afs_norefpanic;
extern struct vcache *ReclaimedVCList;
extern ino_t vcacheMetaInode;
extern struct osi_file *afs_vcacheMetaInodep;

extern void afs_FlushReclaimedVcaches(void);
void afs_vcacheInit(int astatSize);
extern struct vcache *afs_FindVCache(struct VenusFid *afid, afs_int32 * retry,
				     afs_int32 flag);
extern afs_int32 afs_FetchStatus(struct vcache *avc, struct VenusFid *afid,
				 struct vrequest *areq,
				 struct AFSFetchStatus *Outsp);

extern afs_int32 afs_FlushVCBs(afs_int32 lockit);
extern void afs_InactiveVCache(struct vcache *avc, afs_ucred_t *acred);
extern struct vcache *afs_LookupVCache(struct VenusFid *afid,
				       struct vrequest *areq,
				       afs_int32 * cached, struct vcache *adp,
				       char *aname);
extern int afs_FlushVCache(struct vcache *avc, int *slept);
extern struct vcache *afs_GetRootVCache(struct VenusFid *afid,
					struct vrequest *areq,
					afs_int32 * cached,
					struct volume *tvolp);
extern struct vcache *afs_NewVCache(struct VenusFid *afid,
				    struct server *serverp);
extern struct vcache *afs_NewBulkVCache(struct VenusFid *afid,
					struct server *serverp, int seq);
extern int afs_VerifyVCache2(struct vcache *avc, struct vrequest *areq);
extern struct vcache *afs_GetVCache(register struct VenusFid *afid,
				    struct vrequest *areq, afs_int32 * cached,
				    struct vcache *avc);
extern void afs_PutVCache(register struct vcache *avc);
extern void afs_ProcessFS(register struct vcache *avc,
			  register struct AFSFetchStatus *astat,
			  struct vrequest *areq);
extern struct afs_cbr *afs_AllocCBR(void);
extern int afs_FreeCBR(register struct afs_cbr *asp);
extern void afs_RemoveVCB(register struct VenusFid *afid);
extern void afs_FlushActiveVcaches(register afs_int32 doflocks);
extern int afs_WriteVCache(register struct vcache *avc,
			   register struct AFSStoreStatus *astatus,
			   struct vrequest *areq);
extern int afs_RemoteLookup(register struct VenusFid *afid,
			    struct vrequest *areq, char *name,
			    struct VenusFid *nfid,
			    struct AFSFetchStatus *OutStatusp,
			    struct AFSCallBack *CallBackp,
			    struct server **serverp,
			    struct AFSVolSync *tsyncp);
extern void afs_ResetVCache(struct vcache *, afs_ucred_t *);
extern afs_int32 afs_NFSFindVCache(struct vcache **avcp,
				   struct VenusFid *afid);
extern void afs_vcacheInit(int astatSize);
extern void shutdown_vcache(void);
extern void afs_DisconGiveUpCallbacks(void);
extern void afs_ClearAllStatdFlag(void);

/* VNOPS/afs_vnop_access.c */
extern afs_int32 afs_GetAccessBits(register struct vcache *avc,
				   register afs_int32 arights,
				   register struct vrequest *areq);
extern int afs_AccessOK(struct vcache *avc, afs_int32 arights,
			struct vrequest *areq, afs_int32 check_mode_bits);
#if defined(AFS_SUN5_ENV) || (defined(AFS_SGI_ENV) && !defined(AFS_SGI65_ENV))
extern int afs_access(OSI_VC_DECL(avc), register afs_int32 amode, int flags,
		      afs_ucred_t *acred);
#else
extern int afs_access(OSI_VC_DECL(avc), register afs_int32 amode,
		      afs_ucred_t *acred);
#endif
extern int afs_getRights(OSI_VC_DECL(avc), register afs_int32 arights,
			 afs_ucred_t *acred);

/* VNOPS/afs_vnop_attrs.c */
extern int afs_CopyOutAttrs(register struct vcache *avc,
			    register struct vattr *attrs);
#if     defined(AFS_SUN5_ENV) || defined(AFS_SGI_ENV)
extern int afs_getattr(OSI_VC_DECL(avc), struct vattr *attrs, int flags,
		       afs_ucred_t *acred);
#else
extern int afs_getattr(OSI_VC_DECL(avc), struct vattr *attrs,
		       afs_ucred_t *acred);
#endif
extern int afs_VAttrToAS(register struct vcache *avc,
			 register struct vattr *av,
			 register struct AFSStoreStatus *as);
#if defined(AFS_SUN5_ENV) || defined(AFS_SGI_ENV)
extern int afs_setattr(OSI_VC_DECL(avc), register struct vattr *attrs,
		       int flags, afs_ucred_t *acred);
#else
extern int afs_setattr(OSI_VC_DECL(avc), register struct vattr *attrs,
		       afs_ucred_t *acred);
#endif

/* VNOPS/afs_vnop_create.c */
#ifdef AFS_SGI64_ENV
extern int afs_create(OSI_VC_DECL(adp), char *aname, struct vattr *attrs,
		      int flags, int amode, struct vcache **avcp,
		      afs_ucred_t *acred);
#else /* AFS_SGI64_ENV */
extern int afs_create(OSI_VC_DECL(adp), char *aname, struct vattr *attrs,
		      enum vcexcl aexcl, int amode, struct vcache **avcp,
		      afs_ucred_t *acred);
#endif /* AFS_SGI64_ENV */
extern int afs_LocalHero(register struct vcache *avc,
			 register struct dcache *adc,
			 register AFSFetchStatus * astat, register int aincr);

/* VNOPS/afs_vnop_dirops.c */

extern int afs_mkdir(OSI_VC_DECL(adp), char *aname, struct vattr *attrs, 
		     register struct vcache **avcp, afs_ucred_t *acred);
#if defined(AFS_SUN5_ENV) || defined(AFS_SGI_ENV)
extern int afs_rmdir(OSI_VC_DECL(adp), char *aname, struct vnode *cdirp, 
		     afs_ucred_t *acred);
#else
extern int afs_rmdir(OSI_VC_DECL(adp), char *aname, afs_ucred_t *acred);
#endif

struct fid;
/* VNOPS/afs_vnop_fid.c */
#if !defined(AFS_ATHENA_ENV)
#ifdef AFS_AIX41_ENV
int afs_fid(OSI_VC_DECL(avc), struct fid *fidpp, struct ucred *credp);
#elif defined(AFS_SUN54_ENV)
int afs_fid(OSI_VC_DECL(avc), struct fid *fidpp);
#else
int afs_fid(OSI_VC_DECL(avc), struct fid **fidpp);
#endif                          /* AFS_AIX41_ENV */
#endif

/* VNOPS/afs_vnop_flock.c */
extern afs_int32 lastWarnTime;

extern void lockIdSet(struct AFS_FLOCK *flock, struct SimpleLocks *slp,
		      int clid);
extern int HandleFlock(register struct vcache *avc, int acom,
		       struct vrequest *areq, pid_t clid, int onlymine);

#if defined(AFS_SGI_ENV) || defined(AFS_DARWIN_ENV) || defined(AFS_XBSD_ENV)
extern int afs_lockctl(struct vcache * avc, struct AFS_FLOCK * af, int acmd,
		       afs_ucred_t * acred, pid_t clid);
#else
extern int afs_lockctl(struct vcache * avc, struct AFS_FLOCK * af, int acmd,
		       afs_ucred_t * acred);
#endif

/* VNOPS/afs_vnop_link.c */
#if defined(AFS_SUN5_ENV) || defined(AFS_SGI_ENV)
extern int afs_link(OSI_VC_DECL(adp), struct vcache *avc, char *aname, 
		    afs_ucred_t *acred);
#else
extern int afs_link(struct vcache *avc, OSI_VC_DECL(adp), char *aname, 
		    afs_ucred_t *acred);
#endif

/* VNOPS/afs_vnop_lookup.c */
extern int EvalMountPoint(register struct vcache *avc, struct vcache *advc,
			  struct volume **avolpp,
			  register struct vrequest *areq);
extern void afs_InitFakeStat(struct afs_fakestat_state *state);
extern int afs_EvalFakeStat(struct vcache **avcp,
			    struct afs_fakestat_state *state,
			    struct vrequest *areq);
extern int afs_TryEvalFakeStat(struct vcache **avcp,
			       struct afs_fakestat_state *state,
			       struct vrequest *areq);
extern void afs_PutFakeStat(struct afs_fakestat_state *state);
extern int afs_ENameOK(register char *aname);
extern void Check_AtSys(register struct vcache *avc, const char *aname,
			struct sysname_info *state, struct vrequest *areq);
extern int Next_AtSys(register struct vcache *avc, struct vrequest *areq,
		      struct sysname_info *state);
extern int afs_DoBulkStat(struct vcache *adp, long dirCookie,
			  struct vrequest *areqp);

#if defined(AFS_SUN5_ENV) || defined(AFS_SGI_ENV)
extern int afs_lookup(OSI_VC_DECL(adp), char *aname, struct vcache **avcp, 
		      struct pathname *pnp, int flags, struct vnode *rdir, 
		      afs_ucred_t *acred);
#elif defined(UKERNEL)
extern int afs_lookup(OSI_VC_DECL(adp), char *aname, struct vcache **avcp, 
		      afs_ucred_t *acred, int flags);
#else
extern int afs_lookup(OSI_VC_DECL(adp), char *aname, struct vcache **avcp, 
		      afs_ucred_t *acred);
#endif
	
/* VNOPS/afs_vnop_open.c */
#ifdef AFS_SGI64_ENV
extern int afs_open(bhv_desc_t * bhv, struct vcache **avcp, afs_int32 aflags,
		    afs_ucred_t *acred);
#else
extern int afs_open(struct vcache **avcp, afs_int32 aflags,
		    afs_ucred_t *acred);
#endif


/* VNOPS/afs_vnop_read.c */
extern int afs_MemRead(register struct vcache *avc, struct uio *auio,
		       afs_ucred_t *acred, daddr_t albn,
		       struct buf **abpp, int noLock);
extern int afs_UFSRead(register struct vcache *avc, struct uio *auio,
		       afs_ucred_t *acred, daddr_t albn,
		       struct buf **abpp, int noLock);
extern void afs_PrefetchChunk(struct vcache *avc, struct dcache *adc,
			      afs_ucred_t *acred, struct vrequest *areq);


/* VNOPS/afs_vnop_readdir.c */
extern int afs_rd_stash_i;
#if defined(AFS_SUN5_ENV) || defined(AFS_SGI_ENV) || defined(AFS_DARWIN_ENV) || defined(AFS_XBSD_ENV)
extern int afs_readdir(OSI_VC_DECL(avc), struct uio *auio, 
		       afs_ucred_t *acred, int *eofp);
#elif defined(AFS_HPUX100_ENV)
extern int afs_readdir2(OSI_VC_DECL(avc), struct uio *auio, 
		        afs_ucred_t *acred);
#else
extern int afs_readdir(OSI_VC_DECL(avc), struct uio *auio, 
		       afs_ucred_t *acred);
#endif

/* VNOPS/afs_vnop_remove.c */
extern int afsremove(register struct vcache *adp, register struct dcache *tdc,
		     register struct vcache *tvc, char *aname,
		     afs_ucred_t *acred, struct vrequest *treqp);
extern int afs_remunlink(register struct vcache *avc, register int doit);
extern int afs_remove(OSI_VC_DECL(adp), char *aname, afs_ucred_t *acred);
extern char *afs_newname(void);

/* VNOPS/afs_vnop_rename.c */
extern int afsrename(struct vcache *aodp, char *aname1, struct vcache *andp,
		     char *aname2, afs_ucred_t *acred,
		     struct vrequest *areq);
#ifdef AFS_SGI_ENV
extern int afs_rename(OSI_VC_DECL(aodp), char *aname1, struct vcache *andp, 
		      char *aname2, struct pathname *npnp, 
		      afs_ucred_t *acred);
#else
extern int afs_rename(OSI_VC_DECL(aodp), char *aname1, struct vcache *andp, 
		      char *aname2, afs_ucred_t *acred);
#endif
	
/* VNOPS/afs_vnop_strategy.c */
#if defined(AFS_SUN5_ENV) || defined(AFS_DARWIN_ENV) || defined(AFS_XBSD_ENV)
extern int afs_ustrategy(register struct buf *adp, afs_ucred_t *credp);
#else
extern int afs_ustrategy(register struct buf *adp);
#endif

/* VNOPS/afs_vnop_symlink.c */
extern int afs_MemHandleLink(register struct vcache *avc,
			     struct vrequest *areq);
extern int afs_UFSHandleLink(register struct vcache *avc,
			     struct vrequest *areq);
extern int afs_symlink(OSI_VC_DECL(adp), char *aname, 
		       struct vattr *attrs, char *atargetName, 
		       afs_ucred_t *acred);
extern int afs_readlink(OSI_VC_DECL(avc), struct uio *auio,
			afs_ucred_t *acred);

/* VNOPS/afs_vnop_write.c */
extern int afs_MemWrite(register struct vcache *avc, struct uio *auio,
			int aio, afs_ucred_t *acred, int noLock);
extern int afs_StoreOnLastReference(register struct vcache *avc,
				    register struct vrequest *treq);
extern int afs_UFSWrite(register struct vcache *avc, struct uio *auio,
			int aio, afs_ucred_t *acred, int noLock);
extern int afs_DoPartialWrite(register struct vcache *avc,
			      struct vrequest *areq);
extern int afs_closex(register struct file *afd);

#ifdef AFS_SGI65_ENV
extern int afs_close(OSI_VC_DECL(avc), afs_int32 aflags, 
		     lastclose_t lastclose, afs_ucred_t *acred);
#elif defined(AFS_SGI64_ENV)
extern int afs_close(OSI_VC_DECL(avc), afs_int32 aflags, 
		     lastclose_t lastclose, off_t offset, 
		     afs_ucred_t *acred, struct flid *flp);
#elif defined(AFS_SGI_ENV)
extern int afs_close(OSI_VC_DECL(avc), afs_int32 aflags, 
		     lastclose_t lastclose, off_t offset,
		     afs_ucred_t *acred);
#elif defined(AFS_SUN5_ENV)
extern int afs_close(OSI_VC_DECL(avc), afs_int32 aflags, int count, 
		     offset_t offset, afs_ucred_t *acred);
#else
extern int afs_close(OSI_VC_DECL(avc), afs_int32 aflags,  
		     afs_ucred_t *acred);
#endif

#if defined(AFS_SGI65_ENV)
extern int afs_fsync(OSI_VC_DECL(avc), int flags, afs_ucred_t *acred, 
		     off_t start, off_t stop);
#elif defined(AFS_SGI_ENV) || defined(AFS_SUN53_ENV)
extern int afs_fsync(OSI_VC_DECL(avc), int flag, afs_ucred_t *acred);
#else
extern int afs_fsync(OSI_VC_DECL(avc), afs_ucred_t *acred);
#endif
		

/* afs_volume.c */
extern afs_int32 afs_FVIndex;
extern afs_int32 afs_volCounter;
extern afs_rwlock_t afs_xvolume;
extern struct volume *afs_volumes[NVOLS];
extern afs_dcache_id_t volumeInode;
extern struct volume *afs_FindVolume(struct VenusFid *afid,
				     afs_int32 locktype);
extern struct volume *afs_freeVolList;
extern afs_int32 fvTable[NFENTRIES];
extern void InstallVolumeEntry(struct volume *av, struct vldbentry *ve,
			       int acell);
extern void InstallNVolumeEntry(struct volume *av, struct nvldbentry *ve,
				int acell);
extern void InstallUVolumeEntry(struct volume *av, struct uvldbentry *ve,
				int acell, struct cell *tcell,
				struct vrequest *areq);
extern void afs_ResetVolumeInfo(struct volume *tv);
extern struct volume *afs_MemGetVolSlot(void);
extern void afs_ResetVolumes(struct server *srvp);
extern struct volume *afs_GetVolume(struct VenusFid *afid,
				    struct vrequest *areq,
				    afs_int32 locktype);
extern struct volume *afs_GetVolumeByName(register char *aname,
					  afs_int32 acell, int agood,
					  struct vrequest *areq,
					  afs_int32 locktype);
extern struct volume *afs_UFSGetVolSlot(void);
extern void afs_CheckVolumeNames(int flags);

/* Prototypes for generated files that aren't really in src/afs/ */

/* afs_uuid.c */
extern afs_int32 afs_uuid_equal(afsUUID * u1, afsUUID * u2);
extern afs_int32 afs_uuid_is_nil(afsUUID * u1);
extern void afs_htonuuid(afsUUID * uuidp);
extern void afs_ntohuuid(afsUUID * uuidp);
extern afs_int32 afs_uuid_create(afsUUID * uuid);
extern u_short afs_uuid_hash(afsUUID * uuid);

#if defined(AFS_SUN5_ENV) || defined(AFS_LINUX20_ENV) || defined(AFS_AIX_ENV) || defined(AFS_DARWIN_ENV) || defined(AFS_XBSD_ENV) || defined(AFS_HPUX_ENV) || defined(AFS_SGI62_ENV)
#include "osi_prototypes.h"
#endif

#endif /* _AFS_PROTOTYPES_H_ */
