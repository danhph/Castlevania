#include "QuadtreeNode.h"

QuadTreeNode::QuadTreeNode(const RECT bounds, short level)
{
	this->m_bounds = bounds;
	this->m_level = level;
	this->m_children.reserve(4);
}

short QuadTreeNode::GetIndex(const RECT& bounds)
{
	short index = -1;
	float midpointX = m_bounds.left + (m_bounds.right - m_bounds.left) / 2.0f;
	float midpointY = m_bounds.bottom + (m_bounds.top - m_bounds.bottom) / 2.0f;

	bool topQuadrant = (bounds.bottom > midpointY);

	bool bottomQuadrant = (bounds.top < midpointY);

	if (bounds.right < midpointX)
	{
		if (topQuadrant)
		{
			index = 1;
		}
		else if (bottomQuadrant)
		{
			index = 2;
		}
	}
	else if (bounds.left > midpointX)
	{
		if (topQuadrant)
		{
			index = 0;
		}
		else if (bottomQuadrant)
		{
			index = 3;
		}
	}
	return index;
}

void QuadTreeNode::Insert(BaseObject* object)
{
	if (!isIntersectedInGame(this->m_bounds, object->getBounding()))
		return;

	if (!m_children.empty())
	{
		short index = GetIndex(object->getBounding());
		if (index != -1)
		{
			m_children[index]->Insert(object);
			return;
		}
	}
	m_objects.push_back(object);

	if (m_objects.size() > MAX_OBJECTS && m_level < MAX_LEVELS)
	{
		if (m_children.empty())
			Split();

		short i = 0;
		while (i < m_objects.size())
		{
			short index = GetIndex(m_objects[i]->getBounding());
			if (index != -1)
			{
				m_children[index]->Insert(m_objects[i]);
				m_objects.erase(m_objects.begin() + i);
			}
			else
			{
				i++;
			}
		}
	}
}

vector<BaseObject*> QuadTreeNode::Retrieve(const RECT bounds)
{
	vector<BaseObject*> foundObjects;
	short index = GetIndex(bounds);

	if (!m_children.empty() && index != -1)
	{
		foundObjects = m_children[index]->Retrieve(bounds);
	}
	else
	{
		for (auto child : m_children)
		{
			if (isIntersectedInGame(child->m_bounds, bounds))
			{
				vector<BaseObject*> childObjects = child->Retrieve(bounds);
				foundObjects.insert(foundObjects.end(), childObjects.begin(), childObjects.end());
			}
		}
	}

	foundObjects.insert(foundObjects.end(), m_objects.begin(), m_objects.end());

	return foundObjects;
}

void QuadTreeNode::DeleteObjects()
{
	if (!m_objects.empty())
	{
		auto i = 0;
		while (i < m_objects.size())
		{
			if (m_objects[i]->getStatus() == eStatus::DESTROY)
			{
				auto obj = m_objects[i];
				m_objects.erase(m_objects.begin() + i);
				obj->release();
				delete obj;
			}
			else
				i++;
		}
	}

	if (!m_children.empty())
		for (auto child : m_children)
			child->DeleteObjects();
}


void QuadTreeNode::Split()
{
	const float halfWidth = (m_bounds.right - m_bounds.left) / 2.f;
	const float halfHeight = (m_bounds.top - m_bounds.bottom) / 2.f;

	RECT rect;

	rect.left = m_bounds.left + halfWidth;
	rect.right = m_bounds.right;
	rect.bottom = m_bounds.bottom + halfHeight;
	rect.top = m_bounds.top;
	m_children.push_back(new QuadTreeNode(rect, m_level + 1));

	rect.left = m_bounds.left;
	rect.right = m_bounds.left + halfWidth;
	m_children.push_back(new QuadTreeNode(rect, m_level + 1));

	rect.bottom = m_bounds.bottom;
	rect.top = m_bounds.bottom + halfHeight;
	m_children.push_back(new QuadTreeNode(rect, m_level + 1));

	rect.left = m_bounds.left + halfWidth;
	rect.right = m_bounds.right;
	m_children.push_back(new QuadTreeNode(rect, m_level + 1));
}

void QuadTreeNode::Release()
{
	if (!m_objects.empty())
	{
		for(auto obj : m_objects)
		{
			obj->release();
			SAFE_DELETE(obj);
		}
	}
	if(!m_children.empty())
		for (auto child : m_children)
		{
			child->Release();
			SAFE_DELETE(child);
		}
}

QuadTreeNode* QuadTreeNode::_instance = nullptr;

QuadTreeNode* QuadTreeNode::getInstance()
{
	return _instance;
}

void QuadTreeNode::setInstance(QuadTreeNode* root)
{
	_instance = root;
}
