#include <rBase64.h>

String base64_str_to_base64(String istr)
{

    rbase64.encode(istr);

    return rbase64.result();
}

String base64_base64_to_str(String isbase)
{

    rbase64.decode(isbase);

    return rbase64.result();
}