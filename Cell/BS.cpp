 /***********************************************
 *
 *  DESCRIPTION: Atomic Model Base Station (BS)
 *
 *  AUTHOR: Misagh Tavanpour
 *
 *  DATE: 19/09/2014
 *
 ***********************************************/

 #include "BS.h"
 #include "message.h"       // InternalMessage ....

 BS::BS( const std::string &name ) : Atomic( name )
 , In(addInputPort( "In" ))
 , Out(addOutputPort( "Out" ))
 , ProcessTime (00,00,00,5)
 {
 }

 Model &BS::initFunction()
  {
	cout << "BS initFunction()" << endl;
    state = idle;
    passivate();
	return *this ;
  }

 /*********************************************************/
 Model &BS::externalFunction( const ExternalMessage &msg )
  {
	cout << "BS externalFunction() at " << msg.time() << endl;
	if (msg.port() == In ){
		cout << "		I received packet " << msg.value() << "   at " << msg.time() << endl;
		packetNumber = msg.value();
		state = sendAck;
		holdIn(Atomic::active, ProcessTime);
	}
	return *this;
  }

 /*********************************************************/
 Model &BS::internalFunction( const InternalMessage & )
 {
	cout << "BS internalFunction()" << endl;
	if (state == 0 ) cout << "		The input state is idle" << endl;
	if (state == 1 ) cout << "		The input state is sendAck" << endl;

	switch (state){
				    case idle:
									passivate();
									break;
				    case sendAck:
									state = idle;
									passivate();
									break;
        		  }

	if (state == 0 ) cout << "		The input state is idle" << endl;
	if (state == 1 ) cout << "		The input state is sendAck" << endl;
    return *this;
 }

 /*********************************************************/
 Model &BS::outputFunction( const InternalMessage &msg )
 {
	 cout << "BS outputFunction() at " << msg.time() << endl;
	 if (state == sendAck){
		 sendOutput( msg.time(), Out, packetNumber) ;
		 cout << "		I sent ACK for packet number " << packetNumber << "   at " << msg.time() << endl;
	 }
	return *this ;
 }

 /*********************************************************/
 BS::~BS()
 {
 }

