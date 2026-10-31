/*
 * Copyright © 2019 Collabora, Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "config.h"

#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "weston.h"

int
main(int argc, char *argv[])
{
	char *end;
	long pid;

	if (argc > 1 && strcmp(argv[1], "--input-toggle") == 0) {
		if (argc != 3) {
			fprintf(stderr, "Usage: weston --input-toggle PID\n");
			return 2;
		}

		errno = 0;
		pid = strtol(argv[2], &end, 10);
		if (errno != 0 || end == argv[2] || *end != '\0' ||
		    pid <= 0 || pid > INT_MAX) {
			fprintf(stderr, "Invalid PID: %s\n", argv[2]);
			return 2;
		}

		if (kill((pid_t)pid, SIGRTMIN + 6) < 0) {
			perror("weston --input-toggle");
			return 1;
		}

		return 0;
	}

	return wet_main(argc, argv, NULL);
}
