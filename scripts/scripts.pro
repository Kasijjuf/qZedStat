# qmake .pro file for QZedStat/scripts

TEMPLATE       = app
TARGET         = $(nothing)
QMAKE_STRIP    = /bin/true # prevent stripping the script(s)

scripts.files  = QZedStat-cache-writer
scripts.path   = /usr/bin

INSTALLS      += scripts

