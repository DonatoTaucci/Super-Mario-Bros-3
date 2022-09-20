#Ricorda che il supporto a versioni precedenti sarà presto deprecato
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

#Diamo un nome Test al nostro progetto QT
project(supermario3)

#Se vogliamo fissare c++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB my_sources *.h *.cpp *.qrc)

#Questo per generare il codice qt in automatico è necessario
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#Controllo che si spiega da sè
if(CMAKE_VERSION VERSION_LESS "3.7.0")
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Immaginiamo di voler fare un applicativo Qt che usa queste librerie
# Assicurati di avere nel path "C:\Qt\5.15.2\msvc2019_64\lib\cmake\Qt5
find_package(Qt5 COMPONENTS Multimedia Widgets Core Gui Network REQUIRED)

#Diamo un nome mnemonico al path in cui si troveranno le DLL e i PLUGIN che dovrai copiare post-build
set(QT_BIN_PATH      ${Qt5_DIR}/../../../bin)
set(QT_PLUGINS_PATH  ${Qt5_DIR}/../../../plugins)

#Crea un eseguibile con i tuoi sorgenti considerando che CMAKE_SOURCE_DIR è la directory dove si trova il file CMakeLists.txt
add_executable(supermario3 ${my_sources})

#Per sicurezza includiamo anche le directory con gli header Qt
include_directories(${Qt5_INCLUDE_DIRS})

#Dichiara che il tuo eseguibile dovrà caricare dinamicamente le librerie Qt che intendi usare
target_link_libraries(supermario3 Qt5::Multimedia Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network)

#Crea <CONFIG> directory se non esistono (nel tuo build path avrai le directory Debug e Release)
if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/Debug/")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Debug/")
endif()

if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/Release/")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Release/")
endif()

#A compilazione avvenuta, queste istruzioni copieranno nella directory di build le DLL Qt che hai dichiarato di usare (nota che in /Debug copio <nomeLibreria>d.dll)
add_custom_command(TARGET supermario3 POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy "${QT_BIN_PATH}/Qt5Core.dll" "${CMAKE_CURRENT_BINARY_DIR}/Release/")

add_custom_command(TARGET supermario3 POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy "${QT_BIN_PATH}/Qt5Cored.dll" "${CMAKE_CURRENT_BINARY_DIR}/Debug/")

add_custom_command(TARGET supermario3 POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy "${QT_BIN_PATH}/Qt5Multimedia.dll" "${CMAKE_CURRENT_BINARY_DIR}/Release/")

add_custom_command(TARGET supermario3 POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy "${QT_BIN_PATH}/Qt5Multimediad.dll" "${CMAKE_CURRENT_BINARY_DIR}/Debug/")

add_custom_command(TARGET supermario3 POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy "${QT_BIN_PATH}/Qt5Widgets.dll" "${CMAKE_CURRENT_BINARY_DIR}/Release/")

add_custom_command(TARGET supermario3 POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy "${QT_BIN_PATH}/Qt5Widgetsd.dll" "${CMAKE_CURRENT_BINARY_DIR}/Debug/")

add_custom_command(TARGET supermario3 POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy "${QT_BIN_PATH}/Qt5Gui.dll" "${CMAKE_CURRENT_BINARY_DIR}/Release/")

add_custom_command(TARGET supermario3 POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy "${QT_BIN_PATH}/Qt5Guid.dll" "${CMAKE_CURRENT_BINARY_DIR}/Debug/")

add_custom_command(TARGET supermario3 POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy "${QT_BIN_PATH}/Qt5Network.dll" "${CMAKE_CURRENT_BINARY_DIR}/Release/")

add_custom_command(TARGET supermario3 POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy "${QT_BIN_PATH}/Qt5Networkd.dll" "${CMAKE_CURRENT_BINARY_DIR}/Debug/")

#A compilazione avvenuta, questa istruzione copia della directory di build le DLL delle platform Qt che dovrai avere insieme al .exe che sposti su un altro PC che non ha le Qt installate
add_custom_command(TARGET supermario3 POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory "${QT_PLUGINS_PATH}/platforms" "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/platforms")

# Per compilare:
# Questo file dovrai chiamarlo CMakeLists.txt, apri una shell (Shift premuto e tasto destro del mouse: open powershell window here) e digita:
# mkdir build
# cd build
# cmake ..
# cmake --build . --config Release (o, eventualmente Debug. Questo step puoi anche farlo aprendo il file "Test.sln" che troverai nella directory build per poi compilare con visual studio)

# La directory ./build/Release puoi tranquillamente zipparla e spostarla su un altro PC a tuo piacimento. 
