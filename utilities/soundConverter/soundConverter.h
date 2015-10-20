#ifndef SOUNDCONVERTER_H
#define SOUNDCONVERTER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <sys/stat.h>

#define OUTPUT_FILE     "sounds.c"

// Chunk IDs to identify sections of the WAVE file
#define RIFF_CHUNKID    0x46464952 // "RIFF" backwards
#define RIFF_FORMAT     0x45564157 // "WAVE" backwards

#define FMT_SUBCHUNKID  0x20746D66 // "fmt " backwards

#define DATA_SUBCHUNKID 0x61746164 // "data" backwards

#endif /* SOUNDCONVERTER_H */