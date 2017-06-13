# STMSampler

## Overview
The project of .wav samples player based on STM32F4 Discovery board.
Built with 8-buttons or laser rays with photodiodes.
Sources of the sound found on SD Card.

## Description
The idea to play short .wav samples loaded from SD Card. 
Sound files on SD Card must have a name like 1.wav-8.wav (binded to buttons).
You can run specify sound by intersect a laser ray by your finger or (in casual way) by push button.
We use SPI for sending data from SD card to STM32F4 because SD card module doesn't support SDIO communication. 
It uses DMA module for smoother playback of music. 
Mixer is not implemented at all because is not possible to do it correctly on board with small amount of RAM.


## How to run
- Clone, compile project and flash to STM32F4 Discovery.
- Connect all pins with this schema

SD Card
GND <---> GND
3V <---> 3V3
PB11 <---> CS
PB15 <---> MOSI
PB13 <---> SCK
PB14 <---> MISO
GND <---> GND

Sound triggers
PA1
PA2
PA3
PA4

* Connect headphones or speakers to audio jack

- Format SD Card to FAT32
- Put audio files (1.wav - 8.wav) to SD Card

## Future improvements
Waveform could be displayed on the LCD screen in the future.

# Attributions
- http://www.mind-dump.net/configuring-the-stm32f4-discovery-for-audio
- http://www1.coocox.org/repo/a8bde334-159f-4dae-bc65-686695a3e545/src/STM3240_41_G_EVAL/stm324xg_audio_codec.h.htm
- http://www1.coocox.org/repo/a8bde334-159f-4dae-bc65-686695a3e545/src/STM3240_41_G_EVAL/stm324xg_audio_codec.c.htm

## License
MIT

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.

Supervisor: Marek Kraft/Michał Fularz/Tomasz Mańkowski/Adam Bondyra
