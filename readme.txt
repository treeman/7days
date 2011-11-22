## Fast prototyping framework.

This is my collection of stuff I've needed when making my 2D game prototypes.

Dependencies:
    SFML    (openal, sndfile, freetype maybe something else?)
    boost   (linking to boost_iostreams)
    lua

License:
    None, do what you want with it.

Todo/Ideas:
    Versioning and numbering inside
    Use include-all file instead of listing (All.hpp, rename to reflect)

    What name shall we have?
        Tree?
        7days?
        Either way maybe a little bit more consistency (it's named 7days but we use Tree/<file> hmm...)

    Developer build
        Either don't build static library but link to source directly or update library automatically?

    Makefiles should check for changes in header files too...
        How should we do it for other files that uses that header? That's a good Q.

    Makefile
        Install/Remove

    More examples to showcase:
        Pixelated style
        Isometric tiles and stuff with that
        Square tiled with objects moving around there
        Lazy drawing
        Blank, very basic

    Go through whole codebase and find stuff to refactor/change
        Take lessons from Java project there
            immutable Vec2D (dunno if it is now)
        Incorporate more lua perhaps?

