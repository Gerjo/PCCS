#ifndef SOLIDSTATEBITS_H
#define	SOLIDSTATEBITS_H

enum SolidStateBitsddd {
    NOT_SOLID     = 0,
    PLAYER        = 1,
    ALT_A         = 2, // TODO: rename these to something sensible.
    ALT_B         = 4,
    ALT_C         = 8,
    ALT_D         = 16,
    ALT_E         = 32,
    SOLID_FOR_ALL = 0xffffff
};


#endif	/* SOLIDSTATEBITS_H */

