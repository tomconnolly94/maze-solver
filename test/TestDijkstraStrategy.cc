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

	TEST_F(TestDijkstraStrategy, TestGetNextNodeToVisitSimple) 
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

	TEST_F(TestDijkstraStrategy, TestGetNextNodeToVisitComplex) 
	{
		// set up
		GraphPosition graphPosition1(1, 2);
		GraphPosition graphPosition2(2, 3);
		GraphNode* graphNode1 = new GraphNode(graphPosition1, Up);
		GraphNode* graphNode2 = new GraphNode(graphPosition1, Up);
		GraphNode* parentGraphNode1 = new GraphNode(graphPosition2, Up);
		GraphNode* parentGraphNode2 = new GraphNode(graphPosition2, Up);
		int distanceFromParent1 = 5;
		int distanceFromParent2 = 3;
		dijkstraStrategy->_graphNodePathDataList.push_back(GraphNodePathData(graphNode1, distanceFromParent1, parentGraphNode1));
		dijkstraStrategy->_graphNodePathDataList.push_back(GraphNodePathData(graphNode2, distanceFromParent2, parentGraphNode2));

		// assert pre-conditions
		
		// testable function
		GraphNodePathData graphNodePathData = dijkstraStrategy->GetNextNodeToVisit();

		// expected values

		// assert post conditions
		EXPECT_EQ(graphNode2, graphNodePathData.graphNode);
		EXPECT_EQ(distanceFromParent2, graphNodePathData.distanceFromParent);
		EXPECT_EQ(parentGraphNode2, graphNodePathData.parentGraphNode);

		//clean up
		delete graphNode1;
		delete graphNode2;
		delete parentGraphNode1;
		delete parentGraphNode2;
	}

	TEST_F(TestDijkstraStrategy, TestVisitNode) 
	{
		// set up
		GraphPosition graphPosition(1, 2);
		GraphNode* graphNode1 = new GraphNode(graphPosition, Up);
		GraphNode* graphNode2 = new GraphNode(graphPosition, Up);
		GraphNode* parentGraphNode = new GraphNode(graphPosition, Up);
		int distanceBetweenGN1AndGN2 = 3;
		graphNode1->AddConnection(graphNode2, distanceBetweenGN1AndGN2);
		int distanceFromParent = 2;
		GraphNodePathData graphNodePathData(graphNode1, distanceFromParent, parentGraphNode);
		dijkstraStrategy->_graphNodePathDataList.push_back(graphNodePathData);


		// assert pre-conditions
		
		// testable function
		dijkstraStrategy->VisitNode(graphNodePathData);

		// expected values
		GraphNodePathData pathDataItem1 = dijkstraStrategy->_graphNodePathDataList[0];
		GraphNodePathData pathDataItem2 = dijkstraStrategy->_graphNodePathDataList[1];

		// assert post conditions
		EXPECT_EQ(2, dijkstraStrategy->_graphNodePathDataList.size());
		EXPECT_EQ(1, dijkstraStrategy->_visitedNodes.size());
		EXPECT_EQ(distanceFromParent, pathDataItem1.distanceFromParent);
		EXPECT_EQ(distanceFromParent + distanceBetweenGN1AndGN2, pathDataItem2.distanceFromParent);

		//clean up
		delete graphNode1;
		delete graphNode2;
		delete parentGraphNode;
	}

	TEST_F(TestDijkstraStrategy, TestPopulatePathDataList) 
	{
		// set up
		GraphPosition graphPosition(1, 2);
		GraphNode* graphNode1 = new GraphNode(graphPosition, Up);
		GraphNode* graphNode2 = new GraphNode(graphPosition, Up);
		GraphNode* graphNode3 = new GraphNode(graphPosition, Up);
		GraphNode* graphNode4 = new GraphNode(graphPosition, Up);
		int distanceBetweenGN1AndGN2 = 3;
		int distanceBetweenGN2AndGN3 = 4;
		int distanceBetweenGN3AndGN4 = 5;
		graphNode1->AddConnection(graphNode2, distanceBetweenGN1AndGN2);
		graphNode2->AddConnection(graphNode3, distanceBetweenGN2AndGN3);
		graphNode3->AddConnection(graphNode4, distanceBetweenGN3AndGN4);
		// assert pre-conditions
		
		// testable function
		dijkstraStrategy->PopulatePathDataList(graphNode1);

		// expected values
		GraphNodePathData pathDataItem1 = dijkstraStrategy->_graphNodePathDataList[0];
		GraphNodePathData pathDataItem2 = dijkstraStrategy->_graphNodePathDataList[1];
		GraphNodePathData pathDataItem3 = dijkstraStrategy->_graphNodePathDataList[2];
		GraphNodePathData pathDataItem4 = dijkstraStrategy->_graphNodePathDataList[3];

		// assert post conditions
		EXPECT_EQ(4, dijkstraStrategy->_graphNodePathDataList.size());
		EXPECT_EQ(4, dijkstraStrategy->_visitedNodes.size());
		EXPECT_EQ(0, pathDataItem1.distanceFromParent);
		EXPECT_EQ(distanceBetweenGN1AndGN2, pathDataItem2.distanceFromParent);
		EXPECT_EQ(distanceBetweenGN1AndGN2 + distanceBetweenGN2AndGN3, pathDataItem3.distanceFromParent);
		EXPECT_EQ(distanceBetweenGN1AndGN2 + distanceBetweenGN2AndGN3 + distanceBetweenGN3AndGN4, pathDataItem4.distanceFromParent);

		//clean up
		delete graphNode1;
		delete graphNode2;
		delete graphNode3;
		delete graphNode4;
	}

	TEST_F(TestDijkstraStrategy, TestGetShortestPath) 
	{
		// set up
		GraphPosition graphPosition1(1, 2);
		GraphPosition graphPosition2(3, 4);
		GraphPosition graphPosition3(5, 6);
		GraphPosition graphPosition4(7, 8);
		GraphNode* graphNode1 = new GraphNode(graphPosition1, Up);
		GraphNode* graphNode2 = new GraphNode(graphPosition2, Up);
		GraphNode* graphNode3 = new GraphNode(graphPosition3, Up);
		GraphNode* graphNode4 = new GraphNode(graphPosition4, Up);
		int distanceBetweenGN1AndGN2 = 3;
		int distanceBetweenGN2AndGN3 = 4;
		int distanceBetweenGN3AndGN4 = 5;
		graphNode1->AddConnection(graphNode2, distanceBetweenGN1AndGN2);
		graphNode2->AddConnection(graphNode3, distanceBetweenGN2AndGN3);
		graphNode3->AddConnection(graphNode4, distanceBetweenGN3AndGN4);
		// assert pre-conditions
		
		// testable function
		vector<GraphPosition> nodePositions = dijkstraStrategy->GetShortestPath(graphNode1, graphNode4);

		// expected values
		GraphNodePathData pathDataItem1 = dijkstraStrategy->_graphNodePathDataList[0];
		GraphNodePathData pathDataItem2 = dijkstraStrategy->_graphNodePathDataList[1];
		GraphNodePathData pathDataItem3 = dijkstraStrategy->_graphNodePathDataList[2];
		GraphNodePathData pathDataItem4 = dijkstraStrategy->_graphNodePathDataList[3];

		// assert post conditions
		EXPECT_EQ(4, nodePositions.size());
		EXPECT_EQ(graphPosition4, nodePositions[0]);
		EXPECT_EQ(graphPosition3, nodePositions[1]);
		EXPECT_EQ(graphPosition2, nodePositions[2]);
		EXPECT_EQ(graphPosition1, nodePositions[3]);

		//clean up
		delete graphNode1;
		delete graphNode2;
		delete graphNode3;
		delete graphNode4;
	}
}
#endif