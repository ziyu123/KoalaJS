#include "VM.h"
#include <cstdlib>

using namespace std;
using namespace JSM;

void VM::exec(KoalaJS* js, BCVar *c, void *userdata) {
	KoalaJS kjs(js->getRoot(), js->getInterupter());
	kjs.exec(c->getParameter("src")->getString());
}

void VM::run(KoalaJS* js, BCVar *c, void *userdata) {
	std::string fname = c->getParameter("file")->getString();

	KoalaJS kjs(js->getRoot(), js->getInterupter());
	kjs.run(fname);
}

void VM::loadExt(KoalaJS* js, BCVar *c, void *userdata) {
	std::string fname = c->getParameter("file")->getString();
	size_t pos = fname.rfind(".so");
	if(pos != fname.length() - 3)
		fname += ".so";
	js->loadExt(fname);
}



