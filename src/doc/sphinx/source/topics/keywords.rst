.. _keywords:

.. include:: ../helper.rst

NNP configuration: keywords
===========================

.. warning::

   Documentation under construction...

The NNP settings file (usually named ``input.nn``\ ) contains the setup of neural
networks and symmetry functions. Each line may contain a single keyword with no,
one or multiple arguments. Keywords and arguments are separated by at least one
whitespace. Lines or part of lines can be commented out with the symbol "#",
everything right of "#" will be ignored. The order of keywords is not
important, most keywords may only appear once (exceptions: ``symfunction_short``
and ``atom_energy``\ ). Here is the list of available keywords (if no usage
information is provided, then the keyword does not support any arguments).

General NNP keywords
--------------------

These keywords provide the basic setup for a neural network potential.
Therefore, they are mandatory for most NNP applications and a minimal example
setup file would contain at least:

.. code-block:: none

   number_of_elements 1
   elements H
   global_hidden_layers_short 2
   global_nodes_short 10 10
   global_activation_short t t l
   cutoff_type 1
   symfunction_short ...
   ...

These commands will set up a neural network potential for hydrogen atoms (2
hidden layers with 10 neurons each, hyperbolic tangent activation function) and
the cosine cutoff function for all symmetry functions. Of course, further
symmetry functions need to be specified by adding multiple lines starting with
the ``symfunction_short`` keyword.

----

``number_of_elements``
^^^^^^^^^^^^^^^^^^^^^^

Defines the number of elements the neural network potential is designed for.

**Usage:**
   ``number_of_elements <integer>``

**Examples**:
   ``number_of_elements 3``

----

``elements``
^^^^^^^^^^^^

**Usage**:
   ``elements <string(s)>``

**Examples**:
   ``elements O H Zn``

This keyword defines all elements via a list of element symbols. The number of
items provided has to be consistent with the argument of the
``number_of_elements`` keyword. The order of the items is not important,
elements are automatically sorted according to their atomic number. The list
`nnp::ElementMap::knownElements
<../doxygen/classnnp_1_1ElementMap.html#ad0295785b2db8268cfc175b835046a1e>`__
contains a list of recognized element symbols.

----

``atom_energy``
^^^^^^^^^^^^^^^

**Usage**:
   ``atom_energy <string> <float>``

**Examples**:
   ``atom_energy O -74.94518524``

Definition of atomic reference energy. Shifts the total potential energy by
the given value for each atom of the specified type. The first argument is the
element symbol, the second parameter is the shift energy.

----

``global_hidden_layers_short``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Usage**:
   ``global_hidden_layers_short <integer>``

**Examples**:
   ``global_hidden_layers_short 3``

Sets the number of hidden layers for neural networks of all elements.

----

``global_nodes_short``
^^^^^^^^^^^^^^^^^^^^^^

**Usage**:
   ``global_nodes_short <integer(s)>``

**Examples**:
   ``global_nodes_short 15 10 5``

Sets the number of neurons in the hidden layers of neural networks of all
elements. The number of integer arguments has to be consistent with the
argument of the ``global_hidden_layers_short`` keyword. Note: The number of
input layer neurons is determined by the number of symmetry functions and there
is always only a single output neuron.

----

``global_activation_short``
^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Usage**:
   ``global_activation_short <chars>``

**Examples**:
   ``global_activation_short t t t l``

Sets the activation function per layer for hidden layers and output layers
of neural networks of all elements. The number of integer arguments has to
be consistent with the argument of the ``global_hidden_layers_short`` keyword
(i.e. number of hidden layers + 1). Activation functions are chosen via
single characters from the following table (see also
:cpp:enum:`nnp::NeuralNetwork::ActivationFunction`).

