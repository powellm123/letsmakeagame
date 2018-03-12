
#include "DecisionTree.h"

DecisionTree::DecisionTree()
{
	m_nodes = new std::list<DecisionNode*>();
}

void DecisionTree::AddNode(DecisionNode* node)
{
	m_nodes->push_back(node);
}

int DecisionTree::Think()
{
	int action = 0;
	for (auto& node : *m_nodes)
	{
		action = node->DoAction();
		if (action != 0)
			return action;
	}
}


DecisionNode::DecisionNode(DecisionFn decisionFn) : m_decisionFn(decisionFn)
{
}

void DecisionNode::LinkNodes(DecisionNode * positiveNode)
{
	m_positiveNode = positiveNode;
}



int DecisionNode::DoAction()
{
	if (m_decisionFn == nullptr)
		throw "Decision Can't be null";

	if (m_decisionFn())
	{
		return PositiveAction();
	}
	else
	{
		return NegativeAction();
	}
}

int DecisionNode::PositiveAction()
{
	if (m_positiveNode == nullptr)
		return 0;

	return m_positiveNode->DoAction();
}

int DecisionNode::NegativeAction()
{
	if (m_negativeNode == nullptr)
		return 0;

	return m_negativeNode->DoAction();
}
