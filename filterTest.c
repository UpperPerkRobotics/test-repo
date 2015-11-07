#include "Filter.c"

task main()
{
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterRight(0));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterRight(43));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterRight(98));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterRight(130));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterRight(134));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterRight(85));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterRight(154));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterRight(76));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterRight(113));
}
