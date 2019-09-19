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



Install
=======

If you only need to use **dada**, you can download it from www.bachproject.net/dada and simply install it by putting it inside the Max Packages folder.

You can start by having a look at the dada.overview patcher inside the Extras menu in Max ("dada library" submenu). Every module has help files and reference sheets that document its behavior.

If you want to compile *dada*:
* you'll need the `bach library <http://www.bachproject.net>`_, with its sources, installed as a Max package (at the same location where the *dada* folder is) and its dependencies (including the `Max SDK <https://cycling74.com/downloads/sdk>`_)
* If you want to compile dada.music~, you need to have the GNU `GMP <https://gmplib.org/>`_ and `MPFR <https://www.mpfr.org/>`_ libraries installed; they are expected to be at /usr/local/opt/gmp and /usr/local/opt/mpfr respectively (modify the Xcode parameters if you have them elsewhere)
* If you want to compile dada.graph, you need to have the `Boost <https://www.boost.org/>`_ library installed at /usr/local/opt/boost (modify the Xcode parameters if you have it elsewhere)
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