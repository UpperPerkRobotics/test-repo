/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Competition Test Harness
//
// The Competition test harness is used to test the Competition Functions
// But can also add controls to make testing and modifications easier
//
// TODO: Allow configuration
//
// Copy this and make as many simple harnesses as you want, it doesn't
// conflict with any other stuff.  Delete this whenever you want.
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "CompetitionFunctions.c"

// This is just a simple check of the autonomous function.
// TODO: Improve this by wrapping it in another tasks that can be killed by a timer, to
// ensure the task is limited to the 20 autonomous seconds.
task main()
{

	writeDebugStreamLine("-- Starting Simple Comp Harness");
	// Like the field, call the pre_auto method
	our_pre_auto();

	// This is a test of autonomous
	our_auto(false);
	writeDebugStreamLine("-- Completed Simple Comp Harness");

}
