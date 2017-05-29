#include "musicplayer.h"

MusicPlayer::MusicPlayer()
{

}

void MusicPlayer::setSong(QString value)
{
    playlist.addMedia(QUrl(value));
    mediaPlayer.setPlaylist(&playlist);
}

void MusicPlayer::play(QMediaPlaylist::PlaybackMode mode)
{
    playlist.setPlaybackMode(mode);
    mediaPlayer.play();
}

void MusicPlayer::play()
{
    mediaPlayer.play();
}

void MusicPlayer::stop()
{
    mediaPlayer.stop();
}
