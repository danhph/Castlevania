#ifndef __QNODE_H__
#define __QNODE_H__

#include "define.h"
#include "..\Objects\BaseObject.h"
#include "..\pugixml\pugixml.hpp"
using namespace pugi;

class QNode
{
private:
	RECT _bound;
	INT64 _id;
	int _level;
	QNode* _parent;
	QNode* _childs[4];
	vector<string> _listObject;


public:
	QNode(int id, int level, RECT bound, QNode* parent);
	void insertObject(BaseObject* baseobject);
	void insertObject(string name);
	RECT getBound();
	INT64 getId();
	int getLevel();
	QNode* getParent();
	void setParent(QNode* parent);
	QNode** getChilds();
	void setChilds(QNode* nodes[4]);
	bool isLeaf();


	vector<string> getAllObject();

	static void loadChild(xml_node& node, QNode* parent);
	static QNode* loadQuadTree(const string path);
	static QNode* initNode(xml_node& node);

	vector<string> GetActiveObject(RECT bound, bool botleft = false);
	void fetchActiveObject(RECT bound);
	static vector<string> ActiveObject;
	~QNode();
};


#endif // !__QNODE_H__
