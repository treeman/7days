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

    What name shall we have?
        Namespace shouldn't start with a number so 7days won't work
        Is Tree okay? Or maybe Seven? or something?

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

    Share resources between examples!

    Go through whole codebase and find stuff to refactor/change
        Incorporate more lua perhaps?

        Stuff to check:
            Console is huge and not commented enough

            Uncommented debug code there, should use a switch or remove it

            Comment Dator a bit?

            Make a macro for creating exceptions?

            Graphics isVisible not working
                Changed it, test if it's working

            Is PixFont used inside Pix graphics style?
                Maybe make a subfolder for Pix graphics style?
                Comment a bit more?
                What does PixMap do? Why do we need it?
                Might want to find a faster way of drawing pixmap

            How does Settings work? Why do we need it? Comment a bit better

            We don't have any animation sprite?
                We only use sf::Sprite? Check how it works, and can we do something better?

            What does Tweak do? Why?
                Change name? T.T

            Does VisualDebug work?
                Make examples of all functionality!

