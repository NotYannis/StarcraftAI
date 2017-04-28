#include "Common.h"


Common::Common()
{
}


Common::~Common()
{
}

Common & Common::Instance(){
	static Common instance;
	return instance;
}
