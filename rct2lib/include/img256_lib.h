#ifndef IMG256_LIB__H
#define IMG256_LIB__H
#include <stdtypes.h>

#ifndef NULL
#define NULL 0
#endif

enum
{
    FROM = 0,
    TO   = 1,
};

enum
{
    _IN  = 0,
    _OUT = 1
};

enum
{
    BEFORE = 0,
    AFTER  = 1
};

typedef struct VECT_2D
{
    union {
        long x, i, a;
    };
    union {
        long y, j, b;
    };
    int Set(long x, long y);
    bool operator==(VECT_2D & v2);
} VECT_2D;

typedef struct BOX_2D
{
    union {
        long left, l, x1;
    };
    union {
        long top, t, y1;
    };
    union {
        long right, r, x2;
    };
    union {
        long bottom, bot, b, y2;
    };
    int Set(long l, long t, long r, long b);
    bool IsInBox(BOX_2D & b2);
    bool operator&&(BOX_2D & b2);
    bool PtInBox(int x, int y);
} BOX_2D;

typedef struct IMG_256
{
    union {
        WORD width, w;
    };
    union {
        WORD height, h;
    };
    union {
        BYTE *imgData, *id;
    };
    int operator~();
    int Set(WORD w, WORD h, BYTE * imgData);
    bool ImgMalloc(WORD iw, WORD ih);
    bool ImgMalloc();
    int ImgFree();
    // Paste() -- paste this image into another
    int IMG_256::Paste(long x, long y, IMG_256 & p, bool transparent, WORD bg);
    // Copy() -- copy from this image to another
    int Copy(long x, long y, IMG_256 & p, bool transparent, WORD bg);
    int MoveLine(int length, int x, int y, int i, int j, IMG_256 & p, WORD direction, bool transparent, WORD bg);
    int MovePixel(int x, int y, int i, int j, IMG_256 & p, WORD direction, bool transparent, WORD bg);
    int Clear(WORD bg);
    int Flip();
    int PixOfs(int x, int y);
    bool InImgRange(int x, int y);
    BOX_2D MakeImgBox();
    BYTE & pix(int x, int y);
} IMG_256;

typedef struct IMG_256__CHAIN_LINK
{
    union {
        IMG_256__CHAIN_LINK *l, *yester, *last, *prev;
    };
    union {
        short x, i;
    };
    union {
        short y, j;
    };
    union {
        short z, zOrder;
    };
    union {
        IMG_256 id, imageData;
    };
    union {
        IMG_256__CHAIN_LINK *n, *next;
    };
    int Set(IMG_256__CHAIN_LINK * last, WORD x, WORD y, WORD z, IMG_256 & id, IMG_256__CHAIN_LINK * n);
    bool operator<(IMG_256__CHAIN_LINK & l2) // z order less
        ;
    bool operator>(IMG_256__CHAIN_LINK & l2) // z order greater
        ;
    bool operator>=(IMG_256__CHAIN_LINK & l2) // z order >=
        ;
    bool operator<=(IMG_256__CHAIN_LINK & l2) // z order <=
        ;
    WORD operator=(WORD newZ) // z order =
        ;
    IMG_256__CHAIN_LINK * MallocLink();

} IMG_256__CHAIN_LINK, *IMG_256__CHAIN_LINK__PTR;

typedef struct IMG_256__CHAIN
{
    union {
        IMG_256__CHAIN_LINK *rootLink, *rl
            /*,&root*/
            ;
    };
    union {
        IMG_256__CHAIN_LINK *curLink, *cl
            /*,&cur*/
            ;
    };
    int Set(IMG_256__CHAIN_LINK * rootLink, IMG_256__CHAIN_LINK * curLink);
    int Init();
    int Init(IMG_256__CHAIN_LINK & startLink);

    int Clear();
    IMG_256__CHAIN_LINK * operator+=(IMG_256__CHAIN_LINK & newLink)
        // insert new image into proper z-order
        ;
    bool operator++() // go forward in chain
        ;
    bool operator--() // go back in chain
        ;
    IMG_256__CHAIN_LINK * operator~() // get current link
        ;
} IMG_256__CHAIN;

#endif