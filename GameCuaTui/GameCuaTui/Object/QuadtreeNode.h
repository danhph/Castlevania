#ifndef __QNODE_H__
#define __QNODE_H__

#include "..\Framework\define.h"
#include "BaseObject.h"
#include "..\pugixml\pugixml.hpp"
#include <algorithm>

using namespace pugi;

class QuadTreeNode
{
public:
	QuadTreeNode(const RECT bounds, short level = 0);
	~QuadTreeNode() {};

	vector<BaseObject*> Retrieve(const RECT bounds);	
	void Insert(BaseObject* object);
	void DeleteObjects();
	void Release();

	static QuadTreeNode* getInstance();
	static void setInstance(QuadTreeNode* root);
protected:
	static QuadTreeNode* _instance;

	short m_level;
	RECT m_bounds;
	std::vector<BaseObject*> m_objects; 
	std::vector<QuadTreeNode*> m_children;
	
	short GetIndex(const RECT& bounds);

	void Split(void);
};
#endif // !__QNODE_H__
