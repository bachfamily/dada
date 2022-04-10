==================================================
dada
==================================================

**dada** is a library for `Max <http://cycling74.com/>`_ containing non-standard user interface modules for computer assisted composition and music generation.

**dada** is based on the `bach <http://www.bachproject.net/>`_ public API.

The official website is www.bachproject.net/dada

The official repository is https://github.com/bachfamily/dada. You can find the source code there.


Acknowledgments
===================

**dada** is part of Daniele Ghisi's PhD project, supported by:

* `Ircam <http://www.ircam.fr>`_ (Paris, France)
* `Université Pierre et Marie Curie <http://www.upmc.fr>`_ (UPMC Paris, France)
* `Sorbonne Universités <http://www.sorbonne-university.com/>`_ (Paris, France)
* `CNRS <http://www.cnrs.fr/>`_ (France)

The windows porting of **dada** has been carried out by Andrea Agostini.


Install
=======

If you only need to use **dada**, you can download it from www.bachproject.net/dada and simply install it by putting it inside the Max Packages folder.

You can start by having a look at the dada.overview patcher inside the Extras menu in Max ("dada library" submenu). Every module has help files and reference sheets that document its behavior.

If you want to compile *dada*:

* On Windows, only the x64 Release configuration is correctly setup. The Win32 platform is no longer supported, and should be removed at some point; the Debug configuration needs a lot of updating which might as well be done someday...

* you'll need the `bach library <http://www.bachproject.net>`_, with its sources, installed as a Max package (at the same location where the *dada* folder is) and its dependencies (including the `Max SDK <https://cycling74.com/downloads/sdk>`_)

* If you want to compile dada.music~, you need to have the GNU `GMP <https://gmplib.org/>`_ and `MPFR <https://www.mpfr.org/>`_ libraries installed. On OSX, they are expected to be at /usr/local/opt/gmp and /usr/local/opt/mpfr respectively (modify the Xcode parameters if you have them elsewhere); if you install them with Homebrew, they should be in those places. On Windows, we use MPIR (https://www.mpir.org) instead of GMP, and Brian Gladman's Windows port of MPFR (https://github.com/BrianGladman/mpfr.git), which are expected to be installed in C:\Program Files\mpir and C:\Program Files\mpfr respectively (this may require manually moving the binaries). We recommend downloading the binaries from http://www.holoborodko.com/pavel/wp-content/plugins/download-monitor/download.php?id=5.

* If you want to compile dada.graph, you need to have the `Boost <https://www.boost.org/>`_ library (version 1.71 works properly). On OSX, it must be installed at /usr/local/opt/boost (modify the Xcode parameters if you have it elsewhere); if you install it with Homebrew, it should be in that place. On Windows, it must be installed at C:\Program Files\boost\boost_1_71_0. There is no need to build the Boost binaries.

* On an Apple Silicon machine, things are more complicated. For installing the libraries you need to have two versions of Homebrew installed, respectively for the ARM64 and Intel architectures. The ARM64 is the default one, which you can install by running in the terminal the commands provided listed the Homebrew site home page. Once you've done this, you can run `brew install mpfr' and `brew install mpir' as usual.
  Once you've done this, you must install Homebrew for the Intel architecture. To do so, run `arch -x86_64 zsh' in a terminal. This will open a zsh session under Rosetta 2. Now you have to install Homebrew anew, but the x64 version will be installed in a different location: /usr/local/Homebrew/bin . If you just call the system-wide brew, the arm64 version will be called, so now you have to go in /usr/local/Homebrew/bin and run `./brew install mpfr' and `./brew install mpir'. This is also the time to install Boost: `./brew install boost' .
  At this point, you have two architecture-specific versions of the libraries installed. Now, for each library, you need to pack both architectures in a single fat binary. The arm64 version is in /opt/homebrew/lib, the x86 version is in /usr/local/opt/mpfr/lib and /usr/local/opt/gmp/lib . Notice that these steps don't concern boost, since we are not using the compiled parts of it. So we have to run the following lines:
    lipo /usr/local/opt/mpfr/lib/libmpfr.a /opt/homebrew/lib/libmpfr.a -create -output /usr/local/opt/mpfr/lib/libmpfr.a
    lipo /usr/local/opt/gmp/lib/libgmp.a /opt/homebrew/lib/libgmp.a -create -output /usr/local/opt/mpfr/lib/libgmp.a
  We've only done it for the files that are used by dada, but of course you can repeat the process for any file you want.
  Anyway, now the files that previously contained the x86 version now contain the fat binary, while the arm64 files have not been changed. This should allow you to compile everything.

* The dada.distances target uses the a modified version of the `SimpleMatrix <https://github.com/wq2012/SimpleMatrix>`_ library, included by permission of its creator Quan Wang.

The Max documentation for all modules is compiled from the sources by running `Doctor Max <https://github.com/danieleghisi/DoctorMax>`_ with the preferences stored in the file "docs/dada_DoctorMax_settings.txt", which needs to be modified for your own machine.


Related projects
=================

* `bach: automated composer's helper <http://www.bachproject.net>`__
* `cage <http://www.bachproject.net/cage>`__
* `Doctor Max <https://github.com/danieleghisi/DoctorMax>`__



Copyrights
==========

* Copyright (c) 2017-2019 Daniele Ghisi
