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

		void TearDown() override {
			BaseTest::TearDown();
			delete graphBuilder; // free memory
		}
	public:
	};

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

	TEST_F(TestGraphBuilder, TestScanPixelMazeForNewGraphNode) 
	{
		// set up
		GraphPosition graphPosition {1,2};

		// assert pre-conditions
		EXPECT_EQ(0, graphBuilder->graphNodes.size());
		EXPECT_EQ(false, graphBuilder->graphNodeEvaluationManager.IsNotEmpty());
		
		// testable function
		bool result = graphBuilder->ScanPixelMazeForStartNode();

		// expected values
		GraphPosition expectedGraphPosition{0, 1};

		// assert post conditions
		EXPECT_EQ(1, graphBuilder->graphNodes.size());
		EXPECT_EQ(true, graphBuilder->graphNodeEvaluationManager.IsNotEmpty());
		GraphNode* graphNode = graphBuilder->graphNodeEvaluationManager.GetNextGraphNodeForEvaluation();
		EXPECT_EQ(expectedGraphPosition, graphNode->GetPosition());
		EXPECT_EQ(true, result);
	}

	TEST_F(TestGraphBuilder, TestBuildGraph) 
	{
		// assert pre-conditions
		EXPECT_EQ(0, graphBuilder->graphNodes.size());
		EXPECT_EQ(false, graphBuilder->graphNodeEvaluationManager.IsNotEmpty());
		
		// testable function
		GraphNode* startNode = graphBuilder->BuildGraph();

		// expected values
		GraphPosition expectedGraphNode1Position{0, 1};
		GraphPosition expectedGraphNode2Position{4, 1};

		// assert post conditions
		EXPECT_EQ(2, graphBuilder->graphNodes.size());
		EXPECT_EQ(false, graphBuilder->graphNodeEvaluationManager.IsNotEmpty());
		EXPECT_EQ(expectedGraphNode1Position, startNode->GetPosition());
		EXPECT_EQ(expectedGraphNode2Position, graphBuilder->graphNodes[1]->GetPosition());
	}
	

	TEST_F(TestGraphBuilder, TestGetNewPosition) 
	{
		// set up
		GraphPosition graphPosition {1,2};

		// testable function
		GraphPosition newPosition = graphBuilder->GetNewPosition(graphPosition, Up);

		// assert pre conditions
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

	TEST_F(TestGraphBuilder, TestCreateNewGraphNode) 
	{
		// set up
		GraphPosition graphPosition {3,3};

		// assert pre-conditions
		EXPECT_EQ(0, graphBuilder->graphNodes.size());
		EXPECT_EQ(false, graphBuilder->graphNodeEvaluationManager.IsNotEmpty());
		
		// testable function
		graphBuilder->CreateNewGraphNode(nullptr, graphPosition, 2, Up);

		// assert post conditions
		auto graphNodes = graphBuilder->graphNodes;		
		auto newGraphNode = graphNodes[0];
		auto newGraphNodePosition = newGraphNode->GetPosition();

		EXPECT_EQ(1, graphNodes.size());
		EXPECT_EQ(true, graphBuilder->graphNodeEvaluationManager.IsNotEmpty());
		EXPECT_EQ(1, newGraphNode->GetConnections().size());
		EXPECT_EQ(graphPosition, newGraphNodePosition);
	}

	TEST_F(TestGraphBuilder, TestEvaluateGraphNodeConnections) 
	{
		// set up
		GraphPosition graphPosition { 1, 0 };
        GraphNode* graphNode = new GraphNode(graphPosition, Up);
		graphBuilder->graphNodes.push_back(graphNode);
		graphBuilder->graphNodeEvaluationManager.AddGraphNode(graphNode);
		
		// assert pre-conditions
		EXPECT_EQ(1, graphBuilder->graphNodes.size());
		EXPECT_EQ(true, graphBuilder->graphNodeEvaluationManager.IsNotEmpty());
		
		// testable function
		graphBuilder->EvaluateGraphNodeConnections(graphNode);

		EXPECT_EQ(2, graphBuilder->graphNodes.size());
		EXPECT_EQ(true, graphBuilder->graphNodeEvaluationManager.IsNotEmpty());
		// extract data
		auto graphNode1 = graphBuilder->graphNodes[0];
		auto graphNode2 = graphBuilder->graphNodes[1];
		auto graphNode1Position = graphNode1->GetPosition();
		auto graphNode2Position = graphNode2->GetPosition();
		GraphPosition expectedGraphNode2Position { 1, 4 };

		// assert post conditions
		EXPECT_EQ(true, graphBuilder->graphNodeEvaluationManager.IsNotEmpty());
		EXPECT_EQ(1, graphNode1->GetConnections().size());
		EXPECT_EQ(1, graphNode2->GetConnections().size());
		EXPECT_EQ(graphPosition, graphNode1Position);
		EXPECT_EQ(expectedGraphNode2Position, graphNode2Position);
	}

	TEST_F(TestGraphBuilder, TestTraverseForNewGraphNode) 
	{
		// set up
		GraphPosition graphPosition { 1, 0 };
        GraphNode* graphNode = new GraphNode(graphPosition, Up);
		graphBuilder->graphNodes.push_back(graphNode);
		graphBuilder->graphNodeEvaluationManager.AddGraphNode(graphNode);
		
		// assert pre-conditions
		EXPECT_EQ(1, graphBuilder->graphNodes.size());
		EXPECT_EQ(true, graphBuilder->graphNodeEvaluationManager.IsNotEmpty());
		
		// testable function
		graphBuilder->TraverseForNewGraphNode(*graphNode, Down);

		EXPECT_EQ(2, graphBuilder->graphNodes.size());
		EXPECT_EQ(true, graphBuilder->graphNodeEvaluationManager.IsNotEmpty());
		// extract data
		auto graphNode1 = graphBuilder->graphNodes[0];
		auto graphNode2 = graphBuilder->graphNodes[1];
		auto graphNode1Position = graphNode1->GetPosition();
		auto graphNode2Position = graphNode2->GetPosition();
		GraphPosition expectedGraphNode2Position { 1, 4 };
		GraphConnection* graphConnection = graphNode1->GetConnections()[0];

		// assert post conditions
		EXPECT_EQ(true, graphBuilder->graphNodeEvaluationManager.IsNotEmpty());
		EXPECT_EQ(1, graphNode1->GetConnections().size());
		EXPECT_EQ(1, graphNode2->GetConnections().size());
		EXPECT_EQ(graphPosition, graphNode1Position);
		EXPECT_EQ(expectedGraphNode2Position, graphNode2Position);
		EXPECT_EQ(4, graphConnection->GetConnectionLength());
		EXPECT_EQ(Up, graphNode2->GetDirectionOfParent());
	}
}
#endif