# This is necessary if meson.build has changed, can we do that?
meson setup --wipe builddir
meson compile -C builddir
./builddir/interval_map