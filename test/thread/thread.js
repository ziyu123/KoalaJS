// Child thread, dead loop to get global value which is set by main thread. 
include 'comm.js';

while(true) {
	var v = get('count');

	if(v != undefined)
		print("sub thread get : " + v + ": " + _threadArg + "\n");

	RThread.usleep(100000);
}