#include "Env/TaggedData.hpp"

namespace Env
{

std::unordered_map<void*, std::string> TaggedData::mTags;

void TaggedData::tagData(std::string type, void* data)
{
	mTags[data] = type;
}

std::string TaggedData::getType(void* data)
{
	if (mTags.find(data) != mTags.end())
	{
		return mTags[data];
	}
	else
	{
		return "";
	}
}

}