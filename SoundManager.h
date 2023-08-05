#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QSoundEffect>

class SoundManager
{
private:
    QSoundEffect* player; // Puntero a un objeto QSoundEffect para reproducir efectos de sonido
    QSoundEffect* backgroundMusicPlayer; // Puntero a un objeto QSoundEffect para reproducir música de fondo

    // Constructor privado para evitar la creación de instancias adicionales.
    // Se inicializan los punteros de QSoundEffect en el constructor.
    SoundManager() { player = new QSoundEffect; backgroundMusicPlayer = new QSoundEffect; }

    // Evitar la duplicación y la copia
    SoundManager(const SoundManager&) = delete;
    void operator=(const SoundManager&) = delete;

public:
    // Acceso a la instancia unica a traves de este metodo estatico.
    static SoundManager& instance()
    {
        static SoundManager instance;
        return instance;
    }

    // metodo para reproducir un efecto de sonido especificado por la ruta de archivo en los recursos.
    // Configura el volumen del sonido y lo reproduce.
    void playSound(const QString& sound)
    {
        player->setSource(QUrl(sound));
        player->setVolume(0.10f); // Establece el volumen al 10% del máximo.
        player->play();
    }

    // metodo para reproducir música de fondo especificada por la ruta de archivo en los recursos.
    // Configura el volumen de la música de fondo y la reproduce.
    void playBackgroundMusic(const QString& musicResourcePath)
    {
        backgroundMusicPlayer->setSource(QUrl(musicResourcePath));
        backgroundMusicPlayer->setVolume(0.10f); // Establece el volumen al 10% del máximo.
        backgroundMusicPlayer->play();
    }
};

#endif // SOUNDMANAGER_H
