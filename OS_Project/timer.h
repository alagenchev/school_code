//here we'll put all timer headersi
#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
	inline extern unsigned long long start_timer();
	inline extern unsigned long long stop_timer(unsigned long long start_time, char *name);
	inline extern unsigned long long start_rdtsc_timer();
	inline extern unsigned long long stop_rdtsc_timer(unsigned long long start_time, char *label);
#endif
