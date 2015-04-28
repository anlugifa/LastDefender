#include <SFML/Audio.hpp>

#include <Windows.h>
#include "SoundPlayer.h"


SoundPlayer::SoundPlayer()
{	
	if (_soundMusic.openFromFile("../sounds/music.wav"))
	{
		_soundMusic.setVolume(75);
		_soundMusic.setLoop(true);
	}

	if (_bufferPM.loadFromFile("../sounds/protector_shot.wav"))
	{		
		_soundPM.setBuffer(_bufferPM);
		_soundMusic.setVolume(50);
	}
	if (_bufferAM.loadFromFile("../sounds/alien_shot_short.wav"))
	{		
		_soundAM.setBuffer(_bufferAM);
		_soundMusic.setVolume(50);
	}
	if (_bufferEx.loadFromFile("../sounds/explosion_high.wav"))
	{
		_soundEx.setBuffer(_bufferEx);
		_soundEx.setVolume(100);
	}
	
}

void SoundPlayer::playMusic()
{
	_soundMusic.play();	
}

void SoundPlayer::playSoundMissile()
{	
	mutex.lock();

	if (getSource() == PROTECTOR_MISSILE)
		_soundPM.play();
	else
	{
		/*while (_soundAM.getStatus() == sf::Sound::Status::Playing)
			Sleep(50);*/

		/*_soundAM.play();*/

		sf::Sound sound;
		sound.setBuffer(_bufferAM);
		sound.play();

		sf::sleep(sf::milliseconds(100));
	}
		
	mutex.unlock();
}

void SoundPlayer::playProtectorMissile()
{		
	setSource(PROTECTOR_MISSILE);
	_soundPM.play();
	/*sf::Thread thread(&SoundPlayer::playSoundMissile, this);
	thread.launch();		*/
}

void SoundPlayer::playAlienMissile()
{
	setSource(ALIEN_MISSILE);
	_soundAM.play();
	
	/*sf::Thread thread(&SoundPlayer::playSoundMissile, this);
	thread.launch();*/
}


void SoundPlayer::playExplosion()
{	
	_soundEx.play();
	/*sf::Thread thread(&SoundPlayer::playSoundMissile, this);
	thread.launch();*/
}


int SoundPlayer::getSource()
{	
	return _source;
}

void SoundPlayer::setSource(int value)
{	
	_source = value;	
}


