# set project's name
  PROJECT( kaudio )
  
  cmake_minimum_required(VERSION 2.8)
  
  # with SET() command you can change variables or define new ones
  # here we define KAUDIO_SRCS variable that contains a list of all .cpp files
  # note that we don't need \ at the end of line
  SET( KAUDIO_SRCS
    main.cpp
    mainWindow.cpp
    openRadioWindow.cpp
    playsListView.cpp
    playPauseButton.cpp
    removeFromPlayListWindow.cpp
    exportplaylistwindow.cpp
    lyricswindow.cpp
    addlyricswindow.cpp
    bookmarkwindow.cpp
  )
  
  # another list, this time it includes all header files that should be treated with moc
  SET( KAUDIO_MOC_HDRS
    mainWindow.h
    openRadioWindow.h
    playListView.h
    playPauseButton.h
    removeFromPlayListWindow.h
    exportplaylistwindow.h
    lyricswindow.h
    addlyricswindow.h  
    bookmarkwindow.h
  )
  
  SET( KAUDIO_UIS
    lyricswindow.ui
    exportplaylistwindow.ui
    addlyricswindow.ui
    bookmarkwindow.ui
    )
    
  
    SET( KAUDIO_RCS
        rc.qrc
  )
  
  set(EXECUTABLE_OUTPUT_PATH ${kaudio_SOURCE_DIR})
  
  set ( QT_PHONON_LIBRARY_RELEASE /usr/lib/libphonon.so )
  
  # and finally an resource file
  
  # enable warnings
  ADD_DEFINITIONS( -Wall )
  
  # by default only QtCore and QtGui modules are enabled
  # other modules must be enabled like this:
  SET( QT_USE_DBUS TRUE )   
  SET( QT_USE_PHONON TRUE )
  
  # this command finds Qt4 libraries and sets all required variables
  # note that it's Qt4, not QT4 or qt4
  FIND_PACKAGE( Qt4 REQUIRED )
  
  # add some useful macros and variables
  # (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
  INCLUDE( ${QT_USE_FILE} )
  
  # this command will generate rules that will run rcc on all files from KAUDIO_RCS
  # in result KAUDIO_RC_SRCS variable will contain paths to files produced by rcc
  QT4_ADD_RESOURCES( KAUDIO_RC_SRCS ${KAUDIO_RCS} )
  
  # this will run uic on .ui files:
  QT4_WRAP_UI( KAUDIO_UI_HDRS ${KAUDIO_UIS} )
  
  # and finally this will run moc:
  QT4_WRAP_CPP( KAUDIO_MOC_SRCS ${KAUDIO_MOC_HDRS} )
  
  # we need this to be able to include headers produced by uic in our code
  # (CMAKE_BINARY_DIR holds a path to the build directory, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
  INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} )
  
  # here we instruct CMake to build "kaudio" executable from all of the source files
  ADD_EXECUTABLE( kaudio ${KAUDIO_SRCS} ${KAUDIO_MOC_SRCS} ${KAUDIO_RC_SRCS} ${KAUDIO_UI_HDRS} )
  
  # last thing we have to do is to tell CMake what libraries our executable needs,
  # luckily FIND_PACKAGE prepared QT_LIBRARIES variable for us:
  TARGET_LINK_LIBRARIES( kaudio ${QT_LIBRARIES} )
  
  install(
    TARGETS
        kaudio
    RUNTIME DESTINATION
        ${CMAKE_INSTALL_PREFIX}/bin
)

