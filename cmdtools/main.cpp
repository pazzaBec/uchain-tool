#include "utils.h"
#include "rewardtool.h"
#include "alerttool.h"
#include "wallettool.h"

#include <iomanip>

using namespace std;

static boost::scoped_ptr<ECCVerifyHandle> globalVerifyHandle;
const int cmdindex = 1;

void RegisterCmdForHelp()
{
	cout << "********* commands *********" << endl;
	cout << "signmsg" << endl;
	cout << "verifymsg" << endl;
	cout << "compactsign" << endl;
	cout << "compactverify" << endl;
	cout << "newaddress" << endl;
	cout << "sendalert" << endl;
	cout << "timemicros" << endl;
	cout << "********* commands *********" << endl;
}

int main(int argc, char* argv[])
{
	SetFilePath("tool.conf");
	ReadConfigFile(mapArgs, mapMultiArgs);

	SetParams();
	ECC_Start();
	globalVerifyHandle.reset(new ECCVerifyHandle());
	
	// Sanity check no need
    //if (!ECC_InitSanityCheck())
    //    return showreturn(("ECC_InitSanityCheck sanity check failed. Shutting down."));

	if(argc < 2)
	{
		RegisterCmdForHelp();
		return -1;
	}

	string strcmd = string(argv[cmdindex]);
	
	if("signmsg" == strcmd)
	{
		if(argc < cmdindex+3)
		{
			SignMsgHelp();
			return -1;
		}
		SignMsg(argv[cmdindex+1], argv[cmdindex+2]);
	}
	else if("verifymsg" == strcmd)
	{
		if(argc < cmdindex+4)
		{
			SignVerifyHelp();
			return -1;
		}
		SignVerify(argv[cmdindex+1], argv[cmdindex+2], argv[cmdindex+3]);
	}
	else if("compactsign" == strcmd)
	{
		if(argc < cmdindex+3)
		{
			CompactSignHelp();
			return -1;
		}
		CompactSign(argv[cmdindex+1], argv[cmdindex+2]);
	}
	else if("compactverify" == strcmd)
	{
		if(argc < cmdindex+4)
		{
			CompactVerifyHelp();
			return -1;
		}
		CompactVerify(argv[cmdindex+1], argv[cmdindex+2], argv[cmdindex+3]);
	}
	else if("newaddress" == strcmd)
	{
		if(argc < cmdindex+3)
		{
			NewAddressHelp();
			return -1;
		}
		NewAddress(atob(argv[cmdindex+1]), atoi(argv[cmdindex+2]));
	}
	else if("sendalert" == strcmd)
	{
		if(argc < cmdindex+2)
		{
			SendAlertHelp();
			return -1;
		}
		SendAlertHandle(argv[cmdindex+1]);
	}
	else if("timemicros" == strcmd)
		cout << "micros times = " << GetTimeMicros() << endl;
	else
		cout << "Error: unknown method " << strcmd << endl;

    return 0;
}