.. list-table::
   :header-rows: 1

   * - Character
     - Activation function type
   * - l
     - :cpp:enumerator:`nnp::NeuralNetwork::AF_IDENTITY`
   * - t
     - :cpp:enumerator:`nnp::NeuralNetwork::AF_TANH`
   * - s
     - :cpp:enumerator:`nnp::NeuralNetwork::AF_LOGISTIC`
   * - p
     - :cpp:enumerator:`nnp::NeuralNetwork::AF_SOFTPLUS`
   * - r
     - :cpp:enumerator:`nnp::NeuralNetwork::AF_RELU`
   * - g
     - :cpp:enumerator:`nnp::NeuralNetwork::AF_GAUSSIAN`
   * - c
     - :cpp:enumerator:`nnp::NeuralNetwork::AF_COS`
   * - S
     - :cpp:enumerator:`nnp::NeuralNetwork::AF_REVLOGISTIC`
   * - e
     - :cpp:enumerator:`nnp::NeuralNetwork::AF_EXP`
   * - h
     - :cpp:enumerator:`nnp::NeuralNetwork::AF_HARMONIC`


----

``normalize_nodes``
^^^^^^^^^^^^^^^^^^^

Activates normalized neural network propagation, i.e. the weighted sum of
connected neuron values is divided by the number of incoming connections
before the activation function is applied. Thus, the default formula to calculate the neuron

.. math::

   y^{k}_{i} = f_a \left( b^{k}_{i} + \sum_{j=1}^{n_l} a^{lk}_{ji} \, y^{l}_{j} \right),

is modified according to:

.. math::

   y^{k}_{i} = f_a \left( \frac{b^{k}_{i} + \sum_{j=1}^{n_l} a^{lk}_{ji} \, y^{l}_{j}}{n_l} \right).

----

``cutoff_type``
^^^^^^^^^^^^^^^^^^^

**Usage**:
   ``cutoff_type <integer> <<float>>``

**Examples**:
   ``cutoff_type 2 0.5``

   ``cutoff_type 7``

Defines the cutoff function type used for all symmetry functions. The first
argument determines the functional form, see
:cpp:enum:`nnp::CutoffFunction::CutoffType` for all available options. Use one
of the following integer numbers to select the cutoff type. The second argument
is optional and sets the parameter :math:`\alpha`. If not provided, the default
value is :math:`\alpha = 0.0`.

.. list-table::
   :header-rows: 1

   * - Cutoff #
     - Cutoff type
   * - 0
     - :cpp:enumerator:`nnp::CutoffFunction::CT_HARD`
   * - 1
     - :cpp:enumerator:`nnp::CutoffFunction::CT_COS`
   * - 2
     - :cpp:enumerator:`nnp::CutoffFunction::CT_TANHU`
   * - 3
     - :cpp:enumerator:`nnp::CutoffFunction::CT_TANH`
   * - 4
     - :cpp:enumerator:`nnp::CutoffFunction::CT_EXP`
   * - 5
     - :cpp:enumerator:`nnp::CutoffFunction::CT_POLY1`
   * - 6
     - :cpp:enumerator:`nnp::CutoffFunction::CT_POLY2`
   * - 7
     - :cpp:enumerator:`nnp::CutoffFunction::CT_POLY3`
   * - 8
     - :cpp:enumerator:`nnp::CutoffFunction::CT_POLY4`


----

``center_symmetry_functions``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``scale_symmetry_functions``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``scale_symmetry_functions_sigma``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Combining these keywords determines how the symmetry functions are scaled
before they are used as input for the neural network. See
:cpp:enum:`nnp::SymFnc::ScalingType` and the following table for allowed
combinations:

.. list-table::
   :header-rows: 1

   * - Keywords present
     - Scaling type
   * - ``None``
     - :cpp:enumerator:`nnp::SymFnc::ST_NONE`
   * - ``scale_symmetry_functions``
     - :cpp:enumerator:`nnp::SymFnc::ST_SCALE`
   * - ``center_symmetry_functions``
     - :cpp:enumerator:`nnp::SymFnc::ST_CENTER`
   * - ``scale_symmetry_functions`` + ``center_symmetry_functions``
     - :cpp:enumerator:`nnp::SymFnc::ST_SCALECENTER`
   * - ``scale_symmetry_functions_sigma``
     - :cpp:enumerator:`nnp::SymFnc::ST_SCALESIGMA`


----

``scale_min_short``
^^^^^^^^^^^^^^^^^^^

``scale_max_short``
^^^^^^^^^^^^^^^^^^^

**Usage**:
   ``scale_min_short <float>``

   ``scale_max_short <float>``

