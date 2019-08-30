void seek_forward()
{
	pthread_cancel(playback_tid);
	pthread_cancel(timer_tid);
	snd_pcm_drop(pcm_handle);
	snd_pcm_prepare(pcm_handle);
	seconds += 10;
	lseek64(sfiledesc.ifiledesc, swavheaderinfo.ibyterate*(seconds) , SEEK_SET);
	pthread_create(&playback_tid, NULL, playback_thread, NULL);
	pthread_create(&timer_tid, NULL, timer_display, NULL);
}

void seek_backward()
{
	pthread_cancel(playback_tid);
	pthread_cancel(timer_tid);
	snd_pcm_drop(pcm_handle);
	snd_pcm_prepare(pcm_handle);
	seconds -= 10;
	lseek64(sfiledesc.ifiledesc, swavheaderinfo.ibyterate*(seconds) , SEEK_SET);
	pthread_create(&playback_tid, NULL, playback_thread, NULL);
	pthread_create(&timer_tid, NULL, timer_display, NULL);
}

void seek_to(int s)
{
	pthread_cancel(playback_tid);
	pthread_cancel(timer_tid);
	snd_pcm_drop(pcm_handle);
	snd_pcm_prepare(pcm_handle);
	seconds = s;
	lseek64(sfiledesc.ifiledesc, swavheaderinfo.ibyterate*(seconds) , SEEK_SET);
	pthread_create(&playback_tid, NULL, playback_thread, NULL);
	pthread_create(&timer_tid, NULL, timer_display, NULL);
}