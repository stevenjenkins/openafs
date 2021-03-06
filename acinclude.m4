dnl This file contains the common configuration code which would
dnl otherwise be duplicated between configure and configure-libafs.
dnl
dnl NB: Because this code is a macro, references to positional shell
dnl parameters must be done like $[]1 instead of $1

AC_DEFUN([OPENAFS_CONFIGURE_COMMON],[
AH_VERBATIM([OPENAFS_HEADER],
[#undef HAVE_RES_SEARCH
#undef STRUCT_SOCKADDR_HAS_SA_LEN
#if !defined(__BIG_ENDIAN__) && !defined(__LITTLE_ENDIAN__)
# if ENDIANESS_IN_SYS_PARAM_H
#  ifndef KERNEL
#   include <sys/types.h>
#   include <sys/param.h>
#   if BYTE_ORDER == BIG_ENDIAN
#   define WORDS_BIGENDIAN 1
#   endif
#  else
#   if defined(AUTOCONF_FOUND_BIGENDIAN)
#    define WORDS_BIGENDIAN 1
#   else
#    undef WORDS_BIGENDIAN
#   endif
#  endif
# else
#  if defined(AUTOCONF_FOUND_BIGENDIAN)
#   define WORDS_BIGENDIAN 1
#  else
#   undef WORDS_BIGENDIAN
#  endif
# endif
#else
# if defined(__BIG_ENDIAN__)
#  define WORDS_BIGENDIAN 1
# else
#  undef WORDS_BIGENDIAN
# endif
#endif
#ifdef UKERNEL
/*
 * Always use 64-bit file offsets for UKERNEL code. Needed for UKERNEL stuff to
 * play nice with some other interfaces like FUSE. We technically only would
 * need to define this when building for such interfaces, but set it always to
 * try and reduce potential confusion. 
 */
#define _FILE_OFFSET_BITS 64
#endif

#undef AFS_NAMEI_ENV
#undef BITMAP_LATER
#undef FAST_RESTART
#undef COMPLETION_H_EXISTS
#undef DEFINED_FOR_EACH_PROCESS
#undef DEFINED_PREV_TASK
#undef EXPORTED_KALLSYMS_SYMBOL
#undef EXPORTED_SYS_CALL_TABLE
#undef EXPORTED_IA32_SYS_CALL_TABLE
#undef EXPORTED_TASKLIST_LOCK
#undef INODE_SETATTR_NOT_VOID
#undef IRIX_HAS_MEM_FUNCS
#undef RECALC_SIGPENDING_TAKES_VOID
#undef STRUCT_FS_HAS_FS_ROLLED
#undef STRUCT_INODE_HAS_I_ALLOC_SEM
#undef STRUCT_TASK_STRUCT_HAS_PARENT
#undef STRUCT_TASK_STRUCT_HAS_REAL_PARENT
#undef STRUCT_TASK_STRUCT_HAS_SIG
#undef STRUCT_TASK_STRUCT_HAS_SIGHAND
#undef STRUCT_TASK_STRUCT_HAS_SIGMASK_LOCK
#undef ssize_t
#undef HAVE_ARPA_NAMESER_COMPAT_H
/* glue for RedHat kernel bug */
#undef ENABLE_REDHAT_BUILDSYS
#if defined(ENABLE_REDHAT_BUILDSYS) && defined(KERNEL) && defined(REDHAT_FIX)
#include "redhat-fix.h"
#endif])

AC_CANONICAL_HOST
SRCDIR_PARENT=`pwd`

#BOZO_SAVE_CORES pam

dnl System identity.
AC_ARG_WITH([afs-sysname],
    [AS_HELP_STRING([--with-afs-sysname=sys], [use sys for the afs sysname])])

dnl General feature options.
AC_ARG_ENABLE([pam],
    [AS_HELP_STRING([--disable-pam], [disable PAM support])],
    ,
    [enable_pam="yes"])
AC_ARG_ENABLE([namei-fileserver],
    [AS_HELP_STRING([--enable-namei-fileserver],
        [force compilation of namei fileserver in preference to inode
         fileserver])],
    , 
    [enable_namei_fileserver="default"])
AC_ARG_ENABLE([cache-bypass],
    [AS_HELP_STRING([--enable-cache-bypass],
        [enable client support for cache bypass])],
    , 
    [enable_cache_bypass="no"])
AC_ARG_ENABLE([supergroups],
    [AS_HELP_STRING([--enable-supergroups],
        [enable support for nested pts groups])],
    , 
    [enable_supergroups="no"])
AC_ARG_ENABLE([fast-restart],
    [AS_HELP_STRING([--enable-fast-restart],
        [enable fast startup of file server without salvaging])],
    , 
    [enable_fast_restart="no"])
AC_ARG_ENABLE([bitmap-later],
    [AS_HELP_STRING([--enable-bitmap-later],
        [enable fast startup of file server by not reading bitmap till
         needed])],
    , 
    [enable_bitmap_later="no"])
AC_ARG_ENABLE([demand-attach-fs],
    [AS_HELP_STRING([--enable-demand-attach-fs],
        [enable Demand Attach Fileserver (please see documentation)])],
    , 
    [enable_demand_attach_fs="no"])
AC_ARG_ENABLE([disconnected],
    [AS_HELP_STRING([--enable-disconnected],
        [enable disconnected support in cache manager (experimental)])],
    , 
    [enable_disconnected="no"])
AC_ARG_ENABLE([unix-sockets],
    [AS_HELP_STRING([--enable-unix-sockets],
        [enable use of unix domain sockets for fssync])],
    ,
    [enable_unix_sockets="yes"])
AC_ARG_ENABLE([icmp-pmtu-discovery],
    [AS_HELP_STRING([--enable-icmp-pmtu-discovery],
        [enable path MTU discovery by decoding ICMP unreachable replies])],
    , 
    [enable_icmp_pmtu_discovery="no"])
AC_ARG_ENABLE([tivoli-tsm],
    [AS_HELP_STRING([--enable-tivoli-tsm],
        [enable use of the Tivoli TSM API libraries for butc support])],
    , 
    [enable_tivoli_tsm="no"])
AC_ARG_ENABLE([pthreaded-ubik],
    [AS_HELP_STRING([--enable-pthreaded-ubik],
        [enable installation of pthreaded ubik applications (defaults to
         disabled)])],
    ,
    [enable_pthreaded_ubik="no"])

dnl Kernel module build options.
AC_ARG_WITH([dux-kernel-headers],
    [AS_HELP_STRING([--with-dux-kernel-headers=path],
        [use the kernel headers found at path (optional, defaults to first
         match in /usr/sys)])])
AC_ARG_WITH([linux-kernel-headers],
    [AS_HELP_STRING([--with-linux-kernel-headers=path],
        [use the kernel headers found at path (optional, defaults to
         /usr/src/linux-2.4, then /usr/src/linux)])])
AC_ARG_WITH([linux-kernel-build],
    [AS_HELP_STRING([--with-linux-kernel-build=path],
	[use the kernel build found at path(optional, defaults to 
	/usr/src/linux-2.4, then /usr/src/linux)])])
AC_ARG_WITH([bsd-kernel-headers],
    [AS_HELP_STRING([--with-bsd-kernel-headers=path],
        [use the kernel headers found at path (optional, defaults to
         /usr/src/sys)])])
AC_ARG_WITH([bsd-kernel-build],
    [AS_HELP_STRING([--with-bsd-kernel-build=path], 
        [use the kernel build found at path (optional, defaults to
         KSRC/i386/compile/GENERIC)])])
AC_ARG_WITH([linux-kernel-packaging],
    [AS_HELP_STRING([--with-linux-kernel-packaging],
        [use standard naming conventions to aid Linux kernel build packaging
         (disables MPS, sets the kernel module name to openafs.ko, and
         installs kernel modules into the standard Linux location)])],
    [AC_SUBST(LINUX_KERNEL_PACKAGING, "yes")
     AC_SUBST(LINUX_LIBAFS_NAME, "openafs")],
    [AC_SUBST(LINUX_LIBAFS_NAME, "libafs")])
AC_ARG_ENABLE([kernel-module],
    [AS_HELP_STRING([--disable-kernel-module],
        [disable compilation of the kernel module (defaults to enabled)])],
    , 
    [enable_kernel_module="yes"])
AC_ARG_ENABLE([redhat-buildsys],
    [AS_HELP_STRING([--enable-redhat-buildsys],
        [enable compilation of the redhat build system kernel (defaults to
         disabled)])],
    ,
    [enable_redhat_buildsys="no"])

dnl Installation locations.
AC_ARG_ENABLE([transarc-paths],
    [AS_HELP_STRING([--enable-transarc-paths],
        [use Transarc style paths like /usr/afs and /usr/vice])],
    , 
    [enable_transarc_paths="no"])

dnl Optimization and debugging flags.
AC_ARG_ENABLE([strip-binaries],
    [AS_HELP_STRING([--disable-strip-binaries],
        [disable stripping of symbol information from binaries (defaults to
         enabled)])],
    ,
    [enable_strip_binaries="maybe"])
AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug],
        [enable compilation of the user space code with debugging information
         (defaults to disabled)])],
    , 
    [enable_debug="no"])
AC_ARG_ENABLE([optimize],
    [AS_HELP_STRING([--disable-optimize],
        [disable optimization for compilation of the user space code (defaults
         to enabled)])],
    , 
    [enable_optimize="yes"])
AC_ARG_ENABLE([warnings],
    [AS_HELP_STRING([--enable-warnings],
        [enable compilation warnings when building with gcc (defaults to
         disabled)])],
    ,
    [enable_warnings="no"])