**Examples**:
   ``scale_min_short 0.0``

   ``scale_max_short 1.0``

Set minimum :math:`S_{\min}` and maximum :math:`S_{\max}` for symmetry function
scaling. See :cpp:enumerator:`nnp::SymmetryFunction::ScalingType`.

----

.. _symfunction_short:

``symfunction_short``
^^^^^^^^^^^^^^^^^^^^^

**Usage**:
   ``symfunction_short <string> <integer> ...``

**Examples**:
   ``symfunction_short H 2 H 0.01 0.0 12.0``

   ``symfunction_short H 3 O H 0.2 -1.0 4.0 12.0``

   ``symfunction_short O 9 H H 0.1  1.0 8.0 16.0``

   ``symfunction_short H 12 0.01 0.0 12.0``

   ``symfunction_short O 13 0.1 0.2 1.0 8.0 16.0``

Defines a symmetry function for a specific element. The first argument is the
element symbol, the second sets the type. The remaining parameters depend on
the symmetry function type, follow the links in the right column of the table
and look for the detailed description of the class.

.. list-table::
   :header-rows: 1

   * - Type integer
     - Symmetry function type
   * - 2
     - :cpp:class:`nnp::SymFncExpRad`
   * - 3
     - :cpp:class:`nnp::SymFncExpAngn`
   * - 9
     - :cpp:class:`nnp::SymFncExpAngw`
   * - 12
     - :cpp:class:`nnp::SymFncExpRadWeighted`
   * - 13
     - :cpp:class:`nnp::SymFncExpAngnWeighted`
   * - 20
     - :cpp:class:`nnp::SymFncCompRad`
   * - 21
     - :cpp:class:`nnp::SymFncCompAngn`
   * - 22
     - :cpp:class:`nnp::SymFncCompAngw`
   * - 23
     - :cpp:class:`nnp::SymFncCompRadWeighted`
   * - 24
     - :cpp:class:`nnp::SymFncCompAngnWeighted`
   * - 25
     - :cpp:class:`nnp::SymFncCompAngwWeighted`

----

``ewald_truncation_error_method``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In 4G the Ewald summation is used if periodic boundary conditions are applied.
Both the reciprocal and the real space sum need to be truncated. For this, two
different schemes are available. This defines the behaviour of ``ewald_prec``.

**Usage**:
   ``ewald_truncation_error_method <mode>``

**Examples**:
   ``ewald_truncation_error_method 1``


*  ``0``: *default*, **Method by Jackson & Catlow**

    This method is based on the idea to truncate all terms that are smaller in
    magnitude than a certain threshold [3]_. It is the method used in *RuNNer*.

*  ``1``: **Method by Kolafa & Perram**

    Statistical assumptions are made of the material to incorporate cancelling
    effects of the energy contributions [4]_. It is the recommended method.

``ewald_prec``
^^^^^^^^^^^^^^

Depending on the mode in ``ewald_truncation_error_method`` this keyword has
different meanings. The parameter ``<threshold>`` determines the cutoff radii in
real and reciprocal space. For both methods a smaller threshold leads to
increased radii and thus to a degrade in performance. Also the memory footprint
can become quite noticeable for very small values.

.. warning::

    If n2p2 crashes in 4G mode because it needs more memory than available on
    the machine, it may be related to the ``<threshold>`` parameter. This can
    be tested by increasing its value considerably.

* If ``ewald_truncation_error_method 0``

    **Usage**:
        ``ewald_prec <threshold>``

    ``<threshold>`` is a dimensionless parameter that controls the accuracy of
    the Ewald summation. Typical values are in the range of ``1.e-2`` to
    ``1.e-7``.

