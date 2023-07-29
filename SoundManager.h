#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QSoundEffect>

class SoundManager
{
private:
    QSoundEffect* player;
    QSoundEffect* backgroundMusicPlayer;

    // Constructor privado
    SoundManager() { player = new QSoundEffect; backgroundMusicPlayer=new QSoundEffect;}

    // Evitar la duplicación y la copia
    SoundManager(const SoundManager&) = delete;
    void operator=(const SoundManager&) = delete;

public:
    // Acceso a la instancia única
    static SoundManager& instance()
    {
        static SoundManager instance;
        return instance;
    }

    // Método para reproducir un sonido
    void playSound(const QString& sound)
    {
        player->setSource(QUrl(sound));
        player->setVolume(0.25f);
        player->play();
    }

    void playBackgroundMusic(const QString& musicResourcePath) {
        backgroundMusicPlayer->setSource(QUrl(musicResourcePath));
         player->setVolume(0.25f);
        backgroundMusicPlayer->play();
    }
};

#endif // SOUNDMANAGER_H
