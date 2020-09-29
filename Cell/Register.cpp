 #include <modeladm.h>
 #include <mainsimu.h>

 #include "BS.h"    //New libraries Should be copied.
 #include "UE.h"


 void MainSimulator::registerNewAtomics()
 {
   SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<BS>() , "BS" ) ;
   SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<UE>() , "UE" ) ;
 }
