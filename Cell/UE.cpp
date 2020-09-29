 /***********************************************
 *
 *  DESCRIPTION: Atomic Model User Equipment (UE)
 *
 *  AUTHOR: Misagh Tavanpour
 *
 *  DATE: 19/09/2014
 *
 ***********************************************/

 #include "UE.h"
 #include "message.h"       // InternalMessage ....

 UE::UE( const std::string &name ) : Atomic( name )
 , In(addInputPort( "In" ))
 , Out(addOutputPort( "Out" ))
 , ProcessTime (00,00,00,20)
 //, ProcessTime2 (00,00,00,10)
 {
 }

 Model &UE::initFunction()
  {
	cout << "UE initFunction()" << endl;
	packetNumber = 0;
	state = idle;
	lastSentPacketAcked = 0;
	permissionToSend = 0;
	holdIn(Atomic::active, 0);
	return *this ;
  }

 /*********************************************************/
 Model &UE::externalFunction( const ExternalMessage &msg )
  {
	cout << "UE externalFunction() at " << msg.time() << endl;
	if (msg.port() == In ){
		cout << "		I received ACK for packet " << msg.value() << "   at " << msg.time() << endl;
		ackValue = msg.value();
		state = rcvAck;
		lastSentPacketAcked = 1;
		holdIn(Atomic::active, Time(00,00,00,10));
	}
	return *this;
  }

 /*********************************************************/
 Model &UE::internalFunction( const InternalMessage & )
 {
	cout << "UE internalFunction()" << endl;
	if (state == 0 ) cout << "		The input state is idle" << endl;
	if (state == 1 ) cout << "		The input state is sendPack" << endl;
	if (state == 2 ) cout << "		The input state is rcvAck" << endl;

	switch (state){
				    case idle:
								    if (packetNumber == 0){
                                       state = sendPack;
                                    }
                                     else {
                                          passivate();
                                     }
									break;
				    case sendPack:
									if (packetNumber > 9){
										state = idle;
									}else {
										if (lastSentPacketAcked == 1 || packetNumber == 0){
											packetNumber ++;
											permissionToSend = 1;
											cout << "		packetNumber " << packetNumber << endl;
											holdIn(Atomic::active, ProcessTime);
										}else {
											state = idle;
										}
									}
									break;
				    case rcvAck:
									state = sendPack;
									permissionToSend = 0;
									break;
        		  }

	if (state == 0 ) cout << "		The Output state is idle" << endl;
	if (state == 1 ) cout << "		The Output state is sendPack" << endl;
	if (state == 2 ) cout << "		The Output state is rcvAck" << endl;
    return *this;
 }

 /*********************************************************/
 Model &UE::outputFunction( const InternalMessage &msg )
 {
	 cout << "UE outputFunction() at " << msg.time() << endl;
	 if (state == sendPack && packetNumber > 0 && permissionToSend == 1){
		 sendOutput( msg.time(), Out, packetNumber) ;
		 lastSentPacketAcked = 0;
		 cout << "		I sent packet number " << packetNumber << "   at " << msg.time() << endl;
	 }
	 if (state == rcvAck){
			 cout << "		I finished processing of received ACK for packet number " << ackValue << "   at " << msg.time() << endl;
	 }
	return *this ;
 }

 /*********************************************************/
 UE::~UE()
 {
 }

