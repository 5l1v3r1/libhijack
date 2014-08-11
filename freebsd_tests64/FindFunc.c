/*
 * Copyright (c) 2011-2014, Shawn Webb
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *    1) Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *    2) Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <hijack.h>
#include <hijack_func.h>

void usage(const char *name)
{
	fprintf(stderr, "USAGE: %s <pid> <libname> <funcname>\n", name);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	HIJACK *hijack;
	FUNC *funcs, *func;
	unsigned long addr;
	
	if (argc != 4)
		usage(argv[0]);
	
	hijack = InitHijack();
    ToggleFlag(hijack, F_DEBUG);
    ToggleFlag(hijack, F_DEBUG_VERBOSE);
	AssignPid(hijack, atoi(argv[1]));
	
	if (Attach(hijack) != ERROR_NONE)
	{
		fprintf(stderr, "[-] Couldn't attach!\n");
		exit(EXIT_FAILURE);
	}

    funcs = FindFunctionInLibraryByName(hijack, argv[2], argv[3]);
    for (func = funcs; func != NULL; func = func->next) {
        printf("[*] %s\t0x%016lx\n", func->name, func->vaddr);
    }

	Detach(hijack);
	
	return 0;
}
