#include <gtest/gtest.h>
//#include <gmock/gmock.h>

#include "GraphBuilder.h"
#include "BaseTest.cc"

#ifdef UNIT_TEST

namespace Building
{
	class TestGraphBuilder : public MazeSolverTesting::BaseTest
	{
	protected:

		Building::GraphBuilder* graphBuilder;

		void SetUp() override {

    		BaseTest::SetUp();
			std::vector<std::vector<bool>> twoDimVector(5, { 0, 1, 0, 0, 0 });

			graphBuilder = new Building::GraphBuilder(twoDimVector);
		}
	public:
	};

	TEST_F(TestGraphBuilder, TestGetNewPosition) 
	{
		// set up
		GraphPosition graphPosition {1,2};

		// testable function
		GraphPosition newPosition = graphBuilder->GetNewPosition(graphPosition, Up);

		// assert post conditions
		GraphPosition expectedPositionUp {1,1};
		EXPECT_EQ(expectedPositionUp, newPosition);

		// testable function
		newPosition = graphBuilder->GetNewPosition(graphPosition, Down);

		// assert post conditions
		GraphPosition expectedPositionDown {1,3};
		EXPECT_EQ(expectedPositionDown, newPosition);

		// testable function
		newPosition = graphBuilder->GetNewPosition(graphPosition, Left);

		// assert post conditions
		GraphPosition expectedPositionLeft {0,2};
		EXPECT_EQ(expectedPositionLeft, newPosition);

		// testable function
		newPosition = graphBuilder->GetNewPosition(graphPosition, Right);

		// assert post conditions
		GraphPosition expectedPositionRight {2,2};
		EXPECT_EQ(expectedPositionRight, newPosition);
	}

	TEST_F(TestGraphBuilder, TestEvaluatePositionConnections) 
	{
		// set up
		GraphPosition graphPosition {1,2};

		// assert pre-conditions
		
		// testable function
		std::map<GraphDirection, GraphPosition> positionConnections = graphBuilder->EvaluatePositionConnections(graphPosition.first, graphPosition.second);

		// expected values
		GraphPosition expectedPositionUp {1,1};
		GraphPosition expectedPositionDown {1,3};

		// assert post conditions
		EXPECT_EQ(2, positionConnections.size());
		EXPECT_EQ(expectedPositionUp, positionConnections[Up]);
		EXPECT_EQ(expectedPositionDown, positionConnections[Down]);
	}

	TEST_F(TestGraphBuilder, TestCreateNewGraphNode) 
	{
		// set up
		GraphPosition graphPosition {3,3};

		// assert pre-conditions
		EXPECT_EQ(0, graphBuilder->graphNodes.size());
		EXPECT_EQ(0, graphBuilder->graphNodesToBeEvaluated.size());
		
		// testable function
		graphBuilder->CreateNewGraphNode(nullptr, graphPosition, 2, Up);

		// assert post conditions
		auto graphNodes = graphBuilder->graphNodes;		
		auto newGraphNode = graphNodes[0];
		auto newGraphNodePosition = newGraphNode->GetPosition();

		EXPECT_EQ(1, graphNodes.size());
		EXPECT_EQ(1, graphBuilder->graphNodesToBeEvaluated.size());
		EXPECT_EQ(1, newGraphNode->GetConnections().size());
		EXPECT_EQ(graphPosition, newGraphNodePosition);
	}

	TEST_F(TestGraphBuilder, TestEvaluateGraphNodeConnections) 
	{
		// set up
		GraphPosition graphPosition { 1, 0 };
        GraphNode* graphNode = new GraphNode(graphPosition, Up);
		
		// assert pre-conditions
		EXPECT_EQ(0, graphBuilder->graphNodes.size());
		EXPECT_EQ(0, graphBuilder->graphNodesToBeEvaluated.size());
		
		// testable function
		graphBuilder->EvaluateGraphNodeConnections(graphNode);

		EXPECT_EQ(2, graphBuilder->graphNodes.size());
		// extract data
		auto graphNode1 = graphBuilder->graphNodes[0];
		auto graphNode2 = graphBuilder->graphNodes[1];
		auto graphNode1Position = graphNode1->GetPosition();
		auto graphNode2Position = graphNode2->GetPosition();
		GraphPosition expectedGraphNode2Position { 4, 1 };

		// assert post conditions
		EXPECT_EQ(1, graphBuilder->graphNodesToBeEvaluated.size());
		EXPECT_EQ(1, graphBuilder->graphNodesToBeEvaluated.size());
		EXPECT_EQ(1, graphNode1->GetConnections().size());
		EXPECT_EQ(1, graphNode2->GetConnections().size());
		EXPECT_EQ(graphPosition, graphNode1Position);
		EXPECT_EQ(expectedGraphNode2Position, graphNode2Position);
	}
}
#endif