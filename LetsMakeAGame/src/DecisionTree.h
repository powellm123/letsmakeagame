#pragma once

#include <list>

class DecisionNode
{
	typedef bool(*DecisionFn)();
	DecisionFn m_decisionFn;
	DecisionNode* m_positiveNode;
	DecisionNode* m_negativeNode;
public:
	DecisionNode(DecisionFn decision);
	void LinkNodes(DecisionNode* positiveNode);

	int DoAction();
	int PositiveAction();
	int NegativeAction();
};

class DecisionTree
{
	std::list<DecisionNode*> *m_nodes;
public:
	DecisionTree();
	void AddNode(DecisionNode* node);
	int Think();

};