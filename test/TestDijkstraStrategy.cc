#include <gtest/gtest.h>
//#include <gmock/gmock.h>

#include "DijkstraStrategy.h"
#include "GraphNode.h"
#include "BaseTest.cc"

#ifdef UNIT_TEST

namespace GraphSolvingStrategies
{
	class TestDijkstraStrategy : public MazeSolverTesting::BaseTest
	{
	protected:

		DijkstraStrategy* dijkstraStrategy;

		void SetUp() override {

    		BaseTest::SetUp();

        	dijkstraStrategy = new DijkstraStrategy();
		}

		void TearDown() override {
			BaseTest::TearDown();
			delete dijkstraStrategy; // free memory
		}
	public:
	};

	TEST_F(TestDijkstraStrategy, TestGetNextNodeToVisit) 
	{
		// set up
		GraphPosition graphPosition(1, 2);
		GraphNode* graphNode = new GraphNode(graphPosition, Up);
		GraphNode* parentGraphNode = new GraphNode(graphPosition, Up);
		int distanceFromParent = 5;
		dijkstraStrategy->_graphNodePathDataList.push_back(GraphNodePathData(graphNode, distanceFromParent, parentGraphNode));

		// assert pre-conditions
		
		// testable function
		GraphNodePathData graphNodePathData = dijkstraStrategy->GetNextNodeToVisit();

		// expected values

		// assert post conditions
		EXPECT_EQ(graphNode, graphNodePathData.graphNode);
		EXPECT_EQ(distanceFromParent, graphNodePathData.distanceFromParent);
		EXPECT_EQ(parentGraphNode, graphNodePathData.parentGraphNode);

		//clean up
		delete graphNode;
		delete parentGraphNode;
	}
}
#endif