#include "Var.h"
#include "KoalaJS.h"
#include "Compiler.h"
#include "utils/String/StringUtil.h"
#include <stdio.h>
#include <string.h>

void _moduleLoader(KoalaJS* tinyJS);

//show help message
void help() {
	printf("\033[4m\033[0;33m[Help] JSM Javascript engine, you can input javascript code here.\n"
			"commands:\n"
			"\thelp       : show this help.\n"
			"\tbc         : compiler the whole javascript to bytecode.\n"
			"\trun        : run the new input javascript, will reset runtime first.\n"
			"\texit       : quit shell.\033[0m\n");
}

//js shell
void jshell() {
	std::string input;
	KoalaJS tinyJS;
	tinyJS.loadModule(_moduleLoader);
	help();
	printf("\033[4m\033[0;32mjsh:>\033[0m ");

	bool prompt = true;
	while(true) {
		char buffer[2048+1];
		if(fgets ( buffer, 2048, stdin ) == NULL)
			break;
			
		string ln = buffer;
		ln = StringUtil::trim(ln);
		if(ln.length() == 0) {
			prompt = !prompt;
		}

		if(ln == "help") {
			help();
		}
		else if(ln == "exit") {
			printf("\n\033[4m\033[0;33m[Bye!]\033[0m\n");
			break;
		}
		else if(ln == "run") {
			try {
				tinyJS.reset();
				tinyJS.exec(input);
			} catch (CScriptException *e) {
				printf("ERROR: %s\n", e->text.c_str());
			}
			input = "";
		}
		else if(ln == "bc") {
			Compiler compiler;
			try {
				compiler.exec(input);
				string s = compiler.bytecode.dump();
				printf("%s\n", s.c_str());
			} catch (CScriptException *e) {
				printf("ERROR: %s\n", e->text.c_str());
			}
		}
		else if(ln.length() > 0) {
			input += ln + "\n";
			prompt = false;
		}

		if(prompt)
			printf("\033[4m\033[0;32mjsh:>\033[0m ");
	}	
}

//run js file.
void run(int argc, char** argv) {
	try {
		KoalaJS tinyJS;
		tinyJS.loadModule(_moduleLoader);

		//read args 
		BCVar* args = new BCVar();
		args->setArray();
		for(int i=2; i<argc; ++i) {
			args->setArrayIndex(i-2, new BCVar(argv[i]));
		}
		tinyJS.getRoot()->addChild("_args", args);
		tinyJS.run(argv[1]);
	} 
	catch (CScriptException *e) {
		ERR("ERROR: %s\n", e->text.c_str());
	}
}

//run js file.
void compile(const char* fname) {
	try {
		Compiler compiler;
		compiler.run(fname);
		string s = compiler.bytecode.dump();
		printf("%s\n", s.c_str());
	} 
	catch (CScriptException *e) {
		ERR("ERROR: %s\n", e->text.c_str());
	}
}

int main(int argc, char** argv) {
	if(argc <= 1) {
		jshell();
	}
	else if(argc >= 2) {
		if(strcmp(argv[1], "-v") == 0) {
			compile(argv[2]);
		}
		else {
		//while(true) {
		run(argc, argv);
		//}	
		}
	}
	CodeCache::empty();
	return 0;
}