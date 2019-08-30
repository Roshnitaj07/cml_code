


struct volconfig
 {
     CML_INT64 min, max;
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;
    snd_mixer_elem_t* elem;
    const  CML_CHAR *card = "default";
    const CML_CHAR *selem_name = "Master";

 }svconfig;


void SetAlsaMasterVolume(CML_INT64 volume)
{
    snd_mixer_open(&svconfig.handle, 0);
    snd_mixer_attach(svconfig.handle, card);
    snd_mixer_selem_register(svconfig.handle, NULL, NULL);
    snd_mixer_load(svconfig.handle);

    snd_mixer_selem_id_alloca(&svconfig.sid);
    snd_mixer_selem_id_set_index(svconfig.sid, 0);
    snd_mixer_selem_id_set_name(svconfig.sid, selem_name);
    snd_mixer_find_selem(svconfig.handle, svconfig.sid);

    snd_mixer_selem_get_playback_volume_range(svconfig.elem, &svconfig.min, &svconfig.max);
    snd_mixer_selem_set_playback_volume_all(svconfig.elem, volume * svconfig.max / 100);

    snd_mixer_close(svconfig.handle);
}
 static setvol=50;
 case 'i':setvol=setvol+10;
			SetAlsaMasterVolume(setvol);
                        break;
               case 'd':setvol=setvol-10;
			SetAlsaMasterVolume(setvol);
                        break;