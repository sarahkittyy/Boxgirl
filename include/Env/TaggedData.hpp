#pragma once

#include <string>
#include <unordered_map>

#include "Box2D/Box2D.h"

namespace Env
{

/**
 * @brief Fixtures don't differentiate between the components they're stored in, so I needed a way to store pointers to data in the fixture UserData based upon component type.
 * This class is a solution that involves passing your void* through the tag system first, with a type string, so that anyone who retrieves your void* through the fixture will be able to look it up and find that string.
 * It's up to the programmer to make sure that the string identifiers are unique and that the type of data stored under that string identifier is the same.
 * 
 */
class TaggedData
{
public:
	/**
	 * @brief Tag a pointer with a given type.
	 * 
	 * @param type The type of data stored at the pointer.
	 * @param data The pointer itself. 
	 */
	static void tagData(std::string type, void* data);

	/**
	 * @brief Get the type string associated with a given void*
	 * 
	 * @param data The data to get the type of.
	 * @return std::string A string saved when the data was tagged,
	 * or empty string "" if it was never tagged.
	 */
	static std::string getType(void* data);

private:
	static std::unordered_map<void*, std::string> mTags;
};

}