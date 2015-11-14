#include "Filter.c"

task main()
{
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterLeft(0));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterLeft(43));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterLeft(98));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterLeft(130));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterLeft(134));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterLeft(85));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterLeft(154));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterLeft(76));
	writeDebugStreamLine("Filter Try to Keep 100 - Got: %d", filterLeft(113));
}
