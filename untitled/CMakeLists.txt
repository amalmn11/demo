cmake_minimum_required(VERSION  3.20)
project(untitled C)

set(CMAKE_C_STANDARD 99)

# On utilise le module PkgConfig pour détecter la librairie GTK+ sur le système
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# On dit à CMake d'utiliser GTK+, on indique au compilateur où trouver les fichiers headers
# Et au linker où trouver les librairies
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Instructions pour le compilateur
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

#find_package(LibXml2 REQUIRED)
#add_compile_definitions(test PUBLIC ${LIBXML2_DEFINITIONS})
#include_directories(PUBLIC ${LIBXML2_INCLUDE_DIRS})
#link_libraries(${LIBXML2_LIBRARIES})


##Pour linux, va servir à correctement liers les signaux de notre application au code
#if (UNIX)
#    set(CMAKE_EXE_LINKER_FLAGS "-Wl,-export-dynamic")
#endif (UNIX)

# Ajoute un éxecutable à partir du main.c
add_executable(untitled main.c
        colors.h
        dimension.h
        coordonnees.h
        Style.h
        Image.h
        ComboBox.h
        window.h
        Global.h
        Icon.h
        Entry.h
        GtkBox.h
        BoiteDialog.h
        FixedContainer.h
        Label.h
        Grid.h
        RadioButton.h
        Menue.h
        checkBoxButton.h
        StyleButton.h
        calendrier.h
        menueButton.h
        FileChooser.h
)

# Lie à l'éxecutable la librairie GTK+
TARGET_LINK_LIBRARIES(untitled ${GTK3_LIBRARIES})
