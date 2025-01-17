#include <json/json.h>

using namespace rocksolid::json;

int main(int argc, char *argv[])
{

    if (!JsonValue(nullptr).IsNull())
    {
        return -1;
    }
    if (!JsonValue(false).IsFalse())
    {
        return -1;
    }
    if (!JsonValue(true).IsTrue())
    {
        return -1;
    }

    return 0;
}