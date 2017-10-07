#include "Compiler.h"
#include "Var.h"
#include "libs/File/File.h"

int main(int argc, char** argv) {
	Compiler tinyJS;
	std::string input;

	if(argc <= 1) {

		while(true) {

			char buffer[2048+1];
			if(fgets ( buffer, 2048, stdin ) == NULL)
				break;

			if(strncmp(buffer, ":quit", 2) == 0) {
				break;
			}
			else if(strncmp(buffer, ":c", 2) == 0) {
				tinyJS.exec(input);
				tinyJS.bytecode.dump();
				tinyJS.bytecode.toFile("out.bcode");
				break;
			}
			else if(strncmp(buffer, ":go", 2) == 0) {
				try {
					tinyJS.exec(input);
					tinyJS.bytecode.dump();
				} catch (CScriptException *e) {
					TRACE("ERROR: %s\n", e->text.c_str());
				}
				input = "";
			}
			else {
				input += buffer;
			}

		}	
	}
	else {
		try {
			tinyJS.run(argv[1]);
			tinyJS.bytecode.dump();
			
			string s = argv[1];
			s += ".bcode";

			tinyJS.bytecode.toFile(s);
			tinyJS.bytecode.fromFile(s);
			tinyJS.bytecode.dump();
		} catch (CScriptException *e) {
			TRACE("ERROR: %s\n", e->text.c_str());
		}
	}
	return 0;
}