AC_ARG_ENABLE([checking],
    [AS_HELP_STRING([--enable-checking],
	[turn compilation warnings into errors when building with gcc (defaults
	 to disabled)])],
    [enable_checking="$enableval"],
    [enable_checking="no"])
AC_ARG_ENABLE([debug-kernel],
    [AS_HELP_STRING([--enable-debug-kernel],
        [enable compilation of the kernel module with debugging information
         (defaults to disabled)])],
    ,
    [enable_debug_kernel="no"])
AC_ARG_ENABLE([optimize-kernel],
    [AS_HELP_STRING([--disable-optimize-kernel],
        [disable compilation of the kernel module with optimization (defaults
         based on platform)])],
    , 
    [enable_optimize_kernel="yes"])
AC_ARG_ENABLE([debug-lwp],
    [AS_HELP_STRING([--enable-debug-lwp],
        [enable compilation of the LWP code with debugging information
         (defaults to disabled)])],
    ,
    [enable_debug_lwp="no"])
AC_ARG_ENABLE([optimize-lwp],
    [AS_HELP_STRING([--disable-optimize-lwp],
        [disable optimization for compilation of the LWP code (defaults to
         enabled)])],
    ,
    [enable_optimize_lwp="yes"])
AC_ARG_ENABLE([debug-pam],
    [AS_HELP_STRING([--enable-debug-pam],
        [enable compilation of the PAM code with debugging information
         (defaults to disabled)])],
    ,
    [enable_debug_pam="no"])
AC_ARG_ENABLE([optimize-pam],
    [AS_HELP_STRING([--disable-optimize-pam],
        [disable optimization for compilation of the PAM code (defaults to
         enabled)])],
    ,
    [enable_optimize_pam="yes"])
AC_ARG_ENABLE([linux-syscall-probing],
    [AS_HELP_STRING([--disable-linux-syscall-probing],
	[disabling Linux syscall probing (defaults to enabled)])],
    ,
    [AC_DEFINE(ENABLE_LINUX_SYSCALL_PROBING, 1, 
	[define to enable syscall table probes])])
    

AC_ARG_WITH([xslt-processor],
	AS_HELP_STRING([--with-xslt-processor=ARG],
	[which XSLT processor to use (possible choices are: libxslt, saxon, xalan-j, xsltproc)]),
       	XSLTPROC="$withval",
       	XSLTPROC="libxslt")

AC_ARG_WITH([html-xsl], 
        AS_HELP_STRING([--with-html-xsl],
	[build HTML documentation using Norman Walsh's DocBook XSL stylesheets (default is no; specify a path to chunk.xsl or docbook.xsl)]),
	HTML_XSL="$withval",
	HTML_XSL=no)

enable_login="no"

dnl weird ass systems
dnl AC_AIX
AC_ISC_POSIX
dnl AC_MINIX

dnl Various compiler setup.
AC_TYPE_PID_T
AC_TYPE_SIZE_T

dnl Checks for programs.
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_RANLIB
AC_PROG_YACC
AM_PROG_LEX

OPENAFS_CHECK_BIGENDIAN
OPENAFS_PRINTF_TAKES_Z_LEN

AC_MSG_CHECKING(your OS)
system=$host
case $system in
        *-linux*)

		MKAFS_OSTYPE=LINUX
		if test "x$enable_redhat_buildsys" = "xyes"; then
		 AC_DEFINE(ENABLE_REDHAT_BUILDSYS, 1, [define if you have redhat buildsystem])
		fi
		if test "x$enable_kernel_module" = "xyes"; then
		 if test "x$with_linux_kernel_headers" != "x"; then
		   LINUX_KERNEL_PATH="$with_linux_kernel_headers"
		 else
		   LINUX_KERNEL_PATH="/lib/modules/`uname -r`/source"
		   if test ! -f "$LINUX_KERNEL_PATH/include/linux/version.h"; then
		     LINUX_KERNEL_PATH="/lib/modules/`uname -r`/build"
		   fi
		   if test ! -f "$LINUX_KERNEL_PATH/include/linux/version.h"; then
		     LINUX_KERNEL_PATH="/usr/src/linux-2.4"
		   fi
		   if test ! -f "$LINUX_KERNEL_PATH/include/linux/version.h"; then
		     LINUX_KERNEL_PATH="/usr/src/linux"
		   fi
		 fi
		 if test "x$with_linux_kernel_build" != "x"; then
			 LINUX_KERNEL_BUILD="$with_linux_kernel_build"
		 else
		   LINUX_KERNEL_BUILD=$LINUX_KERNEL_PATH
		 fi
                 if test -f "$LINUX_KERNEL_BUILD/include/generated/utsrelease.h"; then
		   linux_kvers=`fgrep UTS_RELEASE $LINUX_KERNEL_BUILD/include/generated/utsrelease.h |awk 'BEGIN { FS="\"" } { print $[]2 }'|tail -n 1`
		   LINUX_VERSION="$linux_kvers"
		 else
                   if test -f "$LINUX_KERNEL_BUILD/include/linux/utsrelease.h"; then
		     linux_kvers=`fgrep UTS_RELEASE $LINUX_KERNEL_BUILD/include/linux/utsrelease.h |awk 'BEGIN { FS="\"" } { print $[]2 }'|tail -n 1`
		     LINUX_VERSION="$linux_kvers"
                   else
		     if test -f "$LINUX_KERNEL_BUILD/include/linux/version.h"; then
		       linux_kvers=`fgrep UTS_RELEASE $LINUX_KERNEL_BUILD/include/linux/version.h |awk 'BEGIN { FS="\"" } { print $[]2 }'|tail -n 1`
		       if test "x$linux_kvers" = "x"; then
		         if test -f "$LINUX_KERNEL_BUILD/include/linux/version-up.h"; then
		           linux_kvers=`fgrep UTS_RELEASE $LINUX_KERNEL_BUILD/include/linux/version-up.h |awk 'BEGIN { FS="\"" } { print $[]2 }'|tail -n 1`
		           if test "x$linux_kvers" = "x"; then
		             AC_MSG_ERROR(Linux headers lack version definition [2])
		             exit 1
		           else
		             LINUX_VERSION="$linux_kvers"
                           fi
                         else
                           AC_MSG_ERROR(Linux headers lack version definition)
		           exit 1
		         fi
		       else
		         LINUX_VERSION="$linux_kvers"
		       fi
		     else
                       enable_kernel_module="no"
                     fi
                   fi
		 fi
		 if test ! -f "$LINUX_KERNEL_BUILD/include/generated/autoconf.h" &&
		    test ! -f "$LINUX_KERNEL_BUILD/include/linux/autoconf.h"; then
		     enable_kernel_module="no"
		 fi
		 if test "x$enable_kernel_module" = "xno"; then
		  if test "x$with_linux_kernel_headers" != "x"; then
		   AC_MSG_ERROR(No usable linux headers found at $LINUX_KERNEL_PATH)
		   exit 1
		  else
		   AC_MSG_WARN(No usable linux headers found at $LINUX_KERNEL_PATH so disabling kernel module)
		  fi
		 fi
                 dnl do we need to determine SUBARCH from autoconf.h
                 SUBARCH=default
		fi
		AC_MSG_RESULT(linux)
                if test "x$enable_kernel_module" = "xyes"; then
                 AFS_SYSKVERS=`echo $LINUX_VERSION | awk -F\. '{print $[]1 $[]2}'`
                 if test "x${AFS_SYSKVERS}" = "x"; then
                  AC_MSG_ERROR(Couldn't guess your Linux version [2])
                 fi
                fi
                ;;
        *-solaris*)
		MKAFS_OSTYPE=SOLARIS
                AC_MSG_RESULT(sun4)
	        AC_PATH_PROG(SOLARISCC, [cc], ,
		    [/opt/SUNWspro/bin:/opt/SunStudioExpress/bin])
		SOLARIS_UFSVFS_HAS_DQRWLOCK
		SOLARIS_FS_HAS_FS_ROLLED
		SOLARIS_SOLOOKUP_TAKES_SOCKPARAMS
                ;;
        *-sunos*)
		MKAFS_OSTYPE=SUNOS
		enable_kernel_module=no
                AC_MSG_RESULT(sun4)
                ;;
        *-hpux*)
		MKAFS_OSTYPE=HPUX
                AC_MSG_RESULT(hp_ux)
		if test -f "/usr/old/usr/include/ndir.h"; then
		 AC_DEFINE(HAVE_USR_OLD_USR_INCLUDE_NDIR_H, 1, [define if you have old ndir.h])
		fi
                ;;
        *-irix*)
		if test -d /usr/include/sys/SN/SN1; then
		 IRIX_BUILD_IP35="IP35"
		fi
		MKAFS_OSTYPE=IRIX
                AC_MSG_RESULT(sgi)
                ;;
        *-aix*)
		MKAFS_OSTYPE=AIX
                AC_MSG_RESULT(rs_aix)
                ;;
        *-osf*)
		MKAFS_OSTYPE=DUX
                AC_MSG_RESULT(alpha_dux)
                ;;
        powerpc-*-darwin*)
		MKAFS_OSTYPE=DARWIN
                AC_MSG_RESULT(ppc_darwin)
                ;;
        i386-*-darwin*)
		MKAFS_OSTYPE=DARWIN
                AC_MSG_RESULT(x86_darwin)
                ;;
	i386-*-freebsd*)
		MKAFS_OSTYPE=FBSD
		AC_MSG_RESULT(i386_fbsd)
		;;
	x86_64-*-freebsd*)
		MKAFS_OSTYPE=FBSD
		AC_MSG_RESULT(amd64_fbsd)
		;;
	*-netbsd*)
		MKAFS_OSTYPE=NBSD
		AC_MSG_RESULT(nbsd)
		;;
	x86_64-*-openbsd*)
		MKAFS_OSTYPE=OBSD
		AC_MSG_RESULT(amd64_obsd)
		;;
	i386-openbsd*)
		MKAFS_OSTYPE=OBSD
		AC_MSG_RESULT(i386_obsd)
		;;
	*-dragonfly*)
		MKAFS_OSTYPE=DFBSD
		AC_MSG_RESULT(i386_dfbsd)
		;;
        *)
                AC_MSG_RESULT($system)
                ;;
