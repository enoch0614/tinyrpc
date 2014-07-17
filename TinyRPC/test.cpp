//#include <iostream>
//using namespace std;
//
//#include "tinyrpc.h"
//using namespace TinyRPC;
//
//class EchoProtocol : public ProtocolTemplate<int, int>
//{
//public:
//	virtual void handle_request(void * server)
//	{
//		response = request;
//	}
//
//	virtual uint32_t ID()
//	{
//		return 0;
//	}
//};
//
//
//
//int main(int argc, char ** argv)
//{
//	TinyRPCStub * rpc = TinyRPCStub::get_instance();
//	rpc->init(&argc, &argv);
//
//	int rank = rpc->get_node_id();
//	
//	if(rank == 0)
//	{
//		char c;
//		cin>>c;
//	}
//	rpc->barrier();
//
//
//	rpc->RegisterProtocol<EchoProtocol, NULL>();
//	rpc->start_serving();
//
//	if (rank != 0)
//	{
////		MPI_Send(&rank, sizeof(rank), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
//		EchoProtocol p;
//		p.request = 100 + rank;
//		rpc->rpc_call(0, p);
//		cout<<p.response<<endl;
//	}
//
//	rpc->barrier();
//
//	rpc->delete_instance();
//	return 0;
//}

#include <iostream>
#include <type_traits>
#include <functional>
using namespace std;

#include "streambuffer.h"
#include "message.h"
#include "commAsio.h"
#include "tinyrpc.h"
using namespace TinyRPC;

class EchoProtocol : public ProtocolTemplate<int, int>
{
public:
	virtual void handle_request(void * server)
	{
		response = request;
	}

	virtual uint32_t ID()
	{
		return 0;
	}
};

int main()
{
	TinyRPCStub<asioEP> *rpc = new TinyRPCStub<asioEP>(new TinyCommAsio(8080));

    rpc->RegisterProtocol<EchoProtocol, NULL>();

	rpc->start_serving();

	EchoProtocol p;
	p.request = 100;
	rpc->rpc_call(0, p);
	cout << p.response << endl;


    char c;
    cin >> c;
    return 0;
}