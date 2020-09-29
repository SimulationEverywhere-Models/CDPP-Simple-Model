 /***********************************************
 *
 *  DESCRIPTION: Atomic Model User Equipment (BS)
 *
 *  AUTHOR: Misagh Tavanpour
 *
 *  DATE: 19/09/2014
 **********************************************/

 #include <modeladm.h>
 #include <mainsimu.h>

 #include "BS.h"

 void MainSimulator::registerNewAtomics()
 {
   SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<BS>() , "BS" ) ;
 }