esac

if test "x$with_afs_sysname" != "x"; then
        AFS_SYSNAME="$with_afs_sysname"
else
	AC_MSG_CHECKING(your AFS sysname)
	case $host in
		i?86-*-openbsd?.?)
			v=${host#*openbsd}
			vM=${v%.*}
			vm=${v#*.}
			AFS_SYSNAME="i386_obsd${vM}${vm}"
			;;
		sparc64-*-openbsd?.?)
			v=${host#*openbsd}
			vM=${v%.*}
			vm=${v#*.}
			AFS_SYSNAME="sparc64_obsd${vM}${vm}"
			;;
		x86_64-*-openbsd?.?)
			v=${host#*openbsd}
			vM=${v%.*}
			vm=${v#*.}
			AFS_SYSNAME="amd64_obsd${vM}${vm}"
			;;
		i?86-*-freebsd?.*)
			v=${host#*freebsd}
			vM=${v%.*}
			vm=${v#*.}
			AFS_SYSNAME="i386_fbsd_${vM}${vm}"
			;;
		x86_64-*-freebsd?.*)
			v=${host#*freebsd}
			vM=${v%.*}
			vm=${v#*.}
			AFS_SYSNAME="amd64_fbsd_${vM}${vm}"
			;;
		i386-*-dragonfly2.2*)
			AFS_SYSNAME="i386_dfbsd_23"
			;;
		i386-*-dragonfly2.3*)
			AFS_SYSNAME="i386_dfbsd_23"
			;;
		i?86-*-netbsd*1.5*)
			AFS_SYSNAME="i386_nbsd15"
			;;
		alpha-*-netbsd*1.5*)
			AFS_SYSNAME="alpha_nbsd15"
			;;
		i?86-*-netbsd*1.6[[M-Z]]*)
			AFS_SYSNAME="i386_nbsd20"
			;;
		powerpc-*-netbsd*1.6[[M-Z]]*)
			AFS_SYSNAME="ppc_nbsd20"
			;;
		i?86-*-netbsd*2.0*)
			AFS_SYSNAME="i386_nbsd20"
			;;
		amd64-*-netbsd*2.0*)
			AFS_SYSNAME="amd64_nbsd20"
			;;
		x86_64-*-netbsd*3.[[0-8]]*)
# XXX AFS_PARAM_COMMON handled separately, redundant?
			AFS_PARAM_COMMON=param.nbsd30.h
			AFS_SYSNAME="amd64_nbsd30"
			;;
		x86_64-*-netbsd*4.[[0-8]]*)
# XXX AFS_PARAM_COMMON handled separately, redundant?
			AFS_PARAM_COMMON=param.nbsd40.h
			AFS_SYSNAME="amd64_nbsd40"
			;;
		powerpc-*-netbsd*2.0*)
			AFS_SYSNAME="ppc_nbsd20"
			;;
		i?86-*-netbsd*1.6*)
			AFS_SYSNAME="i386_nbsd16"
			;;
		alpha-*-netbsd*1.6*)
			AFS_SYSNAME="alpha_nbsd16"
			;;
		powerpc-*-netbsd*1.6*)
			AFS_SYSNAME="ppc_nbsd16"
			;;
		i?86-*-netbsd*2.1*)
			AFS_SYSNAME="i386_nbsd21"
			;;
		i?86-*-netbsd*2.99*)
			AFS_SYSNAME="i386_nbsd30"
			;;
		i?86-*-netbsd*3.[[0-8]]*)
			AFS_SYSNAME="i386_nbsd30"
			;;
		i?86-*-netbsd*3.99*)
			AFS_SYSNAME="i386_nbsd30"
			;;
		i?86-*-netbsd*4.[[0-8]]*)
			AFS_SYSNAME="i386_nbsd40"
			;;
		i?86-*-netbsd*4.99*)
			AFS_SYSNAME="i386_nbsd40"
			;;
		hppa*-hp-hpux11.0*)
			AFS_SYSNAME="hp_ux110"
			;;
		hppa*-hp-hpux11.11)
			AFS_SYSNAME="hp_ux11i"
			;;
		hppa*-hp-hpux11.23)
			AFS_SYSNAME="hp_ux1123"
			;;
		ia64-hp-hpux11.22)
			AFS_SYSNAME="ia64_hpux1122"
			;;
		ia64-hp-hpux*)
			AFS_SYSNAME="ia64_hpux1123"
			;;
		hppa*-hp-hpux10*)
			AFS_SYSNAME="hp_ux102"
			;;
		powerpc-apple-darwin7*)
			AFS_SYSNAME="ppc_darwin_70"
			;;
		powerpc-apple-darwin8.*)
			AFS_SYSNAME="ppc_darwin_80"
			;;
		i386-apple-darwin8.*)
			AFS_SYSNAME="x86_darwin_80"
			;;
		powerpc-apple-darwin9.*)
			AFS_SYSNAME="ppc_darwin_90"
			;;
		i386-apple-darwin9.*)
			AFS_SYSNAME="x86_darwin_90"
			;;
		i?86-apple-darwin10.*)
			AFS_SYSNAME="x86_darwin_100"
			;;
		sparc-sun-solaris2.5*)
			AFS_SYSNAME="sun4x_55"
			enable_login="yes"
			;;
		sparc-sun-solaris2.6)
			AFS_SYSNAME="sun4x_56"
			;;
		sparc-sun-solaris2.7)
			AFS_SYSNAME="sun4x_57"
			;;
		sparc-sun-solaris2.8)
			AFS_SYSNAME="sun4x_58"
			;;
		sparc-sun-solaris2.9)
			AFS_SYSNAME="sun4x_59"
			;;
		sparc-sun-solaris2.10)
			AFS_SYSNAME="sun4x_510"
			;;
		sparc-sun-solaris2.11)
			AFS_SYSNAME="sun4x_511"
			;;
		sparc-sun-sunos4*)
			AFS_SYSNAME="sun4_413"
			enable_login="yes"
			;;
		i386-pc-solaris2.7)
			AFS_SYSNAME="sunx86_57"
			;;
		i386-pc-solaris2.8)
			AFS_SYSNAME="sunx86_58"
			;;
		i386-pc-solaris2.9)
			AFS_SYSNAME="sunx86_59"
			;;
		i386-pc-solaris2.10)
			AFS_SYSNAME="sunx86_510"
			;;
		i386-pc-solaris2.11)
			AFS_SYSNAME="sunx86_511"
			;;
		alpha*-dec-osf4.0*)
			AFS_SYSNAME="alpha_dux40"
			;;
		alpha*-dec-osf5.0*)
			AFS_SYSNAME="alpha_dux50"
			;;
		alpha*-dec-osf5.1*)
			AFS_SYSNAME="alpha_dux51"
			;;
		mips-sgi-irix6.5)
			AFS_SYSNAME="sgi_65"
			;;
		ia64-*-linux*)
			AFS_SYSNAME="ia64_linuxXX"
			;;
		powerpc-*-linux*)
			AFS_SYSNAME="`/bin/arch`_linuxXX"
			;;
		powerpc64-*-linux*)
			AFS_SYSNAME="ppc64_linuxXX"
			;;
		alpha*-linux*)
			AFS_SYSNAME="alpha_linux_XX"
			;;
		s390-*-linux*)
			AFS_SYSNAME="s390_linuxXX"
			;;
		s390x-*-linux*)
			AFS_SYSNAME="s390x_linuxXX"
			;;
		sparc-*-linux*)
			AFS_SYSNAME="`/bin/arch`_linuxXX"
			;;
		sparc64-*-linux*)
			AFS_SYSNAME="sparc64_linuxXX"
			;;
		i?86-*-linux*)
			AFS_SYSNAME="i386_linuxXX"
			;;
		arm*-linux*)
			AFS_SYSNAME="arm_linuxXX"
			;;
		parisc-*-linux-gnu|hppa-*-linux-gnu)
			AFS_SYSNAME="parisc_linuxXX"
			enable_pam="no"
			;;
		power*-ibm-aix4.2*)
			AFS_SYSNAME="rs_aix42"
			enable_pam="no"
			;;
		power*-ibm-aix4.3*)
			AFS_SYSNAME="rs_aix42"
			enable_pam="no"
			;;
		power*-ibm-aix5.1*)
			AFS_SYSNAME="rs_aix51"
			enable_pam="no"
			;;
		power*-ibm-aix5.2*)
			AFS_SYSNAME="rs_aix52"
			enable_pam="no"
			;;
		power*-ibm-aix5.3*)
			AFS_SYSNAME="rs_aix53"
			enable_pam="no"
			;;
		power*-ibm-aix6.1*)
			AFS_SYSNAME="rs_aix61"
			enable_pam="no"
			;;
		x86_64-*-linux-gnu)
			AFS_SYSNAME="amd64_linuxXX"
			enable_pam="yes"
			;;
		*)
			AC_MSG_ERROR(An AFS sysname is required)
			exit 1
			;;
	esac
	case $AFS_SYSNAME in
		*_linux* | *_umlinux*)
			if test "x${AFS_SYSKVERS}" = "x"; then
			 AC_MSG_ERROR(Couldn't guess your Linux version. Please use the --with-afs-sysname option to configure an AFS sysname.)
			fi
			_AFS_SYSNAME=`echo $AFS_SYSNAME|sed s/XX\$/$AFS_SYSKVERS/`
			AFS_SYSNAME="$_AFS_SYSNAME"
			AC_TRY_KBUILD(
			 [],
			 [#ifndef CONFIG_USERMODE
			  #error not UML
			  #endif],
			 ac_cv_linux_is_uml=yes,)
			if test "${ac_cv_linux_is_uml}" = yes; then
			 _AFS_SYSNAME=`echo $AFS_SYSNAME|sed s/linux/umlinux/`
			fi
			AFS_SYSNAME="$_AFS_SYSNAME"
			;;
	esac
        AC_MSG_RESULT($AFS_SYSNAME)
fi

case $AFS_SYSNAME in
	*_darwin*)
		DARWIN_PLIST=src/libafs/afs.${AFS_SYSNAME}.plist
		DARWIN_INFOFILE=afs.${AFS_SYSNAME}.plist
		;;
esac

dnl Some hosts have a separate common param file they should include.  Figure
dnl out if we're on one of them now that we know the sysname.
case $AFS_SYSNAME in
    *_nbsd15)   AFS_PARAM_COMMON=param.nbsd15.h  ;;
    *_nbsd16)   AFS_PARAM_COMMON=param.nbsd16.h  ;;
    *_nbsd20)   AFS_PARAM_COMMON=param.nbsd20.h  ;;
    *_nbsd21)   AFS_PARAM_COMMON=param.nbsd21.h  ;;
    *_nbsd30)   AFS_PARAM_COMMON=param.nbsd30.h  ;;
    *_nbsd40)   AFS_PARAM_COMMON=param.nbsd40.h  ;;
    *_obsd31)   AFS_PARAM_COMMON=param.obsd31.h  ;;
    *_obsd32)   AFS_PARAM_COMMON=param.obsd32.h  ;;
    *_obsd33)   AFS_PARAM_COMMON=param.obsd33.h  ;;
    *_obsd34)   AFS_PARAM_COMMON=param.obsd34.h  ;;
    *_obsd35)   AFS_PARAM_COMMON=param.obsd35.h  ;;
    *_obsd36)   AFS_PARAM_COMMON=param.obsd36.h  ;;
    *_obsd37)   AFS_PARAM_COMMON=param.obsd37.h  ;;
    *_obsd38)   AFS_PARAM_COMMON=param.obsd38.h  ;;
    *_obsd39)   AFS_PARAM_COMMON=param.obsd39.h  ;;
    *_obsd40)   AFS_PARAM_COMMON=param.obsd40.h  ;;
    *_obsd41)   AFS_PARAM_COMMON=param.obsd41.h  ;;
    *_obsd42)   AFS_PARAM_COMMON=param.obsd42.h  ;;
    *_obsd43)   AFS_PARAM_COMMON=param.obsd43.h  ;;
    *_obsd44)   AFS_PARAM_COMMON=param.obsd44.h  ;;
    *_obsd45)   AFS_PARAM_COMMON=param.obsd45.h  ;;
    *_obsd46)   AFS_PARAM_COMMON=param.obsd46.h  ;;
    *_linux22)  AFS_PARAM_COMMON=param.linux22.h ;;
    *_linux24)  AFS_PARAM_COMMON=param.linux24.h ;;
    *_linux26)  AFS_PARAM_COMMON=param.linux26.h ;;
