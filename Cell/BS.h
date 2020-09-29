 /***********************************************
 *
 *  DESCRIPTION: Atomic Model Base Station (BS)
 *
 *  AUTHOR: Misagh Tavanpour
 *
 *  DATE: 19/09/2014
 *
 ***********************************************/

 #ifndef __BS_H
 #define __BS_H

 #include "atomic.h"      // class Atomic
 #include "string.h"	  // class String

 class BS : public Atomic
 {
   public:
	       BS( const std::string &name = "BS" );  //Default constructor
	       virtual std::string className() const {  return "BS" ;}
	       ~BS();

   protected:
	          Model &initFunction();
	          Model &externalFunction( const ExternalMessage & );
	          Model &internalFunction( const InternalMessage & );
	          Model &outputFunction( const InternalMessage & );

   private:
	        const Port &In;
	        Port &Out;
	        Time ProcessTime;
	        int packetNumber;
         	enum State{
			            idle,
			            sendAck,
		              };
		    State state;
 };

#endif   //__BS_H