* If ``ewald_truncation_error_method 1``

    **Usage**:
        ``ewald_prec <threshold> <max charge> <<real space cutoff>>``

    ``<threshold>`` loosely corresponds to the standard deviation of the
    electrostatic force error one would like to achieve and has to be given in
    the same units as the forces in the training data. However, the methods
    tends to overestimate the actual error, so one may test the accuracy for
    different values. Choosing values that are orders of magnitude smaller than
    the RMSE of the short-range force errors does not make sense.
    ``<max charge>`` should be the maximum charge (in magnitude) that appears during
    training. This does not have to be very precise but should be given in the
    same units as in the training data. :ref:`nnp-norm` outputs this quantity.
    The default is ``1.``.

    It is important to note that this method has two different modes.
    ``<<real space cutoff>>`` is an optional parameter. It fixes the real space
    cutoff in the Ewald summation and adjusts the Ewald parameter and the
    reciprocal space cutoff accordingly such that the specified ``<threshold>``
    is still satisfied. If ``<<real space cutoff>>`` is chosen unreasonably
    small, the truncation error estimate may not be reliable anymore and
    a warning is given. This mode is useful when n2p2 is used in combination
    with other programs like LAMMPS, since they often expect a fixed cutoff
    during the simulation. If ``<<real space cutoff>>`` is not specified, an
    optimal combination of the real and reciprocal space cutoff is computed.
    However, "optimal" refers to the computational effort inside n2p2. If used
    in combination with other programs like LAMMPS, it will not be optimal in
    general. Also note that the optimal cutoffs may change during the
    simulation since they depend on factors like simulation cell volume, number
    of atoms etc. In general we recommend the optimal choice of the cutoffs
    only if n2p2 is used as a standalone tool. If it is used in the interface
    mode, a good choice is to set ``<<real space cutoff>>`` to the symmetry
    function cutoff. This choice may also decrease the memory footprint.


Training-specific keywords
--------------------------

The following keywords are solely used for training with :ref:`nnp-train`. All
other tools and interfaces will ignore these keywords.

----

``selection_mode``
^^^^^^^^^^^^^^^^^^

**Usage**:
   ``selection_mode <integer> <<pairs of integers>>``

**Examples**:
   ``selection_mode 0``

   ``selection_mode 2 15 1 20 2``

Sets the scheme to select energy and force candidates during training (first
integer argument, mandatory). If only one argument is given the chosen mode is
used for the entire training. The optional pairs of integers allow to switch the
selection mode during training. The first integer of each pair determines the
epoch when to switch while the second denotes the selection mode to switch to.
Hence, the above example means: Start the training with selection mode ``2``,
then after 15 epochs switch to mode ``1`` and finally at epoch 20 switch back to
mode ``2`` until training is completed. There are three selection modes
implemented:

*  ``0``: **Random selection**

   Select training candidates randomly.

*  ``1``: **Sort by RMSE**

   At the beginning of each epoch all training candidates are sorted according
   to their current RMSE. Throughout the epoch this list is then processed
   sequentially in order of descending RMSE, i.e. from highest to lowest
   error. This selection scheme can be helpful to decrease the error of
   outlier forces when used in conjunction with the optional selection mode
   switching (see above).

*  ``2``: **Random selection with threshold**

   Select training candidates randomly but use the choice only for training if
   the current error is above a threshold. Otherwise, select another candidate.
   The threshold can be set for energies and forces separately with the keywords
   ``short_energy_error_threshold`` and ``short_force_error_threshold`` and is
   expressed in terms of the last epochs RMSE, e.g.
   ``short_energy_error_threshold 1.5`` means a threshold of :math:`1.5 \times
   RMSE`. Training candidates are selected randomly until the threshold condition
   is fulfilled or a the number of trial choices (keyword
   ``rmse_threshold_trials``) is exceeded. If even in the latter case no
   candidate above the threshold is found, the candidate with the highest error
   so far is used. This selection scheme is a variation of the adaptive process
   described by Blank and Brown [1]_ and is described here [2]_.

----

``main_error_metric``
^^^^^^^^^^^^^^^^^^^^^

**Usage**:
   ``main_error_metric <string>``

**Examples**:
   ``main_error_metric RMSEpa``

   ``main_error_metric MAE``

Selects the error metric to display on the screen during training. Four variants
are available:

* ``RMSEpa``: RMSE of energies per atom, RMSE of forces.

* ``RMSE``: RMSE of energies, RMSE of forces.

* ``MAEpa``: MAE of energies per atom, MAE of forces.

* ``MAE``: MAE of energies, MAE of forces.

If this keyword is omitted the default value is ``RMSEpa``. The keyword does not
influence the output in the ``learning-curve.out`` file. There, all error metrics
are written.

----

.. _normalize_data_set:

``normalize_data_set``
^^^^^^^^^^^^^^^^^^^^^^

**Usage**:
   ``normalize_data_set <string>``

**Examples**:
   ``normalize_data_set ref``

   ``normalize_data_set force``

Enables automatic data set normalization (see also :ref:`units`) as a
pre-processing step during training with :ref:`nnp-train`. If this keyword is
present, an additional calculation will be performed after the initialization of
weights. The file and screen output will contain a corresponding section ``DATA
SET NORMALIZATION`` summarizing the results of the data set normalization step.
Three different modes of normalization can be selected:

*  ``stats-only`` : **No or manually provided normalization, compute only statistics**

   This option will trigger a calculation of statistics: mean and standard
   deviation of reference energies and forces will be computed. Also, a first
   prediction with the (randomly) initialized NN weights will be executed.
   Finally, statistics for these energy and force predictions will be collected
   and printed to screen. If present, already given normalization data (keywords
   ``mean_energy``, ``conv_energy`` and ``conv_length``) in the ``input.nn``
   file will be read and applied.

*  ``ref`` : **Normalization based on reference energies and forces**

   Energy and force statistics are computed as in mode ``stats-only``. The mean
   and standard deviation of reference energies and forces are used to compute
   three numbers for normalization: (1) the mean energy per atom, (2) a
   conversion factor for energies , and (3) a conversion factor for lengths .
   These are computed in such way that the normalized (indicated by :math:`^*`)
   data satisfies:

   .. math::

      \left<e^*_\text{ref}\right> = 0 \quad \text{and} \quad
      \sigma_{e^*_\text{ref}} = \sigma_{F^*_\text{ref}} = 1,

   i.e., the mean reference energy per atom vanishes and there is unity standard
   deviation of reference energies per atom and forces. As the training run
   continues all necessary quantities are automatically converted to this
   normalized unit system.

   .. important::

      The three numbers (1), (2) and (3) are automatically written to the first
      lines of ``input.nn`` as arguments of the keywords ``mean_energy``,
      ``conv_energy`` and ``conv_length``, respectively. They are read in and
      normalization is applied by other tools if necessary. No additional user
      interaction is required. In particular, it is **not** required to convert
      settings in ``input.nn`` (e.g. cutoff radii, some symmetry function
      parameters), nor the configuration data in ``input.data``. All unit
      conversion will be handled internally.

*  ``force`` : **Normalization based on reference and predicted forces (recommended)**

   Same procedure as in mode ``ref`` but the normalization with respect to
   standard deviation of energies per atom is omitted. Instead, the standard
   deviation of **predicted** forces is set to unity:

   .. math::

      \left<e^*_\text{ref}\right> = 0 \quad \text{and} \quad
      \sigma_{F^*_\text{NNP}} = \sigma_{F^*_\text{ref}} = 1,

   The prediction is carried out with the previously (randomly) initialized
   neural network weights. Usually this normalization procedure results in a
   very uniform distribution of data points in the initial
   reference-vs-prediction plot of the forces (see the files
   ``train/testforces.000000.out``). This seems to be a good starting point for
   the HDNNP training often resulting in lower force errors than the ``ref``
   mode.

.. [1] Blank, T. B.; Brown, S. D. Adaptive, Global, Extended Kalman Filters for
   Training Feedforward Neural Networks. J. Chemom. 1994, 8 (6), 391–407.
   https://doi.org/10.1002/cem.1180080605

.. [2] Singraber, A.; Morawietz, T.; Behler, J.; Dellago, C. Parallel
   Multistream Training of High-Dimensional Neural Network Potentials. J. Chem.
   Theory Comput. 2019, 15 (5), 3075–3092. https://doi.org/10.1021/acs.jctc.8b01092

.. [3] Jackson, R. A.; Catlow, C. R. A. Computer Simulation Studies of Zeolite
   Structure. Molecular Simulation 1988, 1 (4), 207–224.
   https://doi.org/10.1080/08927028808080944.

.. [4] Kolafa, J.; Perram, J. W. Cutoff Errors in the Ewald Summation Formulae
   for Point Charge Systems. Molecular Simulation 1992, 9 (5), 351–368.
   https://doi.org/10.1080/08927029208049126.