esac

case $AFS_SYSNAME in *_linux* | *_umlinux*)

		# Add (sub-) architecture-specific paths needed by conftests
		case $AFS_SYSNAME  in
			*_umlinux26)
				UMLINUX26_FLAGS="-I$LINUX_KERNEL_PATH/arch/um/include"
				UMLINUX26_FLAGS="$UMLINUX26_FLAGS -I$LINUX_KERNEL_PATH/arch/um/kernel/tt/include"
 				UMLINUX26_FLAGS="$UMLINUX26_FLAGS -I$LINUX_KERNEL_PATH/arch/um/kernel/skas/include"
				CPPFLAGS="$CPPFLAGS $UMLINUX26_FLAGS"
		esac

		if test "x$enable_kernel_module" = "xyes"; then
		 if test "x$enable_debug_kernel" = "xno"; then
			LINUX_GCC_KOPTS="$LINUX_GCC_KOPTS -fomit-frame-pointer"
		 fi
		 OPENAFS_GCC_SUPPORTS_MARCH
		 AC_SUBST(P5PLUS_KOPTS)
		 OPENAFS_GCC_NEEDS_NO_STRENGTH_REDUCE
		 OPENAFS_GCC_NEEDS_NO_STRICT_ALIASING
		 OPENAFS_GCC_SUPPORTS_NO_COMMON
		 OPENAFS_GCC_SUPPORTS_PIPE
		 AC_SUBST(LINUX_GCC_KOPTS)
	         ifdef([OPENAFS_CONFIGURE_LIBAFS],
	           [LINUX_BUILD_VNODE_FROM_INODE(src/config,src/afs)],
	           [LINUX_BUILD_VNODE_FROM_INODE(${srcdir}/src/config,src/afs/LINUX,${srcdir}/src/afs/LINUX)]
	         )

                 LINUX_KBUILD_USES_EXTRA_CFLAGS
		 LINUX_KERNEL_COMPILE_WORKS
		 LINUX_EXPORTS_FIND_TASK_BY_PID
		 LINUX_EXPORTS_PROC_ROOT_FS
                 LINUX_HAVE_CURRENT_KERNEL_TIME
		 LINUX_HAVE_WRITE_BEGIN_AOP
                 LINUX_HAVE_BDI_INIT
                 LINUX_KMEM_CACHE_INIT
                 LINUX_HAVE_GRAB_CACHE_PAGE_WRITE_BEGIN
		 LINUX_HAVE_PAGEVEC_LRU_ADD_FILE
		 LINUX_HAVE_SPLICE_DIRECT_TO_ACTOR
                 LINUX_STRUCT_TASK_HAS_CRED
		 LINUX_STRUCT_PROC_DIR_ENTRY_HAS_OWNER
		 LINUX_HAVE_KMEM_CACHE_T
		 LINUX_KMEM_CACHE_CREATE_CTOR_TAKES_VOID
		 LINUX_D_PATH_TAKES_STRUCT_PATH
		 LINUX_NEW_EXPORT_OPS
		 LINUX_CONFIG_H_EXISTS
		 LINUX_COMPLETION_H_EXISTS
		 LINUX_SEMAPHORE_H_EXISTS
		 LINUX_EXPORTFS_H_EXISTS
		 LINUX_DEFINES_FOR_EACH_PROCESS
		 LINUX_DEFINES_PREV_TASK
		 LINUX_FS_STRUCT_SUPER_HAS_ALLOC_INODE
		 LINUX_STRUCT_SUPER_BLOCK_HAS_S_BDI
		 LINUX_STRUCT_BDI_HAS_NAME
		 LINUX_FS_STRUCT_INODE_HAS_I_ALLOC_SEM
		 LINUX_FS_STRUCT_INODE_HAS_I_BLKBITS
		 LINUX_FS_STRUCT_INODE_HAS_I_BLKSIZE
		 LINUX_FS_STRUCT_INODE_HAS_I_MUTEX
		 LINUX_FS_STRUCT_INODE_HAS_I_SECURITY
	  	 LINUX_INODE_SETATTR_RETURN_TYPE
	  	 LINUX_IOP_I_CREATE_TAKES_NAMEIDATA
	  	 LINUX_IOP_I_LOOKUP_TAKES_NAMEIDATA
	  	 LINUX_IOP_I_PERMISSION_TAKES_NAMEIDATA
	  	 LINUX_IOP_I_PUT_LINK_TAKES_COOKIE
	  	 LINUX_DOP_D_REVALIDATE_TAKES_NAMEIDATA
	  	 LINUX_FOP_F_FLUSH_TAKES_FL_OWNER_T
	  	 LINUX_AOP_WRITEBACK_CONTROL
		 LINUX_FS_STRUCT_FOP_HAS_FLOCK
		 LINUX_FS_STRUCT_FOP_HAS_SENDFILE
		 LINUX_FS_STRUCT_FOP_HAS_SPLICE
		 LINUX_KERNEL_LINUX_SEQ_FILE_H
		 LINUX_KERNEL_POSIX_LOCK_FILE_WAIT_ARG
		 LINUX_POSIX_TEST_LOCK_RETURNS_CONFLICT
		 LINUX_POSIX_TEST_LOCK_CONFLICT_ARG
		 LINUX_KERNEL_SOCK_CREATE
		 LINUX_KERNEL_PAGE_FOLLOW_LINK
		 LINUX_KERNEL_HLIST_UNHASHED
                 LINUX_KEY_TYPE_H_EXISTS
		 LINUX_EXPORTS_KEY_TYPE_KEYRING
		 LINUX_KEYS_HAVE_SESSION_TO_PARENT
		 LINUX_NEED_RHCONFIG
		 LINUX_RECALC_SIGPENDING_ARG_TYPE
		 LINUX_SCHED_STRUCT_TASK_STRUCT_HAS_PARENT
		 LINUX_SCHED_STRUCT_TASK_STRUCT_HAS_REAL_PARENT
		 LINUX_SCHED_STRUCT_TASK_STRUCT_HAS_SIG
		 LINUX_SCHED_STRUCT_TASK_STRUCT_HAS_SIGHAND
		 LINUX_SCHED_STRUCT_TASK_STRUCT_HAS_SIGMASK_LOCK
		 LINUX_SCHED_STRUCT_TASK_STRUCT_HAS_RLIM
		 LINUX_SCHED_STRUCT_TASK_STRUCT_HAS_SIGNAL_RLIM
		 LINUX_SCHED_STRUCT_TASK_STRUCT_HAS_EXIT_STATE
		 LINUX_SCHED_STRUCT_TASK_STRUCT_HAS_TGID
		 LINUX_SCHED_STRUCT_TASK_STRUCT_HAS_TODO
		 LINUX_SCHED_STRUCT_TASK_STRUCT_HAS_THREAD_INFO
		 LINUX_EXPORTS_TASKLIST_LOCK
		 LINUX_GET_SB_HAS_STRUCT_VFSMOUNT
		 LINUX_STATFS_TAKES_DENTRY
		 LINUX_FREEZER_H_EXISTS
		 LINUX_HAVE_SVC_ADDR_IN
		 if test "x$ac_cv_linux_freezer_h_exists" = "xyes" ; then
		  AC_DEFINE(FREEZER_H_EXISTS, 1, [define if you have linux/freezer.h])
		 fi
		 LINUX_REFRIGERATOR
		 LINUX_LINUX_KEYRING_SUPPORT
		 LINUX_KEY_ALLOC_NEEDS_STRUCT_TASK
		 LINUX_KEY_ALLOC_NEEDS_CRED
		 LINUX_DO_SYNC_READ
		 LINUX_GENERIC_FILE_AIO_READ
		 LINUX_INIT_WORK_HAS_DATA
		 LINUX_REGISTER_SYSCTL_TABLE_NOFLAG
		 LINUX_SYSCTL_TABLE_CHECKING
		 LINUX_STRUCT_CTL_TABLE_HAS_CTL_NAME
		 LINUX_HAVE_IGET
		 if test "x$ac_cv_linux_have_iget" = "xno"; then
		   AC_DEFINE([LINUX_USE_FH], 1, [define to use linux file handles for cache files])
		 fi
		 LINUX_HAVE_I_SIZE_READ
		 LINUX_HAVE_D_ALLOC_ANON
		 if test "x$ac_cv_linux_d_alloc_anon" = "xno"; then
		   AC_DEFINE([AFS_NONFSTRANS], 1, [define to disable the nfs translator])
		 fi
		 LINUX_FS_STRUCT_NAMEIDATA_HAS_PATH
	         LINUX_EXPORTS_INIT_MM
                 LINUX_EXPORTS_SYS_CHDIR
                 LINUX_EXPORTS_SYS_OPEN
		 LINUX_EXPORTS_RCU_READ_LOCK
		 if test "x$with_linux_kernel_packaging" = "xno" ; then
		   LINUX_WHICH_MODULES
		 else
		   AC_SUBST(MPS,'SP')
		 fi
                 if test "x$ac_cv_linux_config_modversions" = "xno" -o $AFS_SYSKVERS -ge 26; then
                   AC_MSG_WARN([Cannot determine sys_call_table status. assuming it isn't exported])
                   ac_cv_linux_exports_sys_call_table=no
		   if test -f "$LINUX_KERNEL_PATH/include/asm/ia32_unistd.h"; then
		     ac_cv_linux_exports_ia32_sys_call_table=yes
		   fi
                 else
                   LINUX_EXPORTS_KALLSYMS_ADDRESS
                   LINUX_EXPORTS_KALLSYMS_SYMBOL
                   LINUX_EXPORTS_SYS_CALL_TABLE
                   LINUX_EXPORTS_IA32_SYS_CALL_TABLE
                   if test "x$ac_cv_linux_exports_sys_call_table" = "xno"; then
                         linux_syscall_method=none
                         if test "x$ac_cv_linux_exports_init_mm" = "xyes"; then
                            linux_syscall_method=scan
                            if test "x$ac_cv_linux_exports_kallsyms_address" = "xyes"; then
                               linux_syscall_method=scan_with_kallsyms_address
                            fi
                         fi
                         if test "x$ac_cv_linux_exports_kallsyms_symbol" = "xyes"; then
                            linux_syscall_method=kallsyms_symbol
                         fi
                         if test "x$linux_syscall_method" = "xnone"; then
			    AC_MSG_WARN([no available sys_call_table access method -- guessing scan])
                            linux_syscall_method=scan
                         fi
                   fi
                 fi
		 if test -f "$LINUX_KERNEL_PATH/include/linux/in_systm.h"; then
		  AC_DEFINE(HAVE_IN_SYSTM_H, 1, [define if you have in_systm.h header file])
	         fi
		 if test -f "$LINUX_KERNEL_PATH/include/linux/mm_inline.h"; then
		  AC_DEFINE(HAVE_MM_INLINE_H, 1, [define if you have mm_inline.h header file])
	         fi
		 if test "x$ac_cv_linux_exports_sys_chdir" = "xyes" ; then
		  AC_DEFINE(EXPORTED_SYS_CHDIR, 1, [define if your linux kernel exports sys_chdir])
		 fi
		 if test "x$ac_cv_linux_exports_sys_open" = "xyes" ; then
		  AC_DEFINE(EXPORTED_SYS_OPEN, 1, [define if your linux kernel exports sys_open])
		 fi
                 if test "x$ac_cv_linux_exports_sys_call_table" = "xyes"; then
                  AC_DEFINE(EXPORTED_SYS_CALL_TABLE, 1, [define if your linux kernel exports sys_call_table])
                 fi
                 if test "x$ac_cv_linux_exports_ia32_sys_call_table" = "xyes"; then
                  AC_DEFINE(EXPORTED_IA32_SYS_CALL_TABLE, 1, [define if your linux kernel exports ia32_sys_call_table])
                 fi
                 if test "x$ac_cv_linux_exports_kallsyms_symbol" = "xyes"; then
                  AC_DEFINE(EXPORTED_KALLSYMS_SYMBOL, 1, [define if your linux kernel exports kallsyms])
                 fi
                 if test "x$ac_cv_linux_exports_kallsyms_address" = "xyes"; then
                  AC_DEFINE(EXPORTED_KALLSYMS_ADDRESS, 1, [define if your linux kernel exports kallsyms address])
                 fi
		 if test "x$ac_cv_linux_completion_h_exists" = "xyes" ; then
		  AC_DEFINE(COMPLETION_H_EXISTS, 1, [define if completion_h exists])
		 fi
		 if test "x$ac_cv_linux_config_h_exists" = "xyes" ; then
		  AC_DEFINE(CONFIG_H_EXISTS, 1, [define if config.h exists])
		 fi
		 if test "x$ac_cv_linux_exportfs_h_exists" = "xyes"; then
		  AC_DEFINE(EXPORTFS_H_EXISTS, 1, [define if linux/exportfs.h exists])
		 fi
		 if test "x$ac_cv_linux_key_type_h_exists" = "xyes" ; then
		  AC_DEFINE(KEY_TYPE_H_EXISTS, 1, [define if key-type.h exists])
		 fi
		 if test "x$ac_cv_linux_defines_for_each_process" = "xyes" ; then
		  AC_DEFINE(DEFINED_FOR_EACH_PROCESS, 1, [define if for_each_process defined])
		 fi
		 if test "x$ac_cv_linux_defines_prev_task" = "xyes" ; then
		  AC_DEFINE(DEFINED_PREV_TASK, 1, [define if prev_task defined])
		 fi
		 if test "x$ac_cv_linux_func_inode_setattr_returns_int" = "xyes" ; then
		  AC_DEFINE(INODE_SETATTR_NOT_VOID, 1, [define if your setattr return return non-void])
		 fi
		 if test "x$ac_cv_linux_fs_struct_super_has_alloc_inode" = "xyes" ; then
		  AC_DEFINE(STRUCT_SUPER_HAS_ALLOC_INODE, 1, [define if your struct super_operations has alloc_inode])
		 fi
		 if test "x$ac_cv_linux_fs_struct_inode_has_i_alloc_sem" = "xyes"; then 
		  AC_DEFINE(STRUCT_INODE_HAS_I_ALLOC_SEM, 1, [define if your struct inode has alloc_sem])
		 fi
		 if test "x$ac_cv_linux_fs_struct_inode_has_i_blksize" = "xyes"; then 
		  AC_DEFINE(STRUCT_INODE_HAS_I_BLKSIZE, 1, [define if your struct inode has i_blksize])
		 fi
		 if test "x$ac_cv_linux_fs_struct_inode_has_i_security" = "xyes"; then 
		  AC_DEFINE(STRUCT_INODE_HAS_I_SECURITY, 1, [define if you struct inode has i_security])
		 fi
		 if test "x$ac_cv_linux_fs_struct_inode_has_i_mutex" = "xyes"; then 
		  AC_DEFINE(STRUCT_INODE_HAS_I_MUTEX, 1, [define if you struct inode has i_mutex])
		 fi
		 if test "x$ac_cv_linux_func_recalc_sigpending_takes_void" = "xyes"; then
		  AC_DEFINE(RECALC_SIGPENDING_TAKES_VOID, 1, [define if your recalc_sigpending takes void])
		 fi
		 if test "x$ac_cv_linux_kernel_posix_lock_file_wait_arg" = "xyes" ; then
		  AC_DEFINE(POSIX_LOCK_FILE_WAIT_ARG, 1, [define if your linux kernel uses 3 arguments for posix_lock_file])
		 fi
		 if test "x$ac_cv_linux_kernel_sock_create_v" = "xyes" ; then
		  AC_DEFINE(LINUX_KERNEL_SOCK_CREATE_V, 1, [define if your linux kernel uses 5 arguments for sock_create])
		 fi
		 if test "x$ac_cv_linux_kernel_page_follow_link" = "xyes" ; then
		  AC_DEFINE(HAVE_KERNEL_PAGE_FOLLOW_LINK, 1, [define if your linux kernel provides page_follow_link])
		 fi
		 if test "x$ac_cv_linux_kernel_hlist_unhashed" = "xyes" ; then
		  AC_DEFINE(HAVE_KERNEL_HLIST_UNHASHED, 1, [define if your linux kernel provides hlist_unhashed])
		 fi
		 if test "x$ac_linux_seq_file" = "xyes" ; then
		  AC_DEFINE(HAVE_KERNEL_LINUX_SEQ_FILE_H, 1, [define if your linux kernel has linux/seq_file.h])
		 fi
		 if test "x$ac_cv_linux_sched_struct_task_struct_has_parent" = "xyes"; then 
		  AC_DEFINE(STRUCT_TASK_STRUCT_HAS_PARENT, 1, [define if your struct task_struct has parent])
		 fi
		 if test "x$ac_cv_linux_sched_struct_task_struct_has_real_parent" = "xyes"; then 
		  AC_DEFINE(STRUCT_TASK_STRUCT_HAS_REAL_PARENT, 1, [define if your struct task_struct has real_parent])
		 fi
		 if test "x$ac_cv_linux_sched_struct_task_struct_has_sigmask_lock" = "xyes"; then 
		  AC_DEFINE(STRUCT_TASK_STRUCT_HAS_SIGMASK_LOCK, 1, [define if your struct task_struct has sigmask_lock])
		 fi
		 if test "x$ac_cv_linux_sched_struct_task_struct_has_sighand" = "xyes"; then 
		  AC_DEFINE(STRUCT_TASK_STRUCT_HAS_SIGHAND, 1, [define if your struct task_struct has sighand])
		 fi
		 if test "x$ac_cv_linux_sched_struct_task_struct_has_sig" = "xyes"; then 
		  AC_DEFINE(STRUCT_TASK_STRUCT_HAS_SIG, 1, [define if your struct task_struct has sig])
		 fi
		 if test "x$ac_cv_linux_sched_struct_task_struct_has_rlim" = "xyes"; then 
		  AC_DEFINE(STRUCT_TASK_STRUCT_HAS_RLIM, 1, [define if your struct task_struct has rlim])
		 fi
		 if test "x$ac_cv_linux_sched_struct_task_struct_has_signal_rlim" = "xyes"; then 
		  AC_DEFINE(STRUCT_TASK_STRUCT_HAS_SIGNAL_RLIM, 1, [define if your struct task_struct has signal->rlim])
		 fi
		 if test "x$ac_cv_linux_sched_struct_task_struct_has_exit_state" = "xyes"; then 
		  AC_DEFINE(STRUCT_TASK_STRUCT_HAS_EXIT_STATE, 1, [define if your struct task_struct has exit_state])
		 fi
		 if test "x$ac_cv_linux_sched_struct_task_struct_has_tgid" = "xyes"; then 
		  AC_DEFINE(STRUCT_TASK_STRUCT_HAS_TGID, 1, [define if your struct task_struct has tgid])
		 fi
		 if test "x$ac_cv_linux_sched_struct_task_struct_has_todo" = "xyes"; then 
		  AC_DEFINE(STRUCT_TASK_STRUCT_HAS_TODO, 1, [define if your struct task_struct has todo])
		 fi
		 if test "x$ac_cv_linux_sched_struct_task_struct_has_thread_info" = "xyes"; then 
		  AC_DEFINE(STRUCT_TASK_STRUCT_HAS_THREAD_INFO, 1, [define if your struct task_struct has thread_info])
		 fi
		 if test "x$ac_cv_linux_get_sb_has_struct_vfsmount" = "xyes"; then
		  AC_DEFINE(GET_SB_HAS_STRUCT_VFSMOUNT, 1, [define if your get_sb_nodev needs a struct vfsmount argument])
		 fi
		 if test "x$ac_cv_linux_statfs_takes_dentry" = "xyes"; then
		  AC_DEFINE(STATFS_TAKES_DENTRY, 1, [define if your statfs takes a dentry argument])
		 fi
		 if test "x$ac_cv_linux_func_a_writepage_takes_writeback_control" = "xyes" ; then
		  AC_DEFINE(AOP_WRITEPAGE_TAKES_WRITEBACK_CONTROL, 1, [define if your aops.writepage takes a struct writeback_control argument])
		 fi
		 if test "x$ac_cv_linux_func_refrigerator_takes_pf_freeze" = "xyes" ; then
		  AC_DEFINE(LINUX_REFRIGERATOR_TAKES_PF_FREEZE, 1, [define if your refrigerator takes PF_FREEZE])
		 fi
		 if test "x$ac_cv_linux_func_i_create_takes_nameidata" = "xyes" ; then
		  AC_DEFINE(IOP_CREATE_TAKES_NAMEIDATA, 1, [define if your iops.create takes a nameidata argument])
		 fi
		 if test "x$ac_cv_linux_func_f_flush_takes_fl_owner_t" = "xyes" ; then
		  AC_DEFINE(FOP_FLUSH_TAKES_FL_OWNER_T, 1, [define if your fops.flush takes an fl_owner_t argument])
		 fi
		 if test "x$ac_cv_linux_func_i_lookup_takes_nameidata" = "xyes" ; then
		  AC_DEFINE(IOP_LOOKUP_TAKES_NAMEIDATA, 1, [define if your iops.lookup takes a nameidata argument])
		 fi
		 if test "x$ac_cv_linux_func_i_permission_takes_nameidata" = "xyes" ; then
		  AC_DEFINE(IOP_PERMISSION_TAKES_NAMEIDATA, 1, [define if your iops.permission takes a nameidata argument])
		 fi
		 if test "x$ac_cv_linux_func_d_revalidate_takes_nameidata" = "xyes" ; then
		  AC_DEFINE(DOP_REVALIDATE_TAKES_NAMEIDATA, 1, [define if your dops.d_revalidate takes a nameidata argument])
		 fi
		 if test "x$ac_cv_linux_init_work_has_data" = "xyes" ; then
		  AC_DEFINE(INIT_WORK_HAS_DATA, 1, [define if INIT_WORK takes a data (3rd) argument])
		 fi
		 if test "x$ac_cv_linux_fs_struct_fop_has_flock" = "xyes" ; then
		  AC_DEFINE(STRUCT_FILE_OPERATIONS_HAS_FLOCK, 1, [define if your struct file_operations has flock])
		 fi
		 if test "x$ac_cv_linux_fs_struct_fop_has_sendfile" = "xyes" ; then
		  AC_DEFINE(STRUCT_FILE_OPERATIONS_HAS_SENDFILE, 1, [define if your struct file_operations has sendfile])
		 fi
		 if test "x$ac_cv_linux_fs_struct_fop_has_splice" = "xyes" ; then
		  AC_DEFINE(STRUCT_FILE_OPERATIONS_HAS_SPLICE, 1, [define if your struct file_operations has splice_write and splice_read])
		 fi
		 if test "x$ac_cv_linux_register_sysctl_table_noflag" = "xyes" ; then
		  AC_DEFINE(REGISTER_SYSCTL_TABLE_NOFLAG, 1, [define if register_sysctl_table has no insert_at head flag])
		 fi
		 if test "x$ac_cv_linux_sysctl_table_checking" = "xyes" ; then
		  AC_DEFINE(SYSCTL_TABLE_CHECKING, 1, [define if your kernel has sysctl table checking])
		 fi
		 if test "x$ac_cv_linux_have_iget" = "xyes" ; then
		  AC_DEFINE(HAVE_IGET, 1, [define if your kernel has iget])
		 fi
		 if test "x$ac_cv_linux_struct_nameidata_has_path" = "xyes" ; then
		  AC_DEFINE(STRUCT_NAMEIDATA_HAS_PATH, 1, [define if your struct nameidata has path])
		 fi
		 if test "x$ac_cv_linux_exports_init_mm" = "xyes" ; then
		  AC_DEFINE(EXPORTED_INIT_MM, 1, [define if your kernel exports init_mm])
		 fi
		 if test "x$ac_cv_linux_exports_tasklist_lock" = "xyes" ; then
		  AC_DEFINE(EXPORTED_TASKLIST_LOCK, 1, [define if tasklist_lock exported])
		 fi
		 if test "x$ac_cv_linux_have_kmem_cache_t" = "xyes" ; then
		  AC_DEFINE(HAVE_KMEM_CACHE_T, 1, [define if kmem_cache_t exists])
		 fi
		 if test "x$ac_cv_linux_kmem_cache_init" = "xyes" ; then
		  AC_DEFINE(KMEM_CACHE_INIT, 1, [define for new kmem_cache init function parameters])
		 fi
		 if test "x$ac_cv_linux_have_current_kernel_time" = "xyes" ; then
		  AC_DEFINE(HAVE_CURRENT_KERNEL_TIME, 1, [define if current_kernel_time() exists])
		 fi
		 if test "x$ac_cv_linux_have_kmem_cache_t" = "xyes" ; then
		  AC_DEFINE(KMEM_CACHE_TAKES_DTOR, 1, [define if kmem_cache_create takes a destructor argument])
		 fi
		 if test "x$ac_cv_linux_kernel_page_follow_link" = "xyes" -o "x$ac_cv_linux_func_i_put_link_takes_cookie" = "xyes"; then
		  AC_DEFINE(USABLE_KERNEL_PAGE_SYMLINK_CACHE, 1, [define if your kernel has a usable symlink cache API])
		 else
		  AC_MSG_WARN([your kernel does not have a usable symlink cache API])
		 fi
		 if test "x$ac_cv_linux_have_svc_addr_in" = "xyes"; then
		  AC_DEFINE(HAVE_SVC_ADDR_IN, 1, [define if svc_add_in exists])
                 fi
                :
		fi
esac

AC_CACHE_VAL(ac_cv_sockaddr_len,
[
AC_MSG_CHECKING([if struct sockaddr has sa_len field])
AC_TRY_COMPILE( [#include <sys/types.h>
#include <sys/socket.h>],
[struct sockaddr *a;
a->sa_len=0;], ac_cv_sockaddr_len=yes, ac_cv_sockaddr_len=no)
AC_MSG_RESULT($ac_cv_sockaddr_len)])
if test "$ac_cv_sockaddr_len" = "yes"; then
   AC_DEFINE(STRUCT_SOCKADDR_HAS_SA_LEN, 1, [define if you struct sockaddr sa_len])
fi
if test "x${MKAFS_OSTYPE}" = "xIRIX"; then
        echo Skipping library tests because they confuse Irix.
else
  AC_SEARCH_LIBS([socket], [socket inet])
  AC_SEARCH_LIBS([connect], [nsl])
  AC_SEARCH_LIBS([gethostbyname], [dns nsl resolv])

  dnl darwin wants it, aix hates it
  AC_MSG_CHECKING(for the useability of arpa/nameser_compat.h)
  AC_TRY_COMPILE([
  #include <stdlib.h>
  #include <stdio.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <arpa/nameser.h>
  #include <arpa/nameser_compat.h>
  #include <resolv.h>
  ], [static int i; i = 0;],
  [AC_MSG_RESULT(yes)
   AC_DEFINE(HAVE_ARPA_NAMESER_COMPAT_H, 1, [define if arpa/nameser_compat.h exists])],
  [AC_MSG_RESULT(no)
   ])

  openafs_save_libs="$LIBS"
  AC_MSG_CHECKING([for res_search])
  AC_FUNC_RES_SEARCH

  if test "$ac_cv_func_res_search" = no; then
      for lib in dns nsl resolv; do
        if test "$ac_cv_func_res_search" != yes; then
	  LIBS="-l$lib $LIBS"
          AC_FUNC_RES_SEARCH
          LIBS="$openafs_save_libs"
        fi
      done    
      if test "$ac_cv_func_res_search" = yes; then
        LIB_AFSDB="-l$lib"
	AC_DEFINE(HAVE_RES_SEARCH, 1, [])
        AC_MSG_RESULT([yes, in lib$lib])
      else
        AC_MSG_RESULT(no)
      fi
  else
    AC_DEFINE(HAVE_RES_SEARCH, 1, [])
    AC_MSG_RESULT(yes)
  fi
  
fi

AC_CHECK_RESOLV_RETRANS

AC_CACHE_VAL(ac_cv_setsockopt_iprecverr,
[
AC_MSG_CHECKING([for setsockopt(, SOL_IP, IP_RECVERR)])
AC_TRY_COMPILE( [#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>],
[int on=1;
setsockopt(0, SOL_IP, IP_RECVERR, &on, sizeof(on));], ac_cv_setsockopt_iprecverr=yes, ac_cv_setsockopt_iprecverr=no)
AC_MSG_RESULT($ac_cv_setsockopt_iprecverr)])
if test "$ac_cv_setsockopt_iprecverr" = "yes"; then
   AC_DEFINE(ADAPT_PMTU_RECVERR, 1, [define if asynchronous socket errors can be received])
fi

PTHREAD_LIBS=error
if test "x$MKAFS_OSTYPE" = OBSD; then
        PTHREAD_LIBS="-pthread"
fi
if test "x$MKAFS_OSTYPE" = xDFBSD; then
        PTHREAD_LIBS="-pthread"
fi
if test "x$PTHREAD_LIBS" = xerror; then
        AC_CHECK_LIB(pthread, pthread_attr_init,
                PTHREAD_LIBS="-lpthread")
fi
if test "x$PTHREAD_LIBS" = xerror; then
        AC_CHECK_LIB(pthreads, pthread_attr_init,
                PTHREAD_LIBS="-lpthreads")
fi
if test "x$PTHREAD_LIBS" = xerror; then
        AC_CHECK_LIB(c_r, pthread_attr_init,
                PTHREAD_LIBS="-lc_r")
fi
if test "x$PTHREAD_LIBS" = xerror; then
        AC_CHECK_FUNC(pthread_attr_init, PTHREAD_LIBS="")
fi
if test "x$PTHREAD_LIBS" = xerror; then
        # pthread_attr_init is a macro under HPUX 11.0 and 11.11
        AC_CHECK_LIB(pthread, pthread_attr_destroy,
                PTHREAD_LIBS="-lpthread")
fi
if test "x$PTHREAD_LIBS" = xerror; then
        AC_MSG_WARN(*** Unable to locate working posix thread library ***)
fi
AC_SUBST(PTHREAD_LIBS)

HOST_CPU="$host_cpu"

if test "x$with_bsd_kernel_headers" != "x"; then
	BSD_KERNEL_PATH="$with_bsd_kernel_headers"
else
	BSD_KERNEL_PATH="/usr/src/sys"
fi

if test "x$with_bsd_kernel_build" != "x"; then
	BSD_KERNEL_BUILD="$with_bsd_kernel_build"
else
	case $AFS_SYSNAME in
		*_fbsd_4?)
			BSD_KERNEL_BUILD="${BSD_KERNEL_PATH}/compile/GENERIC"
			;;
		*_fbsd_*)
			BSD_KERNEL_BUILD="${BSD_KERNEL_PATH}/${HOST_CPU}/compile/GENERIC"
			;;
	esac
fi

# Fast restart
if test "$enable_supergroups" = "yes"; then
	AC_DEFINE(SUPERGROUPS, 1, [define if you want to have support for nested pts groups])
fi

if test "$enable_fast_restart" = "yes"; then
	AC_DEFINE(FAST_RESTART, 1, [define if you want to have fast restart])
fi

if test "$enable_bitmap_later" = "yes"; then
	AC_DEFINE(BITMAP_LATER, 1, [define if you want to salvager to check bitmasks later])
fi

if test "$enable_demand_attach_fs" = "yes"; then
	AC_DEFINE(DEMAND_ATTACH_ENABLE, 1, [define if you want the demand attach fileserver])
	DEMAND_ATTACH="yes"
else
	DEMAND_ATTACH="no"
fi
AC_SUBST(DEMAND_ATTACH)

if test "$enable_disconnected" = "yes"; then
	AC_DEFINE(AFS_DISCON_ENV, 1, [define if you want support for disconnected operation])
fi

if test "$enable_unix_sockets" = "yes"; then
	AC_DEFINE(USE_UNIX_SOCKETS, 1, [define if you want to use UNIX sockets for fssync.])
	USE_UNIX_SOCKETS="yes"
else
	USE_UNIX_SOCKETS="no"
fi
AC_SUBST(USE_UNIX_SOCKETS)

if test "$enable_fast_restart" = "yes" &&
   test "$enable_demand_attach_fs" = "yes" ; then
	AC_MSG_ERROR([The Demand Attach and Fast Restart extensions are mutually exclusive.  Demand Attach fileservers automatically salvage volumes in the background, thereby making Fast Restart pointless.])
	exit 1
fi

if test "$enable_icmp_pmtu_discovery" = "yes"; then
   if test "$ac_cv_setsockopt_iprecverr" = "yes"; then
	AC_DEFINE(ADAPT_PMTU, 1, [define if you want to decode icmp unreachable packets to discover path mtu])
   fi
fi

if test "$enable_cache_bypass" = "yes"; then
	AC_DEFINE(AFS_CACHE_BYPASS, 1, [define to activate cache bypassing Unix client])
fi

if test "$enable_namei_fileserver" = "yes"; then
	AC_DEFINE(AFS_NAMEI_ENV, 1, [define if you want to want namei fileserver])
	VFSCK=""
else
	if test "$enable_namei_fileserver" = "default"; then
		case $host in
			*-solaris2.10*)
				AC_MSG_WARN(Some Solaris 10 versions are not safe with the inode fileserver. Forcing namei. Override with --disable-namei-fileserver)
				AC_DEFINE(AFS_NAMEI_ENV, 1, [define if you want to want namei fileserver])
				VFSCK=""
				;;
			*-solaris2.11*)
				AC_MSG_WARN(Solaris 11 versions are not safe with the inode fileserver. Forcing namei. Override with --disable-namei-fileserver)
				AC_DEFINE(AFS_NAMEI_ENV, 1, [define if you want to want namei fileserver])
				VFSCK=""
				;;
			*)
				VFSCK="vfsck"
				;;
		esac
        else
		VFSCK="vfsck"
	fi
