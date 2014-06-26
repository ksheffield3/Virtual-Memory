//ksheffield3
//902601249
#include <stdlib.h>
#include <stdio.h>
#include "tlb.h"
#include "pagetable.h"
#include "global.h" /* for tlb_size */
#include "statistics.h"

/*******************************************************************************
 * Looks up an address in the TLB. If no entry is found, attempts to access the
 * current page table via cpu_pagetable_lookup().
 *
 * @param vpn The virtual page number to lookup.
 * @param write If the access is a write, this is 1. Otherwise, it is 0.
 * @return The physical frame number of the page we are accessing.
 */
pfn_t tlb_lookup(vpn_t vpn, int write) {
   pfn_t pfn;
   int i;
   ///int tempHits = count_tlbhits;
   int noHit = 0;
   /* 
    * FIX ME : Step 6
    */

   /* 
    * Search the TLB for the given VPN. Make sure to increment count_tlbhits if
    * it was a hit!
    */
    for(int i = 0; i < tlb_size; i++)
    {
      if(tlb[i].vpn == vpn)
      {
        count_tlbhits++;
        pfn = tlb[i].pfn;
        printf("got a hit in TLB\n");
        printf("The tlb vpn is: %u\n", tlb[i].vpn); 
        return pfn;
      }
      else
      {
        noHit = 1;
      }
    }
    
   /* If it does not exist (it was not a hit), call the page table reader */
    if(noHit)
    {
      pfn = pagetable_lookup(vpn, write);
        /* 
        * Replace an entry in the TLB if we missed. Pick invalid entries first,
        * then do a clock-sweep to find a victim.
        */
        printf("TLB clock sweep\n");
        for(i = 0; i < tlb_size; i++)
        {
          if(tlb[i].valid==0)
          {
            tlb[i].pfn = pfn;  
            tlb[i].vpn = vpn;
            tlb[i].valid = 1;  

            printf("Updated TLB \n");
            if(write)
            {
              tlb[i].dirty = 1;    
            }

            return pfn; 

          }

        }
      }
        else{
          printf("TLB else \n");
          pfn = tlb[0].pfn;
          return pfn;
        }
              
  

   /*
    * Perform TLB house keeping. This means marking the found TLB entry as
    * accessed and if we had a write, dirty. We also need to update the page
    * table in memory with the same data.
    *
    * We'll assume that this write is scheduled and the CPU doesn't actually
    * have to wait for it to finish (there wouldn't be much point to a TLB if
    * we didn't!).
    */
    
   return pfn;
}

