#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class MusicPlayer
{
private:
    QMediaPlayer mediaPlayer;
    QMediaPlaylist playlist;

public:
    MusicPlayer();

public slots:
    void addSong(QString value);
    void play(QMediaPlaylist::PlaybackMode mode);
    void play();
    void stop();

};

#endif // MUSICPLAYER_H
