//echo task
var cs = _threadArg;

var b = cs.read(100);

if(b != undefined) 
	cs.write(b, b.size()); 

print("closed.\n");
cs.close();
