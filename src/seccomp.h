/*
 * seccomp.h
 * Ansilove 4.2.0
 * https://www.ansilove.org
 *
 * Copyright (c) 2019-2024, Frederic Cambus
 * All rights reserved.
 *
 * Ansilove is licensed under the BSD 2-Clause license.
 * See LICENSE file for details.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef SECCOMP_H
#define SECCOMP_H

#include <stddef.h>
#include <sys/prctl.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <linux/audit.h>
#include <linux/filter.h>
#include <linux/seccomp.h>

#if defined(__i386__)
#define SECCOMP_AUDIT_ARCH AUDIT_ARCH_I386
#elif defined(__x86_64__)
#define SECCOMP_AUDIT_ARCH AUDIT_ARCH_X86_64
#elif defined(__arm__)
#define SECCOMP_AUDIT_ARCH AUDIT_ARCH_ARM
#elif defined(__aarch64__)
#define SECCOMP_AUDIT_ARCH AUDIT_ARCH_AARCH64
#else
#error "Seccomp is only supported on i386, x86_64, arm, and aarch64 architectures."
#endif

#define ANSILOVE_SYSCALL_ALLOW(syscall) \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_##syscall, 0, 1), \
	BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW)

static struct sock_filter filter[] = {
	/* Validate architecture */
	BPF_STMT(BPF_LD+BPF_W+BPF_ABS, offsetof(struct seccomp_data, arch)),
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, SECCOMP_AUDIT_ARCH, 1, 0),
	BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_KILL),

	/* Load syscall */
	BPF_STMT(BPF_LD+BPF_W+BPF_ABS, offsetof(struct seccomp_data, nr)),

	ANSILOVE_SYSCALL_ALLOW(brk),
	ANSILOVE_SYSCALL_ALLOW(clock_gettime),	/* i386 glibc */
	ANSILOVE_SYSCALL_ALLOW(close),
	ANSILOVE_SYSCALL_ALLOW(exit_group),
	ANSILOVE_SYSCALL_ALLOW(fstat),
#if defined(__NR_fstat64)
	ANSILOVE_SYSCALL_ALLOW(fstat64),	/* i386 glibc */
#endif
	ANSILOVE_SYSCALL_ALLOW(ioctl),
	ANSILOVE_SYSCALL_ALLOW(lseek),
#if defined(__NR__llseek)
	ANSILOVE_SYSCALL_ALLOW(_llseek),	/* i386 glibc */
#endif
#if defined(__NR_open)
	ANSILOVE_SYSCALL_ALLOW(open),
#endif
	ANSILOVE_SYSCALL_ALLOW(openat),
	ANSILOVE_SYSCALL_ALLOW(madvise),
#if defined(__NR_mmap)
	ANSILOVE_SYSCALL_ALLOW(mmap),
#endif
#if defined(__NR_mmap2)
	ANSILOVE_SYSCALL_ALLOW(mmap2),		/* i386 glibc */
#endif
	ANSILOVE_SYSCALL_ALLOW(mremap),
	ANSILOVE_SYSCALL_ALLOW(munmap),
	ANSILOVE_SYSCALL_ALLOW(read),
	ANSILOVE_SYSCALL_ALLOW(readv),
	ANSILOVE_SYSCALL_ALLOW(write),
	ANSILOVE_SYSCALL_ALLOW(writev),

	BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_KILL)
};

struct sock_fprog ansilove = {
	.len = sizeof(filter)/sizeof(filter[0]),
	.filter = filter
};

#endif /* SECCOMP_H */
