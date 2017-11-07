#include "VM.h"
#include <cstdlib>

using namespace std;
using namespace JSM;

void VM::exec(KoalaJS* js, BCVar *c, void *userdata) {
	KoalaJS kjs(js->getRoot());
	kjs.exec(c->getParameter("src")->getString());
}

void VM::run(KoalaJS* js, BCVar *c, void *userdata) {
	std::string fname = c->getParameter("file")->getString();

	KoalaJS kjs(js->getRoot());
	kjs.run(fname);
}


