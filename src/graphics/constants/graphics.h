#ifndef GRAPHICS_H
#define GRAPHICS_H

enum OBJECTS {
    POINTER, /* Item Selection */
    RECTANGLE,
    CIRCLE,
    ARROW,
    TEXT,
    CROP,
    HIGHLIGHT /* Highlighter */
};

enum action {
    CREATE,
    MOVE,
    DELETE,
    DELETE_ALL,
    IMG_CROP
};
#endif // GRAPHICS_H
