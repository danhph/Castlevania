#ifndef __QNODE_H__
#define __QNODE_H__

#include "define.h"
#include "..\Objects\BaseObject.h"
#include "..\pugixml\pugixml.hpp"
#include <memory>
using namespace pugi;

class QuadTreeNode
{
public:
	QuadTreeNode(const RECT bounds, short level = 0);
	~QuadTreeNode() {};

	vector<BaseObject*> Retrieve(const RECT bounds);	
	void Insert(BaseObject* object);
protected:
	short m_level;
	RECT m_bounds;
	std::vector<BaseObject*> m_objects; 
	std::vector<QuadTreeNode*> m_children;
	
	short GetIndex(const RECT& bounds);

	void Split(void);
};
#endif // !__QNODE_H__
