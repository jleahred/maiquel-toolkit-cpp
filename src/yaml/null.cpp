#include "yaml/null.h"
#include "yaml/node.h"

namespace YAML
{
	_Null Null;

	bool IsNull(const Node& node)
	{
		return node.Read(Null);
	}
}
