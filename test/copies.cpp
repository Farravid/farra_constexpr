#include <gtest/gtest.h>
#include "interval_map.hpp"
#include "lifeobject.hpp"

void cleanLifeObject()
{
	farra::LifeObject::timesConstructor = 0;
	farra::LifeObject::timesCopyConstructor = 0;
	farra::LifeObject::timesMoveConstructor = 0;
	farra::LifeObject::timesCopyAssignment = 0;
	farra::LifeObject::timesMoveAssignment = 0;
	farra::LifeObject::timesDestructor = 0;
}

TEST(Copies, ZeroCopy) 
{
	cleanLifeObject();
	using LO = farra::LifeObject;
	using map_pair = std::pair<int,LO>;
	farra::flat_interval_map<int, LO, 5> map 
	{ 
		map_pair{1, LO{}}, map_pair{3, LO{}}, map_pair{4, LO{}}, map_pair{6, LO{}}, map_pair{8, LO{}}
	};

	EXPECT_EQ(LO::timesCopyConstructor, 0);
	EXPECT_EQ(LO::timesCopyAssignment, 0);
}
