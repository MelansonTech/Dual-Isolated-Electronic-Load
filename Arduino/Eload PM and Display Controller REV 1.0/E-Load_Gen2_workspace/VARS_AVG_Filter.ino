struct VARS AVG_Filter(struct VARS avg,float filter){
  
    //float filterFast;
    float filterSlow;
    
    //filterFast = filter;
    filterSlow = filter;
    
//    filterFast /= MAF_sizeFast;
//    avg.filteredFast += filterFast;
//    avg.filteredFast -= avg.ARRFast[avg.indexFast];
//    avg.ARRFast[avg.indexFast] =  filterFast;
//    avg.indexFast +=1;
//
//    if (avg.indexFast > (MAF_sizeFast-1)){
//
//    avg.indexFast=0;
//          
//    } 
  
    filterSlow /= MAF_sizeSlow;
    avg.filteredSlow += filterSlow;
    avg.filteredSlow -= avg.ARRSlow[avg.indexSlow];
    avg.ARRSlow[avg.indexSlow] = filterSlow;
    avg.indexSlow +=1;

    if (avg.indexSlow >= (MAF_sizeSlow)){

    avg.indexSlow=0;
          
    } 
  
  return avg;
 
  }
  
