#include "pythonBot.h"
#include <Python.h>

PythonBot::PythonBot() {
    Py_Initialize();

    PyObject *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int i;


    std::string functionName = "main";
    std::string programName = "pythonBot";

    Py_Initialize();
    PyObject *pName = PyUnicode_DecodeFSDefault(programName.c_str());
    /* Error checking of pName left out */
    /* set search path for learning.py */
    PyObject *sysPath = PySys_GetObject("path");
    if(sysPath != nullptr) {
        PyList_Append(sysPath, PyUnicode_DecodeFSDefault("../src/pythonBot/"));
    }

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pName == nullptr) {
        fprintf(stderr, "Libname not found\n");
        return;
    }


    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, functionName.c_str());
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {

            PyObject *pArgs = pArgs = PyTuple_New(1);
            pValue = PyUnicode_FromString("H10");
            PyTuple_SetItem(pArgs, 0, pValue);

            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %s\n", PyUnicode_AsUTF8(pValue));
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", functionName.c_str());
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n",programName.c_str());
    }
    if (Py_FinalizeEx() < 0) {
    }
}


PythonBot::~PythonBot() {
    Py_Finalize();
}

Card PythonBot::nextRound() {
    Card c = m_cards.back();
    m_cards.pop_back();
    return c;
}

void PythonBot::setCards(std::vector<Card> cards) {
    Player::setCards(cards);
}

void PythonBot::cardPlayed(size_t playerID, Card card) {
    Player::cardPlayed(playerID, card);
}

void PythonBot::playerWonCards(size_t playerID) {
    Player::playerWonCards(playerID);
}

