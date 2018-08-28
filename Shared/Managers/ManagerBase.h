/* =========================================================
V:Multiplayer - http://www.vmultiplayer.com

-- File: ManagerBase.h
-- Project: Shared
-- Author(s): OrMisicL

=============================================================*/

#ifndef MANAGERBASE_H
#define MANAGERBASE_H

#include <vector>

template <typename T>
class CManagerBase
{
public:
	CManagerBase(DWORD dwMaxEntities)
	{
		// Save the entities limit
		m_dwMaxEntities = dwMaxEntities;
		// Create the valid buffer
		m_pbValid = new bool[dwMaxEntities];
		// Empty the entities vector
		m_vectorEntities.clear();
		// Reset the buffers
		for (DWORD i = 0; i < dwMaxEntities; i++)
			m_pbValid[i] = false;
	
		// Push NULLs for all entities
		for (DWORD i = 0; i < dwMaxEntities; i++)
			m_vectorEntities.push_back(NULL);
	};

	~CManagerBase()
	{
		// Loop through all the entities
		for (DWORD i = 0; i < m_dwMaxEntities; i++)
			Remove(i);

		// Delete buffers
		SAFE_DELETE(m_pbValid);
	};

	// Add an entity to the manager
	void Add(T *pEntity, DWORD dwPosition)
	{
		// Validate the entity
		if (dwPosition < m_dwMaxEntities)
		{
			m_vectorEntities[dwPosition] = pEntity;
			m_pbValid[dwPosition] = true;
		}
	};

	// Remove an entity from the manager
	void Remove(DWORD dwPosition)
	{
		// Validate the entity
		if (dwPosition < m_dwMaxEntities && m_pbValid[dwPosition])
		{
			m_vectorEntities[dwPosition] = NULL;
			m_pbValid[dwPosition] = false;
		}
	};

	bool IsValid(DWORD dwPosition) { return (dwPosition < m_dwMaxEntities) ? m_pbValid[dwPosition] : false; };
	T *GetAt(DWORD dwPosition) { return (dwPosition < m_dwMaxEntities) ? m_vectorEntities[dwPosition] : NULL; };

private:
	bool					*m_pbValid;
	std::vector<T *>		m_vectorEntities;
	DWORD					m_dwMaxEntities;
};

#endif