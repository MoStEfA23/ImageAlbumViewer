TEMPLATE = subdirs

SUBDIRS += \
    gallery-core \
    gallery-mobile \
    gallery-desktop

gallery-desktop.depends = gallery-core
