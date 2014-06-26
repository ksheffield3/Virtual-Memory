//ksheffield3
//902601249
#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "pagetable.h"
#include "global.h"
#include "process.h"

/*******************************************************************************
 * Finds a free physical frame. If none are available, uses a clock sweep
 * algorithm to find a used frame for eviction.
 *
 * @return The physical frame number of a free (or evictable) frame.
 */
pfn_t get_free_frame(void) {
   int i;
  // int j;
   printf("Entering get free frame\n");
   /* See if there are any free frames */
   for (i = 0; i < CPU_NUM_FRAMES; i++)
    //  printf("Get free frame called\n");
      if (rlt[i].pcb==NULL)
         return i;
     
   /* FIX ME : Problem 5 */
   /* IMPLEMENT A CLOCK SWEEP ALGORITHM HERE */
  
    for(i = 0; i < CPU_NUM_FRAMES; i++)
    {
    	if((rlt[i].pcb->pagetable->used)==0)
    	{
    		printf("Page replacement PID: %u\n", rlt[i].pcb->pid);
    	//	j = 1;
    		return i;
    	}
    	else
    	{
    		rlt[i].pcb->pagetable->used = 0;
    		printf("Page replacement PID: %u\n", rlt[i].pcb->pid);
    		if(i == CPU_NUM_FRAMES -1)
    		{
    			printf("Page replacement PID: %u\n", rlt[i].pcb->pid);
    			i = 0; 
    		}
    		return i;
    	}
    }
    

   /* If all else fails, return a random frame */
   return rand() % CPU_NUM_FRAMES;
    //return i;
}
