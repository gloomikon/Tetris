QT += widgets

HEADERS       = board.h \
                piece.h \
                window.h \
    superpiece.h \
    linebombpiece.h \
    drawable.h
SOURCES       = main.cpp \
                board.cpp \
                piece.cpp \
                window.cpp \
    superpiece.cpp \
    linebombpiece.cpp \
    drawable.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/tetrix
INSTALLS += target
