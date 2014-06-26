//ksheffield3
//902601249
#include "statistics.h"

#define MEMORY_ACCESS_TIME      100 /* 100 ns */
#define DISK_ACCESS_TIME   10000000 /* 10 million ns = 10 ms */

double compute_emat() {
   /* FIX ME - Compute the average mean access time.  You should only need the
    * numbers contained in the following variables. You may or may not need to
    * use them all:
    *    count_pagefaults   - the number of page faults that occurred
    *                         (note: this _does_ include the unavoidable page
    *                                fault when a process is first brought into
    *                                memory upon starting)
    *    count_tlbhits      - the number of tlbhits that occurred
    *    count_writes       - the number of stores/writes that occurred
    *    count_reads        - the number of reads that occurred
    *
    * Any other values you might need are composites of the above values.  Some
    * of these computations have been done for you, in case you need them.
    */

   /* long int total_accesses = count_writes + count_reads; */
   /* long int tlb_misses     = total_accesses - count_tlbhits; */

    /**
    TLB miss = two memory access
    TLB hit = one memory access
    pagefault = two memory accesses and a disk access
    **/


    /**
    emat = memory_access + misses * disk_access
    memory_access =
    MEMORY_ACCESS_TIME * total_accesses (time for all accesses to memory)

    misses = (total_accesses-count_tlbhits)*(2*MEMORY_ACCESS_TIME) //two times of memory access

    disk access happens whenever a pagefault happens
    so,
    disk_access = count_pagefaults*((2*MEMORY_ACCESS_TIME)+DISK_ACCESS_TIME

    then divide by total accesses
    **/

    /**
    Calculate total times memory is accessed
    totalMem = MEMORY_ACCESS_TIME*total_accesses
    Plus how often a TLB miss happens
    totalMissTime=  (total_accesses-count_tlbhits)*(2*MEMORY_ACCESS_TIME)
    Plus how often the disk has to be accessed
    diskAccessTime = count_pagefaults*((2*MEMORY_ACCESS_TIME)+DISK_ACCESS_TIME)

    Then divide by total number of accesses 

    So,

    EMAT = (totalMem)+(totalMissTime)+(diskAccessTime)/total_accesses

    **/
    int totalMemoryTime = MEMORY_ACCESS_TIME * (count_tlbhits+count_reads+count_writes);
    int totalMissTime = ((count_reads+count_writes)-count_tlbhits)*(2*(MEMORY_ACCESS_TIME));
    int diskAccessTime = (count_pagefaults*((2*MEMORY_ACCESS_TIME)+DISK_ACCESS_TIME));
    int misses = totalMissTime+diskAccessTime;
    int EMAT = (totalMemoryTime+totalMissTime+diskAccessTime+misses)/(count_reads+count_writes);
    //int totalMissTime = 

   return EMAT;
}