fi

dnl check for tivoli
AC_MSG_CHECKING(for tivoli tsm butc support)
XBSA_CFLAGS=""
if test "$enable_tivoli_tsm" = "yes"; then
	XBSADIR1=/usr/tivoli/tsm/client/api/bin/xopen
	XBSADIR2=/opt/tivoli/tsm/client/api/bin/xopen
	XBSADIR3=/usr/tivoli/tsm/client/api/bin/sample
	XBSADIR4=/opt/tivoli/tsm/client/api/bin/sample

	if test -r "$XBSADIR3/dsmapifp.h"; then
		XBSA_CFLAGS="-Dxbsa -DNEW_XBSA -I$XBSADIR3"
		XBSA_XLIBS="-ldl"
		AC_MSG_RESULT([yes, $XBSA_CFLAGS])
	elif test -r "$XBSADIR4/dsmapifp.h"; then
		XBSA_CFLAGS="-Dxbsa -DNEW_XBSA -I$XBSADIR4"
		XBSA_XLIBS="-ldl"
		AC_MSG_RESULT([yes, $XBSA_CFLAGS])
	elif test -r "$XBSADIR1/xbsa.h"; then
		XBSA_CFLAGS="-Dxbsa -I$XBSADIR1"
		XBSA_XLIBS=""
		AC_MSG_RESULT([yes, $XBSA_CFLAGS])
	elif test -r "$XBSADIR2/xbsa.h"; then
		XBSA_CFLAGS="-Dxbsa -I$XBSADIR2"
		XBSA_XLIBS=""
		AC_MSG_RESULT([yes, $XBSA_CFLAGS])
	else
		AC_MSG_RESULT([no, missing xbsa.h and dsmapifp.h header files])
	fi
