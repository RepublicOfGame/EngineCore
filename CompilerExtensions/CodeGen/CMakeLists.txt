ExternalProject_Add(GunGen
        GIT_REPOSITORY git://git.savannah.gnu.org/gengen.git
        GIT_TAG rel_1_4_3
        CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>
        LOG_CONFIGURE 1
        LOG_BUILD 1)