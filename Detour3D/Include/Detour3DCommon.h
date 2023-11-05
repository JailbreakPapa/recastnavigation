//
// Copyright (c) 2009-2010 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#include "DetourCommon.h"

#ifndef DETOUR3DCOMMON_H
#define DETOUR3DCOMMON_H
/**
@defgroup detour Detour3D

Members in this module are used to create, manipulate, and query navigation 
meshes for 3D Navigation 

@note This is a summary list of members.  Use the index or search 
feature to find minor members.
*/

#include <function>
#include <queue>
#include <vector>
    // Huge thanks to Venugopalan Sreedharan (DonAI) for this PriorityQueue Code
	template<typename T, typename Number = uint32>
	struct PriorityQueue {
		typedef std::pair<Number, T> PQElement;
		std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement >> elements;

		inline bool empty() { return elements.empty(); }

		inline void put(T item, Number priority) {
			elements.emplace(priority, item);
		}

		inline T get() {
			T best_item = elements.top().second;
			elements.pop();
			return best_item;
		}
	};

    enum dtNavigationQueryStatus
    {
        NotAssigned = 0,
        InProgress = 1,
        Successful = 2,
        Failed = 3,
        /// @brief The 3D Query has taken too long to complete, so we just assume its impossible (agent is to big to navigate, invalid space, etc...)
        Impossible = 4,
        /// @brief Something is wrong if query execution times out. (App chokes up, voxel grid updates, deadlock, etc...)
        Timeout = 5,
    }

#endif