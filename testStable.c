#include "StableCheck.c"
task main()
{
	writeDebugStreamLine("Is Left stable with 800? %s", isLeftStable(800)? "true":"false");
	writeDebugStreamLine("Is Left stable with 800? %s", isLeftStable(800)? "true":"false");
	writeDebugStreamLine("Is Left stable with 800? %s", isLeftStable(800)? "true":"false");
	writeDebugStreamLine("Is Left stable with 800? %s", isLeftStable(800)? "true":"false");
	writeDebugStreamLine("Is Left stable with -800? %s", isLeftStable(-800)? "true":"false");
	writeDebugStreamLine("Is Left stable with 10000? %s", isLeftStable(10000)? "true":"false");
	writeDebugStreamLine("Is Left stable with 10000? %s", isLeftStable(10000)? "true":"false");
	writeDebugStreamLine("Is Left stable with 10010? %s", isLeftStable(10000)? "true":"false");
	writeDebugStreamLine("Is Left stable with 10000? %s", isLeftStable(10000)? "true":"false");
	writeDebugStreamLine("Is Left stable with 10000? %s", isLeftStable(10020)? "true":"false");
	writeDebugStreamLine("Is Left stable with 10000? %s", isLeftStable(10000)? "true":"false");
	writeDebugStreamLine("Is Left stable with 10040? %s", isLeftStable(10000)? "true":"false");
	writeDebugStreamLine("Is Left stable with 800? %s", isLeftStable(800)? "true":"false");
	writeDebugStreamLine("Is Left stable with 800? %s", isLeftStable(800)? "true":"false");
	writeDebugStreamLine("Is Left stable with 800? %s", isLeftStable(800)? "true":"false");
	writeDebugStreamLine("Is Left stable with 800? %s", isLeftStable(800)? "true":"false");
	writeDebugStreamLine("Is Left stable with -800? %s", isLeftStable(-800)? "true":"false");
	writeDebugStreamLine("Is Left stable with 10000? %s", isLeftStable(9000)? "true":"false");
	writeDebugStreamLine("Is Left stable with 10000? %s", isLeftStable(10000)? "true":"false");
	writeDebugStreamLine("Is Left stable with 10010? %s", isLeftStable(10000)? "true":"false");
	writeDebugStreamLine("Is Left stable with 10000? %s", isLeftStable(10000)? "true":"false");
	writeDebugStreamLine("Is Left stable with 10060? %s", isLeftStable(10020)? "true":"false");
	writeDebugStreamLine("Is Left stable with 10000? %s", isLeftStable(10000)? "true":"false");
	writeDebugStreamLine("Is Left stable with 10040? %s", isLeftStable(10010)? "true":"false");
	isRightStable(800);
}
