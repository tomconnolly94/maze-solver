#include <gtest/gtest.h>

#include "GraphBuilder.h"
//#include <BaseTest.cc>

namespace BuildingTesting
{
	class TestGraphBuilder : public testing::Test
	{
	protected:

		Building::GraphBuilder* graphBuilder;

		void SetUp() override {

    		//BaseTest::SetUp();
			std::vector<bool> oneDimVector{ 0, 1, 0 };
			std::vector<std::vector<bool>> twoDimVector(3, { 0, 1, 0 });

			graphBuilder = new Building::GraphBuilder(twoDimVector);
		}
	public:
		std::vector<GraphNode*> GetGraphNodes()
		{
			//return std::vector<GraphNode*>{};
			return graphBuilder->graphNodes;
		}

		void CreateNodeReturnDirections()
		{
			GraphPosition graphPosition {3,3};
			graphBuilder->CreateNewGraphNode(nullptr, graphPosition, 2, Up);
		}
	};

	TEST_F(TestGraphBuilder, TestCreateNewGraphNode) {

		EXPECT_EQ(0, GetGraphNodes().size());

		CreateNodeReturnDirections();

		EXPECT_EQ(1, GetGraphNodes().size());
	}
}
