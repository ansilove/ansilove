/*
 * seccomp.h
 * Ansilove 4.0.3
 * https://www.ansilove.org
 *
 * Copyright (c) 2019, Frederic Cambus
 * All rights reserved.
 *
 * Ansilove is licensed under the BSD 2-Clause License.
 * See LICENSE file for details.
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

#define ANSILOVE_SYSCALL_ALLOW(syscall) \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_##syscall, 0, 1), \
	BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW)

static struct sock_filter filter[] = {
	BPF_STMT(BPF_LD+BPF_W+BPF_ABS, offsetof(struct seccomp_data, nr)),

	ANSILOVE_SYSCALL_ALLOW(brk),
	ANSILOVE_SYSCALL_ALLOW(close),
	ANSILOVE_SYSCALL_ALLOW(exit_group),
	ANSILOVE_SYSCALL_ALLOW(fstat),
	ANSILOVE_SYSCALL_ALLOW(ioctl),
	ANSILOVE_SYSCALL_ALLOW(lseek),
#if defined(SYS_open)
	ANSILOVE_SYSCALL_ALLOW(open),
#endif
	ANSILOVE_SYSCALL_ALLOW(openat),
	ANSILOVE_SYSCALL_ALLOW(madvise),
	ANSILOVE_SYSCALL_ALLOW(mmap),
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
