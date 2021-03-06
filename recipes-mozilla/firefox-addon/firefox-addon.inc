# Copyright (C) 2009-2012, O.S. Systems Software Ltda. All Rights Reserved
# Released under the MIT license (see packages/COPYING)

DEPENDS = "mozilla-devscripts-native"
RDEPENDS = "firefox"

LICENSE = "MPLv1 | GPLv2+ | LGPLv2.1+"

# Ugly hack for now; we need to check license per recipe later
LIC_FILES_CHKSUM = "file://${COREBASE}/LICENSE;md5=3f40d7994397109285ec7b81fdeb3b58"

S = "${WORKDIR}"

INC_PR = "r4"

inherit allarch

do_configure() {
    i=0
    for e in `find -iname '*.xpi'`; do
        xpi-unpack $e xpi$i
        i=`expr $i + 1`
    done
}

do_install() {
    for e in `ls -d xpi[0-9]`; do
        EXTENSION=`sed --posix '/em:id=/!d;s/[ ]*em:id="//;s/".*//' $e/install.rdf`
        [ -z "$EXTENSION" ] && exit 1

        mkdir -p ${D}${libdir}/firefox/extensions/
        mv $e ${D}${libdir}/firefox/extensions/${EXTENSION}
    done
}

FILES_${PN} += "${libdir}/firefox"
