/* 
 * vertex_impl.h
 * 
 * Created on: Feb 1, 2016
 * Description: 
 * 
 * Copyright (c) 2017 Ruixiang Du (rdu)
 */

#ifndef VERTEX_IMPL_H
#define VERTEX_IMPL_H

#include <cstdint>
#include <algorithm>

#include "graph/internal/edge_impl.h"

namespace librav
{

/****************************************************************************/
/*								 Vertex_t										*/
/****************************************************************************/
/// A vertex data structure template.
template <typename StateType>
template <class T, typename std::enable_if<std::is_pointer<T>::value>::type *>
Vertex_t<StateType>::Vertex_t(T bundled_data) : // attributes related to associated node
												state_(bundled_data), vertex_id_(bundled_data->data_id_),
												// common attributes
												search_parent_(nullptr),
												is_checked_(false), is_in_openlist_(false),
												f_astar_(0), g_astar_(0), h_astar_(0){};

template <typename StateType>
template <class T, typename std::enable_if<!std::is_pointer<T>::value>::type *>
Vertex_t<StateType>::Vertex_t(T bundled_data) : // attributes related to associated node
												state_(bundled_data), vertex_id_(bundled_data.data_id_),
												// common attributes
												search_parent_(nullptr),
												is_checked_(false), is_in_openlist_(false),
												f_astar_(0), g_astar_(0), h_astar_(0){};

/// Clear exiting search info before a new search
template <typename StateType>
void Vertex_t<StateType>::ClearVertexSearchInfo()
{
	is_checked_ = false;
	is_in_openlist_ = false;
	search_parent_ = nullptr;

	f_astar_ = 0.0;
	g_astar_ = 0.0;
	h_astar_ = 0.0;
}

/// == operator overloading. If two vertices have the same id, they're regarded as equal.
template <typename StateType>
bool Vertex_t<StateType>::operator==(const Vertex_t<StateType> &other) const
{
	if (vertex_id_ == other.vertex_id_)
		return true;
	else
		return false;
}

/// Get edge cost from current vertex to given vertex. -1 is returned if no edge between
///		the two vertices exists.
template <typename StateType>
double Vertex_t<StateType>::GetEdgeCost(const Vertex_t<StateType> &dst_node) const
{
	double cost = -1;

	for (const auto &it : edges_)
	{
		if (it.dst_.vertex_id_ == dst_node.vertex_id_)
		{
			cost = it.cost_;
			break;
		}
	}

	return cost;
}

/// Get all neighbor vertices of this vertex.
template <typename StateType>
std::vector<Vertex_t<StateType> *> Vertex_t<StateType>::GetNeighbours()
{
	std::vector<Vertex_t<StateType> *> neighbours;

	for (const auto &edge : edges_)
		neighbours.push_back(edge.dst_);

	return neighbours;
}

/// Check if a given vertex is the neighbor of current vertex.
template <typename StateType>
bool Vertex_t<StateType>::CheckNeighbour(Vertex_t<StateType> *dst_node)
{
	std::vector<Vertex_t<StateType> *> neighbours = GetNeighbours();

	auto it = find(neighbours.begin(), neighbours.end(), dst_node);

	if (it != neighbours.end())
		return true;
	else
		return false;
}
}

#endif /* VERTEX_IMPL_H */
