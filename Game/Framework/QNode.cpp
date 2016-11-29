#include "QNode.h"

vector<string> QNode::ActiveObject;

QNode::QNode(int id, int level, RECT bound, QNode* parent)
{
	this->_id = id;
	this->_level = level;
	this->_bound = bound;
	this->_parent = parent;
	for (int i = 0; i < 4; i++)
	{
		_childs[i] = NULL;
	}
}

void QNode::insertObject(BaseObject* baseobject)
{
	//this->_listOject.push_back(baseobject);
}

void QNode::insertObject(string objectname)
{
	this->_listObject.push_back(objectname);
}

RECT QNode::getBound()
{
	return _bound;
}

INT64 QNode::getId()
{
	return _id;
}

int QNode::getLevel()
{
	return _level;
}

QNode* QNode::getParent()
{
	return _parent;
}

void QNode::setParent(QNode* parent)
{
	this->_parent = parent;
}

vector<string> QNode::getAllObject()
{
	return _listObject;
}

bool QNode::isLeaf()
{
	if (this->_childs[0] == NULL)
		return true;
	return false;
}

void QNode::fetchActiveObject(RECT bound)
{
	if (isContains(this->_bound, bound) || isIntersectd(this->_bound, bound) || isContains(bound, this->_bound))
	{
		if (this->isLeaf() == true)
		{
			for (string obj : _listObject)
			{
				auto it = std::find(ActiveObject.begin(), ActiveObject.end(), obj);
				if (it == ActiveObject.end() || it._Ptr == nullptr)
				{
					ActiveObject.push_back(obj);
				}
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				_childs[i]->fetchActiveObject(bound);
			}
		}
	}
}

vector<string> QNode::GetActiveObject(RECT bound, bool botleft)
{
	if (botleft)
	{
		// đổi từ bot-left sang top-left
		bound.bottom = WINDOW_HEIGHT - bound.bottom;
		bound.top = WINDOW_HEIGHT - bound.top;
	}

	QNode::ActiveObject.clear();
	this->fetchActiveObject(bound);
	return QNode::ActiveObject;
}

QNode* QNode::loadQuadTree(const string path)
{
#pragma region
	QNode* node = nullptr;
	pugi::xml_document doc;

	// Mở file và đọc
	xml_parse_result result = doc.load_file(path.data(), pugi::parse_default | pugi::parse_pi);
	if (result == false)
	{
		return nullptr;
	}
#pragma endregion
	pugi::xml_node rootxml = doc.first_child();
	node = initNode(rootxml);
	loadChild(rootxml, node);
	return node;
}

QNode* QNode::initNode(xml_node& node)
{
	RECT bound;
	int id = node.attribute("Id").as_int();
	int level = node.attribute("Level").as_int();
	bound.top = node.attribute("Y").as_int();
	bound.left = node.attribute("X").as_int();
	bound.right = bound.left + node.attribute("Width").as_int();
	bound.bottom = bound.top + node.attribute("Height").as_int();
	QNode* qnode = new QNode(id, level, bound, NULL);
	return qnode;
}

void QNode::loadChild(pugi::xml_node& node, QNode* parent)
{
	QNode* child[4] = {NULL};
	auto childnodes = node.children();
	string nodename;
	int childindex = 0;
	for each (xml_node childnode in childnodes)
	{
		nodename = childnode.name();
		if (nodename == "Objects")
		{
			string text = childnode.text().as_string();
			auto objectnames = splitString(text, ' ');
			for each (string name in objectnames)
			{
				//auto obj = listobject[name];
				//if (obj == NULL)
				//	continue;
				//parent->insertObject(obj);
				parent->insertObject(name);
			}
		}
		else if (nodename == "QNode")
		{
			QNode* qnode = initNode(childnode);
			qnode->setParent(parent);
			loadChild(childnode, qnode);
			child[childindex] = qnode;
			childindex++;
		}
	}
	parent->setChilds(child);
}

QNode** QNode::getChilds()
{
	return _childs;
}

void QNode::setChilds(QNode* nodes[4])
{
	for (int i = 0; i < 4; i++)
	{
		this->_childs[i] = nodes[i];
	}
}

QNode::~QNode()
{
	for (int i = 0; i < 4; i++)
	{
		SAFE_DELETE(_childs[i]);
	}
}