else
	AC_MSG_RESULT([no])
fi
AC_SUBST(XBSA_CFLAGS)
AC_SUBST(XBSA_XLIBS) 

dnl checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_HEADER_DIRENT
AC_CHECK_HEADERS(stdlib.h string.h unistd.h fcntl.h sys/time.h sys/file.h grp.h)
AC_CHECK_HEADERS(netinet/in.h netdb.h sys/fcntl.h sys/mnttab.h sys/mntent.h)
AC_CHECK_HEADERS(mntent.h sys/vfs.h sys/param.h sys/fs_types.h sys/fstyp.h)
AC_CHECK_HEADERS(sys/mount.h strings.h termios.h signal.h sys/pag.h)
AC_CHECK_HEADERS(windows.h direct.h sys/ipc.h)
AC_CHECK_HEADERS(security/pam_modules.h ucontext.h regex.h sys/statvfs.h sys/statfs.h sys/bitypes.h)
AC_CHECK_HEADERS(linux/errqueue.h,,,[#include <linux/types.h>])
AC_CHECK_HEADERS(et/com_err.h)

AC_CHECK_TYPES([fsblkcnt_t],,,[
#include <sys/types.h>
#ifdef HAVE_SYS_BITYPES_H
#include <sys/bitypes.h>
#endif
#ifdef HAVE_SYS_STATFS_H
#include <sys/statfs.h>
#endif
#ifdef HAVE_SYS_STATVFS_H
#include <sys/statvfs.h>
#endif
])

OPENAFS_TEST_PACKAGE(libintl,[#include <libintl.h>],[-lintl],,,INTL)

dnl Don't build PAM on IRIX; the interface doesn't work for us.
if test "$ac_cv_header_security_pam_modules_h" = yes -a "$enable_pam" = yes; then
        case $AFS_SYSNAME in
        sgi_*)
                HAVE_PAM="no"
                ;;
        *)
	        HAVE_PAM="yes"
                ;;
        esac
else
	HAVE_PAM="no"
fi
AC_SUBST(HAVE_PAM)

if test "$enable_login" = yes; then
	BUILD_LOGIN="yes"
else
	BUILD_LOGIN="no"
fi
AC_SUBST(BUILD_LOGIN)

AC_CHECK_FUNCS(snprintf strlcat strlcpy flock)
AC_CHECK_FUNCS(setprogname getprogname sigaction mkstemp vsnprintf strerror strcasestr)
AC_CHECK_FUNCS(setvbuf vsyslog getcwd)
AC_CHECK_FUNCS(regcomp regexec regerror)
AC_MSG_CHECKING([for POSIX regex library])
if test "$ac_cv_header_regex_h" = "yes" && \
	test "$ac_cv_func_regcomp" = "yes" && \
	test "$ac_cv_func_regexec" = "yes" && \
	test "$ac_cv_func_regerror" = "yes"; then
    AC_DEFINE(HAVE_POSIX_REGEX, 1, [define if you have POSIX regex library])
    AC_MSG_RESULT(yes)
else
    AC_MSG_RESULT(no)
fi

AC_TYPE_SOCKLEN_T
AC_TYPE_SIGNAL
AC_CHECK_SIZEOF(void *)
AC_CHECK_SIZEOF(unsigned long long)
AC_CHECK_SIZEOF(unsigned long)
AC_CHECK_SIZEOF(unsigned int)
AC_TYPE_INTPTR_T
AC_TYPE_UINTPTR_T
AC_CHECK_TYPE(ssize_t, int)
AC_CHECK_TYPE([sig_atomic_t], ,
    [AC_DEFINE([sig_atomic_t], [int],
        [Define to int if <signal.h> does not define.])],
[#include <sys/types.h>
#include <signal.h>])
AC_SIZEOF_TYPE(long)

AC_HEADER_PAM_CONST

AC_CHECK_FUNCS(timegm)
AC_CHECK_FUNCS(daemon)

dnl Directory PATH handling
if test "x$enable_transarc_paths" = "xyes"  ; then 
    afsconfdir=${afsconfdir=/usr/afs/etc}
    viceetcdir=${viceetcdir=/usr/vice/etc}
    afskerneldir=${afskerneldir=${viceetcdir}}
    afssrvbindir=${afssrvbindir=/usr/afs/bin}
    afssrvsbindir=${afssrvsbindir=/usr/afs/bin}
    afssrvlibexecdir=${afssrvlibexecdir=/usr/afs/bin}
    afsdbdir=${afsdbdir=/usr/afs/db}
    afslogsdir=${afslogsdir=/usr/afs/logs}
    afslocaldir=${afslocaldir=/usr/afs/local}
    afsbackupdir=${afsbackupdir=/usr/afs/backup}
    afsbosconfigdir=${afsbosconfigdir=/usr/afs/local}
    afsdatadir=${afsdatadir=/usr/vice/etc}
else 
    afsconfdir=${afsconfdir='${sysconfdir}/openafs/server'}
    viceetcdir=${viceetcdir='${sysconfdir}/openafs'}
    afskerneldir=${afskerneldir='${libdir}/openafs'}
    afssrvbindir=${afssrvbindir='${bindir}'}
    afssrvsbindir=${afssrvsbindir='${sbindir}'}
    afssrvlibexecdir=${afssrvlibexecdir='${libexecdir}/openafs'}
    afsdbdir=${afsdbdir='${localstatedir}/openafs/db'}
    afslogsdir=${afslogsdir='${localstatedir}/openafs/logs'}
    afslocaldir=${afslocaldir='${localstatedir}/openafs'}
    afsbackupdir=${afsbackupdir='${localstatedir}/openafs/backup'}
    afsbosconfigdir=${afsbosconfigdir='${sysconfdir}/openafs'}
    afsdatadir=${afsdatadir='${datadir}/openafs'}
fi
AC_SUBST(afsconfdir)
AC_SUBST(viceetcdir)
AC_SUBST(afskerneldir)
AC_SUBST(afssrvbindir)
AC_SUBST(afssrvsbindir)
AC_SUBST(afssrvlibexecdir)
AC_SUBST(afsdbdir)
AC_SUBST(afslogsdir)
AC_SUBST(afslocaldir)
AC_SUBST(afsbackupdir)
AC_SUBST(afsbosconfigdir)
AC_SUBST(afsdatadir)

if test "x$enable_kernel_module" = "xyes"; then
ENABLE_KERNEL_MODULE=libafs
fi

if test "x$enable_pthreaded_ubik" = "xyes"; then
ENABLE_PTHREADED_UBIK=yes
fi

AC_SUBST(VFSCK)
AC_SUBST(AFS_SYSNAME)
AC_SUBST(AFS_PARAM_COMMON)
AC_SUBST(ENABLE_KERNEL_MODULE)
AC_SUBST(ENABLE_PTHREADED_UBIK)
AC_SUBST(LIB_AFSDB)
AC_SUBST(LINUX_KERNEL_PATH)
AC_SUBST(LINUX_KERNEL_BUILD)
AC_SUBST(HOST_CPU)
AC_SUBST(BSD_KERNEL_PATH)
AC_SUBST(BSD_KERNEL_BUILD)
AC_SUBST(LINUX_VERSION)
AC_SUBST(MKAFS_OSTYPE)
AC_SUBST(TOP_OBJDIR)
AC_SUBST(TOP_SRCDIR)
AC_SUBST(TOP_INCDIR)
AC_SUBST(TOP_LIBDIR)
AC_SUBST(DEST)
AC_SUBST(DARWIN_INFOFILE)
AC_SUBST(IRIX_BUILD_IP35)
AC_SUBST(HTML_XSL)
AC_SUBST(XSLTPROC)

OPENAFS_OSCONF
OPENAFS_KRB5CONF

TOP_SRCDIR="${srcdir}/src"
dnl
dnl If we're using ./configure, need a more reasonable TOP_SRCDIR, since relative links don't work everywhere
dnl
case $TOP_SRCDIR in
        /*)
                ;;
        *)
		TOP_SRCDIR=`cd $TOP_SRCDIR; pwd`
		;;
esac

TOP_OBJDIR="${SRCDIR_PARENT}"
TOP_INCDIR="${SRCDIR_PARENT}/include"
TOP_LIBDIR="${SRCDIR_PARENT}/lib"
if test "${DEST}x" = "x"; then
        DEST="${SRCDIR_PARENT}/${AFS_SYSNAME}/dest"
fi

HELPER_SPLINT="${TOP_SRCDIR}/helper-splint.sh"
HELPER_SPLINTCFG="${TOP_SRCDIR}/splint.cfg"
AC_SUBST(HELPER_SPLINT)
AC_SUBST(HELPER_SPLINTCFG)

mkdir -p ${TOP_OBJDIR}/src/JAVA/libjafs

])
