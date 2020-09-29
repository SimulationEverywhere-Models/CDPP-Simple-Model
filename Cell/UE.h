 /***********************************************
 *
 *  DESCRIPTION: Atomic Model User Equipment (UE)
 *
 *  AUTHOR: Misagh Tavanpour
 *
 *  DATE: 19/09/2014
 *
 ***********************************************/

 #ifndef __UE_H
 #define __UE_H

 #include "atomic.h"   // class Atomic
 #include "string.h"	  // class String

 class UE : public Atomic
 {
   public:
	       UE ( const std::string &name = "UE" );  //Default constructor
	       virtual std::string className() const {  return "UE" ;}
	       ~UE();

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
         	int ackValue;
         	int lastSentPacketAcked;
         	int permissionToSend;
         	enum State{
			            idle,
			            sendPack,
			            rcvAck,
		              };
		    State state;
 };

#endif   //__UE_H
