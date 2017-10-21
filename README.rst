==================================================
dada
==================================================

**dada** is a library for `Max <http://cycling74.com/>`_ containing non-standard user interface modules for computer assisted composition and music generation.

**dada** is based on the `bach <http://www.bachproject.net/>`_ public API.

The official website is www.bachproject.net/dada

The official repository is https://github.com/danieleghisi/dada


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

If you want to improve *dada* or add other modules, you'll need some libraries:

* The `bach library <http://www.bachproject.net>`_ 
* The `bach 0.8 SDK <http://www.bachproject.net/download-2/>`_
* `Simple Matrix <https://sites.google.com/site/simpmatrix/>`_ library (v4.1), used for multidimensional scaling in the dada.distances module
* The `Boost <http://www.boost.org>`_ library, used for graph placement algorithms in the dada.graph module

The Max documentation for all modules is compiled from the sources by running `Doctor Max <https://github.com/danieleghisi/DoctorMax>`_ with the preferences stored in the file "docs/dada_DoctorMax_settings.txt"


Related projects
=================

* `bach: automated composer's helper <http://www.bachproject.net>`__
* `cage <http://www.bachproject.net/cage>`__
* `Doctor Max <https://github.com/danieleghisi/DoctorMax>`__



Copyrights
==========

* Copyright (c) 2017 Daniele Ghisi


License
=======

dada is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

dada is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

Read the LICENSE.txt file for more details.
