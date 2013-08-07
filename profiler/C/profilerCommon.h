/*
 * (C) Copyright 2013 - Thales SA (author: Simon DENEL - Thales Research & Technology)
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser General Public License
 * (LGPL) version 2.1 which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/lgpl-2.1.html
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
*/
#ifndef PROFILER_COMMON_H
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <sys/time.h>
	#include <time.h>

	#define PROFILER_COMMON_H
	
	#define ON  1
	#define OFF 0
	
	#define PROFILING ON // <-- THE SWITCH IS HERE!
	#define PROFILER_VERBOSE 1
	
	struct profiler_t_taskInstance {
		int  idTask;
		char name[500];
		char* details;
		long queued;
		long submitted;
		long start;
		long end;
		long size;/* must contain the data size transferred during the task, otherwise 0 */
		long bandwidth;/* bytes/s */
		profiler_t_taskInstance *next;
	};
	typedef struct profiler_t_taskInstance profiler_t_taskInstance;

	struct profiler_t_task {
		int id;
		char name[500];
		profiler_t_task *next;
	};
	typedef struct profiler_t_task profiler_t_task;

	struct profiler_t_stream {
		int id;
		char name[500];
		profiler_t_taskInstance *firstTaskInstance;
		profiler_t_stream *next;
	};
	typedef struct profiler_t_stream profiler_t_stream;

	struct profiler_t_device {
		int id;
		char name[500];
		char *details;
		long timeOffset;
		profiler_t_stream *firstStream;
		profiler_t_device *next;
	};
	typedef struct profiler_t_device profiler_t_device;

	struct profiler_t_end_functions {
		void (*function)();
		profiler_t_end_functions *next;
	};
	typedef struct profiler_t_end_functions profiler_t_end_functions;

	void profiler_start();

	void profiler_addDevice(
		int idDevice,
		const void *nameDevice,
		void *detailsDevice=NULL,
		long timeOffset=0
	);

	void profiler_addStream(
		int idStream,
		int idDevice,
		const void *name
	);

	void profiler_addTask(
		int idTask,
		const void *nameTask
	);

	void profiler_addTaskInstance(
		int idTask,
		const char* name,
		char* details,
		int idStream,
		long queued,
		long submitted,
		long start,
		long end,
		long size = 0,
		long bandwidth = 0
	);

	void profiler_stopAndRecord(
		const void *filename
	);

#endif
