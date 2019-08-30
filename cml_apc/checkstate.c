void (*setstate)(CML_playerstate)
void setstate(CML_playerstate curstate)
{	switch(curstate)
	{
	 STOP_STATE:ssetcurstate.icurstate=101;break;
	 PLAY_STATE:ssetcurstate.icurstate=102;break;
	 PAUSE_STATE:ssetcurstate.icurstate=103;break;
	}
}
