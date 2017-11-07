#include <Python.h>
#include "wrapper.h"

// Docstrings
static char module_docstring[] = "This is a python wrapper for the Waveshare AD-DA board.";

// Functions
static PyObject * startADC(PyObject * self, PyObject * args);
static PyObject * stopADC(PyObject * self, PyObject * args);
static PyObject * collectData(PyObject * self, PyObject * args);
static PyObject * readChannelRaw(PyObject * self, PyObject * args);
static PyObject * readChannelVolts(PyObject * self, PyObject * args);
static PyObject * readAllChannelsRaw(PyObject * self, PyObject * args);
static PyObject * readAllChannelsVolts(PyObject * self, PyObject * args);

// Method specification
static PyMethodDef module_methods[] = {
	{"startADC", startADC, METH_VARARGS, "Set gain, sampling rate, and scan mode on ads1256 chip."},
	{"stopADC", stopADC, METH_VARARGS, "End spi interface."},
	{"collectData", collectData, METH_VARARGS, "Collect data from chip."},
	{"readChannelRaw", readChannelRaw, METH_VARARGS, "Read single channel."},
	{"readChannelVolts", readChannelVolts, METH_VARARGS, "Read single channel and convert to volts."},
	{"readAllChannelsRaw", readAllChannelsRaw, METH_VARARGS, "Read all channels."},
	{"readAllChannelsVolts", readAllChannelsVolts, METH_VARARGS, "Read all channels and convert to volts."},
	{NULL, NULL, 0, NULL}
};

// Module specification
static struct PyModuleDef pyadda_module = {
    PyModuleDef_HEAD_INIT,
    "pyadda",   /* name of module */
    module_docstring, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    module_methods
};

PyMODINIT_FUNC PyInit_pyadda(void) {

    return PyModule_Create(&pyadda_module);
}

static PyObject * startADC(PyObject * self, PyObject * args) {
	int gain, sampling_rate, scan_mode;

	// parse arguments as long integers
	if (!PyArg_ParseTuple(args, "iii", &gain, &sampling_rate, &scan_mode)) {
		return NULL;
	}

	// run start_ADC()
	start_ADC(gain, sampling_rate, scan_mode);

	// return None
    return Py_BuildValue("");
}

static PyObject * stopADC(PyObject * self, PyObject * args) {
	// run stop_ADC()
	stop_ADC();

	// return None
    return Py_BuildValue("");
}

static PyObject * collectData(PyObject * self, PyObject * args) {
	// run collect_data()
	collect_data();

	// return None
    return Py_BuildValue("");
}

static PyObject * readChannelRaw(PyObject * self, PyObject * args) {
	int channel;
	long int adc;

	// parse arguments as long integers
	if (!PyArg_ParseTuple(args, "i", &channel)) {
		return NULL;
	}

	// run read_channel_raw()
	adc = read_channel_raw(channel);

	// build the output tuple
	PyObject * ret = Py_BuildValue("l",adc);
    return ret;
}

static PyObject * readChannelVolts(PyObject * self, PyObject * args) {
	int channel;
	double volts;

	// parse arguments as long integers
	if (!PyArg_ParseTuple(args, "i", &channel)) {
		return NULL;
	}

	// run read_channel_volts()
	volts = read_channel_volts(channel);

	// build the output tuple
	PyObject * ret = Py_BuildValue("d",volts);
    return ret;
}

static PyObject * readAllChannelsRaw(PyObject * self, PyObject * args) {
	int ch;
	PyObject * ret;

	// parse arguments as long integers
	if (!PyArg_ParseTuple(args, "i", &ch)) {
		return NULL;
	}

	// number of channels must be 4 or 8 to read all channels
	if ((ch != 4) & (ch != 8)) {return NULL;}

	long int adc[ch];

	// run read_all_channels_raw()
	read_all_channels_raw(adc, ch);

	if (ch == 4) {
		ret = Py_BuildValue("[l,l,l,l]", adc[0], adc[1], adc[2], adc[3]);
	} else {
		ret = Py_BuildValue("[l,l,l,l,l,l,l,l]", adc[0], adc[1], adc[2], adc[3], adc[4], adc[5], adc[6], adc[7]);
	}

	return ret;
}

static PyObject * readAllChannelsVolts(PyObject * self, PyObject * args) {
	int ch;
	PyObject * ret;

	// parse arguments as long integers
	if (!PyArg_ParseTuple(args, "i", &ch)) {
		return NULL;
	}

	// number of channels must be 4 or 8 to read all channels
	if ((ch != 4) & (ch != 8)) {return NULL;}

	double volts[ch];

	// run read_all_channels_volts()
	read_all_channels_volts(volts, ch);

	if (ch == 4) {
		ret = Py_BuildValue("[d,d,d,d]", volts[0], volts[1], volts[2], volts[3]);
	} else {
		ret = Py_BuildValue("[d,d,d,d,d,d,d,d]", volts[0], volts[1], volts[2], volts[3], volts[4], volts[5], volts[6], volts[7]);
	}

	return ret;
}
